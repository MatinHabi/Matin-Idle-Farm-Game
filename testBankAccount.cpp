#include "BankAccount.h"
#include <iostream>

int main(){
    Player p1("Gechhai");

    cout << p1.get_balance() << endl;

    p1.addMoney(50.0);
    cout << p1.get_balance() << endl;

    if(p1.subtractMoney(30.00)){
        cout << "Purchase successfully" << endl;
    } else {
        cout << "Insufficient funds" << endl;
    }

    // save state
    p1.saveToFile("bank_data.txt");

    // load state
    Player p2;
    p2.loadFromFile("bank_data.txt");
    cout << p2.get_username() << endl;
    cout << p2.get_balance() << endl;



}