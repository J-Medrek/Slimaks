//
// Created by Julia on 21.03.2024.
//

#include <QtCore>
#include "headers/Akwarium.h"


void Akwarium::dodajObiekt(std::unique_ptr<SymulowanyObiekt> obiekt) {
    symulowaneObiekty.push_back(std::move(obiekt));
}

void Akwarium::usunObiekt(const std::unique_ptr<SymulowanyObiekt> &obiekt) {
    symulowaneObiekty.erase(std::find(symulowaneObiekty.begin(), symulowaneObiekty.end(), obiekt));
}

int Akwarium::wezNumerIteracji() const {
    return numerIteracji;
}

void Akwarium::zwiekszNumerIteracji() {
    Akwarium::numerIteracji++;
}


const std::vector<std::unique_ptr<SymulowanyObiekt>> &Akwarium::wezSymulowaneObiekty() const {
    return symulowaneObiekty;
}

double Akwarium::wezWzrostRoslin() const {
    return wzrostRoslin;
}

void Akwarium::ustawWzrostRoslin(double wzrostRoslin) {
    Akwarium::wzrostRoslin = wzrostRoslin;
}

int Akwarium::iloscChorychSlimakow() {
    int iloscChorych = 0;
    for (const auto &obiekt: symulowaneObiekty) {
        if (auto slimak = dynamic_cast<Slimak *>(obiekt.get())) {
            iloscChorych += slimak->wezChoroba();
        }
    }
    return iloscChorych;
}


Zdarzenie &Akwarium::wezZdarzenie() {
    return zdarzenie;
}

Akwarium::~Akwarium() {
    std::cout << "Usuwam akwarium\n";
    symulowaneObiekty.clear();
}

double Akwarium::calkowitaZarlocznosc() {
    double dziennaZarlocznosc = 0;
    for (const auto &obiekt: symulowaneObiekty) {
        if (auto slimak = dynamic_cast<Slimak *>(obiekt.get())) {
            dziennaZarlocznosc += slimak->wezZarlocznosc();
        }
    }
    return dziennaZarlocznosc;
}

int Akwarium::wezPoczatkowaIloscRoslin() const {
    return poczatkowaIloscRoslin;
}

int Akwarium::wezPoczatkowaIloscSlimakow() const {
    return poczatkowaIloscSlimakow;
}

double Akwarium::calkowitaIloscRoslin() {
    double dziennaZarlocznosc = 0;
    for (const auto &obiekt: symulowaneObiekty) {
        if (auto roslina = dynamic_cast<Roslina *>(obiekt.get())) {
            dziennaZarlocznosc += roslina->wezWielkosc();
        }
    }
    return dziennaZarlocznosc;
}

int Akwarium::wezSzybkoscZasiedlania() const {
    return szybkoscZasiedlania;
}

void Akwarium::ustawZmienneSymulacji(int iloscSlimakow, int iloscRoslin, double wzrostRoslin, int szybkoscZasiedlania,
                                     double szansaAnomalia, double szansaChoroba, double spadekWzrostuRoslin,
                                     int czasTrwaniaAnomalii) {
    if (szansaAnomalia + szansaChoroba > 1.0) {
        throw std::runtime_error("Szansa na anomalię i szansa na chorobę nie mogą być razem większe niż 1");
    }
    if (wzrostRoslin <= spadekWzrostuRoslin) {
        throw std::runtime_error(
                "Spadek wzrostu roślin w trakcie anomali nie powinien być mniejszy od stałego wzrostu");
    }
    Akwarium::poczatkowaIloscSlimakow = iloscSlimakow;
    Akwarium::poczatkowaIloscRoslin = iloscRoslin;
    Akwarium::wzrostRoslin = wzrostRoslin;
    Akwarium::szybkoscZasiedlania = szybkoscZasiedlania;
    Akwarium::szansaAnomalia = szansaAnomalia;
    Akwarium::szansaChoroba = szansaChoroba;
    Akwarium::czasTrwaniaAnomalii = czasTrwaniaAnomalii;
    Akwarium::spadekWzrostuRoslin = spadekWzrostuRoslin;
}

double Akwarium::wezSzansaAnomalia() const {
    return szansaAnomalia;
}

double Akwarium::wezSzansaChoroba() const {
    return szansaChoroba;
}

double Akwarium::wezSpadekWzrostuRoslin() const {
    return spadekWzrostuRoslin;
}

int Akwarium::wezCzasTrwaniaAnomalii() const {
    return czasTrwaniaAnomalii;
}

