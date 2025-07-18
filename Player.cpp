#include "Player.h"

Player :: Player(){

}


Player :: Player(string name){
    username = name;
    balance = 1000.00; // Initailizing balance to 1000 so player can start off somewhere
    farm_sizes = 1;
}

Player :: ~Player(){

}

void Player :: addMoney(double amount){
    // Making sure the amount is positive
    if(amount > 0){
        balance += amount;
    } else {
        cout << "Amount must be positive." << endl;
    }
}

bool Player :: subtractMoney(double amount){

    // Checks if the amount is positive and if there are enough funds before subtracting.
    if(amount > 0 && balance > amount){
        balance -= amount;
        return true;
    } else {
        return false;
    }
}

void Player :: loadFromFile(){
    string filename = username + ".txt";
    // This create an input file stream object name infile. It tries to open the file name filename for reading
    ifstream infile(filename);

    // checking if the file exist
    if (!infile){
        cout << "Cout not open file :" << filename << endl;
        return;
    }

    // Reading line of text from the file and store that line into username;
    getline(infile,username);
    infile >> balance;
    infile >> farm_sizes;
    infile.close();
}

void Player :: saveToFile(){
    string filename = username + ".txt";
    ofstream outfile(filename); // open in append mode 

    // Check if the file exist
    if(!outfile){
        cout << "Could not open file: " << filename << endl;;
        return;
    }

    // if the file opened successfully, writes username and balance into the file.
    outfile << username <<endl;
    outfile << balance << endl;
    outfile << farm_sizes << endl;
    outfile.close();
}

bool Player :: isRegistered(){
    if(username.empty()){
        return false;
    }
    string filename = username + ".txt";
    ifstream infile(filename);
    return infile.good(); // return true if the file exist
}

bool Player :: registerUsername(const string& name){
    if(name.empty()){
        return false; // name cannot be empty
    }

    username = name; // set username if not already taken

    if(isRegistered()){   
        username.clear(); // Reset the username if already taken
        return false;
    }

    return true;
}

// Implement getter
double Player :: get_balance(){
    return balance; 
}

string Player :: get_username(){
    return username;
}

int Player :: get_farm_size(){
    return farm_sizes;
}



// Implement setter
void Player :: set_balance(double amount){
    balance = amount;
}

void Player :: set_username(string name){
    username = name;
}

void Player :: set_farm_size(int size){
    farm_sizes = size;
}

bool Player::upgrade_farm(){
    if(subtractMoney(1000)){
        farm_sizes += 1;
        saveToFile();
        return true;
    }
    return false;
}