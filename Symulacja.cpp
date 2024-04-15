#include "headers/Symulacja.h"
#include "headers/Zdarzenie.h"
#include <random>
#include <thread>
#include "headers/stale.h"

Symulacja::Symulacja(Akwarium *akwarium) : akwarium(akwarium) {}

void Symulacja::rozpocznijSymulacje() {
    for (int i = 0; i < akwarium->getPoczatkowaIloscRoslin(); ++i) {
        akwarium->dodajObiekt(std::make_unique<Roslina>(akwarium->getWzrostRoslin()));
    }
    for (int i = 0; i < akwarium->getPoczatkowaIloscSlimakow(); ++i) {
        akwarium->dodajObiekt(std::make_unique<Slimak>(12, akwarium));
    }
    akwarium->ustawNumerIteracji(1);
    emit koniecRozpoczeniaSymulacji();
}

void Symulacja::symulujIteracje() {
    std::this_thread::sleep_for(std::chrono::milliseconds(stale::CZAS_ITERACJI_MS));
    if (akwarium->getIloscRoslin() != 0 && akwarium->getIloscSlimakow() != 0) {
        symulujZdarzenieLosowe();

        int i = 0;
        while (i < akwarium->getSymulowaneObiekty().size()) {
            akwarium->getSymulowaneObiekty()[i]->symulujZachowanie();
            i++;
        }

        i = 0;
        while (i < akwarium->getSymulowaneObiekty().size()) {
            if (akwarium->getSymulowaneObiekty()[i]->symulujEliminacje()) {
                akwarium->usunObiekt(akwarium->getSymulowaneObiekty()[i]);
            } else {
                i++;
            }
        }
        akwarium->ustawNumerIteracji(akwarium->getNumerIteracji() + 1);
        emit koniecIteracji();
    }
}

void Symulacja::symulujZdarzenieLosowe() {
    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::BRAK) {
        akwarium->getZdarzenie().setZdarzenieLosowe(losujZdarzenieLosowe());
        akwarium->getZdarzenie().setCzasTrwania(1);
    } else {
        akwarium->getZdarzenie().setCzasTrwania(akwarium->getZdarzenie().getCzasTrwania() + 1);
    }

    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        if (akwarium->iloscChorychSlimakow() == 0 && akwarium->getZdarzenie().getCzasTrwania() != 1) {
            akwarium->getZdarzenie().setCzasTrwania(0);
            akwarium->getZdarzenie().setZdarzenieLosowe(ZdarzenieLosowe::BRAK);
        }
    }

    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA) {
        if (akwarium->getZdarzenie().getCzasTrwania() == 1) {
            akwarium->setWzrostRoslin(akwarium->getWzrostRoslin() - 0.05);
        }
        if (akwarium->getZdarzenie().getCzasTrwania() == 15) {
            akwarium->getZdarzenie().setZdarzenieLosowe(ZdarzenieLosowe::BRAK);
            akwarium->getZdarzenie().setCzasTrwania(0);
        }
    }
}

ZdarzenieLosowe Symulacja::losujZdarzenieLosowe() {
    std::mt19937 generator(rd());
    std::discrete_distribution<> prawdopodobienstwoZdarzenLosowych(
            {1 - stale::SZANSA_NA_ANOMALIE - stale::SZANSA_NA_CHOROBE, stale::SZANSA_NA_CHOROBE,
             stale::SZANSA_NA_ANOMALIE});
    return ZdarzenieLosowe(prawdopodobienstwoZdarzenLosowych(generator));
}
