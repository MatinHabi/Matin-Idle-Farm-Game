#include "Crop.h"
using namespace std;

#ifndef ANNUALCROP_H
#define ANNUALCROP_H

class AnnualCrop: public Crop {
    protected:
        int growTime;
        const bool isRemovedAtHarvest = 1;
    public:
        int get_growTime() override;
        int get_phase() override;
        bool get_isRemovedAtHarvest() override;
        double Harvest() override;
};

#endif