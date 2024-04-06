//
// Created by Julia on 24.03.2024.
//

#ifndef SLIMAKS_WIZUALIZATORSYMULACJI_H
#define SLIMAKS_WIZUALIZATORSYMULACJI_H

#include <QWidget>
#include <QFutureWatcher>
#include <QtConcurrent>
#include "../headers/Slimak.h"
#include "../headers/Akwarium.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WizualizatorSymulacji; }
QT_END_NAMESPACE

class WizualizatorSymulacji : public QWidget {
Q_OBJECT

public:
    explicit WizualizatorSymulacji(QWidget *parent = nullptr);

    ~WizualizatorSymulacji() override;

private slots:

    void start();

    void drawObjects(QPainter *qp);

private:
    Ui::WizualizatorSymulacji *ui;
    Akwarium *akwarium;

    void paintEvent(QPaintEvent *event);

};


#endif //SLIMAKS_WIZUALIZATORSYMULACJI_H
