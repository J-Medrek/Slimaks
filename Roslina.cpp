

#include <iostream>
#include "headers/Roslina.h"

Roslina::Roslina(double predkoscWzrostu) : predkoscWzrostu(predkoscWzrostu) {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> xDistribution(0, 675);
    std::uniform_int_distribution<int> yDistribution(0, 625);
    x = xDistribution(generator);
    y = yDistribution(generator);
}

void Roslina::symulujZachowanie() {
    wielkosc += predkoscWzrostu;
}

double Roslina::getWielkosc() const {
    return wielkosc;
}

void Roslina::setWielkosc(double wielkosc) {
    Roslina::wielkosc = wielkosc;
}

void Roslina::rysuj(QPainter *qp) {
    QPixmap pixmap("interface\\icons\\grass.png");
    int skala = 10 * wielkosc < 30 ? 10 * wielkosc : 30;
    pixmap = pixmap.scaled(skala, skala);
    qp->drawPixmap(x, y, pixmap);
}

Roslina::~Roslina() {
    std::cout << "Usuwam rosline\n";
}

bool Roslina::symulujEliminacje() {
    if (wielkosc == 0) {
        return true;
    }
    return false;
}

