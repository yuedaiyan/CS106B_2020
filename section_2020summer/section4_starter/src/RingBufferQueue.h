/***********************************************************************
 * File: RingBufferQueue.h
 * This file defines the interface of a first-in, first-out data
 * structure called the RingBufferQueue, as defined in Section Handout
 * #4 on Classes and Objects. This data structure is implemented using
 * a dynamically-allocated array that acts a circular buffer.
 *
 * The section handout was created by Marty Stepp, Julie Zelenski, and
 * Kate Rydberg. Links to the section handout and the solution PDF are
 * available from the CS106B course website. This starter code project
 * was put together by Anand Shankar.
 */
#pragma once

#include <iostream>

class RBQueue {

public:
    // 构建对象
    RBQueue();
    // 析构对象
    ~RBQueue();
    // 方法：添加元素
    void enqueue(int elem);
    // 方法：删除元素（先进先出）
    int dequeue();
    // 方法：看一眼第一个元素（不删除任何元素）
    int peek() const;
    // 方法：看是不是空对象
    bool isEmpty() const;
    // 方法：看对象是否填满
    bool isFull() const;
    // 方法：看对象大小
    int size() const;

private:
    int _maxCapacity;
    int* _elements;
    int _head;
    int _tail;
    int _classSize;

    // out输出方法
    friend std::ostream& operator<<(std::ostream& out, const RBQueue& queue);
};
