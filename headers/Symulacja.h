#ifndef SLIMAKS_SYMULACJA_H
#define SLIMAKS_SYMULACJA_H

#include <vector>
#include "Slimak.h"
#include "Roslina.h"
#include "Akwarium.h"
#include <QObject>

class Symulacja : public QObject {
Q_OBJECT

public:
    Symulacja(Akwarium *akwarium, const int poczatkowaIloscSlimakow, const int poczatkowaIloscRoslin);

public slots:

    void run();

private:
    Akwarium *akwarium;
    const int poczatkowaIloscSlimakow;
    const int poczatkowaIloscRoslin;

    void symulujIteracje();

};


#endif //SLIMAKS_SYMULACJA_H
