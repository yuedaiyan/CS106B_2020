// OurVector.cpp
// Implementation of OurVector class
#include "error.h"
#include "strlib.h"
#include "OurVector.h"
#include "testing/SimpleTest.h"

const int INITIAL_CAPACITY = 8;

// constructor
OurVector::OurVector() {
    this->allocatedCapacity = INITIAL_CAPACITY;
    this->numItems = 0;
    this->elements = new int[allocatedCapacity];
}

// destructor
OurVector::~OurVector(){
    delete[] elements;
}

// append value to the end of our array
void OurVector::add(int value){
    if (this->numItems == this->allocatedCapacity - 1) {
        // error("Index out of bounds!");
        this->expand();
    }
    this->elements[numItems] = value;
    numItems++;
}

// insert value at index
void OurVector::insert(int index, int value){
    if (index > this->numItems || index < 0) {
        // error("Index out of bounds!");
        this->expand();
    }
    for (int i = this->numItems; i > index; i--) {
        this->elements[i] = this->elements[i - 1];
    }
    this->elements[index] = value;
    this->numItems++;
}

// return the element at index
int OurVector::get(int index) const {
    if (index < this->numItems && index >= 0) {
        return this->elements[index];
    } else {
        error("Index out of bounds!");
    }
}

// remove value from index
void OurVector::remove(int index){
    if (index < this->numItems && index >= 0) {
        for (int i = index; i < this->numItems + 1; i++) {
            this->elements[i] = this->elements[i + 1];
        }
        this->numItems--;
    } else {
        error("Index out of bounds!");
    }
}

// returns the number of elements
int OurVector::size() const {
    return this->numItems;
}

// returns true if there aren't any elements
bool OurVector::isEmpty() const {
    return this->numItems == 0;
}

// expand capacity
void OurVector::expand() {
    this->allocatedCapacity *= 2;
    int* newElements = new int[this->allocatedCapacity];
    for (int i = 0; i < this->numItems; i++) {
        newElements[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = newElements;
}

void OurVector::printDebugInfo() const {
    cout << endl;
    cerr << "allocatedCapacity: " << this->allocatedCapacity << endl;
    cerr << "numItems: " << this->numItems << endl;
    for (int i = 0; i < this->numItems; i++) {
        cerr << "index: " << i << "    value: " << this->elements[i] << endl;
    }
    cout << endl;
}


PROVIDED_TEST("Construct vector and see constructor/destructor be called."){
    OurVector vec;
}

PROVIDED_TEST("Check that newly created vector is empty"){
    OurVector vec;
    EXPECT_EQUAL(vec.isEmpty(), true);
}

PROVIDED_TEST("Add 5 elements to vector."){
    OurVector vec;
    for (int i = 0; i < 5; i++){
        vec.add(i);
    }

    EXPECT_EQUAL(vec.size(), 5);
    EXPECT_EQUAL(vec.isEmpty(), false);
    cout << endl;
    vec.printDebugInfo();
}

PROVIDED_TEST("Add 5 elements and then insert another element at index 3."){
    OurVector vec;
    for (int i = 0; i < 5; i++){
        vec.add(i);
    }

    vec.insert(3, 100);
    EXPECT_EQUAL(vec.size(), 6);
    EXPECT_EQUAL(vec.get(3), 100);

    cout << endl;
    vec.printDebugInfo();
}

PROVIDED_TEST("Add 5 elements and then remove element at index 3."){
    OurVector vec;
    for (int i = 0; i < 5; i++){
        vec.add(i);
    }

    vec.remove(3);
    EXPECT_EQUAL(vec.size(), 4);
    EXPECT_EQUAL(vec.get(3), 4);

    cout << endl;
    vec.printDebugInfo();
}

PROVIDED_TEST("Add 5 elements and then do an insertion at the very beginning and very end of vector."){
    OurVector vec;
    for (int i = 0; i < 5; i++){
        vec.add(i);
    }

    vec.insert(0, 200);
    EXPECT_EQUAL(vec.size(), 6);
    EXPECT_EQUAL(vec.get(0), 200);
    for (int i = 0; i < 5; i++){
        EXPECT_EQUAL(vec.get(i+1), i);
    }
    cout << endl;
    vec.printDebugInfo();

    vec.insert(6, 300);
    EXPECT_EQUAL(vec.size(), 7);
    EXPECT_EQUAL(vec.get(0), 200);
    for (int i = 0; i < 5; i++){
        EXPECT_EQUAL(vec.get(i+1), i);
    }
    EXPECT_EQUAL(vec.get(6), 300);
    vec.printDebugInfo();
}

PROVIDED_TEST("Add 50 elements. Tests expansion (twice)"){
    OurVector vec;
    for (int i = 0; i < 50; i++){
        vec.add(i);
    }

    vec.printDebugInfo();

    EXPECT_EQUAL(vec.size(), 50);
    for (int i = 0; i < 50; i++){
        EXPECT_EQUAL(vec.get(i), i);
    }
    EXPECT_EQUAL(vec.isEmpty(), false);
    cout << endl;
    vec.printDebugInfo();
}
