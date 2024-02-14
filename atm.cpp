//
// Created by andrew.genualdo on 2/13/2024.
//
#include <iostream>
#include <fstream>
#include "atm.h"
using namespace std;

int ATM::loadUsers()
{
    ifstream userListStream(FILE_USER_LIST);
    int user = 0;
    if(userListStream.is_open()) {
        while(!userListStream.eof() && user < MAX_USERS) {
            getline(userListStream, users[user].mAccountNumber);
            user++;
        }
    }
    userListStream.close();
    //it counts 1 extra user every time
    user--;

    for(int i = 0; i < user; i++) {
        ifstream userStream(FILE_DATA_FOLDER + users[i].mAccountNumber + FILE_TYPE);
        if(userStream.is_open()) {
            getline(userStream, users[i].mName);
            getline(userStream, users[i].mSSN);
            userStream >> users[i].mPassword;
            userStream >> users[i].mPin;
            userStream >> users[i].mBalance;
        } else {
            cout << "Failed to open user file: '" << FILE_DATA_FOLDER << users[i].mAccountNumber << FILE_TYPE << "'!" << endl;
            cout << "User #" << i << endl;
        }
        userStream.close();
    }
    cout << "Loaded " << user << " users!" << endl;
    return user;
}


int ATM::loadAdmins()
{
    ifstream adminStream(FILE_ADMIN_LIST);
    int i=0;
    if(adminStream.is_open()) {
        while(!adminStream.eof() && i < MAX_ADMINS) {
            adminStream >> admins[i].mID;
            adminStream >> admins[i].mPin;
            i++;
        }
    }
    adminStream.close();
    cout << "Loaded " << i << " admins!" << endl;
    return i;
}

void ATM::loadBalance() {
    ifstream balanceStream(FILE_BALANCE);
    if(balanceStream.is_open()) {
        balanceStream >> balance;
        balanceStream.close();
        cout << "ATM balance has been loaded at $" << balance << "!" << endl;
    } else {
        balance = STARTING_BALANCE;
        balanceStream.close();
        cout << "ATM balance file could not be found! Balance is now $" << balance << "!" << endl;
        saveBalance();
    }
}

void ATM::saveBalance() {
    ofstream balanceStream(FILE_BALANCE);
    if(balanceStream.is_open()) {
        balanceStream.setf(ios::fixed | ios::showpoint);
        balanceStream.precision(2);
        balanceStream << balance << endl;
        cout << "ATM balance of $" << balance << " has been saved!" << endl;
    }
    balanceStream.close();
}
