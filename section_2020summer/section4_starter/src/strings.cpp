/*
 * CS106B Section Handout Test Harness: Section 8
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
#include "strlib.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "vector.h"
#include <iostream>
#include <string>
using namespace std;

/*
 * String Review (Code Writing)
 * --------------------------------------------------------
 * Write a function that reverses a string “in-place.” That is,
 * you should take the string to reverse as a reference parameter
 * and modify it so that it ends up holding its reverse. Your
 * function should use only O(1) auxiliary space.
 *
 * Then, imagine you have a string containing a bunch of words
 * from a sentence.Here’s a nifty little algorithm for reversing
 * the order of the words in the sentence: reverse each individual
 * string in the sentence, then reverse the entire resulting
 * string. (Try it – it works!) Go and code a function that
 * accomplishes this task and uses only O(1) auxiliary storage space.
 */

void reverseInPlaceOneHalfNSpace(string& str) {
    // cerr << "before: " << str << "   size: " << str.size() << endl;
    if (str.size() <= 1) {
        return;
    }
    char left = str[0];
    char right = str[str.size() - 1];
    str = str.substr(1, str.size() - 2);
    reverseInPlaceOneHalfNSpace(str);
    str.insert(0, 1, right);
    str.insert(str.size(), 1, left);
    // cerr << "after: " << str << "   size: " << str.size() << endl;
}

void reverseWordOrderingInOneHalfNSpace(string& sentence) {
    // base case: no space
    if (sentence.find(' ') == string::npos) {
        return;
    }

    // base case: one space
    if (sentence.find(' ') == sentence.rfind(' ')) {
        int space = sentence.find(' ');
        string left = sentence.substr(0, space);
        string right = sentence.substr(space + 1);
        sentence = right + ' ' + left;
        return;
    }

    // recursive case: two of more space
    int leftSpace = sentence.find(' ');
    int rightSpace = sentence.rfind(' ');
    string left = sentence.substr(0, leftSpace);
    string right = sentence.substr(rightSpace + 1);
    int len = sentence.length() - (left.length() + 1) - (right.length() + 1);
    sentence = sentence.substr(leftSpace + 1, len);
    reverseWordOrderingInOneHalfNSpace(sentence);
    sentence = right + ' ' + sentence + ' ' + left;
    return;
}

void reverseInPlace(string& str) {
    for (int i = 0; i < str.length() / 2; i++) {
        char left = str[i];
        char right = str[str.length() - 1 - i];
        str[i] = right;
        str[str.length() - 1 - i] = left;
    }
    return;
}

void reverseWordOrderingInHelp(string& sentence, int start, int end) {
    cerr << "Help() start!" << endl;
    while (start < end) {
        char left = sentence[start];
        char right = sentence[end];

        sentence[start] = right;
        sentence[end] = left;

        start++;
        end--;
    }
    cerr << "Help() end!" << endl;
    return;
}

void reverseWordOrderingIn(string& sentence) {
    cout << endl;
    reverseInPlace(sentence);
    int start = 0;
    for (int end = start; end < sentence.length(); end++) {
        cerr << "start: " << start << "   end: " << end << "    before: " << sentence << "      curr: " << sentence[end] << endl;
        if (sentence[end] == ' ') {
            reverseWordOrderingInHelp(sentence, start, end - 1);
            start = end + 1;
        }
        cerr << "start: " << start << "   end: " << end << "    after : " << sentence << endl;
    }
    reverseWordOrderingInHelp(sentence, start, sentence.length() - 1);
    cerr << "start: " << start << "    return : " << sentence << endl;
    return;
}

void learn_1() {
    string str = "hello";
    string subStr = str.substr(1, str.size() - 2);
    cout << endl;
    cerr << subStr << endl;
}

STUDENT_TEST("Learn: ") {
    // learn_1();
    EXPECT(true);
}

PROVIDED_TEST("Simple Tests of Reverse String") {
    string s = "Hello, World!";
    string soln = "!dlroW ,olleH";
    reverseInPlace(s);
    EXPECT_EQUAL(s, soln);

    s = "";
    soln = "";
    reverseInPlace(s);
    EXPECT_EQUAL(s, soln);

    s = "I";
    soln = "I";
    reverseInPlace(s);
    EXPECT_EQUAL(s, soln);
}

PROVIDED_TEST("Simple Tests of Reverse Sentence") {
    string s = "Hello, World!";
    string soln = "World! Hello,";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);

    s = "Congrats on finishing CS106B";
    soln = "CS106B finishing on Congrats";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);

    s = "";
    soln = "";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);

    s = "I";
    soln = "I";
    reverseWordOrderingIn(s);
    EXPECT_EQUAL(s, soln);
}

PROVIDED_TEST("Simple Tests of Reverse String for OneHalfNSpace() ") {
    string s = "Hello, World!";
    string soln = "!dlroW ,olleH";
    reverseInPlaceOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);

    s = "";
    soln = "";
    reverseInPlaceOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);

    s = "I";
    soln = "I";
    reverseInPlaceOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);
}

PROVIDED_TEST("Simple Tests of Reverse Sentence for OneHalfNSpace() ") {
    string s = "Hello, World!";
    string soln = "World! Hello,";
    reverseWordOrderingInOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);

    s = "Congrats on finishing CS106B";
    soln = "CS106B finishing on Congrats";
    reverseWordOrderingInOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);

    s = "";
    soln = "";
    reverseWordOrderingInOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);

    s = "I";
    soln = "I";
    reverseWordOrderingInOneHalfNSpace(s);
    EXPECT_EQUAL(s, soln);
}
