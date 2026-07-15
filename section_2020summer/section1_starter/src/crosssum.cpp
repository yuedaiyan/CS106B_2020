/*
 * CS106B Section Handout Test Harness: Section 1
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
#include "grid.h"
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
using namespace std;

/*
 * CrossSum (Code Write)
 * ----------------------------------
 * Given 3 parameters, a reference to a grid of integers and two integers for
 * a row and column, return the sum of all numbers in the row / col provided.
 *
 * You may assume row and col are within the bounds of the grid.
 * Do not modify the grid.
 */

int crossSum(const Grid<int>& g, int row, int col) {

    int fullSize = g.size();
    int rowSize = g[1].size();
    int colSize = fullSize / rowSize;
    cout << "fullSize" << fullSize << endl;
    cout << "rowSize" << rowSize << endl;
    cout << "colSzie" << colSize << endl;

    Vector<int> rowVector;
    Vector<int> colVector;

    // 限定 col - y 轴, 变化 x 坐标, 获得横向完整 col
    for (int i = 0; i < colSize; i++) {
        cout << "(" << i << "," << col << ")" << endl;
        cout << g.get(i, col) << endl;
        colVector.add(g.get(i, col));
    }
    // 限定 row - x 轴, 变化 y 坐标, 获得横向完整 row
    for (int i = 0; i < rowSize; i++) {
        cout << "(" << i << "," << col << ")" << endl;
        cout << g.get(row, i) << endl;
        rowVector.add(g.get(row, i));
    }
    cout << "rowVector: " << rowVector << endl;
    cout << "colVector: " << colVector << endl;

    // 获得重复数值
    int centerValue = g.get(row, col);
    cout << "centerValue: " << centerValue << endl;

    int result = 0;

    // cout << "rowVector[0]: " << rowVector.get(0) << endl;
    // cout << "rowVector[8]: " << rowVector.get(8) << endl;
    for (int i : rowVector) {
        // cout << "i: " << i << endl;
        result += i;
    }
    for (int i : colVector) {
        result += i;
    }
    result -= centerValue;

    cout << "result: " << result << endl;

    return result;
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Provided Test: Verifies our solution works on the handout's example case.") {
    Grid<int> g = { {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9} };
    EXPECT_EQUAL(crossSum(g, 1, 1), 25);
}

PROVIDED_TEST("Provided Test: Verifies our solution works on a larger grid.") {
    Grid<int> g = { {1, 6, 5, 4, 2, 73, 2, 9, 0, -4, 24, 7},
                    {2, 43, 64, -53, 8, 4, 6, 78, 5, 1, 4, -6},
                    {7, 8, 9, 10, 11, -12, 5, 65, 4, 0,-6, 13},
                    {14, 52, 6, 8, 4, 2, -6, 5, 8, 3, 6, -33} };
    EXPECT_EQUAL(crossSum(g, 2, 8), 127);
}
