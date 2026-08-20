#include <iostream>
#include "console.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "RandomBag.h"
#include "BankAccount.h"

using namespace std;

/*
SPOTIFY PLAYLIST
1. Member variables:
    Vector‹strings> songs; double totalTime; string nameofPlaylist
2. Member functions:
    moveSong(string song, int location) --> moving song to new location;
    addSong(string song) --> add the song to the end of the playlist;
    removeSong (string song);
    playSong() --> iterates over your playlist;
    shuffle() --> randomly play songs from your playlist
3. Constructor:
    Creating the empty songs vector;
    define the playlist's name (default: Untitled X); set totalTime = 0;
*/

/*
BANK ACCOUNT
1. Member variables:
    int balance;
    string accountHolderName
2. Member functions:
    transfer (BankAccount sender, BankAccount receiver);
    deposit (int amount);
    withdraw(int amount)
3. Constructor:
    Initialize balance;
    define the account holder's name
*/

/* Prints out how many items are in the bag. Note that we have to mark the
 * RandomBag::size() member function const for this to work, since otherwise
 * C++ won't know that member function doesn't mutate the bag.
 */
void printBagSize(const RandomBag& bag) {
    cout << "The bag has " << bag.size () << " things in it." << endl;
}

void randomBagDemo() {
    /* Some sample code using the RandomBag. */
    RandomBag bag;
    for (int i = 0; i < 10; i++) {
        bag.add(i);
    }
    printBagSize(bag);
    while (!bag.isEmpty()) {
        cout << bag.removeRandom() << endl;
    }
}

struct BankAccountStruct {
    string name;
    double amount;
};

void bankDemoStructs(){
    cerr << endl;
    cerr << string(20, '-') << endl;
    BankAccountStruct nick = { "Nick", 100 };
    BankAccountStruct kylie = {"Kylie", 1000};
    /* Nick gets a paycheck and deposits it. */
    nick.amount += 500;
    /* Kylie buys a new dog stroller for Saki. */
    kylie.amount -= 900;
    /* Nick wants to travel to Costa Rica to hang out with sloths */
    nick.amount -= 2000;
    /* This is BAD! Nick doesn't have enough money to do this. */
    /* Nick wants to transfer some money to Kylie for lunch. */
    kylie.amount += 20;
    /* This is BAD! The money appeared out of nowhere! */
    /* Nick tries to commit identity fraud. */
    nick.name = "Kylie"; 
    /* This is BAD! We shouldn't be able to do this! */
    cout << nick.name << " " << nick.amount << endl;
    cout << kylie.name << " " << kylie.amount << endl;
    cerr << string(20, '-') << endl;
}

void bankDemoClasses(){
    cerr << endl;
    cerr << string(20, '-') << endl;
    BankAccount nick("Nick", 100);
    BankAccount kylie("Kylie", 1000);
    /* Nick gets his paycheck and deposits it. */
    nick.deposit(500);
    /* Kylie buys a new dog stroller for Saki. */
    kylie.withdraw(900);
    /* Nick wants to travel to Costa Rica to hang out with sloths. */
    // nick.withdraw(2000); // This now throws an error!
    /* Nick wants to transfer some money to Kylie for lunch. */
    nick.transfer(20, kylie);
    /* Nick tries to commit identity fraud. */
    // nick.name = "Kylie"; // This line won't compile!
    cout << nick.getName() << " " << nick.getAmount() << endl;
    cout << kylie.getName() << " " << kylie.getAmount() << endl;
    cerr << string(20, '-') << endl;
}

int main() {
    if (runSimpleTests(NO_TESTS)) {
        return 0;
    }
    bankDemoStructs();
    bankDemoClasses();

    // randomBagDemo();
    return 0;
}



