//
// Created by Julia on 25.03.2024.
//

#include "headers/Zdarzenie.h"

Zdarzenie::Zdarzenie(int czasTrwania, ZdarzenieLosowe zdarzenieLosowe) : czasTrwania(czasTrwania),
                                                                         zdarzenieLosowe(zdarzenieLosowe) {}

int Zdarzenie::wezCzasTrwania() const {
    return czasTrwania;
}

void Zdarzenie::ustawCzasTrwania(int czasTrwania) {
    Zdarzenie::czasTrwania = czasTrwania;
}

ZdarzenieLosowe Zdarzenie::wezZdarzenieLosowe() const {
    return zdarzenieLosowe;
}

void Zdarzenie::ustawZdarzenieLosowe(ZdarzenieLosowe zdarzenieLosowe) {
    Zdarzenie::zdarzenieLosowe = zdarzenieLosowe;
}
