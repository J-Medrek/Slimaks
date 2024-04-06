#ifndef SLIMAKS_MLODYSLIMAK_H
#define SLIMAKS_MLODYSLIMAK_H


#include "Slimak.h"

class MlodySlimak : public Slimak {

public:
    MlodySlimak(Akwarium *akwarium);

private:

    void symulujZachowanie() override;
};


#endif //SLIMAKS_MLODYSLIMAK_H
