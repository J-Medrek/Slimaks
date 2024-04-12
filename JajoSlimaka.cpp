//
// Created by Julia on 25.03.2024.
//

#include "headers/JajoSlimaka.h"

void JajoSlimaka::symulujZachowanie() {
    czasDoWyklucia = czasDoWyklucia - 1;
}

void JajoSlimaka::rysuj(QPainter *qp) {

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
}

void JajoSlimaka::wykluj() {
    akwarium->dodajObiekt(std::make_unique<Slimak>(0, akwarium));
}

JajoSlimaka::~JajoSlimaka() {
    std::cout << "Usuwam jajko\n";
}
