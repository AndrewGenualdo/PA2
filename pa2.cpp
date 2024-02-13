#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

const string FILE_DATA_FOLDER = "data/";
const string FILE_TYPE = ".pa2";

const string FILE_USER_LIST = FILE_DATA_FOLDER + "accounts" + FILE_TYPE;
const string FILE_ADMIN_LIST = FILE_DATA_FOLDER + "admins" + FILE_TYPE;

const int STATE_GENERAL_LOGIN = 0;
const int STATE_GENERAL_DEPOSIT = 1;
const int STATE_GENERAL_CHECK_BALANCE = 2;
const int STATE_GENERAL_CHANGE_PIN = 3;

int loadUsers(Account users[MAX_USERS])
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
    return user;
}


int loadAdmins(Admin admins[MAX_ADMINS])
{
    ifstream adminStream(FILE_ADMIN_LIST);
    if(adminStream.is_open()) {

    }
    adminStream.close();
}

void login()
{

}

int main()
{
    Account users[MAX_USERS];
    Admin admins[MAX_ADMINS];

    int userCount = loadUsers(users);
    //int adminCount = loadAdmins(admins);
    cout << userCount << " users!" << endl;

    /*bool shutDown = false;
    string input;
    int state = 0;
    while (!shutDown)
    {
        getline(cin, input);

    }*/
    return 0;
}
