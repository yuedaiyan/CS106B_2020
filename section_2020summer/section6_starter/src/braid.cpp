/*
 * CS106B Section Handout Test Harness: Section 6
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
#include "node.h"
#include "utility.h"
#include "error.h"
#include "stack.h"
#include "set.h"
using namespace std;

/*
 * Braiding a Linked List (Code Writing)
 * --------------------------------------------------------
 * Write a function braid that takes a linked list, and weaves
 * the reverse of that list into the original. (In this case,
 * you will need to create new nodes.)
 */

// 调用条件:确定 front 链表中至少有 1 个元素
int getReverseElem(Node*& front, bool leftOrRight) {
    int result;

    if (front->next == nullptr) {
        result = front->data;
        delete front;
        front = nullptr;
        return result;
    }

    if (leftOrRight) {
        result = front->data;
        Node* temp = front;
        front = front->next;
        delete temp;
    } else {
        Node* prev = front;
        Node* last = front;
        while (last->next != nullptr) {
            prev = last;
            last = last->next;
        }
        result = last->data;
        delete last;
        prev->next = nullptr;
    }
    return result;
}

// bad version, O(n^2) on timing
void braid_myVersion(Node*& front) {
    if (front == nullptr) {
        cout << "front is empty list" << endl;
        return;
    }

    bool leftOrRight = true;
    Node* result = nullptr;
    Node* midLeft = nullptr;

    while (front != nullptr) {
        int currInt = getReverseElem(front, leftOrRight);
        leftOrRight = !leftOrRight;

        Node* leftNode = new Node(currInt, nullptr);
        Node* rightNode = new Node(currInt, nullptr);

        if (result == nullptr) {
            // 刚开始建立链表
            result = leftNode;
            leftNode->next = rightNode;
            midLeft = leftNode;
        } else {
            // 向已存在列表中央插入元素
            Node* midRight = midLeft->next;
            midLeft->next = leftNode;
            midLeft = leftNode;
            leftNode->next = rightNode;
            rightNode->next = midRight;
        }
    }
    front = result;
}

Node* reverseList(Node* copyList) {
    Node* reverse = nullptr;
    for (Node* curr = copyList; curr != nullptr; curr = curr->next) {
        Node* newNode = new Node(curr->data, reverse);
        reverse = newNode;
    }
    return reverse;
}

Node* getElem(Node*& list) {
    Node* result = list;
    list = list->next;
    result->next = nullptr;
    return result;
}

void braid(Node*& front) {
    Node* reverse = reverseList(front);

    for (Node* curr = front; curr != nullptr; curr = curr->next->next) {
        Node* insert = getElem(reverse);
        Node* next = curr->next;
        curr->next = insert;
        insert->next = next;
    }
}

/* * * * * Provided Tests Below This Point * * * * */
STUDENT_TEST("getReverseElem(): 1 elements") {
    Node* originalList = createListFromVector({ 1, 2, 3, 4, 5 });

    EXPECT_EQUAL(1, getReverseElem(originalList, true));
    EXPECT_EQUAL(5, getReverseElem(originalList, false));
    EXPECT_EQUAL(2, getReverseElem(originalList, true));
    EXPECT_EQUAL(4, getReverseElem(originalList, false));
    EXPECT_EQUAL(3, getReverseElem(originalList, true));
}

STUDENT_TEST("reverseList(): 1 elements") {
    Node* originalList = createListFromVector({ 1 });
    Node* braidedList = createListFromVector({ 1 });
    originalList = reverseList(originalList);
    EXPECT(listEqual(originalList, braidedList));
}

STUDENT_TEST("reverseList(): 4 elements") {
    Node* originalList = createListFromVector({ 1, 2, 3, 4 });
    Node* braidedList = createListFromVector({ 4, 3, 2, 1 });
    originalList = reverseList(originalList);
    EXPECT(listEqual(originalList, braidedList));
}

STUDENT_TEST("reverseList(): 5 elements") {
    Node* originalList = createListFromVector({ 1, 2, 3, 4, 5 });
    Node* braidedList = createListFromVector({ 5, 4, 3, 2, 1 });
    originalList = reverseList(originalList);
    EXPECT(listEqual(originalList, braidedList));
}

PROVIDED_TEST("First example from handout"){
    Node* originalList = createListFromVector({ 1, 4, 2 });
    Node* braidedList = createListFromVector({ 1, 2, 4, 4, 2, 1 });

    braid(originalList);

    EXPECT(listEqual(originalList, braidedList));
}

PROVIDED_TEST("Second example from handout"){
    Node *originalList = createListFromVector({3});
    Node *braidedList = createListFromVector({3, 3});

    braid(originalList);

    EXPECT(listEqual(originalList, braidedList));
}

PROVIDED_TEST("Third example from handout"){
    Node *originalList = createListFromVector({1, 3, 6, 10, 15});
    Node *braidedList = createListFromVector({1, 15, 3, 10, 6, 6, 10, 3, 15, 1});

    braid(originalList);

    EXPECT(listEqual(originalList, braidedList));
}
