#include "Crop.h"
using namespace std;


Crop::Crop(){}

string Crop::get_cropName(){
    return name;
}

int Crop::get_initialCost(){
    return initialCost;
}

int Crop::get_harvestProfit(){
    return harvestProfit;
}

int Crop::get_growTime(){return 0;}

int Crop::get_phase(){return 0;}

double Crop::Harvest(){return 0;}

bool Crop::get_isRemovedAtHarvest(){return 0;}

double Crop::HarvestMinigame(){return 0;}

Crop::~Crop(){}