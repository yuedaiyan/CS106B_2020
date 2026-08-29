/*
 * Banzhaf Power Index 计算程序
 * 输入各州选举人票数,计算出各州的 Banzhaf Power Index.
 */
#include "voting.h"
#include "set.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <iostream> // for cout, endl
#include <string> // for string class
using namespace std;

// 根据各州选举人票,计算绝对多数票
int getWinningGap(Vector<int>& blocks) {
    int blocksSum = 0;
    for (int block : blocks) {
        blocksSum += block;
    }
    return blocksSum / 2 + 1;
}

// 递归函数: 求所有子集
int getAllSubSetReturnInt(Vector<int>& originSet, int index, int currSum, int winningGap, int winningGapWithOutIndex) {
    if (currSum >= winningGap) {
        return 0;
    }
    if (index == originSet.size()) {
        if (currSum >= winningGapWithOutIndex) {
            return 1;
        } else {
            return 0;
        }
    }
    return getAllSubSetReturnInt(originSet, index + 1, currSum, winningGap, winningGapWithOutIndex)
        + getAllSubSetReturnInt(originSet, index + 1, currSum + originSet.get(index), winningGap, winningGapWithOutIndex);
}

// 主函数: 传入选举人团票数(Vector),按照相同位置返回 Banzhaf Power Index.
Vector<int> computePowerIndexes(Vector<int>& blocks) {
    Vector<int> allCoalitions;
    int winningGap = getWinningGap(blocks);
    Vector<int> result;
    for (int skipIndex = 0; skipIndex < blocks.size(); skipIndex++) {
        Vector<int> blocksWithOutIndex = blocks;
        blocksWithOutIndex.remove(skipIndex);
        int winningGapWhitOutIndex = winningGap - blocks.get(skipIndex);
        int allSubSet = getAllSubSetReturnInt(blocksWithOutIndex, 0, 0, winningGap, winningGapWhitOutIndex);
        result.insert(skipIndex, allSubSet);
    }

    // 计算百分比
    allCoalitions = result;
    cout << endl;
    cerr << "blocks: " << blocks.toString() << endl;
    cerr << "allCoalitinos before Convert to percentage: " << allCoalitions.toString() << endl;
    int totalCoalitions = 0;
    for (int c : allCoalitions) {
        totalCoalitions += c;
    }
    cerr << "totalCoalitions: " << totalCoalitions << endl;
    for (int& c : allCoalitions) {
        c = static_cast<double>(c) / totalCoalitions * 100;
    }
    cerr << "allCoalitinos after Convert to percentage: " << allCoalitions.toString() << endl;
    return allCoalitions;
}

/* * * * * * Test Cases * * * * * */
STUDENT_TEST("getwinningGap() test: ") {
    Vector<int> blocks = { 50, 49, 1 };
    EXPECT_EQUAL(getWinningGap(blocks), 51);
}

STUDENT_TEST("getwinningGap() simple test: ") {
    Vector<int> blocks = { 1, 1, 1 };
    EXPECT_EQUAL(getWinningGap(blocks), 2);
}

STUDENT_TEST("computerPowerIndex() test: index sum = 100") {
    Vector<int> blocks = { 50, 49, 1 };
    Vector<int> result = computePowerIndexes(blocks);
    cerr << endl;
    cerr << result.toString() << endl;
    int sum = 0;
    for (int i : result) {
        sum += i;
    }
    EXPECT_EQUAL(sum, 100);
}

PROVIDED_TEST("Test power index, blocks 50-49-1") {
    Vector<int> blocks = { 50, 49, 1 };
    Vector<int> expected = { 60, 20, 20 };
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks Hempshead 1-1-3-7-9-9") {
    Vector<int> blocks = { 1, 1, 3, 7, 9, 9 };
    Vector<int> expected = { 0, 0, 0, 33, 33, 33 };
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks CA-TX-NY 55-38-39") {
    Vector<int> blocks = { 55, 38, 29 };
    Vector<int> expected = { 33, 33, 33 };
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks CA-TX-GA 55-38-16") {
    Vector<int> blocks = { 55, 38, 16 };
    Vector<int> expected = { 100, 0, 0 };
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Test power index, blocks EU post-Nice") {
    // Estonia is one of those 4s!!
    // blocks size = 28
    Vector<int> blocks = { 29, 29, 29, 29, 27, 27, 14, 13, 12, 12, 12, 12, 12, 10, 10, 10, 7, 7, 7, 7, 7, 4, 4, 4, 4, 4, 3 };
    Vector<int> expected = { 8, 8, 8, 8, 7, 7, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 15; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}

STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 13; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}

STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 17; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}

STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 21; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}

STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 25; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}

STUDENT_TEST("Time power index operation") {
    Vector<int> blocks;
    for (int i = 0; i < 29; i++) {
        blocks.add(randomInteger(1, 10));
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}