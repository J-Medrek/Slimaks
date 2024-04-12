//
// Created by Julia on 21.03.2024.
//

#include <QtCore>
#include "headers/Akwarium.h"


void Akwarium::dodajObiekt(std::unique_ptr<SymulowanyObiekt> obiekt) {
    if (dynamic_cast<Roslina *>(obiekt.get())) {
        iloscRoslin++;
    }
    if (dynamic_cast<Slimak *>(obiekt.get())) {
        iloscSlimakow++;
    }
    if (dynamic_cast<JajoSlimaka *>(obiekt.get())) {
        iloscJaj++;
    }
    symulowaneObiekty.push_back(std::move(obiekt));
}

void Akwarium::usunObiekt(const std::unique_ptr<SymulowanyObiekt> &obiekt) {
    if (dynamic_cast<Roslina *>(obiekt.get())) {
        iloscRoslin--;
    }
    if (dynamic_cast<Slimak *>(obiekt.get())) {
        iloscSlimakow--;
    }
    if (dynamic_cast<JajoSlimaka *>(obiekt.get())) {
        iloscJaj--;
    }
    symulowaneObiekty.erase(std::find(symulowaneObiekty.begin(), symulowaneObiekty.end(), obiekt));
}

int Akwarium::getNumerIteracji() const {
    return numerIteracji;
}

void Akwarium::ustawNumerIteracji(int numerIteracji) {
    Akwarium::numerIteracji = numerIteracji;
    emit nastepnaIteracja();
}


const std::vector<std::unique_ptr<SymulowanyObiekt>> &Akwarium::getSymulowaneObiekty() const {
    return symulowaneObiekty;
}

double Akwarium::getWzrostRoslin() const {
    return wzrostRoslin;
}

void Akwarium::setWzrostRoslin(double wzrostRoslin) {
    Akwarium::wzrostRoslin = wzrostRoslin;
}

int Akwarium::iloscChorychSlimakow() {
    int iloscChorych = 0;
    for (const auto &obiekt: symulowaneObiekty) {
        if (auto slimak = dynamic_cast<Slimak *>(obiekt.get())) {
            iloscChorych += slimak->isChoroba();
        }
    }
    return iloscChorych;
}


Zdarzenie &Akwarium::getZdarzenie() {
    return zdarzenie;
}

Akwarium::~Akwarium() {
    std::cout << "Usuwam akwarium\n";
    symulowaneObiekty.clear();
}

int Akwarium::getIloscJaj() const {
    return iloscJaj;
}

int Akwarium::getIloscRoslin() const {
    return iloscRoslin;
}

int Akwarium::getIloscSlimakow() const {
    return iloscSlimakow;
}

double Akwarium::dziennaZarlocznosc() {
    double dziennaZarlocznosc = 0;
    for (const auto &obiekt: symulowaneObiekty) {
        if (auto slimak = dynamic_cast<Slimak *>(obiekt.get())) {
            dziennaZarlocznosc += slimak->getZarlocznosc();
        }
    }
    return dziennaZarlocznosc;
}

