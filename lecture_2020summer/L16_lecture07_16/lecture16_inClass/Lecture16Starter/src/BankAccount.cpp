#include "BankAccount.h"
#include "error.h"
using namespace std;

BankAccount::BankAccount(string name, double amount){
    this->name = name;
    this->amount = amount;
}

void BankAccount::deposit(double depositAmount){
    if (depositAmount < 0) {
        error("Can's have negative money!");
    }
    amount += depositAmount;
}

void BankAccount::withdraw(double withdrawlAmount){
    if (withdrawlAmount < 0) {
        error("Can's have negative money!");
    }
    if (amount - withdrawlAmount < 0) {
        error("余额不足");
    }
    amount -= withdrawlAmount;
}

void BankAccount::transfer(double transferAmount, BankAccount& recipient){
    withdraw(transferAmount);
    recipient.deposit(transferAmount);
}


/* These methods can be marked const because they don't modify the
 * contents of the bank account.
 */

double BankAccount::getAmount() const {
    /* TODO: Fill in this method! */
    return amount;
}

string BankAccount::getName() const {
    /* TODO: Fill in this method! */
    return name;
}
