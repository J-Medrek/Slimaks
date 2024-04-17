#ifndef SLIMAKS_ROSLINA_H
#define SLIMAKS_ROSLINA_H

#include <random>
#include "SymulowanyObiekt.h"
#include "Akwarium.h"

class Akwarium;

/**
 * @brief Klasa Roslina to pochodna klasy SymulowanyObiekt, określa symulowane rośliny
 *
 */
class Roslina : public SymulowanyObiekt {

public:
    /**
    * konstruktor klasy Roslina
    * @param predkoscWzrostu predkość wzrostu roślin
    */
    explicit Roslina(Akwarium *akwarium);

    /**
    * symulujZachowanie to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
    * Co iterację pole wielkosc zwieksza się o prędkość wzrostu
    */
    void symulujZachowanie() override;

    /**
    * wezWielkosc zwraca wartość pola wielkosc
    *
    * @return liczba double  określająca wartość pola wielkosc
    */
    double wezWielkosc() const;

    /**
    * ustawWielkosc pozwala na ustawienie wartości pola wielkosc
    *
    * @param wielkosc liczba double określająca wymaganą wartość pola wielkosc
    */
    void ustawWielkosc(double wielkosc);

    /**
     * rysuj to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Rysuje wyskalowaną względem wielkości ikonę rośliny w odpowiednim, wylosowanym przy tworzeniu obiektu miejscu
     * @param qp obiekt klasy QPainter pozwalający na rysowanie na widgecie
     */
    void rysuj(QPainter *qp) override;

    /**
     * symulujEliminacje to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Zwraca prawdę gdy wielkosc zmniejszy się do 0
     * @return zmienna logiczna określająca stan po skończeniu iteracji, true - obiekt został wyeliminowany
     */
    bool symulujEliminacje() override;

    /**
     * domyślny destruktor klasy Roslina
     */
    ~Roslina() override;

private:
    /// wielkość rośliny
    double wielkosc = 1;
    /// predkość wzrostu roślin
    Akwarium *akwarium;
    /// generator liczb losowych
    std::random_device rd;
    /// współrzędna x miejsca narysowania obiektu na widgecie
    int x;
    /// współrzędna y miejsca narysowania obiektu na widgecie
    int y;


};


#endif //SLIMAKS_ROSLINA_H
