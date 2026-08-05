#include "set.h"
#include "testing/SimpleTest.h"
#include <iostream>

using namespace std;

void listSubsetsHelp(Set<string>& choices, Set<string>& soFar) {
    if (choices.isEmpty()) {
        cout << soFar.toString() << endl;
    } else {
        string curr = choices.first();
        choices.remove(curr);

        // not include curr
        listSubsetsHelp(choices, soFar);

        // include curr
        soFar.add(curr);
        listSubsetsHelp(choices, soFar);

        // reset
        soFar.remove(curr);
        choices.add(curr);
    }
}

void listSubsets(Set<string>& choices) {
    Set<string> soFar;
    cout << endl;
    listSubsetsHelp(choices, soFar);
}

STUDENT_TEST("main(): ") {
    Set<string> trySet = { "a", "b", "c" };
    listSubsets(trySet);
}
