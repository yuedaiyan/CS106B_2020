#include "cs106lib.h"

int countPaths(int street, int avenue) {
    // base case
    if (street == 1 || avenue == 1) {
        return 1;
    }
    // recursive case
    else {
        return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
    }
}

STUDENT_TEST("countPaths test: ") {
    int k = countPaths(2, 3);
    EXPECT_EQUAL(k, 3);
}