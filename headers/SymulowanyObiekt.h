#ifndef SLIMAKS_SYMULOWANYOBIEKT_H
#define SLIMAKS_SYMULOWANYOBIEKT_H

#include <QPainter>

/**
 * @brief Klasa abstrakcyjna SymulowanyObiekt, uogólnia symulowane obiekty (ślimaki, rośliny i jajka ślimaka)
 *
 */

class SymulowanyObiekt {
public:
    /**
    * symulujZachowanie  to funkcja czysto wirtualna
    * Określa zachowanie każdego obiektu klas pochodnych
    */
    virtual void symulujZachowanie() = 0;

    /**
    * rysuj  to funkcja czysto wirtualna
    * Określa sposób rysowania każdego obiektu klas pochodnych
    * @param qp obiekt klasy QPainter pozwalający na rysowanie na widgecie
    */
    virtual void rysuj(QPainter *qp) = 0;

    /**
     * symulujEliminacje to funkcja czysto wirtualna
     * Określa stan obiektu klasy pochodnej po symulacji w danej iteracji
     * @return zmienna logiczna określająca stan po skończeniu iteracji, true - obiekt został wyeliminowany
     */
    virtual bool symulujEliminacje() = 0;

    /**
     * domyślny destruktor
     */
    virtual ~SymulowanyObiekt() = default;
};


#endif //SLIMAKS_SYMULOWANYOBIEKT_H
