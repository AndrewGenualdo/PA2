//
// Created by andrew.genualdo on 2/13/2024.
//

#ifndef PA2_ACCOUNT_H
#define PA2_ACCOUNT_H

#include <string>
using namespace std;

const int MAX_USERS = 2000;

struct Account {
    string mName,
           mSSN,
           mPassword,
           mPin,
           mAccountNumber;
    double mBalance;
};

#endif //PA2_ACCOUNT_H
