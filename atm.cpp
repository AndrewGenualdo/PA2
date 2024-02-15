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


#include <iostream>
#include <fstream>
#include "atm.h"

using namespace std;


/*     Pre: None
 *    Post: users[MAX_USERS] will be populated with all users listed in accounts.pa2
 * Purpose: Load the customer's accounts into memory
 ***********************************************************************************************************/
void ATM::loadAccounts()
{
    ifstream userListStream(FILE_USER_LIST);
    int user = 0;
    if (userListStream.is_open())
    {
        while (!userListStream.eof() && user < MAX_USERS)
        {
            getline(userListStream, users[user].mAccountNumber);
            user++;
        }
    }
    else
    {
        cout << "No account list file found!" << endl;
        userCount = FILE_NOT_FOUND;
        return;
    }
    userListStream.close();
    //it counts 1 extra user every time
    user--;

    for (int i = 0; i < user; i++)
    {
        ifstream userStream(FILE_DATA_FOLDER + users[i].mAccountNumber + FILE_TYPE);
        if (userStream.is_open())
        {
            //it's ok to mix them here since it only breaks if getline() is after
            getline(userStream, users[i].mName);
            getline(userStream, users[i].mSSN);
            userStream >> users[i].mPassword;
            userStream >> users[i].mPin;
            userStream >> users[i].mBalance;
        }
        else
        {
            cout << "Failed to open user file: '" << FILE_DATA_FOLDER << users[i].mAccountNumber << FILE_TYPE << "'!"
                 << endl;
            cout << "User #" << i << endl;
        }
        userStream.close();
    }
    cout << "Loaded " << user << " users!" << endl;
    userCount = user;
}

/*     Pre: None
 *    Post: admins[MAX_ADMINS] will be populated with admin accounts from admins.pa2
 * Purpose: Load the admin accounts into memory
 ***********************************************************************************************************/
void ATM::loadAdmins()
{
    ifstream adminStream(FILE_ADMIN_LIST);
    int i = 0;
    if (adminStream.is_open())
    {
        while (!adminStream.eof() && i < MAX_ADMINS)
        {
            adminStream >> admins[i].mID;
            adminStream >> admins[i].mPin;
            i++;
        }
    }
    else
    {
        cout << "No admin list file found!" << endl;
        userCount = FILE_NOT_FOUND;
        return;
    }
    adminStream.close();
    cout << "Loaded " << i << " admins!" << endl;
    adminCount = i;
}

/*     Pre: None
 *    Post: balance will be loaded from balance.pa2
 * Purpose: Load the ATM balance into memory
 ***********************************************************************************************************/
void ATM::loadBalance()
{
    ifstream balanceStream(FILE_BALANCE);
    if (balanceStream.is_open())
    {
        balanceStream >> balance;
        balanceStream.close();
        cout << "ATM balance has been loaded at $" << balance << "!" << endl;
    }
    else
    {
        balance = STARTING_BALANCE;
        balanceStream.close();
        cout << "ATM balance file could not be found! Balance is now $" << balance << "!" << endl;
        saveBalance();
    }
}

/*     Pre: Customer accounts must be loaded
 *    Post: data/accountId.pa2 will be saved with the data from memory
 * Purpose: Save an account to file
 ***********************************************************************************************************/
void ATM::saveAccount(const Account &account)
{
    ofstream accountStream(FILE_DATA_FOLDER + account.mAccountNumber + FILE_TYPE);
    if (accountStream.is_open())
    {
        accountStream.setf(ios::fixed | ios::showpoint);
        accountStream.precision(2);
        accountStream << account.mName << endl
                      << account.mSSN << endl
                      << account.mPassword << " " << account.mPin << " " << account.mBalance << endl;
    }
    else
    {
        cout << "Failed to save account '" << account.mName << "'!" << endl;
    }

    accountStream.close();
}

/*     Pre: Admin accounts must be loaded
 *    Post: data/admins.pa2 will be saved with all admin login information from memory
 * Purpose: Save the admins login information to file
 ***********************************************************************************************************/
void ATM::saveAdmins()
{
    ofstream adminStream(FILE_ADMIN_LIST);
    if (adminStream.is_open())
    {
        for (int i = 0; i < adminCount; i++)
        {
            adminStream << admins[i].mID << " " << admins[i].mPin << endl;
        }
    }
    else
    {
        cout << "Failed to save admin accounts!" << endl;
    }
    adminStream.close();
}

/*     Pre: Admin accounts must be loaded
 *    Post: data/balance.pa2 will be saved with the balance in memory
 * Purpose: Save the balance to file
 ***********************************************************************************************************/
void ATM::saveBalance()
{
    ofstream balanceStream(FILE_BALANCE);
    if (balanceStream.is_open())
    {
        balanceStream.setf(ios::fixed | ios::showpoint);
        balanceStream.precision(2);
        balanceStream << balance << endl;
    }
    balanceStream.close();
}

/*     Pre: Admin accounts must be loaded and an admin must be signed in
 *    Post: data/admins.pa2 will be updated with the logged-in admin's new pin
 * Purpose: Allow admins to change their pin with console input
 ***********************************************************************************************************/
int ATM::stateAdminChangePin(int &account)
{
    cout << "[ADMIN] Please enter your current pin:" << endl << ">";
    string oldPin;
    getline(cin, oldPin);
    if (admins[account].mPin == oldPin)
    {
        cout << "[ADMIN] Please enter your new pin:" << endl << ">";
        string newPin;
        getline(cin, newPin);
        admins[account].mPin = newPin;
        saveAdmins();
        cout << "[ADMIN] Your new pin has been saved as '" << newPin << "'!" << endl;
    }
    else
    {
        cout << "[ADMIN] Invalid pin!" << endl;
    }
    return STATE_ADMIN_CHOOSE;
}

/*     Pre: Admin accounts must be loaded and an admin must be signed in
 *    Post: None
 * Purpose: Print the ATM's cash balance to the console
 ***********************************************************************************************************/
int ATM::stateAdminCheckCash()
{
    cout << "[ADMIN] This ATM currently has $" << balance << "!" << endl;
    return STATE_ADMIN_CHOOSE;
}

/*     Pre: Admin accounts must be loaded and an admin must be signed in
 *    Post: state will hold the admins destination based on their input
 * Purpose: Allow the admin to navigate to different functions of the ATM
 ***********************************************************************************************************/
int ATM::stateAdminChoose()
{
    cout << "[ADMIN] Please choose from the following options:" << endl
         << " 'reset' - Resets the ATM's balance back to $" << STARTING_BALANCE << endl
         << " 'cash' - Check the ATM's balance" << endl
         << " 'pin' - Change your pin to a new one" << endl
         << " 'logout' - Log out from your account" << endl
         << " 'shutdown' - Shut down the ATM" << endl
         << ">";
    string choice;
    getline(cin, choice);
    if (choice == "reset")
        return STATE_ADMIN_RESET;
    else if (choice == "cash")
        return STATE_ADMIN_CHECK_CASH;
    else if (choice == "pin")
        return STATE_ADMIN_CHANGE_PIN;
    else if (choice == "logout")
        return STATE_ADMIN_LOGOUT;
    else if (choice == "shutdown")
        return STATE_ADMIN_SHUTDOWN;
    else
        cout << "Invalid choice!" << endl;
    return STATE_ADMIN_CHOOSE;
}

/*     Pre: Admin accounts must be loaded
 *    Post: account will have the selected admin account
 * Purpose: Allow an admin to enter their ID
 ***********************************************************************************************************/
int ATM::stateAdminLoginId(int &account)
{
    cout << "[ADMIN] Please enter your ID or type 'cancel' to cancel:" << endl << ">";
    string userId;
    getline(cin, userId);
    if (userId == "cancel")
    {
        return STATE_GENERAL_LOGIN_ID;
    }
    else
    {
        account = ACCOUNT_NOT_FOUND;
        for (int i = 0; i < adminCount; i++)
        {
            if (admins[i].mID == userId)
            {
                account = i;
                break;
            }
        }

        if (account != ACCOUNT_NOT_FOUND)
        {
            return STATE_ADMIN_LOGIN_PIN;
        }
        else
        {
            cout << "[ADMIN] Invalid user ID!" << endl;
        }
    }
    return STATE_ADMIN_LOGIN_ID;
}

/*     Pre: Admin accounts must be loaded, and they must have entered their ID.
 *    Post: if password is correct, admin will proceed to choice menu, otherwise, back to enter admin ID menu
 * Purpose: Allow the admin to enter their pin with the entered ID
 ***********************************************************************************************************/
int ATM::stateAdminLoginPin(int &account)
{
    cout << "[ADMIN] Please enter your pin:" << endl << ">";
    string pin;
    getline(cin, pin);
    if (pin == admins[account].mPin)
    {
        cout << "[ADMIN] Logged in successfully with ID '" << admins[account].mID << "'!" << endl;
        return STATE_ADMIN_CHOOSE;
    }
    else
    {
        cout << "[ADMIN] Invalid pin!" << endl;
        return STATE_ADMIN_LOGIN_ID;
    }
}

/*     Pre: Admin accounts must be loaded and an admin must be signed in
 *    Post: state will point to the general ID login menu
 * Purpose: Allow admins to logout
 ***********************************************************************************************************/
int ATM::stateAdminLogout(int &account)
{
    cout << "Logged out of admin account with ID: " << admins[account].mID << endl;
    return STATE_GENERAL_LOGIN_ID;
}

/*     Pre: Admin accounts must be loaded and an admin must be signed in
 *    Post: balance will be reset to STARTING_BALANCE (100,000)
 * Purpose: Allow an admin to reset the ATM
 ***********************************************************************************************************/
int ATM::stateAdminReset()
{
    cout << "[ADMIN] Reset the ATM's balance to $" << STARTING_BALANCE << endl;
    balance = STARTING_BALANCE;
    saveBalance();
    return STATE_ADMIN_CHOOSE;
}


/*     Pre: Customer accounts must be loaded and an admin must be signed in
 *    Post: data/accountId.pa2 will be written to with the updated pin
 * Purpose: Allow a customer to update their pin
 ***********************************************************************************************************/
int ATM::stateGeneralChangePin(int &account)
{
    cout << "Please enter your current pin:" << endl << ">";
    string oldPin;
    getline(cin, oldPin);
    if (users[account].mPin == oldPin)
    {
        cout << "Please enter your new pin:" << endl << ">";
        string newPin;
        getline(cin, newPin);
        users[account].mPin = newPin;
        saveAccount(users[account]);
        cout << "Your new pin has been saved as '" << newPin << "'" << endl;
    }
    else
    {
        cout << "Invalid pin!" << endl;
    }
    return STATE_GENERAL_CHOOSE;
}

/*     Pre: Customer accounts must be loaded and a customer must be signed in
 *    Post: None
 * Purpose: Allow a customer to check their balance
 ***********************************************************************************************************/
int ATM::stateGeneralCheckBalance(int &account)
{
    cout << "You have a balance of $" << users[account].mBalance << endl;
    return STATE_GENERAL_CHOOSE;
}

/*     Pre: Customer accounts must be loaded and a customer must be signed in
 *    Post: state will be set to the entered function
 * Purpose: Allow a customer to navigate to different functions on the ATM
 ***********************************************************************************************************/
int ATM::stateGeneralChoose()
{
    cout << "Please choose from the following options:" << endl
         << " 'deposit' - Deposit money into your account" << endl
         << " 'withdraw' - Withdraw money from your account (max of $" << MAX_WITHDRAW << " per day)"
         << endl
         << " 'balance' - Check the balance of your account" << endl
         << " 'pin' - Change your current pin to a new one" << endl
         << " 'logout' - Log out of your account" << endl
         << ">";
    string choice;
    getline(cin, choice);
    if (choice == "deposit")
        return STATE_GENERAL_DEPOSIT;
    else if (choice == "withdraw")
        return STATE_GENERAL_WITHDRAW;
    else if (choice == "balance")
        return STATE_GENERAL_CHECK_BALANCE;
    else if (choice == "pin")
        return STATE_GENERAL_CHANGE_PIN;
    else if (choice == "logout")
        return STATE_GENERAL_LOGOUT;
    else
        cout << "Invalid choice!" << endl;
    return STATE_GENERAL_CHOOSE;
}

/*     Pre: Customer accounts must be loaded and a customer must be signed in
 *    Post: the customer's balance and the ATM balance will increase by the entered amount
 * Purpose: Allow the customer to deposit money into their account
 ***********************************************************************************************************/
int ATM::stateGeneralDeposit(int &account)
{
    cout << "Please enter the amount you wish to deposit (or type 'cancel' to cancel):" << endl << ">";
    string amount;
    getline(cin, amount);
    if (amount == "cancel")
    {
        return STATE_GENERAL_CHOOSE;
    }
    else
    {
        double value = stod(amount);
        if (value > 0)
        {
            users[account].mBalance += value;
            saveAccount(users[account]);

            balance += value;
            saveBalance();

            cout << "You have deposited $" << value << " into your account! You now have $"
                 << users[account].mBalance << "!" << endl;
            return STATE_GENERAL_CHOOSE;
        }
        else
        {
            cout << "Invalid amount!" << endl;
        }
    }
    return STATE_GENERAL_DEPOSIT;
}

/*     Pre: Customer accounts must be loaded
 *    Post: the desired account will be specified, and they will proceed to enter their pin
 * Purpose: Allow the customer to enter their ID
 ***********************************************************************************************************/
int ATM::stateGeneralLoginId(int &account)
{
    cout << "Please enter your ID: " << endl << ">";
    string userId;
    getline(cin, userId);
    if (userId == "admin login")
    {
        return STATE_ADMIN_LOGIN_ID;
    }
    else
    {
        account = ACCOUNT_NOT_FOUND;
        for (int i = 0; i < userCount; i++)
        {
            if (users[i].mAccountNumber == userId)
            {
                account = i;
                break;
            }
        }
        if (account != ACCOUNT_NOT_FOUND)
        {
            return STATE_GENERAL_LOGIN_PIN;
        }
        else
        {
            cout << "Invalid user ID!" << endl;
        }
    }
    return STATE_GENERAL_LOGIN_ID;
}

/*     Pre: Customer accounts must be loaded and a customer must have entered their ID.
 *    Post: state will be the customer choice menu
 * Purpose: Allow the customer to enter their pin to login
 ***********************************************************************************************************/
int ATM::stateGeneralLoginPin(int &account)
{
    cout << "Please enter your pin:" << endl << ">";
    string pin;
    getline(cin, pin);
    if (users[account].mPin == pin)
    {
        cout << "Logged in successfully as '" << users[account].mName << "'!" << endl;
        return STATE_GENERAL_CHOOSE;
    }
    else
    {
        cout << "Invalid pin!" << endl;
        return STATE_GENERAL_LOGIN_ID;
    }
}

/*     Pre: Customer accounts must be loaded and a customer must be signed in
 *    Post: state will be the customer login id menu
 * Purpose: Allow the customer to logout
 ***********************************************************************************************************/
int ATM::stateGeneralLogout(int &account)
{
    cout << "Logged out of account for '" << users[account].mName << "'!" << endl;
    return STATE_GENERAL_LOGIN_ID;
}

/*     Pre: Customer accounts must be loaded and a customer must be signed in
 *    Post: customer balance will be taken out, their daily withdrawn amount will be increased with the specified amount
 * Purpose: Allow the customer to withdraw money from their account
 ***********************************************************************************************************/
int ATM::stateGeneralWithdraw(int &account)
{
    cout << "Please enter the amount you wish to withdraw or type 'cancel' to cancel: " << endl
         << "Note: You can withdraw up to $" << (MAX_WITHDRAW - users[account].mWithdrawn) << " more today"
         << endl << ">";
    string amount;
    getline(cin, amount);
    if (amount == "cancel")
    {
        return STATE_GENERAL_CHOOSE;
    }
    else
    {
        double value = stod(amount);
        if (value < 0)
        {
            cout << "Invalid amount!" << endl;
        }
        else if (users[account].mWithdrawn + value > MAX_WITHDRAW)
        {
            cout << "You can't withdraw that much!" << endl;
        }
        else if (value > users[account].mBalance)
        {
            cout << "You don't have that much in your account!" << endl;
        }
        else if (value > balance)
        {
            cout << "The ATM does not have that much in it's balance!" << endl;
        }
        else
        {
            users[account].mWithdrawn += value;
            users[account].mBalance -= value;
            saveAccount(users[account]);
            balance -= value;
            saveBalance();
            cout << "You have withdrawn $" << value << " from your account. You have $"
                 << users[account].mBalance << " left!" << endl;
            return STATE_GENERAL_CHOOSE;
        }
    }
    return STATE_GENERAL_WITHDRAW;
}