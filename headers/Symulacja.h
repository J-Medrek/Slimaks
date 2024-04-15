#ifndef SLIMAKS_SYMULACJA_H
#define SLIMAKS_SYMULACJA_H

#include "Akwarium.h"
#include <QObject>
#include <random>

class Symulacja : public QObject {
Q_OBJECT

public:
    Symulacja(Akwarium *akwarium);

public slots:

    void rozpocznijSymulacje();

    void symulujIteracje();

signals:

    void koniecIteracji();

    void koniecRozpoczeniaSymulacji();

private:
    Akwarium *akwarium;
    std::random_device rd;

    ZdarzenieLosowe losujZdarzenieLosowe();

    void symulujZdarzenieLosowe();

};


#endif //SLIMAKS_SYMULACJA_H
