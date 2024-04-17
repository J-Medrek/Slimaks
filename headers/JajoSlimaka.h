#ifndef SLIMAKS_JAJOSLIMAKA_H
#define SLIMAKS_JAJOSLIMAKA_H


#include "Akwarium.h"
#include "stale.h"

class Akwarium;

/**
 * @brief Klasa JajoSlimaka to pochodna klasy SymulowanyObiekt, określa symulowane jajka ślimaka
 *
 */

class JajoSlimaka : public SymulowanyObiekt {
public:
    /**
     * symulujZachowanie to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Co iterację pole czasDoWyklucia zmniejsza się o 1
     */
    void symulujZachowanie() override;

    /**
     * rysuj to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Rysuje owalny kształt w odpowiednim, wylosowanym przy tworzeniu obiektu miejscu
     * @param qp obiekt klasy QPainter pozwalający na rysowanie na widgecie
     */
    void rysuj(QPainter *qp) override;

    /**
     * domyślny destruktor klasy JajoSlimaka
     */
    ~JajoSlimaka() override;

    /**
     * symulujEliminacje to implementacja funkcji czysto wirtualnej klasy SymulowanyObiekt
     * Zwraca prawdę gdy czasDoWyklucia zmniejszy się do 0 lub gdy występuje anomalia temperaturowa
     * @return zmienna logiczna określająca stan po skończeniu iteracji, true - obiekt został wyeliminowany
     */
    bool symulujEliminacje() override;

    /**
    * konstruktor klasy JajoSlimaka
     * @param akwarium wskaźnik do obiektu klasy Akwarium dzielonego z obiektami symulowanymi i interfejsem
    */
    explicit JajoSlimaka(Akwarium *akwarium);

private:
    /// czas do wyklucia ustalany za pomocą stałej zmiennej
    int czasDoWyklucia = stale::CZAS_WYKLUCIA;
    /// wskaźnik do obiektu typu Akwarium
    Akwarium *akwarium;
    /// generator liczb losowych
    std::random_device rd;
    /// współrzędna x miejsca narysowania obiektu na widgecie
    int x;
    /// współrzędna y miejsca narysowania obiektu na widgecie
    int y;

    /**
    * wykluj to funkcja wywoływana przy spadku czasu do wyklucia do zera.
     * Dodaje do Akwarium nowy obiekt typu Slimak.
    */
    void wykluj();

};

#endif //SLIMAKS_JAJOSLIMAKA_H
