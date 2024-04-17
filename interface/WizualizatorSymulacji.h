//
// Created by Julia on 24.03.2024.
//

#ifndef SLIMAKS_WIZUALIZATORSYMULACJI_H
#define SLIMAKS_WIZUALIZATORSYMULACJI_H

#include <QWidget>
#include <QFutureWatcher>
#include "../headers/Slimak.h"
#include "../headers/Akwarium.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WizualizatorSymulacji; }
QT_END_NAMESPACE

/**
 * @brief Klasa WizualizatorSymulacji odpowiada za wizualizację stanu symulacji.
 * Jest odpowiedzialna za przekazanie do Akwarium zmiennych przekazanych przez użytkownika.
 */

class WizualizatorSymulacji : public QWidget {
Q_OBJECT

public:

    /**
    * konstruktor klasy WizualizatorSymulacji
    * @param akwarium wskaźnik do obiektu klasy Akwarium
     * @param parent wskaźnik do obiektu klasy bazowej QWidget, domyślnie nullptr
    */
    explicit WizualizatorSymulacji(Akwarium *akwarium, QWidget *parent = nullptr);

    /**
    * destruktor klasy
    */
    ~WizualizatorSymulacji() override;

public slots:

    /**
    * odbiera sygnał wysłany przez wciśnięęty przycisk rozpoczęcia symulacji
     * przekazuje wartości użytkownika do Akwarium oraz emituje sygnał rozpoczęcia symulacji odbierany później przez klasę Symulacja
    */
    void start();

signals:

    /**
    * Sygnał wysyłany po przekazaniu wartości do użytkownika
    */
    void rozpocznijSymulacje();

    /**
    * Sygnał wysyłany po wizualizacji danej iteracji
    */
    void rozpocznijIteracje();

private:
    ///obiekt wygenerowany na podstawie pliku .ui
    Ui::WizualizatorSymulacji *ui;
    ///wskaźnik do obiektu klasy Akwarium
    Akwarium *akwarium;
    ///zmienna określająca czy w danym momencie wywołana jest symulacja
    bool trwaSymulacja;
    /// zmienna zwiększana po narysowaniu stanu danej iteracji, mniejsza o 1 od obecnej, służy do określenia czy po narysowaniu należy wysłać sygnał rozpocznijIteracje
    int poprzedniaIteracja = 0;

    /**
    * przeciążona funkcja paintEvent, która odbiera sygnał w przypadku gdy jest potrzeba narysowania widgeta
     * @param event wskaźnik do obiektu klasy QPaintEvent
    */
    void paintEvent(QPaintEvent *event) override;

    /**
    * funkcja narysujIteracje, która rysuje obiekty akwarium
     * @param qp wskaźnik do obiektu klasy QPainter
    */
    void narysujIteracje(QPainter *qp);

    /**
    * funkcja generujOpisIteracji, która generuje opis iteracji zawierający takie informacje jak ilości obiektów, numer iteracji, całościową żarłoczność itp.
    * @returns napis zawierający opis iteracji
    */
    std::string generujOpisIteracji();

    /**
    * funkcja generujOpisZdarzenia, która generuje opis zdarzenia zawierający takie informacje jak typ, czas trwania, ilość chorych ślimaków w przypadku choroby itp..
    * @returns napis zawierający opis zdarzenia
    */
    std::string generujOpisZdarzenia();


};


#endif //SLIMAKS_WIZUALIZATORSYMULACJI_H
