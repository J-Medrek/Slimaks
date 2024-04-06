#include "headers/Symulacja.h"
#include <ctime>
#include <cstdio>

Symulacja::Symulacja(Akwarium *akwarium, const int poczatkowaIloscSlimakow, const int poczatkowaIloscRoslin) : akwarium(
        akwarium), poczatkowaIloscSlimakow(poczatkowaIloscSlimakow), poczatkowaIloscRoslin(poczatkowaIloscRoslin) {}

void Symulacja::run() {
    int numerIteracji = 0;
    for (int i = 0; i < poczatkowaIloscSlimakow; ++i) {
        akwarium->dodajSlimaka(new Slimak(12, akwarium));
    }
    for (int i = 0; i < poczatkowaIloscRoslin; ++i) {
        akwarium->dodajRosline(new Roslina());
    }
    double time_counter = 0;
    clock_t this_time = clock();
    clock_t last_time = this_time;
    while (!akwarium->getRosliny().empty() && !akwarium->getSlimaki().empty()) {
        this_time = clock();
        time_counter += (double) (this_time - last_time);
        if (time_counter > CLOCKS_PER_SEC) {
            time_counter -= CLOCKS_PER_SEC;
            printf("%d\n", numerIteracji);
            symulujIteracje();
            numerIteracji++;
            akwarium->ustawNumerIteracji(numerIteracji);
        }
        last_time = this_time;
    }

}

void Symulacja::symulujIteracje() {
    //losuj zdarzenie losowe

    //jesli jest czyli akwarium.getZdarzenie.getENUM() to symulujemy


//    akwarium->setZdarzenieLosowe(Zdarzenie(0, ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA));


    //CHOROBA

    /*
     * - slimaki same to sobie zrobia czyli:
     * -ustawia czy chory/ zdrowy
     * - flage dlugosci choroby jak sa chorzy
     *
     *
     * POTEM czystki czyli: - usuwamy wszystkie Slimaki ktore choruja jakis czas
     *
     * - sprawdzamy ilosc chorych slimakow zeby sprawddzic czy choroba nadal byc powinna
     * */


    //ANOMALIA

    /*
     * zmniejszamy wzrost roslin
     * usuwamy czesc jaj jak ANOMALIA czas trwania == 0
     * */

    //



    // SYMULUJEMY SLIMAKI I ROSLINY / Zdarzenie losowe bedzie symulowane przez Slimaki i Rosliny w ich klasach


    for (SymulowanyObiekt *symulowanyObiekt: akwarium->getSymulowaneObiekty()) {
        symulowanyObiekt->symulujZachowanie();
    }

    // sprawdzamy czy jajka sie wykluwaja

    // zmniejszamy czas wyklucia o 1
}
