//
// Created by Julia on 24.03.2024.
//

#include "WizualizatorSymulacji.h"
#include "ui_WizualizatorSymulacji.h"
#include "../headers/Symulacja.h"
#include <QPen>
#include <QPainter>
#include <QHBoxLayout>
#include <iostream>

std::mutex akwariumMutex;

std::map<ZdarzenieLosowe, std::string> NAZWY_ZDARZEN{{ZdarzenieLosowe::BRAK,                   "BRAK"},
                                                     {ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA, "ANOMALIA TEMPERATUROWA"},
                                                     {ZdarzenieLosowe::CHOROBA,                "CHOROBA"}};


WizualizatorSymulacji::WizualizatorSymulacji(QWidget *parent) :
        QWidget(parent), ui(new Ui::WizualizatorSymulacji) {
    akwarium = new Akwarium();
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,
            this, [this] { start(); });
    connect(akwarium, &Akwarium::nastepnaIteracja, this, [this] { update(); });
    auto *mainLayout = new QVBoxLayout(this);
    ui->widget->setLayout(mainLayout);
}

void WizualizatorSymulacji::start() {
    if (zwalidujWprowadzoneDane() && !trwaSymulacja) {
        akwarium->setWzrostRoslin(ui->wzrostRoslin->value());
        auto *watekSymulacji = new QThread(this);
        auto *symulacja = new Symulacja(akwarium, ui->iloscSlimakow->value(), ui->iloscRoslin->value());
        symulacja->moveToThread(watekSymulacji);
        connect(watekSymulacji, &QThread::started, symulacja, &Symulacja::run);
        watekSymulacji->start();
        trwaSymulacja = true;
    }
}

void WizualizatorSymulacji::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    drawObjects(&painter);
}

WizualizatorSymulacji::~WizualizatorSymulacji() {
    delete ui;
    delete akwarium;
}

void WizualizatorSymulacji::drawObjects(QPainter *qp) {
    QPen pen(Qt::black, 2, Qt::SolidLine);
    if (!akwarium->getSymulowaneObiekty().empty()) {
        akwariumMutex.lock();
        for (int i = 0; i < akwarium->getSymulowaneObiekty().size(); ++i) {
            auto obiekt = akwarium->getSymulowaneObiekty()[i].get();
            obiekt->rysuj(qp);
        }
/*        for (const auto &obiekt: akwarium->getSymulowaneObiekty()) {
            obiekt->rysuj(qp);
        }*/
    }
    qp->setPen(pen);
    qp->drawRect(0, 0, 700, 650);
    ui->plainTextEdit->setPlainText(QString::fromStdString(generujOpisIteracji()));
    akwariumMutex.unlock();
}

std::string WizualizatorSymulacji::generujOpisIteracji() {
    return std::string("Numer iteracji: " + std::to_string(akwarium->getNumerIteracji()) + "\n"
                       + "Ilosc slimakow: " + std::to_string(akwarium->getIloscSlimakow()) + "\n"
                       + "Ilosc roslin: " + std::to_string(akwarium->getIloscRoslin()) + "\n"
                       + "Ilosc jaj: " + std::to_string(akwarium->getIloscJaj()) + "\n"
                       + "Dzienna zarlocznosc: " + std::to_string(akwarium->dziennaZarlocznosc()) + "\n"
                       + "Codzienny wzrost roslin: " +
                       std::to_string(akwarium->getIloscRoslin() * akwarium->getWzrostRoslin() -
                                      akwarium->dziennaZarlocznosc()) + "\n"
                       + generujOpisZdarzenia());
}

std::string WizualizatorSymulacji::generujOpisZdarzenia() {
    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA) {
        return std::string("\nZdarzenie losowe: " + NAZWY_ZDARZEN[akwarium->getZdarzenie().getZdarzenieLosowe()] + "\n"
                           + "Dlugosc trwania: " + std::to_string(akwarium->getZdarzenie().getCzasTrwania()));
    }
    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        return std::string("\nZdarzenie losowe: " + NAZWY_ZDARZEN[akwarium->getZdarzenie().getZdarzenieLosowe()] + "\n"
                           + "Ilosc chorych: " + std::to_string(akwarium->iloscChorychSlimakow()) + "\n"
                           + "Ilosc  zdrowych: " +
                           std::to_string(akwarium->getIloscSlimakow() - akwarium->iloscChorychSlimakow()) + "\n"
                           + "Dlugosc trwania: " + std::to_string(akwarium->getZdarzenie().getCzasTrwania()));
    }
    return std::string("\nZdarzenie losowe: " + NAZWY_ZDARZEN[akwarium->getZdarzenie().getZdarzenieLosowe()]);
}

bool WizualizatorSymulacji::zwalidujWprowadzoneDane() {
    if (ui->iloscRoslin->value() > 0
        && ui->iloscSlimakow->value() > 0
        && ui->wzrostRoslin->value() > 0.0
        && ui->szybkoscZasiedlania->value() > 0) {
        return true;
    }
    return false;
}
