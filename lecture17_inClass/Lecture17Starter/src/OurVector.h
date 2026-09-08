// OurVector.h
// Header file for our Vector of ints Class
#pragma once

#include<ostream>
using namespace std;

class OurVector {
public:
    OurVector(); // constructor
    ~OurVector(); // destructor

    void add(int value); // append value at end
    void insert(int index, int value); // insert a value at index
    int get(int index) const; // return value at index
    void remove(int index); // remove value at index
    int size() const; // return the number of elements in the array
    bool isEmpty() const; // true if zero elements

    /* Useful for viewing and debugging internal state of vector. */
    void printDebugInfo() const;

private:
    int* elements;
    int allocatedCapacity;
    int numItems;
};
