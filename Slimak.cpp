

#include "headers/Slimak.h"
#include <QIcon>

Slimak::Slimak(int wiek, Akwarium *akwarium) : wiek(wiek), akwarium(akwarium) {}

void Slimak::symulujZachowanie() {
    wyznaczSymulowaneZmienne();
    zjedzRosline();
    symulujChorobe();
    symulujRozmnazanie();
}

void Slimak::wyznaczSymulowaneZmienne() {
    wiek += 1;
    szansaNaWyzdrowienie = szansaNaWyzdrowienie + 0.1 <= 0.90 ? szansaNaWyzdrowienie + 0.1 : 0.90;
    szansaNaChorobe = szansaNaChorobe - 0.1 >= 0.15 ? szansaNaChorobe - 0.1 : 0.15;
    wyznaczZarlocznosc();
}

void Slimak::zjedzRosline() {
    double doZjedzenia = zarlocznosc;
    for (auto &obiekt: akwarium->getSymulowaneObiekty()) {
        if (auto roslina = dynamic_cast<Roslina *>(obiekt.get())) {
            if (roslina->getWielkosc() >= doZjedzenia) {
                roslina->setWielkosc(roslina->getWielkosc() - doZjedzenia);
                doZjedzenia = 0;
            } else {
                roslina->setWielkosc(0);
                doZjedzenia -= roslina->getWielkosc();
            }
            if (!doZjedzenia) {
                break;
            }
        }
    }
}

void Slimak::symulujChorobe() {
    std::mt19937 generator(rd());
    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        std::discrete_distribution<> prawdopodobienstwoChoroby({1 - szansaNaChorobe, szansaNaChorobe});
        std::discrete_distribution<> prawdopodobienstwoWyzdrowienia({1 - szansaNaWyzdrowienie, szansaNaWyzdrowienie});
        if (choroba) {
            if (prawdopodobienstwoWyzdrowienia(generator)) {
                choroba = false;
                szansaNaWyzdrowienie = szansaNaWyzdrowienie + 0.1 <= 0.90 ? szansaNaWyzdrowienie + 0.1 : 0.90;
                szansaNaChorobe = szansaNaChorobe - 0.1 >= 0.15 ? szansaNaChorobe - 0.1 : 0.15;
                dlugoscChoroby = 1;
            } else {
                dlugoscChoroby++;
            }
        } else {
            if (prawdopodobienstwoChoroby(generator)) {
                choroba = true;
                dlugoscChoroby++;
            }
        }

    }
}

void Slimak::symulujRozmnazanie() {
    //is July
    std::mt19937 generator(rd());
    // if (akwarium->getNumerIteracji() % 29 == 23 && akwarium->getSlimaki().size() > 1) {
    if (akwarium->getNumerIteracji() % 5 == 0) {
        std::discrete_distribution<> prawdopodobienstwoRozmnazania({60, 40});
        if (prawdopodobienstwoRozmnazania(generator)) {
            akwarium->dodajObiekt(std::make_unique<JajoSlimaka>(akwarium));
        }
    }
}

bool Slimak::symulujEliminacje() {
    if (dlugoscChoroby == 15) {
        return true;
    }
    return false;
}

void Slimak::wyznaczZarlocznosc() {
    // 0.30 dla x = 1 zwieksza sie do 0.60 dla x = 30, 30-120 0.60, 0.20
    zarlocznosc = 0.20;
    if (wiek <= 30) {
        zarlocznosc = 0.30 + 0.30 * (wiek - 1) / 29;
    } else if (wiek <= 120) {
        zarlocznosc = 0.60;
    } else if (wiek <= 180) {
        zarlocznosc = 0.20 * (wiek - 120) / 60;
    }
}

void Slimak::rysuj(QPainter *qp) {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> xDistribution(0, 675);
    std::uniform_int_distribution<int> yDistribution(0, 625);
    int x = xDistribution(generator);
    int y = yDistribution(generator);
    QPixmap pixmap("interface\\icons\\snail.png");
    pixmap = pixmap.scaled(25, 25);
    qp->drawPixmap(x, y, pixmap);
}

bool Slimak::isChoroba() const {
    return choroba;
}

Slimak::~Slimak() {
    std::cout << "Usuwam slimaka\n";
}

double Slimak::getZarlocznosc() const {
    return zarlocznosc;
}
