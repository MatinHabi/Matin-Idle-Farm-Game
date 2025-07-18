#include "Plot.h"
#include <sstream>

using namespace std;

string intToTime(int totalSeconds){
    string output;

    int days = totalSeconds / (3600*24);
    if (days > 0) {output += to_string(days) + " days, ";}

    int hours = totalSeconds % (3600*24)/3600;
    if (hours <= 9) {output += '0' + to_string(hours) + ':';}
    else{output += to_string(hours) + ':';}

    int minutes = (totalSeconds % 3600)/60;
    if (minutes <= 9) {output += '0' + to_string(minutes) + ':';}
    else{output += to_string(minutes) + ':';}

    int seconds = totalSeconds % 60;
    if (seconds <= 9) {output += '0' + to_string(seconds);}
    else{output += to_string(seconds);}
    
    return output;
}

Plot::Plot(){
    crop = new Crop *[1];
    crop[0] = nullptr;
    plantTime = 0;
}

void Plot::get_saved(string fileName, int plotNumber){
    ifstream userFarm(fileName);
    if (!userFarm) return;

    string line;
    // Skip to the correct line
    for (int i = 0; i <= plotNumber; i++) {
        if (!getline(userFarm, line)) return; // Not enough lines
    }

    // Now parse the line
    // Example line: "1700000000,Wheat,0" or ",,"
    stringstream ss(line);
    string plantTimeStr, cropNameStr, phaseStr;

    getline(ss, plantTimeStr, ',');
    getline(ss, cropNameStr, ',');
    getline(ss, phaseStr, ',');

    // Reset plot
    if (crop[0]) { delete crop[0]; crop[0] = nullptr; }
    plantTime = 0;

    if (!plantTimeStr.empty()) {
        plantTime = static_cast<time_t>(stoull(plantTimeStr));
    }

    if (cropNameStr == "Wheat") {
        crop[0] = new Wheat();
    } else if (cropNameStr == "Apple") {
        int phase = 0;
        if (!phaseStr.empty()) phase = stoi(phaseStr);
        crop[0] = new Apple(phase);
    }
}

void Plot::get_info(string &cropName, string &phase, string &timeLeft){ //Only for UI graphics, this does not intervene with data
    if (crop[0] == nullptr){
        cropName = "(Empty)";
        phase = "";
        timeLeft = "";
    }
    else {
        cropName = this->crop[0]->get_cropName();
        switch(this->crop[0]->get_phase()){
            case -1:
                phase = "";
                break;
            case 0:
                phase = "(Juvenile) ";
                break;
            case 1:
                phase = "(Mature) ";
                break;
        };
        int timePassed = time(nullptr) - plantTime;
        int growTime = crop[0]->get_growTime();
        if (timePassed < growTime){
            timeLeft = "(" + intToTime(growTime - timePassed) + ")";
        }
        else {timeLeft = "(Ready)";}
    }
    
    
    
}

int Plot::Plant(string cropName, Player &username, int plotNumber){
    if (crop[0] != nullptr){return 0;}
    Crop *selectedCrop = nullptr;
    if (cropName == "Wheat"){
        selectedCrop = new Wheat();
    }
    else if (cropName == "Apple"){
        selectedCrop = new Apple(0);
    }

    int initialCost = selectedCrop->get_initialCost();
    if (username.get_balance() < initialCost){
        delete selectedCrop;
        return -1; // not enough money
    }
    else {
        username.subtractMoney(initialCost);
        crop[0] = selectedCrop;
        plantTime = time(nullptr);
        save(username, plotNumber);
        return 1;
    }

}

void Plot::save(Player &user, int plotNumber){
    
    string filename = user.get_username() + "Farm.txt"; // Find file name
    int farmSize = user.get_farm_size(); // Get farmSize from Player
    string *data = new string[farmSize]; // A buffer for file data

    

    ifstream file(filename); // Open file to read
    
    for (int i = 0; i < farmSize; i++){
        if (i == plotNumber){
            getline(file, data[i]); // Read but do nothing, to proceed the cursor
            if (crop[0] == nullptr) { // Save Empty plots
                data[i] = ",,";
            }
            else { // Save non-Empty plots
                data[i] = to_string(plantTime) + ',' + crop[0]->get_cropName() + ',' + to_string(crop[0]->get_phase());
            }
            
        }
        else {
            getline(file, data[i]); // get data into the buffer
        } 
    }
    file.close();    

    

    ofstream out(filename);
    for (int i = 0; i < farmSize; i++){
        out << data[i] << "\n"; //Write data
    }
    out.close();

}

int Plot::Harvest(Player &player, int plotNumber){
    if (crop[0] == nullptr){return 0;}
    else{
        int timeLeft = crop[0]->get_growTime() - time(nullptr) + plantTime;
        if (timeLeft > 0){return -1;}
        
        crop[0]->Harvest();
        player.addMoney(crop[0]->get_harvestProfit());

        if (crop[0]->get_isRemovedAtHarvest()){
            delete crop[0];
            crop[0] = nullptr;
        }
        else {
            plantTime = time(nullptr);
        }
        
        player.saveToFile();
        save(player, plotNumber);
        return 1;
    }
}

bool Plot::isFree(){
    return crop[0] == nullptr;
}