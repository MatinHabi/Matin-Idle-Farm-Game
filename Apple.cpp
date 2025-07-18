#include "Apple.h"
#include <random>
#include <algorithm>
#include <limits>
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;

// Portable getch() replacement for Unix-like systems
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}



Apple::Apple(int phase){
    name = "Apple";
    initialCost = 100;
    harvestProfit = 200;
    juvenileGrowTime = 30;
    matureGrowTime = 15;
    this->phase = phase;
}

double Apple::HarvestMinigame(){
    string chosen_interface[3][3]; // The chosen string interface which contains _ for unchosen position and X for chosen
    bool chosen[3][3]; // The chosen bool memory for easy comparison
    int chosen_count = 0; // Number of chosen positions

    
    for (int i = 0; i < 3; i++){ // Initialise values for these arrays
        for (int j = 0; j < 3; j++){
            chosen_interface[i][j] = "_";
            chosen[i][j] = false;
        }
    }

    int x = 0; // Coordinate of the user's cursor
    int y = 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    tcflush(STDIN_FILENO, TCIFLUSH);
    while (chosen_count < 5){ // Choosing
        cout << "\033[2J\033[H";
        cout << "Picking Apple" << endl;
        cout << "There are 5 hidden apples! Use arrows to move between positions, press Enter to choose" << endl;
        cout << "Alternative control: WASD" << endl;
        cout << " _ _ _" << endl;
        for (int i = 0; i < 3; i++){
            cout << "|";
            for (int j = 0; j < 3; j++){ // Loop through positions and show where the cursor is by changing background color to red
                if (i == y && j == x){
                    cout << "\033[41m" << chosen_interface[i][j] << "|" << "\033[0m"; // Change to red if the cursor is there
                }
                else {
                    cout << chosen_interface[i][j] << "|";
                }
            }
            cout << endl;
        }

        int ch = getch();
        if (ch == 27) { // Arrow keys (Linux)
            if (getch() == 91) {
                int arrow = getch();
                switch (arrow) {
                    case 'A': if (y > 0) y -= 1; break; // Up
                    case 'B': if (y < 2) y += 1; break; // Down
                    case 'C': if (x < 2) x += 1; break; // Right
                    case 'D': if (x > 0) x -= 1; break; // Left
                }
            }
        }
        else if(ch == 10){ // Enter key (Linux)
            if(!chosen[y][x]){
                chosen_interface[y][x] = "X";
                chosen[y][x] = true;
                chosen_count += 1;
            }
        }
        else{
            switch (ch){
                case 'W': case 'w': if (y > 0) y -= 1; break;
                case 'S': case 's': if (y < 2) y += 1; break;
                case 'D': case 'd': if (x < 2) x += 1; break;
                case 'A': case 'a': if (x > 0) x -= 1; break;
                default: break;
            }
        }
    }
    
    bool result[3][3]; // Respective result

    // Initialize all positions to false
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result[i][j] = false;

    // Randomly choose 5 unique positions for apples
    int numbers[9] = {0,1,2,3,4,5,6,7,8}; 
    random_device rd;
    mt19937 gen(rd());
    shuffle(begin(numbers), end(numbers), gen);
    for (int k = 0; k < 5; k++) {
        int idx = numbers[k];
        int i = idx / 3;
        int j = idx % 3;
        result[i][j] = true;
    }

    int correct = 0;
    string cin_string;
    // Show the player the correct position and claim reward
    cout << "\033[2J\033[H";
    cout << " _ _ _" << endl;
    for (int i = 0; i < 3; i++){
        cout << "|";
        for (int j = 0; j < 3; j++){
            if (chosen[i][j] && result[i][j]) correct += 1; //Claim rewards
            if (result[i][j]){ // Make the reward position green
                cout << "\033[32m" << chosen_interface[i][j] << "|" << "\033[0m";
            }
            else {
                cout << chosen_interface[i][j] << "|";
            }
            
        }
        cout << endl;
    }
    cout << "Correctly chosen: " << correct << endl;
    cout << "Yield boost: " << correct * 10 << "%";
    cout << "\nPress any button to continue:\n";
    cin >> cin_string;
    return correct;
}

std::string Apple::get_type(){
    return "Perennial";
}