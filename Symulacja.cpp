#include "headers/Symulacja.h"
#include "headers/Zdarzenie.h"
#include <ctime>
#include <memory>
#include <random>

Symulacja::Symulacja(Akwarium *akwarium, const int poczatkowaIloscSlimakow, const int poczatkowaIloscRoslin) : akwarium(
        akwarium), poczatkowaIloscSlimakow(poczatkowaIloscSlimakow), poczatkowaIloscRoslin(poczatkowaIloscRoslin) {}

void Symulacja::run() {
    int numerIteracji = 0;
    for (int i = 0; i < poczatkowaIloscSlimakow; ++i) {
        akwarium->dodajObiekt(std::make_unique<Slimak>(12, akwarium));
    }
    for (int i = 0; i < poczatkowaIloscRoslin; ++i) {
        akwarium->dodajObiekt(std::make_unique<Roslina>(akwarium->getWzrostRoslin()));
    }
    double time_counter = 0;
    clock_t this_time = clock();
    clock_t last_time = this_time;
    while (akwarium->getIloscRoslin() != 0 && akwarium->getIloscSlimakow() != 0) {
        this_time = clock();
        time_counter += (double) (this_time - last_time);
        if (time_counter > CLOCKS_PER_SEC) {
            time_counter -= CLOCKS_PER_SEC;
            symulujIteracje();
            numerIteracji++;
            akwarium->ustawNumerIteracji(numerIteracji);
        }
        last_time = this_time;
    }

}

void Symulacja::symulujIteracje() {
    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::BRAK) {
        akwarium->getZdarzenie().setZdarzenieLosowe(losujZdarzenieLosowe());
        akwarium->getZdarzenie().setCzasTrwania(1);
    } else {
        akwarium->getZdarzenie().setCzasTrwania(akwarium->getZdarzenie().getCzasTrwania() + 1);
    }

    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        if (akwarium->iloscChorychSlimakow() == 0) {
            akwarium->getZdarzenie().setCzasTrwania(0);
            akwarium->getZdarzenie().setZdarzenieLosowe(ZdarzenieLosowe::BRAK);
        }
    }

    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA) {
        if (akwarium->getZdarzenie().getCzasTrwania() == 15) {
            akwarium->getZdarzenie().setZdarzenieLosowe(ZdarzenieLosowe::BRAK);
            akwarium->getZdarzenie().setCzasTrwania(0);
        }
    }

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
}

ZdarzenieLosowe Symulacja::losujZdarzenieLosowe() {
    std::mt19937 generator(rd());
    std::discrete_distribution<> prawdopodobienstwoZdarzenLosowych({0.20, 0.40, 0.40});
    return ZdarzenieLosowe(prawdopodobienstwoZdarzenLosowych(generator));
}
