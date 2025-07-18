#ifndef Player_H
#define Player_H

#include <iostream>
#include <fstream>
using namespace std;

class Player
{
private:
    string username;
    double balance;
    int farm_sizes;
public:
    Player();
    Player(const string name);
    ~Player();

    // Functions
    void addMoney(double amount);
    bool subtractMoney(double amount);
    void saveToFile();
    void loadFromFile();
    bool registerUsername(const std::string& name);
    bool isRegistered();

    // Getter Functions
    double get_balance();
    string get_username();
    int get_farm_size();

    // Setter Functions
    void set_balance (double amount);
    void set_username (string name);
    void set_farm_size(int size);
    bool upgrade_farm();
};


#endif