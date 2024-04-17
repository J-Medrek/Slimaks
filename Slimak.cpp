

#include "headers/Slimak.h"
#include <QIcon>
#include "headers/stale.h"

Slimak::Slimak(int wiek, Akwarium *akwarium) : wiek(wiek), akwarium(akwarium) {}

void Slimak::symulujZachowanie() {
    wyznaczSymulowaneZmienne();
    zjedzRosline();
    symulujChorobe();
    symulujRozmnazanie();
}

void Slimak::wyznaczSymulowaneZmienne() {
    wiek += 1;
    szansaNaWyzdrowienie =
            szansaNaWyzdrowienie + 0.1 <= stale::MAKSYMALNA_SZANSA_NA_WYZDROWIENIE ? szansaNaWyzdrowienie + 0.01
                                                                                   : stale::MAKSYMALNA_SZANSA_NA_WYZDROWIENIE;
    szansaNaChorobe = szansaNaChorobe - 0.1 >= stale::MINIMALNA_SZANSA_NA_CHOROBE ? szansaNaChorobe - 0.01
                                                                                  : stale::MINIMALNA_SZANSA_NA_CHOROBE;
    wyznaczZarlocznosc();
}

void Slimak::zjedzRosline() {
    double doZjedzenia = zarlocznosc;
    for (auto &obiekt: akwarium->wezSymulowaneObiekty()) {
        if (auto roslina = dynamic_cast<Roslina *>(obiekt.get())) {
            if (roslina->wezWielkosc() >= doZjedzenia) {
                roslina->ustawWielkosc(roslina->wezWielkosc() - doZjedzenia);
                doZjedzenia = 0;
            } else {
                roslina->ustawWielkosc(0);
                doZjedzenia -= roslina->wezWielkosc();
            }
            if (!doZjedzenia) {
                break;
            }
        }
    }
}

void Slimak::symulujChorobe() {
    std::mt19937 generator(rd());
    if (akwarium->wezZdarzenie().wezZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        // jesli nie ma chorych ślimaków i zdarzenie się właśnie rozpoczęło, zostań pacjentem zero
        if (akwarium->iloscChorychSlimakow() == 0 && akwarium->wezZdarzenie().wezCzasTrwania() == 1) {
            choroba = true;
        } else {
            std::discrete_distribution<> prawdopodobienstwoChoroby({1 - szansaNaChorobe, szansaNaChorobe});
            std::discrete_distribution<> prawdopodobienstwoWyzdrowienia(
                    {1 - szansaNaWyzdrowienie, szansaNaWyzdrowienie});
            if (choroba) {
                //jesli slimak wyzdrowial zwieksz odporność
                if (prawdopodobienstwoWyzdrowienia(generator)) {
                    choroba = false;
                    szansaNaWyzdrowienie = szansaNaWyzdrowienie + 0.01 <= stale::MAKSYMALNA_SZANSA_NA_WYZDROWIENIE
                                           ? szansaNaWyzdrowienie + 0.01
                                           : stale::MAKSYMALNA_SZANSA_NA_WYZDROWIENIE;
                    szansaNaChorobe = szansaNaChorobe - 0.01 >= stale::MINIMALNA_SZANSA_NA_CHOROBE
                                      ? szansaNaChorobe - 0.01
                                      : stale::MINIMALNA_SZANSA_NA_CHOROBE;
                    dlugoscChoroby = 0;
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
}

void Slimak::symulujRozmnazanie() {
    std::mt19937 generator(rd());
    if (akwarium->wezNumerIteracji() % 10 == 0 && akwarium->wyznaczIloscObiektow<Slimak>() > 1) {
        std::discrete_distribution<> prawdopodobienstwoRozmnazania(
                {1 - stale::PRAWDOPODOBIENSTWO_ROZMNAZANIA, stale::PRAWDOPODOBIENSTWO_ROZMNAZANIA});
        if (prawdopodobienstwoRozmnazania(generator)) {
            for (int i = 0; i < akwarium->wezSzybkoscZasiedlania(); i++) {
                akwarium->dodajObiekt(std::make_unique<JajoSlimaka>(akwarium));
            }
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
    // 0.30 dla wiek = 1 zwieksza sie do 0.60 dla wiek = 30, zmniejsza sie do 0.20
    if (wiek <= 30) {
        zarlocznosc = 0.30 + (0.65 - 0.30) * (wiek - 1) / (30 - 1);
    } else if (wiek <= 60) {
        zarlocznosc = 0.65;
    } else
        zarlocznosc = 0.20;
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

bool Slimak::wezChoroba() const {
    return choroba;
}

Slimak::~Slimak() {
    std::cout << "Usuwam slimaka\n";
}

double Slimak::wezZarlocznosc() const {
    return zarlocznosc;
}
