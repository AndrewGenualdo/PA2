//
// Created by andrew.genualdo on 2/13/2024.
//

#ifndef PA2_ATM_H
#define PA2_ATM_H

#include "admin.h"
#include "account.h"

const int MAX_USERS = 2000;
const int MAX_ADMINS = 10;
const double STARTING_BALANCE = 100000.00;

const string FILE_DATA_FOLDER = "data/";
const string FILE_TYPE = ".pa2";
const string FILE_USER_LIST = FILE_DATA_FOLDER + "accounts" + FILE_TYPE;
const string FILE_ADMIN_LIST = FILE_DATA_FOLDER + "admins" + FILE_TYPE;
const string FILE_BALANCE = FILE_DATA_FOLDER+"balance"+FILE_TYPE;

const int STATE_GENERAL_LOGIN = 0;
const int STATE_GENERAL_DEPOSIT = 1;
const int STATE_GENERAL_CHECK_BALANCE = 2;
const int STATE_GENERAL_CHANGE_PIN = 3;

class ATM {
private:
    Account users[MAX_USERS];
    Admin admins[MAX_ADMINS];
    double balance;

    int loadAdmins();
    void loadBalance();
    int loadUsers();
    void saveBalance();

    public:
    ATM() {
        loadBalance();
        loadUsers();
        loadAdmins();
        saveBalance();
    }


};

#endif //PA2_ATM_H
