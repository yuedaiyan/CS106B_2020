/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include "testing/SimpleTest.h"
#include <iostream>
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0)
            cout << "." << flush; // progress bar
    }
    cout << endl
         << "Done searching up to " << stop << endl;
}

/* Replace this comment with a descriptive function
 * header comment.
 */
long smarterSum(long n) {
    long total = 0;
    // divisor * divisor < 0  → 这部分没有 <= 0, 这样可以自动规避 1 的问题.
    for (long divisor = 1; divisor * divisor < n; divisor++) {
        if (n % divisor == 0) {
            // 现将当前的因数放入结果中
            total += divisor;

            // 将本轮的因数的对应因数也计算进来(对应因数更大)
            long pair = n / divisor;
            if (pair > divisor && pair < n) {
                // 检查无误后,将对应的因数也放入结果中
                total += pair;
            }
        }
    }
    return total;
}

/* Replace this comment with a descriptive function
 * header comment.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* Replace this comment with a descriptive function
 * header comment.
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0)
            cout << "." << flush; // progress bar
    }
    cout << endl
         << "Done searching up to " << stop << endl;
}

/* Replace this comment with a descriptive function
 * header comment.
 */
long findNthPerfectEuclid(long k) {
    // make sure input must be postive number
    if (k <= 0) {
        cout << "please input postive number!" << endl;
        return 0;
    }
    while (1) {
        long m = pow(2, k) - 1;
        // check m is a prime number or not
        if (smarterSum(m) == 1) {
            // m is a prime number
            long nth = m * pow(2, k - 1);
            if (isPerfectSmarter(nth))
                return nth;
        }
        k++;
    }
    return 0;
}

/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */
PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

STUDENT_TEST("Confirm divisorSum() of small inputs") {
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(13), 1);
    EXPECT_EQUAL(divisorSum(19), 1);
    EXPECT_EQUAL(divisorSum(24), 36);
    EXPECT_EQUAL(divisorSum(25), 6);
    EXPECT_EQUAL(divisorSum(28), 28);
    EXPECT_EQUAL(divisorSum(496), 496);
    EXPECT_EQUAL(divisorSum(8128), 8128);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

STUDENT_TEST("Copy the provided_test") {
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
    TIME_OPERATION(80000, findPerfects(80000));
    TIME_OPERATION(160000, findPerfects(160000));
}

STUDENT_TEST("isPerfect() on a few different negative inputs") {
    EXPECT(!isPerfect(-1));
    EXPECT(!isPerfect(0));
    EXPECT(isPerfect(6));
    EXPECT(!isPerfect(-6));
    EXPECT(isPerfect(28));
    EXPECT(!isPerfect(-28));
    EXPECT(isPerfect(496));
    EXPECT(!isPerfect(-496));
    EXPECT(isPerfect(8128));
    EXPECT(!isPerfect(-8128));
}

STUDENT_TEST("smarterSum() test") {
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(12), 16);
    EXPECT_EQUAL(divisorSum(13), 1);
    EXPECT_EQUAL(divisorSum(19), 1);
    EXPECT_EQUAL(divisorSum(24), 36);
    EXPECT_EQUAL(divisorSum(25), 6);
    EXPECT_EQUAL(divisorSum(28), 28);
    EXPECT_EQUAL(divisorSum(496), 496);
    EXPECT_EQUAL(divisorSum(8128), 8128);
}

STUDENT_TEST("isPerfectSmart() test") {
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
    TIME_OPERATION(80000, findPerfectsSmarter(80000));
    TIME_OPERATION(160000, findPerfectsSmarter(160000));
    TIME_OPERATION(320000, findPerfectsSmarter(320000));
    TIME_OPERATION(640000, findPerfectsSmarter(640000));
}

STUDENT_TEST("findNthPerfectEuclid() Test, EXPECT_EQUAL") {
    EXPECT_EQUAL(findNthPerfectEuclid(2), 6);
    EXPECT_EQUAL(findNthPerfectEuclid(3), 28);
    EXPECT_EQUAL(findNthPerfectEuclid(5), 496);
    EXPECT_EQUAL(findNthPerfectEuclid(13), 33550336);
    EXPECT_EQUAL(findNthPerfectEuclid(17), 8589869056);
    EXPECT_EQUAL(findNthPerfectEuclid(19), 137438691328);
}

STUDENT_TEST("findNthPerfectEuclid() Test, EXPECT") {
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(1)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(2)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(3)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(4)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(5)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(6)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(7)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(8)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(9)));
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(10)));
}

STUDENT_TEST("findNthPerfectEuclid() Test, EXPECT, for_loop") {
    for (long i = 1; i <= 20; i++) {
        long nth = findNthPerfectEuclid(i);
        EXPECT(isPerfectSmarter(nth));
        cout << "i: " << i << " – " << nth << endl;
    }
}
