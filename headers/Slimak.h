#ifndef SLIMAKS_SLIMAK_H
#define SLIMAKS_SLIMAK_H

#include <random>
#include <iostream>
#include "SymulowanyObiekt.h"
#include "Akwarium.h"

class Akwarium;

/**
 * @brief Klasa Slimak to pochodna klasy SymulowanyObiekt, określa symulowane ślimaki
 *
 */
class Slimak : public SymulowanyObiekt {

public:
    /**
    * konstruktor klasy Slimak
    * @param wiek zmienna całkowita określająca wiek ślimaka
    * @param akwarium wskaźnik do obiektu klasy Akwarium dzielonego z obiektami symulowanymi i interfejsem
    */
    Slimak(int wiek, Akwarium *akwarium);

    /**
     * symulujZachowanie to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Określa nowe wartości pól ślimaka, rozmnażanie, jedzenie roślin oraz symuluje efekty choroby
     */
    void symulujZachowanie() override;

    /**
     * rysuj to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Rysuje ikonę ślimaka w wylosowanym w tym momencie miejscu
     * @param qp obiekt klasy QPainter pozwalający na rysowanie na widgecie
     */
    void rysuj(QPainter *qp) override;

    /**
    * wezChoroba zwraca wartość pola choroba
    *
    * @return zmienna logiczna określająca wartość pola choroba
    */
    bool wezChoroba() const;

    /**
     * domyślny destruktor klasy Slimak
     */
    ~Slimak() override;

    /**
    * wezZarlocznosc zwraca wartość pola zarlocznosc
    *
    * @return zmienna double określająca wartość pola zarlocznosc
    */
    double wezZarlocznosc() const;

    /**
     * symulujEliminacje to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Zwraca prawdę gdy minie odpowiedni czasTrwaniaChoroby
     * @return zmienna logiczna określająca stan po skończeniu iteracji, true - obiekt został wyeliminowany
     */
    bool symulujEliminacje() override;

private:
    /// wiek ślimaka
    int wiek;
    /// żarłoczność ślimaka
    double zarlocznosc = 0.15;
    /// flaga określająca stan choroby ślimaka
    bool choroba = false;
    /// długość choroby ślimaka
    int dlugoscChoroby = 0;
    /// wskaźnik do obiektu typu Akwarium
    Akwarium *akwarium;
    /// generator liczb losowych
    std::random_device rd;
    /// szansa na wyzdrowienie ślimaka
    double szansaNaWyzdrowienie = 0.15;
    /// szansa na chorobę ślimaka
    double szansaNaChorobe = 0.15;

    /**
    * zjedzRosline to funkcja wykorzystywana w symulacji ślimaka. Ślimak zmniejsza wielkość rośliny aż do spaddku żarłoczności do zera
    */
    void zjedzRosline();

    /**
    * wyznaczSymulowaneZmienne to funkcja wykorzystywana w symulacji ślimaka.
    * Ślimak zwiększa swój wiek oraz wyznacza żarłoczność oraz szansę na wyzdrowienie i chorobę.
    */
    void wyznaczSymulowaneZmienne();

    /**
    * symulujChorobe to funkcja wykorzystywana w symulacji ślimaka.
    * Ślimak w przypadku rozpoczęcia choroby zostaje wyznaczony na pacjenta zero.
    * W przypadku trwania choroby następuje losowanie wyzdrownienia/choroby.
    */
    void symulujChorobe();

    /**
    * symulujRozmnazanie to funkcja wykorzystywana w symulacji ślimaka.
    * Tworzone są obiekty typu JajoSlimaka w przypadku określonej wartości iteracji oraz losu.
    */
    void symulujRozmnazanie();

    /**
    * wyznaczZarlocznosc to funkcja wykorzystywana w wyznaczSymulowaneZmienne. Wyznacza żarłoczność na podstawie wieku.
    */
    void wyznaczZarlocznosc();
};


#endif //SLIMAKS_SLIMAK_H
