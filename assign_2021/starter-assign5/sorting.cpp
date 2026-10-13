#include "listnode.h"
#include "vector.h"
#include "testing/SimpleTest.h"
using namespace std;

void partition(ListNode*& front, ListNode*& less, ListNode*& equal, ListNode*& greater, int pivot) {
    while (front != nullptr) {
        ListNode* curr = front;
        front = front->next;

        if (curr->data < pivot) {
            if (less == nullptr) {
                curr->next = nullptr;
            } else {
                curr->next = less;
            }
            less = curr;
        } else if (curr->data == pivot) {
            if (equal == nullptr) {
                curr->next = nullptr;
            } else {
                curr->next = equal;
            }
            equal = curr;
        } else {
            if (greater == nullptr) {
                curr->next = nullptr;
            } else {
                curr->next = greater;
            }
            greater = curr;
        }
    }
}

ListNode* getLastNode(ListNode*& front) {
    // 传入参数检查
    if (front == nullptr) {
        return front;
    }

    // 核心逻辑
    ListNode* end = front;
    while (end->next != nullptr) {
        end = end->next;
    }
    return end;
}

void concatenate(ListNode*& front, ListNode*& less, ListNode*& equal, ListNode*& greater) {
    // 传入参数检查
    if (front != nullptr) {
        error("concatenate()第一个参数为空指针(nullptr)!");
    }
    if (less == nullptr && equal == nullptr && greater == nullptr) {
        error("concatenate()三个参数都为nullptr!");
    }

    // 核心逻辑
    ListNode* last = nullptr;
    if (less != nullptr) {
        if (front == nullptr) {
            front = less;
        }
        last = getLastNode(front);
    }
    if (equal != nullptr) {
        if (front == nullptr) {
            front = equal;
        }
        if (last != nullptr) {
            last->next = equal;
        }
        last = getLastNode(equal);
    }
    if (greater != nullptr) {
        if (front == nullptr) {
            front = greater;
        }
        if (last != nullptr) {
            last->next = greater;
        }
        last = getLastNode(greater);
    }
}

// 使用智能取中间值可以尽可能将所有情况都转换为O(NlogN)
int findBetterPivot(ListNode*& front) {
    // function precheck
    if (front->next == nullptr) {
        return front->data;
    }

    // main
    ListNode* curr = front;
    int a, b, c;
    b = front->data;
    a = b - 1;
    c = b + 1;

    int length = 1;
    int times = 0;

    while (curr != nullptr) {
        if (times == length) {
            length *= 2;
            times = 1;

            if (curr->data < a) {
                a = curr->data;
            }
            if (curr->data > c) {
                c = curr->data;
            }

            b = (a + c) / 2;
        }

        curr = curr->next;
        times += 1;
    }
    return b;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment about your implementation of the function.
 */
void quickSort(ListNode*& front) {
    /* A list with 0 or 1 elements is already sorted by definition. */
    if (front == nullptr) {
        return;
    }
    if (front->next == nullptr) {
        return;
    }

    /* Pick the pivot and partition the list into three components.
     * 1) elements less than the pivot
     * 2) elements equal to the pivot
     * 3) elements greater than the pivot
     */
    // Define three empty lists : less, equal, greater
    ListNode *less = nullptr, *equal = nullptr, *greater = nullptr;
    // pivot = first element of vector(arbitrary choice)
    // int pivot = front->data;
    int pivot = findBetterPivot(front);
    // cerr << "pivot: " << pivot << endl;

    partition(front, less, equal, greater, pivot);

    /* Recursively sort the two unsorted components. */
    quickSort(less);
    quickSort(greater);

    /* Concatenate newly sorted results and store in original vector */
    concatenate(front, less, equal, greater);
}

/* * * * * * Test Code Below This Point * * * * * */

/* TODO: Write your own student tests below to test your sorting helper
 * functions and overall sorting algorithm correctness. We have provided
 * the skeleton of some tests below to help you get started with this
 * process.
 */

/*
 * We have provided this utility function as a convenience. This
 * function traverses the linked list represented by the provided
 * front pointer and prints out the data stored in the list along
 * the way in a convenient format. You may find it to be helpful to
 * use this function as a debugging aid.
 */
void printList(ListNode* front) {
   cout << "{";
   for (ListNode *cur = front; cur != nullptr; cur = cur->next) {
       cout << cur->data;
       if (cur->next != nullptr){
           cout << ", ";
       }
   }
   cout << "}" << endl;
}

/*
 * This utility function deallocates the memory for all the nodes in a
 * given linked list. It can be used to recycle the memory allocated
 * during a test case and avoid memory leaks.
 */
void deallocateList(ListNode* front) {
    while (front != nullptr) {
        ListNode* temp = front;
        front = front->next;
        delete temp;
    }

    // cout << "deallocateList: ";
    // printList(front);
    // cout << endl;
}

/*
 * This utility function is given a vector of values and constructs
 * an equivalent linked list containing the same values in the same order.
 * It can be used to construct a linked list to use as an input to
 * a function being tested.
 */
ListNode* createList(Vector<int> values){
    ListNode* front = nullptr;
    ListNode* last = front;

    for (int value : values) {
        ListNode* curr = new ListNode(value, nullptr);
        if (front == nullptr) {
            front = curr;
            last = curr;
            continue;
        }
        last->next = curr;
        last = curr;
    }
    // cerr << "-------" << endl;
    // printList(front);
    // cerr << "-------" << endl;
    return front;
}

/*
 * This utility function compares a linked list and a vector for
 * equivalence and returns true if both contain the same values in the
 * same order. It can be used to confirm a linked list's contents match
 * the expected.
 */
bool areEquivalent(ListNode* front, Vector<int> v){
    for (int value : v) {
        if (front == nullptr) {
            return false;
        }
        if (value != front->data) {
            return false;
        }
        front = front->next;
    }
    if (front != nullptr) {
        return false;
    }
    return true;
}

/* * * * * * Help Function tests * * * * * */
STUDENT_TEST("findBetterPivot():") {
    Vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
    ListNode* list = createList(v);

    int result = findBetterPivot(list);
    cerr << "pivot: " << result << endl;

    EXPECT(result >= 1 && result <= 7);

    deallocateList(list);
}
STUDENT_TEST("findBetterPivot():") {
    Vector<int> v = { 231, 2, -333, 4, 7324, 6, 7, 10000, -345 };
    ListNode* list = createList(v);

    int result = findBetterPivot(list);
    cerr << "pivot: " << result << endl;

    EXPECT(result >= -345 && result <= 10000);

    deallocateList(list);
}
STUDENT_TEST("partition() test: ") {
    Vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
    ListNode* list = createList(v);

    ListNode *lessList = nullptr, *equalList = nullptr, *greaterList = nullptr;
    int pivot = 4;

    partition(list, lessList, equalList, greaterList, pivot);

    Vector<int> lessVector = { 3, 2, 1 };
    Vector<int> equalVector = { 4 };
    Vector<int> greaterVector = { 7, 6, 5 };

    EXPECT(areEquivalent(lessList, lessVector));
    EXPECT(areEquivalent(equalList, equalVector));
    EXPECT(areEquivalent(greaterList, greaterVector));

    deallocateList(list);
    deallocateList(lessList);
    deallocateList(equalList);
    deallocateList(greaterList);
}
STUDENT_TEST("getLastNode() test: ") {
    Vector<int> values = { 1, 2, 3, 4 };
    ListNode* list = createList(values);

    ListNode* listEnd = getLastNode(list);

    EXPECT_EQUAL(listEnd->data, 4);

    deallocateList(list);
}
STUDENT_TEST("getLastNode() test: ") {
    Vector<int> values = { 1, 3, 4, 2 };
    ListNode* list = createList(values);

    ListNode* listEnd = getLastNode(list);

    EXPECT_EQUAL(listEnd->data, 2);

    deallocateList(list);
}
STUDENT_TEST("concatenate() test: three normal list") {
    Vector<int> av = { 1, 2, 3, 4 };
    ListNode* al = createList(av);

    Vector<int> bv = { 5, 6 };
    ListNode* bl = createList(bv);

    Vector<int> cv = { 7, 8, 9 };
    ListNode* cl = createList(cv);

    ListNode* front = nullptr;
    Vector<int> rv = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    concatenate(front, al, bl, cl);

    printList(front);
    EXPECT(areEquivalent(front, rv));

    deallocateList(front);
}
STUDENT_TEST("concatenate() test: one empty list") {
    Vector<int> av = { 1, 2, 3, 4 };
    ListNode* al = createList(av);

    Vector<int> bv = { };
    ListNode* bl = createList(bv);

    Vector<int> cv = { 7, 8, 9 };
    ListNode* cl = createList(cv);

    ListNode* front = nullptr;
    Vector<int> rv = { 1, 2, 3, 4, 7, 8, 9 };

    // printList(front);
    concatenate(front, al, bl, cl);

    cout << endl;
    cout << "-----" << endl;
    printList(front);
    EXPECT(areEquivalent(front, rv));

    deallocateList(front);
}

/* * * * * * Testhelp Function tests * * * * * */
STUDENT_TEST("This is a skeleton to demonstrate an end-to-end student test."){
    /* Initialize vector to sequence of values */
    Vector<int> values = {1, 2, 3, 4};
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);

    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
PROVIDED_TEST("This tests some of the testing helper functions you are recommended to implement."){
    /* Creates a small test list containing the values 1->2->3. */
    ListNode* testList = nullptr;
    testList = new ListNode(3, testList);
    testList = new ListNode(2, testList);
    testList = new ListNode(1, testList);

    /* Test equality comparison function. */
    EXPECT(areEquivalent(testList, {1, 2, 3}));
    EXPECT(!areEquivalent(testList, {1, 2}));
    EXPECT(!areEquivalent(testList, {1, 2, 3, 4}));
    EXPECT(!areEquivalent(testList, {1, 3, 2}));

    /* Test create list function. */
    ListNode* studentList = createList({1, 2, 3, 4});
    printList(studentList);
    ListNode* cur = studentList;
    for (int i = 1; i <= 4; i++){
        EXPECT(cur != nullptr);
        EXPECT_EQUAL(cur->data, i);
        cur = cur->next;
    }

    /* Test deallocate list functions. There should be no memory leaks from this test. */
    deallocateList(studentList);
    deallocateList(testList);
}
/*
 * The provided test case demonstrates a comparsion between the same
 * algorithm (quicksort) operating on a linked list versus a vector.
 */
PROVIDED_TEST("Time linked list quicksort vs vector quicksort") {
    int startSize = 50000;

    for(int n = startSize; n < 10*startSize; n *= 2) {
        Vector<int> v(n);
        ListNode* list = nullptr;

        /* Create linked list and vector with the same random sequence. */
        for (int i = n-1; i >= 0; i--) {
            v[i] = randomInteger(-10000, 10000);
            list = new ListNode(v[i], list);
        }

        /* NOTE: This test does not check correctness of the linked list sort
         * function. It only times the two operations to compare relative speed. */
        TIME_OPERATION(n, quickSort(list));
        TIME_OPERATION(n, v.sort());        /* Standard vector sort operation is backed
                                               with quicksort algorithm. */

        deallocateList(list);
    }
}

/* * * * * * Sorting() tests * * * * * */
STUDENT_TEST("Sorting an empty list") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a single-element list") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { 1 };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a list in already sorted") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { 1, 2, 3, 4, 5 };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a list in reverse sorted order") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { 5, 4, 3, 2, 1 };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a list that contain some duplicate elements") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { 1, 4, 3, 2, 2, 3, 4 };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a list that contain all duplicate elements") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { 3, 3, 3, 3, 3, 3, 3, 3 };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a list that contains positive and negative numbers") {
    /* Initialize vector to sequence of values */
    Vector<int> values = { 1, -1, 2, -2, 3, -3, 4, -4 };
    /* Create equivalent list to use as test input */
    ListNode* list = createList(values);

    /* Sort the list */
    quickSort(list);
    /* Sort the equivalent vector */
    values.sort();

    /* Confirm sorted list matches sorted vector */
    EXPECT(areEquivalent(list, values));

    /* Avoid memory leaks by deallocating list */
    deallocateList(list);
}
STUDENT_TEST("Sorting a list of random values, randomly organized ") {
    int startSize = 50000;

    for (int n = startSize; n < 10 * startSize; n *= 2) {
        /* Initialize vector to sequence of values */
        Vector<int> values(n);
        for (int i = n - 1; i >= 0; i--) {
            values[i] = randomInteger(-10000, 10000);
        }

        /* Create equivalent list to use as test input */
        ListNode* list = createList(values);

        /* Sort the list */
        quickSort(list);
        /* Sort the equivalent vector */
        values.sort();

        /* Confirm sorted list matches sorted vector */
        EXPECT(areEquivalent(list, values));

        /* Avoid memory leaks by deallocating list */
        deallocateList(list);

        // TIME_OPERATION(n, quickSort(list));
        // TIME_OPERATION(n, v.sort());
    }
}

/* * * * * * Sorting Function fun time tests * * * * * */
STUDENT_TEST("Sorting() normal time") {
    int startSize = 50000;

    for (int n = startSize; n < 20 * startSize; n *= 2) {
        /* Initialize vector to sequence of values */
        Vector<int> values(n);
        for (int i = n - 1; i >= 0; i--) {
            values[i] = randomInteger(-10000, 10000);
        }

        /* Create equivalent list to use as test input */
        ListNode* list = createList(values);

        /* Confirm sorted list matches sorted vector */
        TIME_OPERATION(n, quickSort(list));
        // TIME_OPERATION(n, values.sort());

        // EXPECT(areEquivalent(list, values));

        /* Avoid memory leaks by deallocating list */
        deallocateList(list);
    }
}
STUDENT_TEST("Sorting() worst-case time") {
    const int repetitions = 1000;

    for (int n = 100; n <= 800; n *= 2) {
        Vector<int> values(n);
        for (int i = 0; i < n; i++) {
            values[i] = i;
        }

        // 重复1000次放大差异
        TIME_OPERATION(n, {
            for (int r = 0; r < repetitions; r++) {
                ListNode* list = createList(values);
                quickSort(list);
                deallocateList(list);
            }
        });
    }
}
STUDENT_TEST("Linked list QuickSort vs Vector sort") {
    int startSize = 50000;

    for (int n = startSize; n < 10 * startSize; n *= 2) {
        // 准备随机数据
        Vector<int> values(n);
        for (int i = 0; i < n; i++) {
            values[i] = randomInteger(-10000, 10000);
        }

        // 用相同的数据创建链表
        ListNode* list = createList(values);

        cout << "Linked list QuickSort:" << endl;
        TIME_OPERATION(n, quickSort(list));

        cout << "Vector sort:" << endl;
        TIME_OPERATION(n, values.sort());

        // 检查链表排序结果
        EXPECT(areEquivalent(list, values));

        deallocateList(list);
    }
}
