#include <iostream>
#include "set.h"
#include "console.h"
using namespace std;

Set<Set<string>> combinationsRec(Set<string>& remaining, int k, Set<string>& chosen) {
    /* Base Case: If we have filled up all the spots in our combination, then return a
     * set containing the combination we've built up. */
    if (k == 0) {
        return { chosen };
    }

    /* Base Case: If we have less items to choose from than spots to fill, then we
     * can't create any combinations.
     */
    if (remaining.size() < k) {
        return { };
    }

    /* Recursive Case: Select one item out of those that are remaining, and generate all
     * possible combinations both including and exlcuding that item. Then, the final return
     * value we produce is the union of those two sets of combinations.
     */
    string elem = remaining.first();
    remaining -= elem;

    Set<Set<string>> excludeElem = combinationsRec(remaining, k, chosen);

    chosen += elem;

    Set<Set<string>> includeElem = combinationsRec(remaining, k - 1, chosen);

    // reset
    chosen -= elem;
    remaining += elem;

    return excludeElem + includeElem;
}

Set<Set<string>> combinationsOf(Set<string>& elems, int k) {
    Set<string> combinationTracker;
    return combinationsRec(elems, k, combinationTracker);
}

// 主函数
void combinationsDemo() {
    Set<string> usSupremeCourt = {
        "Thomas",
        "Ginsburg",
        "Breyer",
        "Roberts",
        "Alito",
        "Sotomayor",
        "Kagan",
        "Gorsuch",
        "Kavanaugh"
    };

    Set<Set<string>> combinations = combinationsOf(usSupremeCourt, 5);
    cout << "There are " << combinations.size() << " combinations. They are: " << endl;
    for (const Set<string>& combination : combinations) {
        cout << combination << endl;
    }
}
