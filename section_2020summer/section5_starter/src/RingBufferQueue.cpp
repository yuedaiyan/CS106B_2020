#include "RingBufferQueue.h"
#include "error.h"
#include "testing/SimpleTest.h"

using namespace std;

const int kDefaultCapacity = 5;

/* purpose      : 构建函数
 * arguments    : None
 * return value : None
 */
RBQueue::RBQueue() {
    _elements = new int[kDefaultCapacity];
    _head = 0;
    _size = 0;
    _max = kDefaultCapacity;
}

/* purpose      : 析构函数
 * arguments    : None
 * return value : None
 */
RBQueue::~RBQueue() {
    delete[] _elements;
}

/* purpose      : 向队列添加元素
 * arguments    : 新加入的元素（int）
 * return value : None
 */
void RBQueue::enqueue(int elem) {
    // expand if the queue is full
    if (_size == _max) {
        _expand();
    }
    _elements[(_head + _size) % _max] = elem;
    _size++;
}

/* purpose      : 弹出队列的第一个元素
 * arguments    : None
 * return value : 第一个元素的值（int）
 */
int RBQueue::dequeue() {
    if (isEmpty()) {
        error("Can't dequeue at an empty queue!");
    }
    int result = _elements[_head];
    _head = (_head + 1) % _max;
    _size--;
    return result;
}

/* purpose      : 窥探队列的第一个元素
 * arguments    : None
 * return value : 第一个元素值（int）
 */
int RBQueue::peek() const {
    if (isEmpty()) {
        error("Can't peek at an empty queue!");
    }
    return _elements[_head];
}

/* purpose      : 判断队列是不是为空
 * arguments    : None
 * return value : （bool）
 */
bool RBQueue::isEmpty() const {
    return _size == 0;
}

/* purpose      : 判断队列是不是充满
 * arguments    : None
 * return value : （bool）
 */
bool RBQueue::isFull() const {
    return _size == _max;
}

/* purpose      : 求队列实际存入元素大小
 * arguments    : None
 * return value : 大小（int）
 */
int RBQueue::size() const {
    return _size;
}

/* purpose      : 扩容函数（扩容一倍）
 * arguments    : none
 * return value : none
 */
void RBQueue::_expand() {
    int* newElements = new int[_max * 2];

    int currPos = _head;
    for (int i = 0; i < _size; i++) {
        newElements[i] = _elements[currPos];
        currPos = (currPos + 1) % _max;
    }
    _max *= 2;
    _head = 0;
    /*
    cerr << "new elements: " << endl;
    for (int i = 0; i < _max; i++) {
        cout << newElements[i] << "  ";
    }
    cout << endl;
    */
    delete[] _elements;
    _elements = newElements;
}

/* purpose      : out 输出流
 * arguments    : out，队列本体
 * return value : ostream
 */
ostream& operator<<(ostream& out, const RBQueue& queue) {
    out << "{";

    int curr = queue._head;
    for (int i = 0; i < queue._size; i++) {
        if (i != 0) {
            out << ", ";
        }
        int index = (queue._head + i) % queue._max;
        out << queue._elements[index];
    }

    out << "}";
    return out;
}

/* Provided Tests Below This Line */
PROVIDED_TEST("Simple Example From Handout, No resizing") {
    RBQueue q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    EXPECT_EQUAL(q.peek(), 1);
    q.enqueue(4);
    q.enqueue(5);
    EXPECT(q.isFull());
    EXPECT_EQUAL(q.dequeue(), 1);
    EXPECT_EQUAL(q.dequeue(), 2);
    EXPECT_EQUAL(q.peek(), 3);
    q.enqueue(6);
    EXPECT_EQUAL(q.dequeue(), 3);
    EXPECT_EQUAL(q.dequeue(), 4);
    EXPECT_EQUAL(q.dequeue(), 5);
    EXPECT_EQUAL(q.dequeue(), 6);
    EXPECT(q.isEmpty());
}

PROVIDED_TEST("Example from Handout, with Resizing") {
    cout << endl;
    RBQueue q;
    cerr << q << endl;
    for (int i = 10; i <= 50; i += 10) {
        q.enqueue(i);
    }
    cerr << q << endl;
    EXPECT(q.isFull());

    // Adding the 6th element should trigger a resizing
    q.enqueue(60);
    cerr << q << endl;

    EXPECT(!q.isFull());

    for (int i = 10; i <= 60; i += 10) {
        EXPECT_EQUAL(i, q.peek());
        EXPECT_EQUAL(i, q.dequeue());
    }
    EXPECT(q.isEmpty());
}

STUDENT_TEST("绕回后扩容") {
    RBQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);

    q.dequeue(); // 删除 10
    q.dequeue(); // 删除 20

    q.enqueue(60);
    q.enqueue(70); // 此时数组已经绕回，并再次装满
    q.enqueue(80); // 这里触发扩容

    for (int value = 30; value <= 80; value += 10) {
        EXPECT_EQUAL(q.dequeue(), value);
    }

    EXPECT(q.isEmpty());
}