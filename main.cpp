#include <QApplication>
#include "interface/WizualizatorSymulacji.h"
#include "headers/Symulacja.h"

class WizualizatorSymulacji;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *akwarium = new Akwarium();
    WizualizatorSymulacji wizualizator = WizualizatorSymulacji(akwarium);
    Symulacja symulacja = Symulacja(akwarium);
    QObject::connect(&wizualizator, &WizualizatorSymulacji::rozpocznijSymulacje, &symulacja,
                     &Symulacja::rozpocznijSymulacje);
    QObject::connect(&wizualizator, &WizualizatorSymulacji::rozpocznijIteracje, &symulacja,
                     &Symulacja::symulujIteracje);
    QObject::connect(&symulacja, &Symulacja::koniecIteracji, &wizualizator, [&wizualizator] { wizualizator.update(); });
    QObject::connect(&symulacja, &Symulacja::koniecRozpoczeniaSymulacji, &wizualizator,
                     [&wizualizator] { wizualizator.update(); });
    wizualizator.show();
    return QApplication::exec();
}
