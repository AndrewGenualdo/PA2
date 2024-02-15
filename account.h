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

#ifndef PA2_ACCOUNT_H
#define PA2_ACCOUNT_H

#include <string>
using namespace std;

const double MAX_WITHDRAW = 3000.00;

struct Account {
    string mName,
           mSSN,
           mPassword,
           mPin,
           mAccountNumber;
    double mBalance,
           mWithdrawn;
};

#endif //PA2_ACCOUNT_H
