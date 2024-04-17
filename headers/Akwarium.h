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


/**
 * @brief Klasa Akwarium odpowiada za przechowywanie stanu symulacji. Jest wykorzystywana przez symulowane obiekty oraz klasy odpowiedzialne za wizualizację i logikę.
 *  Przechowuje m.in symulowane obiekty, zmienne wprowadzone przez użytkownika.
 *
 */
class Akwarium {

public:

    /**
     * dodajObiekt dodaje obiekt do wektora
     *
     * @param obiekt inteligentny wskaźnik do obiektu typu SymulowanyObiekt
     */
    void dodajObiekt(std::unique_ptr<SymulowanyObiekt> obiekt);

    /**
     * usunObiekt usuwa obiekt z wektora
     *
     * @param obiekt inteligentny wskaźnik do obiektu typu SymulowanyObiekt
     */
    void usunObiekt(const std::unique_ptr<SymulowanyObiekt> &obiekt);

    /**
     * ustawZmienneSymulacji ustawia wartości przechowywanych zmiennych wprowadzone przez użytkownika
     *
     * @param iloscSlimakow wstępna ilość ślimaków
     * @param iloscRoslin wstępna ilość roślin
     * @param wzrostRoslin wzrost roślin co iterację
     * @param szybkoscZasiedlania ilość jaj złożonych jednorazowo
     * @param szansaAnomalia prawdopodobieństwo wylosowania anomalii
     * @param szansaChoroba prawdopodobieństwo wylosowania choroby
     * @param spadekWzrostuRoslin o ile spada wzrost roślin podczas anomalii
     * @param czasTrwaniaAnomalii czas trwania anomalii
    */
    void ustawZmienneSymulacji(int iloscSlimakow, int iloscRoslin, double wzrostRoslin, int szybkoscZasiedlania,
                               double szansaAnomalia, double szansaChoroba, double spadekWzrostuRoslin,
                               int czasTrwaniaAnomalii);

    /**
    * wyznaczIloscObiektow to szablon, który pozwala na wyznaczenie ilości obiektów, które znajdują się w wektorze
    *
    * @tparam T klasa którą chcemy znaleźć
    */
    template<class T>
    int wyznaczIloscObiektow() {
        int ilosc = 0;
        for (const auto &obiekt: symulowaneObiekty) {
            if (auto obiektPochodny = dynamic_cast<T *>(obiekt.get())) {
                ilosc++;
            }
        }
        return ilosc;
    }

    /**
    * destruktor klasy, czyści wektor inteligentnych wskaźników
    *
    */
    ~Akwarium();

    /**
    * wezNumerIteracji zwraca wartość pola numerIteracji
    *
    * @return liczba całkowita int określająca wartość pola numerIteracji
    */

    int wezNumerIteracji() const;

    /**
    * zwiekszNumerIteracji pozwala na zwiększenie pola numerIteracji o 1
    *
    */
    void zwiekszNumerIteracji();

    /**
    * wezSymulowaneObiekty zwraca wszystkie symulowane obiekty
    *
    * @return wektor inteligentnych wskaźnikow na SymulowanyObiekt
    */
    const std::vector<std::unique_ptr<SymulowanyObiekt>> &wezSymulowaneObiekty() const;

    /**
    * wezWzrostRoslin zwraca wartość pola wzrostRoslin
    *
    * @return wartość double określająca wartość pola wzrostRoslin
    */
    double wezWzrostRoslin() const;

    /**
    * ustawWzrostRoslin pozwala na ustawienie wartości pola wzrostRoslin
    *
    * @param wzrostRoslin wartosc double określająca wymaganą wartość pola wzrostRoslin
    */
    void ustawWzrostRoslin(double wzrostRoslin);

    /**
    * iloscChorychSlimakow zwraca ilość obiektów typu Slimak znajdujących się w wektorze z flagą choroba ustawioną na true
    *
    * @return wartość int określająca ilość chorych ślimaków
    */
    int iloscChorychSlimakow();

    /**
    * wezZdarzenie zwraca wartosc pola zdarzenie
    *
    * @return obiekt typu Zdarzenie
    */
    Zdarzenie &wezZdarzenie();

    /**
    * calkowitaZarlocznosc zwraca sumę żarłoczności wszystkich ślimaków w wektorze
    *
    * @return wartość double określająca sumę pola zarlocznosc wszystkich obiektów typu Slimak w wektorze
    */
    double calkowitaZarlocznosc();

    /**
    * calkowitaIloscRoslin zwraca sumę wielkości wszystkich roślin w wektorze
    *
    * @return wartość double określająca sumę pola wielkosc wszystkich obiektów typu Roslina w wektorze
    */
    double calkowitaIloscRoslin();

    /**
    * wezPoczatkowaIloscRoslin zwraca wartość pola poczatkowaIloscRoslin
    *
    * @return wartość int określająca wartość pola poczatkowaIloscRoslin
    */
    int wezPoczatkowaIloscRoslin() const;


    /**
    * wezPoczatkowaIloscSlimakow zwraca wartość pola poczatkowaIloscSlimakow
    *
    * @return wartość int określająca wartość pola poczatkowaIloscSlimakow
    */
    int wezPoczatkowaIloscSlimakow() const;

    /**
    * wezSzybkoscZasiedlania zwraca wartość pola szybkoscZasiedlania
    *
    * @return wartość int określająca wartość pola szybkoscZasiedlania
    */
    int wezSzybkoscZasiedlania() const;

    /**
    * wezSzansaAnomalia zwraca wartość pola szansaAnomalia
    *
    * @return wartość double określająca wartość pola szansaAnomalia
    */
    double wezSzansaAnomalia() const;

    /**
    * wezSzansaChoroba zwraca wartość pola szansaChoroba
    *
    * @return wartość double określająca wartość pola szansaChoroba
    */
    double wezSzansaChoroba() const;

    /**
    * wezSpadekWzrostuRoslin zwraca wartość pola spadekWzrostuRoslin
    *
    * @return wartość double określająca wartość pola spadekWzrostuRoslin
    */
    double wezSpadekWzrostuRoslin() const;

    /**
    * wezCzasTrwaniaAnomalii zwraca wartość pola czasTrwaniaAnomalii
    *
    * @return wartość int określająca wartość pola czasTrwaniaAnomalii
    */
    int wezCzasTrwaniaAnomalii() const;

private:
    /// wektor inteligentych wskaźników na obiekty typu SymulowanyObiekt
    std::vector<std::unique_ptr<SymulowanyObiekt>> symulowaneObiekty = {};
    /// numer obecnej iteracji
    int numerIteracji = 0;
    /// wartość obecnego wydarzenia
    Zdarzenie zdarzenie = Zdarzenie(0, ZdarzenieLosowe::BRAK);
    /// wartość globalnego wzrostu roślin określonego przez użytkownika
    double wzrostRoslin;
    /// wartość początkowej ilości roślin określonej przez użytkownika
    int poczatkowaIloscRoslin;
    /// wartość początkowej ilości ślimaków określonej przez użytkownika
    int poczatkowaIloscSlimakow;
    /// wartość szybkości zasiedlenia określonego przez użytkownika
    int szybkoscZasiedlania;
    /// wartość szansy na wylosowanie anomalii określona przez użytkownika
    double szansaAnomalia;
    /// wartość szansy na wylosowanie chorocy określona przez użytkownika
    double szansaChoroba;
    /// wartość spadku wzrostu roślin podczas anomalii określona przez użytkownika
    double spadekWzrostuRoslin;
    /// wartość czasu trwania anomalii określona przez użytkownika
    int czasTrwaniaAnomalii;

};


#endif //SLIMAKS_AKWARIUM_H
