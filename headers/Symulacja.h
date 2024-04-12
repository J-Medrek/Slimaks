#ifndef SLIMAKS_SYMULACJA_H
#define SLIMAKS_SYMULACJA_H

#include <vector>
#include "Slimak.h"
#include "Roslina.h"
#include "Akwarium.h"
#include <QObject>
#include <random>

class Symulacja : public QObject {
Q_OBJECT

public:
    Symulacja(Akwarium *akwarium, int poczatkowaIloscSlimakow, int poczatkowaIloscRoslin);

public slots:

    void run();

private:
    Akwarium *akwarium;
    const int poczatkowaIloscSlimakow;
    const int poczatkowaIloscRoslin;
    std::random_device rd;

    void symulujIteracje();

    ZdarzenieLosowe losujZdarzenieLosowe();

};


#endif //SLIMAKS_SYMULACJA_H
