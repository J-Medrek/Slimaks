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

public:

    void dodajObiekt(std::unique_ptr<SymulowanyObiekt> obiekt);

    void usunObiekt(const std::unique_ptr<SymulowanyObiekt> &obiekt);

    int getNumerIteracji() const;

    void ustawNumerIteracji(int numerIteracji);

    const std::vector<std::unique_ptr<SymulowanyObiekt>> &getSymulowaneObiekty() const;

    double getWzrostRoslin() const;

    void setWzrostRoslin(double wzrostRoslin);

    int iloscChorychSlimakow();

    int getIloscJaj() const;

    int getIloscRoslin() const;

    int getIloscSlimakow() const;

    Zdarzenie &getZdarzenie();

    ~Akwarium() override;

    double calkowitaZarlocznosc();

    double calkowitaIloscRoslin();

    int getPoczatkowaIloscRoslin() const;

    void setPoczatkowaIloscRoslin(int poczatkowaIloscRoslin);

    int getPoczatkowaIloscSlimakow() const;

    void setPoczatkowaIloscSlimakow(int poczatkowaIloscSlimakow);

    int getSzybkoscZasiedlania() const;

    void setSzybkoscZasiedlania(int szybkoscZasiedlania);

private:
    std::vector<std::unique_ptr<SymulowanyObiekt>> symulowaneObiekty = {};
    int numerIteracji = 0;
    Zdarzenie zdarzenie = Zdarzenie(0, ZdarzenieLosowe::BRAK);
    double wzrostRoslin;
    int poczatkowaIloscRoslin;
    int poczatkowaIloscSlimakow;
    int iloscJaj;
    int iloscRoslin;
    int iloscSlimakow;
    int szybkoscZasiedlania;

signals:

    void nastepnaIteracja();


};


#endif //SLIMAKS_AKWARIUM_H
