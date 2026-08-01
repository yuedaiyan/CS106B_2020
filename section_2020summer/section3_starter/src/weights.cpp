/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Trip Master and Nick
 * Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "error.h"
#include "vector.h"
using namespace std;

/*
 * Weights and Balances (Code Writing)
 * --------------------------------------------------------
 * Write a recursive function that determines whether it is
 * possible to measure out the desired target amount with a
 * given set of weights, which is stored in the vector
 * weights.
 */

bool isMeasurableHelp(int target, Vector<int> weights) {

    if (weights.isEmpty()) {
        return target == 0;
    } else {
        for (int i = 0; i < weights.size(); i++) {
            int curr = weights[i];
            Vector<int> newWeights = weights;
            newWeights.remove(i);
            if (isMeasurableHelp(target - curr, newWeights) || isMeasurableHelp(target + curr, newWeights) || isMeasurableHelp(target, newWeights)) {
                return true;
            }
        }
    }
    return false;
}

bool isMeasurable(int target, Vector<int>& weights) {
    weights.sort();
    return isMeasurableHelp(target, weights);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Simple Positive Example"){
    Vector<int> weights = {1, 3};
    EXPECT(isMeasurable(2, weights));
}

PROVIDED_TEST("Provided Test: Simple Negative Example"){
    Vector<int> weights = {1, 3};
    EXPECT(!isMeasurable(5, weights));
}

PROVIDED_TEST("Provided Test: Complex Positive Example"){
    Vector<int> weights = {1, 3, 7};
    EXPECT(isMeasurable(6, weights));
}
