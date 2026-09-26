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
#include "vector.h"
using namespace std;

/*
 * Linked List Warmup (Code Writing)
 * --------------------------------------------------------
 * Write a function that adds up the values of all the elements
 * in the linked list. Next, write a function that returns a
 * pointer to the last element of a linked list (and reports an
 * error if the list is empty).
 */

int sumOfElementsIn_recursive(Node* list) {
    if (list == nullptr) {
        return 0;
    }
    return list->data + sumOfElementsIn_recursive(list->next);
}

int sumOfElementsIn(Node* list){
    int result = 0;

    while (list != nullptr) {
        result += list->data;
        list = list->next;
    }

    return result;
}

Node* lastElementOf_recursiveHelp(Node* curr) {
    if (curr->next == nullptr) {
        return curr;
    }
    return lastElementOf_recursiveHelp(curr->next);
}

Node* lastElementOf_recursive(Node* list) {
    if (list == nullptr) {
        error("List is empty");
    }
    return lastElementOf_recursiveHelp(list);
}

Node* lastElementOf(Node* list) {
    if (list == nullptr) {
        error("List is empty");
    }

    while (list->next != nullptr) {
        list = list->next;
    }

    return list;
}

/* * * * * Provided Tests Below This Point * * * * */
STUDENT_TEST("Basic Sum Example recursive") {
    Node* list = createListFromVector({ 1, 2, 3, 4, 5 });
    EXPECT_EQUAL(sumOfElementsIn_recursive(list), 15);
    freeList(list);
}

PROVIDED_TEST("Basic Sum Example"){
    Node *list = createListFromVector({1, 2, 3, 4, 5});
    EXPECT_EQUAL(sumOfElementsIn(list), 15);
    freeList(list);
}

PROVIDED_TEST("Basic Find Last Example recursive") {
    Node* list = createListFromVector({ 1, 2, 3 });
    EXPECT_EQUAL(lastElementOf_recursive(list), list->next->next);
    freeList(list);
}

PROVIDED_TEST("Basic Find Last Example"){
    Node *list = createListFromVector({1,2,3});
    EXPECT_EQUAL(lastElementOf(list), list->next->next);
    freeList(list);
}


