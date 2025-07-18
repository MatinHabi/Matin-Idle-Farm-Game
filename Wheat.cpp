#include "Wheat.h"
#include <string>

using namespace std;

Wheat::Wheat(){
    name = "Wheat";
    initialCost = 100;
    harvestProfit = 200;
    growTime = 10;
}




double Wheat::HarvestMinigame(){
    int count = 0;
    string temp;
    while (count < 25){
        cout << "\033[2J\033[H";
        cout << "Harvest Wheat\nPress Space 25 times to get a yield boost\n\nPressed " << count << " times" << endl;
        getline(cin, temp);
        count += 1;
    }
    cout << "\033[2J\033[H";
    cout << "Successfully harvested! You get 20% yield boost" << endl;
    cout << "Press Enter to continue...";
    getline(cin, temp);
    return 20;
}