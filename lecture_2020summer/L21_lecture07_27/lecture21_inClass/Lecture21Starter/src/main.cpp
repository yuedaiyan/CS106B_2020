#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "simpio.h"
#include "linkedlist.h"
using namespace std;

void list_normal() {
    Node* list = readList();

    cerr << "lengthOf():" << endl;
    cout << "This list contains " << lengthOf(list) << " cells." << endl;

    cerr << "printList():" << endl;
    printList(list);

    cerr << "freeList():" << endl;
    freeList(list);

    cout << endl
         << endl;
}

void list_append() {
    Node* head = nullptr;

    cerr << "appendTo(): Trip, Kylie, Nick" << endl;
    appendTo(head, "Trip");
    appendTo(head, "Kylie");
    appendTo(head, "Nick");

    cerr << "printList():" << endl;
    printList(head);
    cerr << "freeList():" << endl;
    freeList(head);
}

void list_recursive() {
    Node* head = nullptr;

    cerr << "prependTo(): Trip, Kylie, Nick" << endl;
    prependTo(head, "Trip");
    prependTo(head, "Kylie");
    prependTo(head, "Nick");

    cerr << "printListRec():" << endl;
    printListRec(head);

    cerr << "freeListRec():" << endl;
    freeListRec(head);

    cout << endl
         << endl;
}

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

    list_normal();
    list_append();
    list_recursive();

    return 0;
}
