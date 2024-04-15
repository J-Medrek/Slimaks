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

class WizualizatorSymulacji : public QWidget {
Q_OBJECT

public:
    explicit WizualizatorSymulacji(Akwarium *akwarium, QWidget *parent = nullptr);

    ~WizualizatorSymulacji() override;

public slots:

    void start();

signals:

    void rozpocznijSymulacje();

    void rozpocznijIteracje();

private:
    Ui::WizualizatorSymulacji *ui;
    Akwarium *akwarium;

    void paintEvent(QPaintEvent *event) override;

    void drawObjects(QPainter *qp);

    std::string generujOpisIteracji();

    std::string generujOpisZdarzenia();

    bool zwalidujWprowadzoneDane();

    bool trwaSymulacja;

    int poprzedniaIteracja = 0;


};


#endif //SLIMAKS_WIZUALIZATORSYMULACJI_H
