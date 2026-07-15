#include <iostream>
#include "console.h"
using namespace std;

void generateSequences(int length);
void generateSequencesHelper(int flipsLeft, string sofar);

void runSequencesDemo() {
    generateSequences(3);
}

void generateSequences(int length) {
    generateSequencesHelper(length, "");
}

void generateSequencesHelper(int flipsLeft, string sofar) {
    if (flipsLeft == 0) {
        cout << sofar << endl;
    } else {
        generateSequencesHelper(flipsLeft - 1, sofar + "H");
        generateSequencesHelper(flipsLeft - 1, sofar + "T");
    }
}