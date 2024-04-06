#ifndef SLIMAKS_AKWARIUM_H
#define SLIMAKS_AKWARIUM_H

#include <vector>
#include "Roslina.h"
#include "Slimak.h"
#include "JajoSlimaka.h"
#include "Zdarzenie.h"
#include <QObject>

class Slimak;

class Roslina;

class JajoSlimaka;

class Akwarium : public QObject {
Q_OBJECT

private:
    std::vector<SymulowanyObiekt *> symulowaneObiekty = {};
    std::vector<Roslina *> rosliny = {};
    std::vector<Slimak *> slimaki = {};
    std::vector<JajoSlimaka *> jaja = {};
    int numerIteracji = 0;
    Zdarzenie zdarzenieLosowe = Zdarzenie(0, ZdarzenieLosowe::BRAK);
    int czasTrwaniaZdarzenia = 0;
    int liczbaJaj;

public:
    const std::vector<Roslina *> &getRosliny() const;

    const std::vector<Slimak *> &getSlimaki() const;

    void dodajSlimaka(Slimak *slimak);

    void dodajRosline(Roslina *roslina);

    int getNumerIteracji() const;

    void ustawNumerIteracji(int numerIteracji);

    const Zdarzenie &getZdarzenieLosowe() const;

    void setZdarzenieLosowe(const Zdarzenie &zdarzenieLosowe);

    const std::vector<SymulowanyObiekt *> &getSymulowaneObiekty() const;

signals:

    void nastepnaIteracja();


};


#endif //SLIMAKS_AKWARIUM_H
