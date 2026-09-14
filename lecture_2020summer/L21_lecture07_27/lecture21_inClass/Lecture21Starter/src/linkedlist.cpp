/*************************************************
 * File: LinkedLists.cpp
 *
 * Lots of fucntions that show off the many different ways
 * to do linked list operations!
 */

#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

/* Given a linked list, returns the length of that list. */
int lengthOf(Node* list) {
    int numNodes = 0;
    while (list != nullptr) {
        numNodes++;
        list = list->next;
    }
    return numNodes;
}

/* Prints the contents of a linked list, in order. */
void printList(Node* list) {
    while (list != nullptr) {
        cout << list->data << endl;
        list = list->next;
    }
}

/* Frees all the memory used by a linked list. */
void freeList(Node* list) {
    while (list != nullptr) {
        Node* curr = list;
        list = list->next;
        delete curr;
    }
    // cerr << "freeList() finished." << endl;
}

/* Reads a linked list from the user one element at a time, stopping when
 * the user enters an empty list. This returns the list, constructed in
 * reverse order.
 */
Node* readList() {
    Node* result = nullptr;
    while (true) {
        string line = getLine("Next item: ");
        if (line == "") break;

        Node* newNode = new Node;
        newNode->data = line;

        newNode->next = result;
        result = newNode;
    }
    return result;
}

/* Given a linked list, returns the length of that list. Operates recursively. */
int lengthOfRec(Node* list) {
    if (list == nullptr) {
        return 0;
    }
    return 1 + lengthOfRec(list->next);
}

/* Prints the contents of a linked list, in order. Operates recursively. */
void printListRec(Node* list) {
    if (list == nullptr) {
        return;
    }
    cout << list->data << endl;
    return printListRec(list->next);
}

/* Frees all the memory used by a linked list. Operates recursively. */
void freeListRec(Node* list) {
    if (list == nullptr) {
        return;
    }
    Node* next = list->next;
    delete list;
    return freeListRec(next);
}

/* Question to ponder: Why do we take this list parameter by reference? */
void prependTo(Node*& list, string data) {
    Node* newData = new Node(data, list);
    list = newData;
}

/* Appends to a linked list represented as a pair of a head and tail pointer. */
void appendTo(Node*& list, string data) {
    Node* newNode = new Node(data, nullptr);

    if (list == nullptr) {
        list = newNode;
    } else {

        Node* end = list;
        while (end->next != nullptr) {
            end = end->next;
        }

        end->next = newNode;
    }
}
