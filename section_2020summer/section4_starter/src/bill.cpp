/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "error.h"
#include "map.h"
#include "set.h"
#include "testing/SimpleTest.h"
#include "testing/TestDriver.h"
#include "testing/TextUtils.h"
#include <iostream>
using namespace std;

/*
 * Splitting the Bill (Code Writing)
 * --------------------------------------------------------
 * Your task is to write a function that takes as input a
 * total amount of money to pay (in dollars) and a set of
 * all the people who ordered something, then lists off every
 * possible way you could split the bill, assuming everyone
 * pays a whole number of dollars.
 */

void listPossiblePaymentsHelp(int total, Set<string>& remainPeople, Map<string, int>& payments) {
    // base case
    if (remainPeople.size() == 1) {
        payments[remainPeople.first()] = total;
        cout << payments.toString() << endl;
        return;
    }

    // recursive case
    string currPeople = remainPeople.first();
    remainPeople -= currPeople;
    for (int pay = 0; pay <= total; pay++) {
        payments[currPeople] = pay;
        listPossiblePaymentsHelp(total - pay, remainPeople, payments);
        payments.remove(currPeople);
    }
    remainPeople += currPeople;
    return;
}

void listPossiblePayments(int total, Set<string>& people) {
    cout << endl;
    if (total < 0) {
        error("total is negtive.");
    }
    if (people.size() <= 1) {
        error("people is empty");
    }

    Map<string, int> payments = { };
    listPossiblePaymentsHelp(total, people, payments);
    return;
}

void bill_learn_1() {
    Map<string, int> map = { { "aa", 1 }, { "bb", 2 }, { "cc", 3 } };
    cout << endl;
    cout << map.toString() << endl;
    cout << map.front() << endl;
    cout << map.back() << endl;
    cout << endl;
    map.put("aa", map.get("aa") + 1);
    cout << map.toString() << endl;
    map.put("aa", map.get("aa") - 1);
    cout << map.toString() << endl;
}

STUDENT_TEST("Learn: ") {
    bill_learn_1();
    EXPECT(true);
}

/* * * * * Provided Tests Below This Point * * * * */

// This test macro allows you to see the text output from a program
// that print results to the screen

MANUAL_TEST("Provided Test: Examples from handout.") {
    Set<string> people = { "A", "B", "C" };
    listPossiblePayments(4, people);
}