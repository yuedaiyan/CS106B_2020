#include <iostream>
#include "vector.h"
#include "testing/SimpleTest.h"

using namespace std;

struct juror {
    string name;
    int bias;
};

void displayJury(Vector<juror>& jury) {
    for (juror j: jury) {
        cout << "(" << j.name << " " << j.bias << ") ";
    }
    cout << endl;
}

void findAllUnbiasedJuriesHelp(Vector<juror>& allCandidates, Vector<juror>& chosen, int biasSum, int index) {
    // base case
    if (index == allCandidates.size()) {
        if (biasSum == 0) {
            cout << "Matching: ";
            displayJury(chosen);
        } else {
            cout << "   Not match: ";
            displayJury(chosen);
            return;
        }
    }
    // else case
    else {
        juror curr = allCandidates.get(index);
        int currBias = curr.bias;
        // not have curr
        findAllUnbiasedJuriesHelp(allCandidates, chosen, biasSum, index + 1);
        // have curr
        chosen.insert(0, curr);
        biasSum += currBias;
        findAllUnbiasedJuriesHelp(allCandidates, chosen, biasSum, index + 1);
        // reset
        biasSum -= currBias;
        chosen.remove(0);
    }
}

void findAllUnbiasedJuries(Vector<juror>& allCandidates) {
    Vector<juror> chosen;
    findAllUnbiasedJuriesHelp(allCandidates, chosen, 0, 0);
}

PROVIDED_TEST("Show jury selection process") {
    cout << endl;
    Vector<juror> allCandidates = {{"Nick", -3}, {"Kylie", 3}, {"Trip", 0}};
    findAllUnbiasedJuries(allCandidates);
}
