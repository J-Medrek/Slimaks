#include "headers/Symulacja.h"
#include "headers/Zdarzenie.h"
#include <random>
#include <thread>
#include "headers/stale.h"

Symulacja::Symulacja(Akwarium *akwarium) : akwarium(akwarium) {}

void Symulacja::rozpocznijSymulacje() {
    //inicjalizacja wstępnych obiektów
    for (int i = 0; i < akwarium->wezPoczatkowaIloscRoslin(); ++i) {
        akwarium->dodajObiekt(std::make_unique<Roslina>(akwarium));
    }
    for (int i = 0; i < akwarium->wezPoczatkowaIloscSlimakow(); ++i) {
        akwarium->dodajObiekt(std::make_unique<Slimak>(12, akwarium));
    }
    akwarium->zwiekszNumerIteracji();
    emit koniecRozpoczeniaSymulacji();
}

void Symulacja::symulujIteracje() {
    std::this_thread::sleep_for(std::chrono::milliseconds(stale::CZAS_ITERACJI_MS));
    if (akwarium->wyznaczIloscObiektow<Roslina>() != 0 && akwarium->wyznaczIloscObiektow<Slimak>() != 0) {
        symulujZdarzenieLosowe();

        // wywołanie symulacji dla każdego obiektu
        for (int j = 0; j < akwarium->wezSymulowaneObiekty().size(); j++) {
            akwarium->wezSymulowaneObiekty()[j]->symulujZachowanie();
        }

        // usuwanie wyeliminowanych obiektow
        int i = 0;
        while (i < akwarium->wezSymulowaneObiekty().size()) {
            if (akwarium->wezSymulowaneObiekty()[i]->symulujEliminacje()) {
                akwarium->usunObiekt(akwarium->wezSymulowaneObiekty()[i]);
            } else {
                i++;
            }
        }
        akwarium->zwiekszNumerIteracji();
        emit koniecIteracji();
    }
}

void Symulacja::symulujZdarzenieLosowe() {
    //losowanie zdarzenia losowego w przypadku braku trwania zdarzenia
    if (akwarium->wezZdarzenie().wezZdarzenieLosowe() == ZdarzenieLosowe::BRAK) {
        akwarium->wezZdarzenie().ustawZdarzenieLosowe(losujZdarzenieLosowe());
        akwarium->wezZdarzenie().ustawCzasTrwania(1);
    } else {
        akwarium->wezZdarzenie().ustawCzasTrwania(akwarium->wezZdarzenie().wezCzasTrwania() + 1);
    }

    // w przypadku gdy wszytkie slimaki wyzdrowialy i nie jest to poczatek choroby zakoncz zdarzenie
    if (akwarium->wezZdarzenie().wezZdarzenieLosowe() == ZdarzenieLosowe::CHOROBA) {
        if (akwarium->iloscChorychSlimakow() == 0 && akwarium->wezZdarzenie().wezCzasTrwania() != 1) {
            akwarium->wezZdarzenie().ustawCzasTrwania(0);
            akwarium->wezZdarzenie().ustawZdarzenieLosowe(ZdarzenieLosowe::BRAK);
        }
    }

    if (akwarium->wezZdarzenie().wezZdarzenieLosowe() == ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA) {
        // w przypadku gdy rozpoczęła się anomalia zmniejsz wzrost roślin
        if (akwarium->wezZdarzenie().wezCzasTrwania() == 1) {
            akwarium->ustawWzrostRoslin(akwarium->wezWzrostRoslin() - akwarium->wezSpadekWzrostuRoslin());
        }
        // w przypadku gdy minal czas trwania zdarzenia, zakoncz anomalie ,przywróć wzrost roślin
        if (akwarium->wezZdarzenie().wezCzasTrwania() == akwarium->wezCzasTrwaniaAnomalii()) {
            akwarium->wezZdarzenie().ustawZdarzenieLosowe(ZdarzenieLosowe::BRAK);
            akwarium->wezZdarzenie().ustawCzasTrwania(0);
            akwarium->ustawWzrostRoslin(akwarium->wezWzrostRoslin() + akwarium->wezSpadekWzrostuRoslin());
        }
    }
}

ZdarzenieLosowe Symulacja::losujZdarzenieLosowe() {
    std::mt19937 generator(rd());
    std::discrete_distribution<> prawdopodobienstwoZdarzenLosowych(
            {1 - akwarium->wezSzansaAnomalia() - akwarium->wezSzansaChoroba(), akwarium->wezSzansaChoroba(),
             akwarium->wezSzansaAnomalia()});
    return ZdarzenieLosowe(prawdopodobienstwoZdarzenLosowych(generator));
}
