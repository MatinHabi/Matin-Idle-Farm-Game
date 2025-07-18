#include "UGI.h"
#include "AnnualCrop.h"
#include "Apple.h"
#include "Player.h"
#include "Crop.h"
#include "PerennialCrop.h"
#include "Plot.h"
#include "Wheat.h"

#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <fstream>
#define CLEAR_SCREEN() std::cout << "\x1B[2J"
#define CURSOR_HOME()  std::cout << "\x1B[H"

void UGI::displayMenu(){
    CLEAR_SCREEN();
    CURSOR_HOME();
    int temp;
    std::cout<< "---------------------------------- Newbie Farmer ----------------------------------------\n";
    std::cout<< "\n[1]Play\n";
    std::cout<< "\n[2]Exit\n";

    temp = readInValue(1,2);

    if(temp == 1){
        play();
    }else if(temp == 2){
        std::cout<<"\nExiting...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        CLEAR_SCREEN();
        CURSOR_HOME();
        return;
    }else{
        std::cout<<"\nInvalid input!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        displayMenu();
    }
}

void UGI::play(){
    CLEAR_SCREEN();
    CURSOR_HOME();
    int temp;
    std::string username;

    std::cout<< "---------------------------------- Newbie Farmer ----------------------------------------\n";
    std::cout<< "\n[1]New Game\n";
    std::cout<< "\n[2]Load\n";
    std::cout<< "\n[3]Exit\n";

    temp = readInValue(1,3);

    switch(temp){
        case 1:
            CLEAR_SCREEN();
            CURSOR_HOME();
            newGame();
            return;
            break;
        case 2:
            CLEAR_SCREEN();
            CURSOR_HOME();
            load();
            return;
            break;
        case 3:
            displayMenu();
            return;
            break;
        default:
            std::cout<<"Invalid Input!\n";
            play();
            return;
            break;
    }
}


int UGI::readInValue(int minVal, int maxVal){
   bool success = false;
   int temp;
   while(!success){
        std::string line;
        std::cout << " \n";
        std::cin >> line;
        try{
            temp = std::stoi(line);
            if(temp < minVal || temp > maxVal){
                throw std::out_of_range("out of range");
            }
            temp = std::stoi(line);
            success = true;
        }
        catch(const std::invalid_argument&){
            std::cerr<< "Error: Invalid Argument\n";
        }
        catch(const std::out_of_range&){
            std::cerr << "Error: Out of range\n";
        }
    }
    return temp;
}

void UGI::newGame(){
    CLEAR_SCREEN();
    CURSOR_HOME();
    std::cout<< "---------------------------------- New Game ---------------------------------------------\n";
    std::string username;
    std::cout << "\nEnter a username: ";
    std:: cin >> username;
    Player *player = new Player(username);
    bool isRegistered = player->registerUsername(username);

    if(!isRegistered){
        //username is already taken
        int temp;
        std::cout<<"\nThis user is already registered would you like to log in?:\n";
        std::cout<<"\n[1]Log in\n";
        std::cout<<"\n[2]Exit\n";

        temp = readInValue(1,2);

        if(temp == 1){
            load();
            return;
        }else if(temp == 2){
            displayMenu();
            return;
        }else{
            std::cout<<"Invalid Input!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            newGame();
            return;
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    player->saveToFile();
    loadFarm(player);
}

void UGI::load(){
    CLEAR_SCREEN();
    CURSOR_HOME();
    std::cout<< "---------------------------------- Load Game --------------------------------------------\n";
    std::string username;
    std::cout << "\nEnter a username: ";
    std:: cin >> username;
    Player *player = new Player(username);
    bool isRegistered = player -> isRegistered();

    if(!isRegistered){
        int temp;
        std::cout<<"\nThis is an unregistered username, would you like to start a New Game?: ";
        std::cout<<"\n[1]New Game\n";
        std::cout<<"\n[2]Exit\n";

        temp = readInValue(1,2);

        if(temp == 1){
            newGame();
            return;
        }else if(temp == 2){
            displayMenu();
            return;
        }else{
            std::cout<<"Invalid Input!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            load();
            return;
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    player->loadFromFile();
    loadFarm(player);

}

void UGI::loadFarm(Player *player){
    int farm_sizes = player->get_farm_size();
    double balance = player->get_balance();
    Plot *farm = new Plot[farm_sizes];
    std::string fileName = player->get_username() + "Farm.txt";
    std::string *cropName = new string;
    std::string *phase = new string;
    std::string *timeLeft = new string;
    for(int i = 0 ; i < farm_sizes; i++){
        farm[i].get_saved(fileName,i);
    }

    
    while(true){
        int temp;
        CLEAR_SCREEN();
        CURSOR_HOME();
        std::cout<< "---------------------------------- Newbie Farmer ----------------------------------------\n";
        std::cout<< player->get_username() << "'s Farm\n";
        std::cout<<"\nBalance: $" << balance << "\n";
        for(int i = 0 ; i < farm_sizes ; i++){
            farm[i].get_info(*cropName,*phase, *timeLeft);
            std::cout<< "[Plot " << i+1 << "] " << *cropName << " " << *phase << *timeLeft << std::endl;
        }
        std::cout<<"\n[1] Plant\n";
        std::cout<<"\n[2] Continue\n";
        std::cout<<"\n[3] Harvest\n";
        std::cout<<"\n[4] Buy Land\n";
        std::cout<<"\n[0] Exit\n";
        temp = readInValue(0,4);
        if(temp == 1){
            displayCropInfo(player, farm);
            return;
            break;
        }else if(temp == 2){
            std::cout<<"Continuing...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }else if(temp == 3){
            std::cout<<"Harvesting...\n";
            harvestCropInfo(player, farm);
            return;
            break;
        }else if(temp == 4){
            buyLand(player, farm);
            return;
        }else if(temp == 0){
            CLEAR_SCREEN();
            CURSOR_HOME();
            std::cout<<"Exiting...\n";
            saveGame(player, farm, player->get_farm_size());
            delete[] farm;
            delete cropName;
            delete phase;
            delete timeLeft;
            displayMenu();
            return;
            break;
        }else{
            std::cout<<"Invalid Input!\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void UGI::displayCropInfo(Player *player, Plot *farm){
    CLEAR_SCREEN();
    CURSOR_HOME();
    std::cout<<"---------------------------------- Crop Info --------------------------------------------\n";
    cropList();
    std::cout<<"\n[1] Plant\n";
    std::cout<<"\n[2] Buy Land\n";
    std::cout<<"\n[0] Exit\n";
    int ans = readInValue(0,2);
    if(ans == 0){
        CLEAR_SCREEN();
        CURSOR_HOME();
        std::cout<<"Exiting...\n";
        saveGame(player, farm, player->get_farm_size());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        loadFarm(player);
        //added return to avoid falling through
        return;
    }else if(ans == 1){
        int plotNumber;
        std::cout<<"Enter plot number: ";
        plotNumber = readInValue(1,player->get_farm_size()) -  1;
        plant(player, plotNumber, farm);
    }else if(ans== 2){
        buyLand(player,farm);
    }else{
        std::cout<<"Invalid Input!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        displayCropInfo(player, farm);
        return;
    }
}

void UGI::plant(Player *player, int plotNumber, Plot *farm){
    CLEAR_SCREEN();
    CURSOR_HOME();
    //checking to see if plot is full
    if(!farm[plotNumber].isFree()){
        std::cout<<"The chosen land is full!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        loadFarm(player);
        return;
    }
    int result = -99; //initalise result to avoid it being unused
    std::cout<< "---------------------------------- Plant Crop --------------------------------------------\n";
    std::cout<< "\n[1] Apple\n";
    std::cout<< "\n[2] Wheat\n";
    std::cout<< "\n[3] Potato\n";
    std::cout<< "\n\n[0] Exit\n";

    std::cout << "Enter the crop you want to plant: ";
    int temp = readInValue(0,3);

    switch (temp){
        case 0:
            CLEAR_SCREEN();
            CURSOR_HOME();
            std::cout<<"Exiting...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            loadFarm(player);
            return;
            break;
        case 1:
            result = farm[plotNumber].Plant("Apple", *player, plotNumber);
            std::cout << "You have planted an Apple tree!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 2:
            result = farm[plotNumber].Plant("Wheat", *player, plotNumber);
            std::cout << "You have planted Wheat!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        case 3:
            result = farm[plotNumber].Plant("Potato", *player, plotNumber);
            std::cout << "You have planted a Potato!\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            break;
        default:
            std::cout<<"Invalid Input!\n";
    }
    //added int result to check whether the planting process was successful
    if (result == 1) {
        std::cout << "You have planted successfully!\n";
    } else if (result == -1) {
        std::cout << "Not enough funds to plant that crop!\n";
    } else if (result == 0) {
        std::cout << "This plot is already taken.\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(700));
    saveGame(player, farm, player->get_farm_size());
    loadFarm(player);
    return;
}

void UGI::saveGame(Player *player, Plot *farm, int farmSize){
    player->saveToFile();
    for(int i = 0; i < farmSize; i++){
        farm[i].save(*player, i);
    }
}

void UGI::cropList(){
   cout << "Name     | Type      | Cost     | Profit     | Grow Time (s)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Wheat    | Annual    | 100      | 200        | 60" << endl;
    cout << "Potato   | Annual    | 1000000  | 20000000   | 10" << endl;
    cout << "Apple    | Perennial | 200      | 400        | 10" << endl;
}

void UGI::harvestCropInfo(Player *player, Plot *farm){
    CLEAR_SCREEN();
    CURSOR_HOME();
    std::cout<< "---------------------------------- Harvest Crop ------------------------------------------\n";
     cropList();
    std::cout<<"\n[1] Close Harvesting Table And Contue To Harvest\n";
    std::cout<< "\n[0] Exit\n";
    int temp = readInValue(0,1);

    if(temp == 0){
        CLEAR_SCREEN();
        CURSOR_HOME();
        std::cout<<"Exiting...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        loadFarm(player);
        return;
    }else if(temp == 1){
        std::cout<<"Enter plot number to harvest:\n";
        int plotNumber = readInValue(1,player->get_farm_size()) - 1;
        harvest(player, plotNumber, farm);
        return;
    }

   
}

void UGI::harvest(Player *player, int plotNumber, Plot *farm){
    CLEAR_SCREEN();
    CURSOR_HOME();

    std::cout<< "---------------------------------- Harvest Crop ------------------------------------------\n";

    int result = farm[plotNumber].Harvest(*player, plotNumber);
    if(result == 1){
        std::cout << "You have harvested " << "Plot " << plotNumber + 1 <<  " successfully!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        loadFarm(player);
        return;
    }else if(result == -1){
        std::cout << "This plot is not ready for hartvest!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        loadFarm(player);
        return;
    }else if(result == 0){
        std::cout << "This plot is empty!\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        loadFarm(player);
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(700));

}

void UGI::buyLand(Player *player, Plot *farm){
    int temp;
    CLEAR_SCREEN();
    CURSOR_HOME();
    std::cout<< "------------------------------------ Buy Land -------------------------------------------\n";
    std::cout<<"1 plot is $500\n\nWould you like to purchase?\n";
    std::cout<< "\n[1] Yes\n";
    std::cout<< "\n[2] No\n";
    std::cout<< "\n\n[0] Exit\n";

    temp = readInValue(0,2);

    if(temp == 1){
        //checking for funds
        if(player->get_balance() < 500){
            std::cout<<"\nInsufficient funds!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            loadFarm(player);
            return;
        }
        //deducting land cost + changing player farm size
        player->set_balance(player->get_balance()-500);
        player->set_farm_size(player->get_farm_size()+1);
        //changing player files
        std::string farmFileName = player->get_username() + "Farm.txt";

        std::ofstream farmFile(farmFileName, std::ios::app);
        if(farmFile.is_open()){
            farmFile << ",,";
            farmFile.close();
        }else{
            std::cout<<"Error opening file\n";
            return;
        }

        std::cout << "\nLand successfully purchased!\n";
        //creating new Farm array for new size
        int newSize = player->get_farm_size();
        Plot* newFarm = new Plot[newSize];
        for(int i = 0; i < newSize; i++){
            newFarm[i].get_saved(farmFileName, i);
        }

        saveGame(player, newFarm, newSize);
        delete[] newFarm;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        loadFarm(player);
        return;
    }else if(temp == 2){
        loadFarm(player);
        return;
    }else if(temp == 0){
        saveGame(player, farm, player->get_farm_size());
        displayMenu();
        return;
    }else{
        std::cout<<"\nInvalid Input!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        buyLand(player, farm);
        return;
    }
}
