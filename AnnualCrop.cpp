#include "AnnualCrop.h"

bool AnnualCrop::get_isRemovedAtHarvest(){
    return isRemovedAtHarvest;
}

int AnnualCrop::get_growTime(){
    return growTime;
}

int AnnualCrop::get_phase(){
    return -1;
}

double AnnualCrop::Harvest(){
    return HarvestMinigame();
}