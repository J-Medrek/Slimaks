#ifndef SLIMAKS_ZDARZENIE_H
#define SLIMAKS_ZDARZENIE_H

#include "ZdarzenieLosowe.h"

class Zdarzenie {
private:
    int czasTrwania;
    ZdarzenieLosowe zdarzenieLosowe;

public:
    Zdarzenie(int czasTrwania, ZdarzenieLosowe zdarzenieLosowe);

    int getCzasTrwania() const;

    void setCzasTrwania(int czasTrwania);

    ZdarzenieLosowe getZdarzenieLosowe() const;

    void setZdarzenieLosowe(ZdarzenieLosowe zdarzenieLosowe);
};


#endif //SLIMAKS_ZDARZENIE_H
