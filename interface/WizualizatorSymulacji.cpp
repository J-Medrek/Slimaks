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


std::map<ZdarzenieLosowe, std::string> NAZWY_ZDARZEN{{ZdarzenieLosowe::BRAK,                   "BRAK"},
                                                     {ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA, "ANOMALIA TEMPERATUROWA"},
                                                     {ZdarzenieLosowe::CHOROBA,                "CHOROBA"}};

WizualizatorSymulacji::WizualizatorSymulacji(Akwarium *akwarium, QWidget *parent) :
        QWidget(parent), ui(new Ui::WizualizatorSymulacji), akwarium(akwarium) {
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked,
            this, [this] { start(); });
    auto *mainLayout = new QVBoxLayout(this);
    ui->widget->setLayout(mainLayout);
}

void WizualizatorSymulacji::start() {
    if (zwalidujWprowadzoneDane() && !trwaSymulacja) {
        akwarium->setPoczatkowaIloscRoslin(ui->iloscRoslin->value());
        akwarium->setPoczatkowaIloscSlimakow(ui->iloscSlimakow->value());
        akwarium->setWzrostRoslin(ui->wzrostRoslin->value());
        akwarium->setSzybkoscZasiedlania(ui->szybkoscZasiedlania->value());
        trwaSymulacja = true;
        emit rozpocznijSymulacje();
    }
}

void WizualizatorSymulacji::paintEvent(QPaintEvent *e) {
    QPainter qp(this);
    drawObjects(&qp);
}

WizualizatorSymulacji::~WizualizatorSymulacji() {
    delete ui;
    delete akwarium;
}

void WizualizatorSymulacji::drawObjects(QPainter *qp) {
    QPen pen(Qt::black, 2, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawRect(0, 0, 700, 650);
    ui->plainTextEdit->setPlainText(QString::fromStdString(generujOpisIteracji()));
    if (!akwarium->getSymulowaneObiekty().empty()) {
        for (const auto &obiekt: akwarium->getSymulowaneObiekty()) {
            obiekt->rysuj(qp);
        }
    }
    if (akwarium->getNumerIteracji() == poprzedniaIteracja + 1) {
        poprzedniaIteracja++;
        emit rozpocznijIteracje();
    }

}

std::string WizualizatorSymulacji::generujOpisIteracji() {
    return std::string("Numer iteracji: " + std::to_string(akwarium->getNumerIteracji()) + "\n"
                       + "Ilosc slimakow: " + std::to_string(akwarium->getIloscSlimakow()) + "\n"
                       + "Ilosc roslin: " + std::to_string(akwarium->getIloscRoslin()) + "\n"
                       + "Ilosc jaj: " + std::to_string(akwarium->getIloscJaj()) + "\n"
                       + "Calkowita zarlocznosc: " + std::to_string(akwarium->calkowitaZarlocznosc()) + "\n"
                       + "Calkowita ilosc roslin: " + std::to_string(akwarium->calkowitaIloscRoslin()) + "\n"
                       + "Codzienny wzrost roslin: " +
                       std::to_string(akwarium->getIloscRoslin() * akwarium->getWzrostRoslin() -
                                      akwarium->calkowitaZarlocznosc()) + "\n"
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
