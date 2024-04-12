//
// Created by Julia on 25.03.2024.
//

#include "headers/Zdarzenie.h"

Zdarzenie::Zdarzenie(int czasTrwania, ZdarzenieLosowe zdarzenieLosowe) : czasTrwania(czasTrwania),
                                                                         zdarzenieLosowe(zdarzenieLosowe) {}

int Zdarzenie::getCzasTrwania() const {
    return czasTrwania;
}

void Zdarzenie::setCzasTrwania(int czasTrwania) {
    Zdarzenie::czasTrwania = czasTrwania;
}

ZdarzenieLosowe Zdarzenie::getZdarzenieLosowe() const {
    return zdarzenieLosowe;
}

void Zdarzenie::setZdarzenieLosowe(ZdarzenieLosowe zdarzenieLosowe) {
    Zdarzenie::zdarzenieLosowe = zdarzenieLosowe;
}
