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

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "testing/TestDriver.h"
#include "error.h"
#include "set.h"
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

void listPossiblePayments(int total, Set<string>& people) {
    // TODO: Your code here
}


/* * * * * Provided Tests Below This Point * * * * */

// This test macro allows you to see the text output from a program
// that print results to the screen

MANUAL_TEST("Provided Test: Examples from handout.") {
    Set<string> people = {"A", "B", "C"};
    listPossiblePayments(4, people);
}

