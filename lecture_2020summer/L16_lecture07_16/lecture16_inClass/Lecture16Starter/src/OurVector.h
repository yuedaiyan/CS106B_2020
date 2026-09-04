/*********************************************************
 * File: OurVector.h
 *
 * A class representing a vector that holds integers.
 */
#pragma once

const int INITIAL_CAPACITY = 8;

class OurVector {
public:
    OurVector();
    ~OurVector();


    // append value at end
    void add(int value);

    // insert a value at index
    void insert(int index, int value);

    // return value at index
    int get(int index);

    // remove value at index
    void remove(int index);

    // return the number of elements in the array
    int size() const;

    // true if zero elements
    bool isEmpty() const;

private:
    /* TODO: What information should go here? */
};
