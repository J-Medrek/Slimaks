//
// Created by Julia on 23.03.2024.
//

#include <iostream>
#include "headers/MlodySlimak.h"

void MlodySlimak::symulujZachowanie() {
    printf("%s\n", "Symuluje mlodego slimaka");
}

MlodySlimak::MlodySlimak(Akwarium *akwarium) : Slimak(0, akwarium) {}
