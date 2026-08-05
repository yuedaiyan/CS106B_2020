#include <iostream>
#include "vector.h"
#include "testing/SimpleTest.h"

using namespace std;

struct juror {
    string name;
    int bias;
};

void displayJury(Vector<juror>& jury){
    for (juror j: jury) {
        cout << "(" << j.name << " " << j.bias << ") ";
    }
    cout << endl;
}

void findAllUnbiasedJuries(Vector<juror>& allCandidates) {
    /* TODO: Fill me in! */
}

PROVIDED_TEST("Show jury selection process") {
    cout << endl;
    Vector<juror> allCandidates = {{"Nick", -3}, {"Kylie", 3}, {"Trip", 0}};
    findAllUnbiasedJuries(allCandidates);
}
