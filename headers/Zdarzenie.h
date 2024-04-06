#ifndef SLIMAKS_ZDARZENIE_H
#define SLIMAKS_ZDARZENIE_H

#include "ZdarzenieLosowe.h"

class Zdarzenie {
    int czasTrwania;
    ZdarzenieLosowe zdarzenieLosowe;

public:
    Zdarzenie(int czasTrwania, ZdarzenieLosowe zdarzenieLosowe);

    explicit Zdarzenie(int czasTrwania);
};


#endif //SLIMAKS_ZDARZENIE_H
