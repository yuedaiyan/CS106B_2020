/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */
#include "grid.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include <iostream>
using namespace std;
#include "filelib.h"
#include "strlib.h"
#include <cctype>
#include <string>

// #include <locale>

/*
 * Sum Numbers (Code Write)
 * ----------------------------------
 * Write a program to read through a given file and sum
 * all of the numbers in the file. You can assume that numbers
 * will be composed entirely of numerical digits, optionally
 * preceded by a single negative sign.
 */
bool isNumber(string str) {
    if (str.length() == 0)
        return false;

    if (str[0] == '-') {
        str.erase(0, 1);
    }

    for (char c : str) {
        // 含有非数字字符
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}

int sumNumbers(string filename){

    ifstream in;
    Vector<string> lins;

    if (openFile(in, filename)) {
        readEntireFile(in, lins);
    } else {
        return 0;
    }

    int result = 0;
    for (const string& line : lins) {
        Vector<string> strs = stringSplit(line, " ");
        for (const string& str : strs) {
            if (isNumber(str))
                result += stringToInteger(str);
        }
        return result;
    }
    return 0;
}

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("given file in handout"){
    EXPECT_EQUAL(sumNumbers("res/numbers.txt"), 42);
}

PROVIDED_TEST("Nonexistent file should sum to zero") {
    EXPECT_EQUAL(sumNumbers("nonexistent_filename"), 0);
}

