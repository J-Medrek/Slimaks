#ifndef SLIMAKS_JAJOSLIMAKA_H
#define SLIMAKS_JAJOSLIMAKA_H


#include "Slimak.h"

class Akwarium;

class JajoSlimaka : public SymulowanyObiekt {
private:
    int czasDoWyklucia = 4;
    Akwarium *akwarium;

    void wykluj();

public:
    void symulujZachowanie() override;

    void rysuj(QPainter *qp) override;

    ~JajoSlimaka() override;

    bool symulujEliminacje() override;

    explicit JajoSlimaka(Akwarium *akwarium);

};

#endif //SLIMAKS_JAJOSLIMAKA_H
