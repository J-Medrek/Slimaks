#ifndef SLIMAKS_JAJOSLIMAKA_H
#define SLIMAKS_JAJOSLIMAKA_H


#include "Akwarium.h"
#include "stale.h"

class Akwarium;

class JajoSlimaka : public SymulowanyObiekt {
private:
    int czasDoWyklucia = stale::CZAS_WYKLUCIA;
    Akwarium *akwarium;
    std::random_device rd;
    int x;
    int y;

    void wykluj();

public:
    void symulujZachowanie() override;

    void rysuj(QPainter *qp) override;

    ~JajoSlimaka() override;

    bool symulujEliminacje() override;

    explicit JajoSlimaka(Akwarium *akwarium);

};

#endif //SLIMAKS_JAJOSLIMAKA_H
