#include "Player.h"
#include "Crop.h"
#include "Plot.h"
#pragma once
#include <string>

class UGI{
public:
    Crop *crops;
    UGI(){}
    void displayMenu();
    void play();
    void newGame();
    int readInValue(int minVal, int maxVal);
    void load();
    void loadFarm(Player *obj);
    void plant(Player *player, int plotNumber, Plot *farm);
    void harvestCropInfo(Player *player, Plot *farm);
    void harvest(Player *player, int plotNumber, Plot *farm);
    void displayCropInfo(Player *player, Plot *farm);
    void saveGame(Player *player, Plot *farm, int farmSize);
    void cropList();
    void buyLand(Player *player, Plot *farm);
};