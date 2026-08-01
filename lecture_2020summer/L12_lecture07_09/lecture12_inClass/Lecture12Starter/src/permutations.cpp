#include "vector.h"
#include "testing/SimpleTest.h"
#include "random.h"

using namespace std;

void listPermutationsHelper(string remaining, string soFar) {
    if (remaining == "") {
        // basid case
        cout << soFar << endl;
    } else {
        // recursive case
        for (int i = 0; i < remaining.length(); i++) {
            char curr = remaining[i];
            string rest = remaining.substr(0, i) + remaining.substr(i + 1);
            listPermutationsHelper(rest, soFar + curr);
        }
    }
}

void listPermutations(string s) {
    listPermutationsHelper(s, "");
}
