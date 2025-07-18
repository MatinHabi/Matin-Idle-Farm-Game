#include "Crop.h"
using namespace std;

#ifndef PERENNIALCROP_H
#define PERENNIALCROP_H

class PerennialCrop: public Crop {
    protected:
        int juvenileGrowTime;
        int matureGrowTime;
        int phase; // 0 = juvenile, 1 = mature
        const bool isRemoveAtHarvest = 0;
    public:
        
        bool get_isRemovedAtHarvest() override;
        int get_phase();
        int get_growTime() override;

        double Harvest() override;
        
};

#endif