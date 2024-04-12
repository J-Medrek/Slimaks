#ifndef SLIMAKS_SLIMAK_H
#define SLIMAKS_SLIMAK_H

#include <random>
#include <iostream>
#include "SymulowanyObiekt.h"
#include "Akwarium.h"

class Akwarium;

class Slimak : public SymulowanyObiekt {
private:
    int wiek;
    double zarlocznosc = 0.15;
    bool choroba = false;
    int dlugoscChoroby = 0;
    Akwarium *akwarium;
    std::random_device rd;
    double szansaNaWyzdrowienie = 0.15;
    double szansaNaChorobe = 0.15;

    void zjedzRosline();

    void wyznaczSymulowaneZmienne();

    void symulujChorobe();

    void symulujRozmnazanie();

    void wyznaczZarlocznosc();

public:
    bool symulujEliminacje() override;

public:
    Slimak(int wiek, Akwarium *akwarium);

    void symulujZachowanie() override;

    void rysuj(QPainter *qp) override;

    bool isChoroba() const;

    ~Slimak() override;

    double getZarlocznosc() const;


};


#endif //SLIMAKS_SLIMAK_H
