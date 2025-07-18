#include "PerennialCrop.h"

int PerennialCrop::get_phase(){
    return phase;
}


int PerennialCrop::get_growTime(){
    switch (phase){
        case 0:
            return juvenileGrowTime;
        case 1: 
            return matureGrowTime;
    }
    return -1;
}

bool PerennialCrop::get_isRemovedAtHarvest(){
    return isRemoveAtHarvest;
}

double PerennialCrop::Harvest(){
    if(phase == 0){phase = 1;}
    return HarvestMinigame();
}