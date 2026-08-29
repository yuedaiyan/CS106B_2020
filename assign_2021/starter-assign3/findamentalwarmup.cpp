/**
 * File: warmup.cpp
 * ----------------
 * This code is provided as part of an exercise to practice using a
 * debugger. This program has buggy use of recursion.
 */

#include <iostream>    // for cout, endl
#include "error.h"
#include "random.h"
#include "testing/SimpleTest.h"
using namespace std;

/* This is a recursive implementation of a function to calculate
 * factorials. This function works correctly for positive values
 * of n whose computed factorial value does not overflow the int
 * data type (n <= 12).
 *
 * As currently written, this function does not correctly handle
 * negative inputs.
 */
int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}


/* The myPower function computes exponentiation.
 * The call myPower(base, exp) returns base raised to the power exp.
 * Note that either/both of base and exp can be negative.
 * The calculation is done using type double to allow for the result
 * to have a fractional component, such as would be needed for
 * a negative exponent.
 */
double myPower(int base, int exp) {
    if (exp == 0) {         // handle zero exp
        return 1;
    }
    /*
    else if (base == 0) { // handle zero base
        return 0;
    }
    */
    else if (exp < 0) { // handle negative exp
        return 1.0 / myPower(base, -exp);
    }
    /*
    else if (base < 0) {  // handle negative base
        return -myPower(-base, exp);
    }
    */
    else { // both base and exp are positive
        return base * myPower(base, exp - 1);
    }
}

/* * * * * * Test Cases * * * * * */
PROVIDED_TEST("Confirm result of factorial(7)") {
    EXPECT_EQUAL(factorial(7), 7*6*5*4*3*2);
}

STUDENT_TEST("Student test of factorial(-1)") {
    /*
    int a = 0;
    while (true) {
        a += 1;
    }

    stack overflow error
    EXPECT_ERROR(factorial(-7));
    */
    EXPECT(true);
}

PROVIDED_TEST("myPower(), compare to library pow(), fixed inputs") {
    EXPECT_EQUAL(myPower(7, 0), pow(7, 0));
    EXPECT_EQUAL(myPower(10, 2), pow(10, 2));
    EXPECT_EQUAL(myPower(5, -1), pow(5, -1));
    EXPECT_EQUAL(myPower(-3, 3), pow(-3, 3));
}

PROVIDED_TEST("myPower(), generated inputs") {
    for (int base = 1; base < 25; base++) {
        for (int exp = 1; exp < 10; exp++) {
            EXPECT_EQUAL(myPower(base, exp), pow(base, exp));
        }
    }
}

STUDENT_TEST("base range[-10,11) of myPower()") {
    // cout << endl;
    for (int base = -10; base < 11; base++) {
        for (int exp = 1; exp < 10; exp++) {
            // cerr << "base: " << base << " exp: " << exp << " = " << myPower(base, exp) << " ( " << "correct pow(): " << pow(base, exp) << " ) " << endl;
            EXPECT_EQUAL(myPower(base, exp), pow(base, exp));
        }
    }
}

STUDENT_TEST("exp range[-10,11) myPower()") {
    for (int base = 1; base < 25; base++) {
        for (int exp = -10; exp < 11; exp++) {
            EXPECT_EQUAL(myPower(base, exp), pow(base, exp));
        }
    }
}