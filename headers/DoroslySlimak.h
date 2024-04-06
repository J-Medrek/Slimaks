#ifndef SLIMAKS_DOROSLYSLIMAK_H
#define SLIMAKS_DOROSLYSLIMAK_H


#include "Slimak.h"

class DoroslySlimak : public Slimak {
public:
    DoroslySlimak(int wiek, Akwarium *akwarium);

    void symulujZachowanie() override;


};


#endif //SLIMAKS_DOROSLYSLIMAK_H
