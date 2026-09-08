/***********************************************************************
 * File: RingBufferQueue.cpp
 */
#include "RingBufferQueue.h"
#include "error.h"
#include "testing/SimpleTest.h"

using namespace std;

int currMax = 5;

// 构建对象
RBQueue::RBQueue() {
    this->_maxCapacity = currMax;
    this->_elements = new int[_maxCapacity];
    this->_head = 0;
    this->_tail = _maxCapacity - 1;
    this->_classSize = 0;
}

// 析构对象
RBQueue::~RBQueue() {
    delete[] this->_elements;
}

// 方法：添加元素
void RBQueue::enqueue(int elem) {
    if (this->_classSize >= this->_maxCapacity) {
        error("Out of bounds!");
    }
    // if (this->_classSize == 0) {
    //     this->_elements[this->_head] = elem;
    // } else {
    this->_tail = (this->_tail + 1) % this->_maxCapacity;
    this->_elements[this->_tail] = elem;
    // }
    this->_classSize++;
}

// 方法：删除元素（先进先出）
int RBQueue::dequeue() {
    if (this->_classSize <= 0) {
        error("Out of bounds!");
    }
    int result = this->_elements[this->_head];
    this->_head = (this->_head + 1) % this->_maxCapacity;
    this->_classSize--;
    return result;
}

// 方法：看一眼第一个元素（不删除任何元素）
int RBQueue::peek() const {
    if (this->_classSize <= 0) {
        error("Out of bounds!");
    }
    return this->_elements[this->_head];
}

// 方法：看是不是空对象
bool RBQueue::isEmpty() const {
    return _classSize == 0;
}

// 方法：看对象是否填满
bool RBQueue::isFull() const {
    return this->_classSize == this->_maxCapacity;
}

// 方法：看对象大小
int RBQueue::size() const {
    return this->_classSize;
}

// out输出方法
ostream& operator<<(ostream& out, const RBQueue& queue) {
    out << "{";
    for (int i = 0; i < queue._classSize; i++) {
        if (i != 0) {
            out << ", ";
        }
        int index = (queue._head + i) % queue._maxCapacity;
        out << queue._elements[index];
    }
    out << "}";
    return out;
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example From Handout"){
    cout << endl;
    RBQueue q;
    q.enqueue(1);
    cerr << q << endl;

    q.enqueue(2);
    cerr << q << endl;

    q.enqueue(3);
    cerr << q << endl;

    EXPECT_EQUAL(q.peek(), 1);
    q.enqueue(4);
    cerr << q << endl;

    q.enqueue(5);
    cerr << q << endl;

    // EXPECT(!q.isFull());
    EXPECT(q.isFull());
    EXPECT_EQUAL(q.dequeue(), 1);
    EXPECT_EQUAL(q.dequeue(), 2);
    EXPECT_EQUAL(q.peek(), 3);
    q.enqueue(6);
    cerr << q << endl;

    EXPECT_EQUAL(q.dequeue(), 3);
    EXPECT_EQUAL(q.dequeue(), 4);
    EXPECT_EQUAL(q.dequeue(), 5);
    EXPECT_EQUAL(q.dequeue(), 6);
    EXPECT(q.isEmpty());
}

STUDENT_TEST("Queue can be reused after becoming empty") {
    RBQueue q;

    q.enqueue(10);
    EXPECT_EQUAL(q.dequeue(), 10);
    EXPECT(q.isEmpty());

    q.enqueue(20);
    q.enqueue(30);

    EXPECT_EQUAL(q.peek(), 20);
    EXPECT_EQUAL(q.dequeue(), 20);
    EXPECT_EQUAL(q.dequeue(), 30);
    EXPECT(q.isEmpty());
}