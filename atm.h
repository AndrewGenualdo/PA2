/*
 * Author: Drew Genualdo
 * Class: CSI-240-04
 * Assignment: PA2
 * Date Assigned: Unknown
 * Due Date: Feb 16, 2024 @ 1pm
 *
 * Description:
 * An ATM with many customer and admin accounts that can manipulate data respectively
 *
 * Certification of Authenticity:
 * I certify that this is entirely my own work, except where I have given
 * fully-documented references to the work of others. I understand the definition and
 * consequences of plagiarism and acknowledge that the assessor of this assignment
 * may, for the purpose of the assessing this assignment:
 * - Reproduce this assignment and provide a copy to another member of academic staff;
 * and/or
 * - Communicate a copy of this assignment to a plagiarism checking service (which may
 * then retain a copy of this assignment on its database for the purpose of future plagiarism checking)
 */

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
const string FILE_BALANCE = FILE_DATA_FOLDER + "balance" + FILE_TYPE;

const int FILE_NOT_FOUND = -1;
const int ACCOUNT_NOT_FOUND = -1;

const int STATE_GENERAL_LOGIN_ID = 0;
const int STATE_GENERAL_LOGIN_PIN = 1;
const int STATE_GENERAL_CHOOSE = 2;
const int STATE_GENERAL_DEPOSIT = 3;
const int STATE_GENERAL_WITHDRAW = 4;
const int STATE_GENERAL_CHECK_BALANCE = 5;
const int STATE_GENERAL_CHANGE_PIN = 6;
const int STATE_GENERAL_LOGOUT = 7;
const int STATE_ADMIN_LOGIN_ID = 8;
const int STATE_ADMIN_LOGIN_PIN = 9;
const int STATE_ADMIN_CHOOSE = 10;
const int STATE_ADMIN_RESET = 11;
const int STATE_ADMIN_CHECK_CASH = 12;
const int STATE_ADMIN_CHANGE_PIN = 13;
const int STATE_ADMIN_LOGOUT = 14;
const int STATE_ADMIN_SHUTDOWN = 15;

class ATM
{
private:

    Account users[MAX_USERS];
    Admin admins[MAX_ADMINS];
    double balance;
    int userCount, adminCount;

    void loadAccounts();

    void loadAdmins();

    void loadBalance();


    void saveAccount(const Account &account);

    void saveAdmins();

    void saveBalance();


    int stateAdminChangePin(int &account);

    int stateAdminCheckCash();

    int stateAdminChoose();

    int stateAdminLoginId(int &account);

    int stateAdminLoginPin(int &account);

    int stateAdminLogout(int &account);

    int stateAdminReset();


    int stateGeneralChangePin(int &account);

    int stateGeneralCheckBalance(int &account);

    int stateGeneralChoose();

    int stateGeneralDeposit(int &account);

    int stateGeneralLoginId(int &account);

    int stateGeneralLoginPin(int &account);

    int stateGeneralLogout(int &account);

    int stateGeneralWithdraw(int &account);


public:
    ATM()
    {
        loadBalance();
        loadAccounts();
        loadAdmins();
        if (userCount == FILE_NOT_FOUND || adminCount == FILE_NOT_FOUND)
        {
            cout << "Startup files are missing!" << endl << "Shutting down..." << endl;
            return;
        }

        int account = ACCOUNT_NOT_FOUND;
        int state = STATE_GENERAL_LOGIN_ID;
        while (state != STATE_ADMIN_SHUTDOWN)
        {
            switch(state) {
                case STATE_GENERAL_LOGIN_ID: state = stateGeneralLoginId(account); break;
                case STATE_GENERAL_LOGIN_PIN: state = stateGeneralLoginPin(account); break;
                case STATE_GENERAL_CHOOSE: state = stateGeneralChoose(); break;
                case STATE_GENERAL_DEPOSIT: state = stateGeneralDeposit(account); break;
                case STATE_GENERAL_WITHDRAW: state = stateGeneralWithdraw(account); break;
                case STATE_GENERAL_CHECK_BALANCE: state = stateGeneralCheckBalance(account); break;
                case STATE_GENERAL_CHANGE_PIN: state = stateGeneralChangePin(account); break;
                case STATE_GENERAL_LOGOUT: state = stateGeneralLogout(account); break;
                case STATE_ADMIN_LOGIN_ID: state = stateAdminLoginId(account); break;
                case STATE_ADMIN_LOGIN_PIN: state = stateAdminLoginPin(account); break;
                case STATE_ADMIN_CHOOSE: state = stateAdminChoose(); break;
                case STATE_ADMIN_RESET: state = stateAdminReset(); break;
                case STATE_ADMIN_CHECK_CASH: state = stateAdminCheckCash(); break;
                case STATE_ADMIN_CHANGE_PIN: state = stateAdminChangePin(account); break;
                case STATE_ADMIN_LOGOUT: state = stateAdminLogout(account); break;
            }
        }
        cout << "Shutting down..." << endl;
    }
};

#endif //PA2_ATM_H
