#ifndef SLIMAKS_ZDARZENIE_H
#define SLIMAKS_ZDARZENIE_H

#include "ZdarzenieLosowe.h"

class Zdarzenie {
private:
    int czasTrwania;
    ZdarzenieLosowe zdarzenieLosowe;

public:
    Zdarzenie(int czasTrwania, ZdarzenieLosowe zdarzenieLosowe);

    int wezCzasTrwania() const;

    void ustawCzasTrwania(int czasTrwania);

    ZdarzenieLosowe wezZdarzenieLosowe() const;

    void ustawZdarzenieLosowe(ZdarzenieLosowe zdarzenieLosowe);
};


#endif //SLIMAKS_ZDARZENIE_H
