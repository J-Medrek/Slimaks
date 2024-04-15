//
// Created by Julia on 25.03.2024.
//

#include "headers/JajoSlimaka.h"

void JajoSlimaka::symulujZachowanie() {
    czasDoWyklucia = czasDoWyklucia - 1;
}

void JajoSlimaka::rysuj(QPainter *qp) {
    qp->drawEllipse(x, y, 5, 5);
}

bool JajoSlimaka::symulujEliminacje() {
    if (czasDoWyklucia == 0) {
        wykluj();
        return true;
    }
    if (akwarium->getZdarzenie().getZdarzenieLosowe() == ZdarzenieLosowe::ANOMALIA_TEMPERATUROWA
        && akwarium->getZdarzenie().getCzasTrwania() == 0) {
        return true;
    }
    return false;
}

JajoSlimaka::JajoSlimaka(Akwarium *akwarium) : akwarium(akwarium) {
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> xDistribution(0, 675);
    std::uniform_int_distribution<int> yDistribution(0, 625);
    x = xDistribution(generator);
    y = yDistribution(generator);
}

void JajoSlimaka::wykluj() {
    akwarium->dodajObiekt(std::make_unique<Slimak>(0, akwarium));
}

JajoSlimaka::~JajoSlimaka() {
    std::cout << "Usuwam jajko\n";
}
