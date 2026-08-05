#include <iostream>
#include "set.h"

using namespace std;

void listSubsetsHelp(Set<string>& remaning, Set<string>& chosen) {
    if (remaning.isEmpty()) {
        cout << chosen.toString() << endl;
    } else {
        string curr = remaning.first();
        remaning.remove(curr);

        // not include curr
        listSubsetsHelp(remaning, chosen);

        // include curr
        chosen.add(curr);
        listSubsetsHelp(remaning, chosen);

        // reset
        remaning.add(curr);
        chosen.remove(curr);
    }
}

void listSubsets(Set<string>& choices) {
    Set<string> chosen;
    listSubsetsHelp(choices, chosen);
}
