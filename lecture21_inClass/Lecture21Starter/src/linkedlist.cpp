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
    /* TODO: Implement this function! */
    return 0;
}

/* Prints the contents of a linked list, in order. */
void printList(Node* list) {
    /* TODO: Implement this function! */
}

/* Frees all the memory used by a linked list. */
void freeList(Node* list) {
    /* TODO: Implement this function! */
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
    /* TODO: Implement this function! */
    return 0;
}

/* Prints the contents of a linked list, in order. Operates recursively. */
void printListRec(Node* list) {
    /* TODO: Implement this function! */
}

/* Frees all the memory used by a linked list. Operates recursively. */
void freeListRec(Node* list) {
    /* TODO: Implement this function! */
}

/* Question to ponder: Why do we take this list parameter by reference? */
void prependTo(Node*& list, string data) {
    /* TODO: Implement this function! */
}

/* Appends to a linked list represented as a pair of a head and tail pointer. */
void appendTo(Node*& list, string data) {
    /* TODO: Implement this function! */
}
