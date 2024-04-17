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
    if (!trwaSymulacja) {
        try {
            akwarium->ustawZmienneSymulacji(ui->iloscSlimakow->value(), ui->iloscRoslin->value(),
                                            ui->wzrostRoslin->value(),
                                            ui->szybkoscZasiedlania->value(), ui->szansaAnomalia->value(),
                                            ui->szansaAnomalia->value(), ui->spadekWzrostuRoslin->value(),
                                            ui->anomaliaCzasTrwania->value());
            trwaSymulacja = true;
            emit rozpocznijSymulacje();
        } catch (const std::exception &ex) {
            ui->plainTextEdit->setPlainText(QString::fromStdString(ex.what()));
            std::cerr << ex.what() << "\n";
        }
    }
}

void WizualizatorSymulacji::paintEvent(QPaintEvent *e) {
    QPainter qp(this);
    narysujIteracje(&qp);
}

WizualizatorSymulacji::~WizualizatorSymulacji() {
    delete ui;
    delete akwarium;
}

void WizualizatorSymulacji::narysujIteracje(QPainter *qp) {
    QPen pen(Qt::black, 2, Qt::SolidLine);
    qp->setPen(pen);
    qp->drawRect(0, 0, 700, 650);
    ui->plainTextEdit->setPlainText(QString::fromStdString(generujOpisIteracji()));
    if (!akwarium->wezSymulowaneObiekty().empty()) {
        for (const auto &obiekt: akwarium->wezSymulowaneObiekty()) {
            obiekt->rysuj(qp);
        }
    }
    if (akwarium->wezNumerIteracji() == poprzedniaIteracja + 1) {
        poprzedniaIteracja++;
        emit rozpocznijIteracje();
    }

}

std::string WizualizatorSymulacji::generujOpisIteracji() {
    return std::string("Numer iteracji: " + std::to_string(akwarium->wezNumerIteracji()) + "\n"
                       + "Ilosc slimakow: " + std::to_string(akwarium->wyznaczIloscObiektow<Slimak>()) + "\n"
                       + "Ilosc roslin: " + std::to_string(akwarium->wyznaczIloscObiektow<Roslina>()) + "\n"
                       + "Ilosc jaj: " + std::to_string(akwarium->wyznaczIloscObiektow<JajoSlimaka>()) + "\n"
                       + "Calkowita zarlocznosc: " + std::to_string(akwarium->calkowitaZarlocznosc()) + "\n"
                       + "Calkowita ilosc roslin: " + std::to_string(akwarium->calkowitaIloscRoslin()) + "\n"
                       + "Codzienny wzrost roslin: " +
                       std::to_string(akwarium->wyznaczIloscObiektow<Roslina>() * akwarium->wezWzrostRoslin() -
                                      akwarium->calkowitaZarlocznosc()) + "\n"
                       + generujOpisZdarzenia());
}

std::string WizualizatorSymulacji::generujOpisZdarzenia() {
    if (akwarium->wezZdarzenie().wezZdarzenieLosowe() == ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA) {
        return std::string("\nZdarzenie losowe: " + NAZWY_ZDARZEN[akwarium->wezZdarzenie().wezZdarzenieLosowe()] + "\n"
                           + "Dlugosc trwania: " + std::to_string(akwarium->wezZdarzenie().wezCzasTrwania()));
    }
    if (akwarium->wezZdarzenie().wezZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        return std::string("\nZdarzenie losowe: " + NAZWY_ZDARZEN[akwarium->wezZdarzenie().wezZdarzenieLosowe()] + "\n"
                           + "Ilosc chorych: " + std::to_string(akwarium->iloscChorychSlimakow()) + "\n"
                           + "Ilosc  zdrowych: " +
                           std::to_string(akwarium->wyznaczIloscObiektow<Slimak>() - akwarium->iloscChorychSlimakow()) +
                           "\n"
                           + "Dlugosc trwania: " + std::to_string(akwarium->wezZdarzenie().wezCzasTrwania()));
    }
    return std::string("\nZdarzenie losowe: " + NAZWY_ZDARZEN[akwarium->wezZdarzenie().wezZdarzenieLosowe()]);
}
