#include "AnnualCrop.h"

#ifndef WHEAT_H
#define WHEAT_H

class Wheat: public AnnualCrop {
    public:
        Wheat();
        double HarvestMinigame() override;
};

#endif