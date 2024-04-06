#ifndef SLIMAKS_ROSLINA_H
#define SLIMAKS_ROSLINA_H


#include "SymulowanyObiekt.h"

class Roslina : public SymulowanyObiekt {
private:
    int wielkosc;
    double predkoscWzrostu;

public:
    void symulujZachowanie() override;
};


#endif //SLIMAKS_ROSLINA_H
