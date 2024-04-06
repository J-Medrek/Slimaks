//
// Created by Julia on 21.03.2024.
//

#include <QtCore>
#include "headers/Akwarium.h"


void Akwarium::dodajRosline(Roslina *roslina) {
    rosliny.push_back(*&roslina);
}

void Akwarium::dodajSlimaka(Slimak *slimak) {
    slimaki.push_back(*&slimak);
}

const std::vector<Roslina *> &Akwarium::getRosliny() const {
    return rosliny;
}

const std::vector<Slimak *> &Akwarium::getSlimaki() const {
    return slimaki;
}

int Akwarium::getNumerIteracji() const {
    return numerIteracji;
}

void Akwarium::ustawNumerIteracji(int numerIteracji) {
    Akwarium::numerIteracji = numerIteracji;
    emit nastepnaIteracja();
}

const Zdarzenie &Akwarium::getZdarzenieLosowe() const {
    return zdarzenieLosowe;
}

void Akwarium::setZdarzenieLosowe(const Zdarzenie &zdarzenieLosowe) {
    Akwarium::zdarzenieLosowe = zdarzenieLosowe;
}
