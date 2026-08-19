/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include <cctype>

using namespace std;

int main(){

    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    return 0;
}