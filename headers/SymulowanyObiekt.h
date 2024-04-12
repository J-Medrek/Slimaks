#ifndef SLIMAKS_SYMULOWANYOBIEKT_H
#define SLIMAKS_SYMULOWANYOBIEKT_H

#include <QPainter>

class SymulowanyObiekt {
public:
    virtual void symulujZachowanie() = 0;

    virtual void rysuj(QPainter *qp) = 0;

    virtual bool symulujEliminacje() = 0;

    virtual ~SymulowanyObiekt() = default;
};


#endif //SLIMAKS_SYMULOWANYOBIEKT_H
