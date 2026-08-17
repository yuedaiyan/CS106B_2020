#include "BankAccount.h"
#include "error.h"
using namespace std;

BankAccount::BankAccount(string name, double amount){
    /* TODO: Fill in this method! */
}

void BankAccount::deposit(double depositAmount){
    /* TODO: Fill in this method! */
}

void BankAccount::withdraw(double withdrawlAmount){
    /* TODO: Fill in this method! */
}

void BankAccount::transfer(double transferAmount, BankAccount& recipient){
    /* TODO: Fill in this method! */
}


/* These methods can be marked const because they don't modify the
 * contents of the bank account.
 */

double BankAccount::getAmount() const {
    /* TODO: Fill in this method! */
    return 0.0;
}

string BankAccount::getName() const {
    /* TODO: Fill in this method! */
    return "";
}
