#include "console.h"
#include "testing/SimpleTest.h"
#include <iostream>

using namespace std;

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    return 0;
}
