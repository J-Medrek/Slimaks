//
// Created by Julia on 24.03.2024.
//

#include "WizualizatorSymulacji.h"
#include "ui_WizualizatorSymulacji.h"
#include "../headers/Symulacja.h"
#include <QPen>
#include <QPainter>
#include <QHBoxLayout>
#include <iostream>

WizualizatorSymulacji::WizualizatorSymulacji(QWidget *parent) :
        QWidget(parent), ui(new Ui::WizualizatorSymulacji) {
    akwarium = new Akwarium();
    ui->setupUi(this);
    QPainter qPainter(this);
    connect(ui->pushButton, &QPushButton::clicked,
            this, [this] { start(); });
    connect(akwarium, &Akwarium::nastepnaIteracja, this, [this] { update(); });
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    ui->widget->setLayout(mainLayout);
}

void WizualizatorSymulacji::start() {
    Symulacja *symulacja = new Symulacja(akwarium, ui->iloscSlimakow->value(), ui->iloscRoslin->value());
    QThread *normalThread = new QThread(this);
    symulacja->moveToThread(normalThread);
    connect(normalThread, &QThread::started, symulacja, &Symulacja::run);
    normalThread->start();
}

void WizualizatorSymulacji::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    drawObjects(&painter);
}

WizualizatorSymulacji::~WizualizatorSymulacji() {
    delete ui;
}

void WizualizatorSymulacji::drawObjects(QPainter *qp) {
    QPen pen(Qt::black, 2, Qt::SolidLine);
    std::cout << "Numer iteracji: " << akwarium->getNumerIteracji() << "Rysujemy." << std::endl;
    if (!akwarium->getSlimaki().empty()) {
        akwarium->getSlimaki().at(0)->symulujZachowanie();
    }
    qp->setPen(pen);
    qp->drawRect(0, 0, 100, 100);
}
