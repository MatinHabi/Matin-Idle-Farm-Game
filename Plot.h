#include <ctime>
#include "Crop.h"
#include <string>
#include "Wheat.h"
#include "Apple.h"
#include <fstream>
#include "Player.h"


#ifndef PLOT_H
#define PLOT_H

class Plot {
    private:
       Crop **crop;
       time_t plantTime;
       
    public:
        Plot();

        void save(Player &username, int plotNumber);
        void get_saved(string fileName, int plotNumber);

        int Plant(string cropName, Player &user, int plotNumber);
        
        void get_info(string &cropName, string &phase, string &timeLeft);
        bool isFree();

        int Harvest(Player &player, int plotNumber);
};

#endif