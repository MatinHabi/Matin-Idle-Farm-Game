#include <string>
#include "Player.h"
using namespace std;

#ifndef CROP_H
#define CROP_H

class Crop {
    protected:
        string name;
        int initialCost;
        int harvestProfit;        
    public:

        Crop(); // Constructor

        string get_cropName();
        int get_initialCost();
        int get_harvestProfit();

        virtual int get_growTime(); // Countdown
        virtual int get_phase();

        virtual double HarvestMinigame(); 
        virtual double Harvest(); 
        virtual bool get_isRemovedAtHarvest();


        virtual ~Crop();

};

#endif

//To print out the crop, firstly check isReadytoHarvest, if = -1, get remaining time, if = 0, print empty, if = 1, print ready
// if isChanged(), just repeat the counting down.