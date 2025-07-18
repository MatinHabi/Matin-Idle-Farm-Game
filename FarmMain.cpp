#include <iostream>
#include "Plot.h"
#include "BankAccount.h"
#include "Crop.h"
#include "AnnualCrop.h"
#include "PerennialCrop.h"
#include "Apple.h"
#include "Wheat.h"
#include <chrono>
#include <thread>
using namespace std;

// Use this to test the piece of code
// Version 1 features: 
// - Taking crop list from "Sevin.txt" and put it inside classes
// - Output the info for user to see
// - Everything is a blackbox - you do not need to know what happen, just make the UI like the following code
// Crop.cpp AnnualCrop.cpp PerennialCrop.cpp Apple.cpp Wheat.cpp Plot.cpp main.cpp BankAccount.cpp -std=c++11 -o a
// ./a
// Version 2 features:
// - Saving
// - Planting


int main(){
    //To start off, we need to get info for a player. I assume we have a Player, Sevin, with 2 plots.
    Player currentPlayer("Sevin"); // A random player with 1000$
    currentPlayer.set_farm_size(2);
    // With all info gotten, we should be able to initialise our farm

    Plot testPlot[currentPlayer.get_farm_size()]; // Our list of plots
    string *cropName = new string; // temp variables to update
    string *phase = new string;
    string *timeLeft = new string;
    
    // Now Sevin has played before. We need to get his info back. 
    for (int i = 0; i < 2; i++){
            testPlot[i].get_saved("SevinFarm.txt", i); // Get saved info. This take info inside files and then put it in each plots
    }
    // Now show him what he got:
    cout << "\033[2J\033[H";
    cout << "His previous run: " << endl << endl;
    for (int i = 0; i < 2; i++){           
            testPlot[i].get_info(*cropName, *phase, *timeLeft); // We use these temp var to store the info
            cout << "[Plot " << i+1 << "] " << *cropName << " " << *phase << *timeLeft << endl; // cout all info
        }
    cout << endl << "You see, he has [Plot 1] Empty. Let's plant something for him" << endl;
    cout << "Enter anything to continue the tutorial..." << endl;
    cin >> *cropName; // Just for waiting

    // Now it's boring to have one plot empty. Let's plant him a Wheat land.
    cout << "\033[2J\033[H";
    testPlot[0].Plant("Wheat", currentPlayer, 0); // <-- You see, the code is actually really simple, a one-line code
    cout << "His remaining Balance: " << currentPlayer.get_balance() << endl;
    cout << "Woa, his balance has been deducted 100$ as the cost of buying seeds" << endl << endl;
    cout << "Enter anything to continue the tutorial..." << endl;
    cin >> *cropName; // Just for waiting

    cout << "\033[2J\033[H";
    cout << "Now let's see the results: " << endl;
    for (int i = 0; i < 2; i++){           
            testPlot[i].get_info(*cropName, *phase, *timeLeft); // We use these temp var to store the info
            cout << "[Plot " << i+1 << "] " << *cropName << " " << *phase << *timeLeft << endl; // cout all info
        }
    cout << endl << "Now click on the SevinFarm.txt, we shall see a change in data as well, not only in this current run, but also in future runs as well";
    cout << endl << "You see, our functions are really peer-friendly LOL. Those who uses our code will feel easy, just look at these sample code lines:" << endl;
    cout << "\t testPlot[i].get_info(*cropName, *phase, *timeLeft);" << endl;
    cout << "\t testPlot[0].Plant(\"Wheat\", currentPlayer, 0);" << endl << endl;
    cout << endl << "Now, shall we observe the timer, some spare time for the Farmer" << endl;
    cout << "Enter anything to continue the tutorial..." << endl;
    cin >> *cropName; // Just for waiting

    while (true){
        cout << "\033[2J\033[H";
        for (int i = 0; i < 2; i++){           
            testPlot[i].get_info(*cropName, *phase, *timeLeft); // Output the info for the user to see. This includes cropName, phase, and time left before being able to harvest.

            cout << "[Plot " << i+1 << "] " << *cropName << " " << *phase << *timeLeft << endl; // cout all info
        }
        this_thread::sleep_for(chrono::seconds(1)); // Update the code every one second
    }
    
    
}