/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "queue.h"
#include "random.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include <cmath> // for cout, endl
#include <iostream> // for cout, endl
using namespace std;

// 辅助函数: 检测 Queue 是不是呈递增趋势
void binaryMergeInputValidation(Queue<int> q) {
    /*
    // 不能使用递归,面对长 Queue, 很容易造成栈溢出
    if (q.size() <= 1) {
        return true;
    } else {
        int curr = q.dequeue();
        int next = q.peek();
        if (curr <= next) {
            if (binaryMergeInputValidation(q)) {
                return true;
            }
        }
        error("输入 Queue 出现递减.");
    }
    */
    int qSize = q.size();
    if (qSize == 0) {
        return;
    }
    int curr = q.peek();
    for (int i = 0; i < qSize; i++) {
        if (curr > q.dequeue()) {
            error("输入 Queue 出现递减.");
        }
    }
}

// 合并两个 Queue, 要求使用迭代而非递归
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    // 测试 a,b 两个 Queue 是否为递增顺序
    binaryMergeInputValidation(a);
    binaryMergeInputValidation(b);

    // 开始主逻辑
    Queue<int> result;
    int aCurr, bCurr;

    while (!a.isEmpty() && !b.isEmpty()) {
        aCurr = a.peek();
        bCurr = b.peek();

        aCurr <= bCurr ? result.enqueue(a.dequeue()) : result.enqueue(b.dequeue());
    }
    // 仅追加
    while (!a.isEmpty()) {
        result.enqueue(a.dequeue());
    }
    while (!b.isEmpty()) {
        result.enqueue(b.dequeue());
    }

    // cerr << "" << endl;
    // cerr << "result: " << result.toString() << endl;
    return result;
}

/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    int allSize = all.size();
    if (allSize == 1) {
        Queue<int> result = all[0];
        return result;
    } else if (allSize == 2) {
        Queue<int> result = binaryMerge(all[0], all[1]);
        return result;
    } else {
        int halfAllSize = allSize / 2;
        Vector<Queue<int>> half_1 = all.subList(0, halfAllSize);
        Vector<Queue<int>> half_2 = all.subList(halfAllSize);
        return binaryMerge(recMultiMerge(half_1), recMultiMerge(half_2));
    }
}

/* * * * * * Test Cases * * * * * */
Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);
/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/*
Test helper to distribute elements of sorted sequence
across k sequences, k is size of Vector
*/
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size() - 1)].enqueue(input.dequeue());
    }
}

STUDENT_TEST("LEARN Queue()") {
    // Queue<int> a = { 2, 4, 5 };
    // while (!a.isEmpty()) {
    //     cerr << "-------" << endl;
    //     cerr << a.dequeue() << endl;
    //     cerr << a.peek() << endl;
    //     cerr << "-------" << endl;
    // }
    EXPECT(true);
}

STUDENT_TEST("LEARN subList()") {
    cerr << "" << endl;
    Vector<int> m = { 1, 2, 3, 4, 5, 6 };
    int mSize = m.size();
    int halfMSize = mSize / 2;
    Vector<int> half_1 = m.subList(0, halfMSize);
    Vector<int> half_2 = m.subList(halfMSize);

    // cerr << "half size: " << halfMSize << endl;
    // cerr << "subList 1: " << half_1 << endl;
    // cerr << "subList 2: " << half_2 << endl;
    EXPECT(true);
}

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

STUDENT_TEST("binaryMerge(), test error selfcheck") {
    Queue<int> a = { 9, 4, 5 };
    Queue<int> b = { 1, 3, 3 };
    EXPECT_ERROR(binaryMerge(a, b));
}

STUDENT_TEST("binaryMerge(), test empty Queue") {
    Queue<int> a = { };
    Queue<int> b = { 1, 3, 3 };
    Queue<int> expected = { 1, 3, 3 };
    EXPECT_EQUAL(binaryMerge(a, b), expected);
}

STUDENT_TEST("binaryMerge(), time check") {
    // for (int i = 0; i < 20; i++) {
    for (int i = 0; i < 18; i++) {
        Queue<int> m;
        int kMax = pow(2, i);
        for (int k = 0; k < kMax; k++) {
            m.enqueue(k);
        }
        Queue n = m;
        TIME_OPERATION(m.size(), binaryMerge(m, n));
    }
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("naiveMultiMerge(), merge 0 queue") {
    Vector<Queue<int>> all = { { 3, 6, 9, 9, 100 },
        { 1, 5, 9, 9, 12 },
        { 5 },
        { },
        { -5, -5 },
        { 3402 } };
    Queue<int> expected = { -5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402 };
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge(), merge empty queue") {
    Vector<Queue<int>> all = {
        { },
        { },
        { },
        { },
    };
    Queue<int> expected = { };
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge(), merge Positive, 0, Negative test") {
    Vector<Queue<int>> all = {
        { 3 },
        { -1 },
        { 0 },
        { },
    };
    Queue<int> expected = { -1, 0, 3 };
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("naiveMultiMerge(), time check") {
    // for (int n = 1; n < 20; n++) {
    for (int n = 1; n < 18; n++) {
        Vector<Queue<int>> all = {
            { }, { }, { }, { }, { }, { }
        };
        int nMax = pow(2, n);
        for (Queue<int>& q : all) {
            int prev = 0;
            for (int k = 0; k < nMax; k++) {
                prev = prev + randomInteger(0, 10);
                q.enqueue(prev);
            }
        }
        TIME_OPERATION(all[0].size() * all.size(), naiveMultiMerge(all));
    }
}

STUDENT_TEST("recMultiMerge, small collection of short sequences") {
    cerr << "" << endl;
    Vector<Queue<int>> all = { { 3, 6, 9, 9, 100 },
        { 1, 5, 9, 9, 12 },
        { 5 },
        { },
        { -5, -5 },
        { 3402 } };
    Queue<int> expected = { -5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402 };
    EXPECT_EQUAL(recMultiMerge(all), expected);
}

STUDENT_TEST("recMultiMerge(), merge 0 queue") {
    cerr << "" << endl;
    Vector<Queue<int>> all = { { 3, 6, 9, 9, 100 },
        { 1, 5, 9, 9, 12 },
        { 5 },
        { },
        { -5, -5 },
        { 3402 } };
    Queue<int> expected = { -5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402 };
    EXPECT_EQUAL(recMultiMerge(all), expected);
}

STUDENT_TEST("recMultiMerge(), merge empty queue") {
    cerr << "" << endl;
    Vector<Queue<int>> all = {
        { },
        { },
        { },
        { },
    };
    Queue<int> expected = { };
    EXPECT_EQUAL(recMultiMerge(all), expected);
}

STUDENT_TEST("recMultiMerge(), merge Positive, 0, Negative test") {
    cerr << "" << endl;
    Vector<Queue<int>> all = {
        { 3 },
        { -1 },
        { 0 },
        { },
    };
    Queue<int> expected = { -1, 0, 3 };
    EXPECT_EQUAL(recMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    cerr << "" << endl;
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}

PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}

STUDENT_TEST("recMultiMerge(), time check, keep k(Vector's size) fixed. n[ 40 , 10485760 ], k = 20") {
    for (int exp = 1; exp < 16; exp++) {
        Vector<Queue<int>> all(20, { });
        int nMax = pow(2, exp);
        for (Queue<int>& q : all) {
            int prev = 0;
            for (int k = 0; k < nMax; k++) {
                prev = prev + randomInteger(0, 10);
                q.enqueue(prev);
            }
        }
        TIME_OPERATION(all[0].size() * all.size(), recMultiMerge(all));
    }
}

STUDENT_TEST("recMultiMerge(), vary k while keeping n fixed") {
    const int n = 1000000;
    Queue<int> input = createSequence(n);
    for (int k = 4; k <= 64 * 64; k *= 4) {
        Vector<Queue<int>> all(k);
        distribute(input, all);
        TIME_OPERATION(k, recMultiMerge(all));
    }
}