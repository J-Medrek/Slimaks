#ifndef SLIMAKS_SLIMAK_H
#define SLIMAKS_SLIMAK_H

#include "SymulowanyObiekt.h"
#include "Akwarium.h"

class Akwarium;

class Slimak : public SymulowanyObiekt {
private:
    int wiek;
    double zarlocznosc;
    bool choroba = false;
    int dlugoscChoroby;
    Akwarium *akwarium;

public:
    Slimak(int wiek, Akwarium *akwarium);

    virtual void symulujZachowanie();

    void zjedzRosline();

    void wyznaczZmiennePochodne();
};


#endif //SLIMAKS_SLIMAK_H
