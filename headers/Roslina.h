#ifndef SLIMAKS_ROSLINA_H
#define SLIMAKS_ROSLINA_H

#include <random>
#include "SymulowanyObiekt.h"

class Roslina : public SymulowanyObiekt {
private:
    double wielkosc = 1;
    double predkoscWzrostu;
    std::random_device rd;
    int x;
    int y;
public:
    explicit Roslina(double predkoscWzrostu);

public:
    void symulujZachowanie() override;

    double getWielkosc() const;

    void setWielkosc(double wielkosc);

    void rysuj(QPainter *qp) override;

    bool symulujEliminacje() override;

    ~Roslina() override;
};


#endif //SLIMAKS_ROSLINA_H
