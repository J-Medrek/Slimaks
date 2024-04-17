#ifndef SLIMAKS_SYMULACJA_H
#define SLIMAKS_SYMULACJA_H

#include "Akwarium.h"
#include <QObject>
#include <random>

/**
 * @brief Klasa Symulacja odpowiada za logikę symulacji. Wywołuje iteracje, uzupełnia wstępny stan symulowanych obiektów w Akwarium,
 * określa stan końcowy Akwarium po symulacji danej iteracji.
 */
class Symulacja : public QObject {
Q_OBJECT

public:
    /**
    * konstruktor klasy Symulacja
    * @param akwarium wskaźnik do obiektu klasy Akwarium dzielonego z obiektami symulowanymi i interfejsem
    */
    Symulacja(Akwarium *akwarium);

public slots:

    /**
    * Funkcja rozpocznijSymulacje po przejęciu sygnału wyemitowanego przez  WizualizatorSymulacji o rozpoczęciu symulacji,
    * uzupełnia Akwarium o początkowe obiekty Slimak i Roslina.
    */
    void rozpocznijSymulacje();

    /**
    * Funkcja symulujIteracje po przejęciu sygnału wyemitowanego przez WizualizatorSymulacji o zakończeniu wizualizacji poprzedniej iteracji
    * rozpoczyna symulację kolejnej iteracji. Losuje zdarzenie losowe oraz po zakończeniu symulacji przez obiekty oczyszcza Akwarium z wyeliminowanych obiektów.
    */
    void symulujIteracje();

signals:

    /**
    * Sygnał wysyłany po zakończeniu symulacji iteracji
    */
    void koniecIteracji();

    /**
    * Sygnał wysyłany po zakończeniu inicjalizacji Akwarium
    */
    void koniecRozpoczeniaSymulacji();

private:
    /// wskaźnik do obiektu typu Akwarium
    Akwarium *akwarium;
    /// generator liczb losowych
    std::random_device rd;

    /**
    * Funkcja losujZdarzenieLosowe generuje zdarzenie losowe wykorzystując generator lcizb losowych
    * @returns obiekt klasy ZdarzenieLosowe
    */
    ZdarzenieLosowe losujZdarzenieLosowe();

    /**
    * Funkcja symulujZdarzenieLosowe wydzielona z symulujIteracje określa stan zdarzenia losowego, kończy chorobę w przypadku wyzdrowienia wszystkich zarażonych,
     * czy kończy anomalię po określonym czasie
    */
    void symulujZdarzenieLosowe();

};


#endif //SLIMAKS_SYMULACJA_H
