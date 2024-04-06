

#include "headers/Slimak.h"


void Slimak::symulujZachowanie() {
    wyznaczZmiennePochodne();

    /*
     * Jeśli choroba
     {
     wyznacz zarazenie {jesli sie rozchorowal, zmniejsz szybkosc wzrostu,}
     jesli chory, wyznacz ozdrowienia
     jesli ozdrowial zwieksz odporonosc na chorobe
     }*/

    /*
     * jesli anomalia temperaturowa
     *
     *
     *
     *
     * */

    // wybierz losowo rosline i ją zjedz? Ale czy wtedy nie byloby problemu z polimorfizmem? Potrzebowałabym wtedy listę roślin

    //moze po prostu zsumuje zarłoczność, ale wtedy też potrzebuję listy ślimaków


}

void Slimak::wyznaczZmiennePochodne() {
    this->wiek = wiek + 1;
}

Slimak::Slimak(int wiek, Akwarium *akwarium) : wiek(wiek), akwarium(akwarium) {}
