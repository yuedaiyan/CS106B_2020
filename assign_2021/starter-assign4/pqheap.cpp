#include "pqheap.h"
#include "error.h"
#include "random.h"
#include "strlib.h"
#include "datapoint.h"
#include "testing/SimpleTest.h"
using namespace std;

const int INITIAL_CAPACITY = 10;
const int NONE = -1; // used as sentinel index

PQHeap::PQHeap() {
    _numFilled = 0;
    _numAllocated = INITIAL_CAPACITY;
    _elements = new DataPoint[_numAllocated]();
}

PQHeap::~PQHeap() {
    delete[] _elements;
}

void PQHeap::expand() {
    _numAllocated *= 2;
    DataPoint* newExpand = new DataPoint[_numAllocated];

    for (int i = 0; i < _numFilled; i++) {
        newExpand[i] = _elements[i];
    }

    delete[] _elements;
    _elements = newExpand;
}

void PQHeap::enqueue(DataPoint elem) {
    // expand() if array is full
    if (_numAllocated == _numFilled) {
        expand();
    }

    // put new element in to the array
    int currLocation = _numFilled;
    _elements[currLocation] = elem;
    _numFilled++;

    // 移动新加入元素，直到符合优先级要求
    while (currLocation != 0 && _elements[currLocation].priority < _elements[getParentIndex(currLocation)].priority) {
        DataPoint parentNode = _elements[getParentIndex(currLocation)];
        _elements[getParentIndex(currLocation)] = _elements[currLocation];
        _elements[currLocation] = parentNode;
        currLocation = getParentIndex(currLocation);
    }
}

DataPoint PQHeap::peek() const {
    if (isEmpty()) {
        error("队列为空，无法 .peek()");
    }
    return _elements[0];
}

// 运用递归搬运节点，自动覆盖根节点
void PQHeap::dequeueHelp(int parentIndex) {
    int leftChildIndex = getLeftChildIndex(parentIndex);
    int rightChildIndex = getRightChildIndex(parentIndex);

    int swapIndex;
    if (leftChildIndex < _numFilled || rightChildIndex < _numFilled) {
        if (leftChildIndex < _numFilled && rightChildIndex >= _numFilled) {
            swapIndex = leftChildIndex;
        } else if (rightChildIndex < _numFilled && leftChildIndex >= _numFilled) {
            swapIndex = rightChildIndex;
        } else {
            // (leftChildIndex < _numFilled && rightChildIndex < _numFilled)
            DataPoint leftChild = _elements[leftChildIndex];
            DataPoint rightChild = _elements[rightChildIndex];
            swapIndex = leftChild.priority <= rightChild.priority ? leftChildIndex : rightChildIndex;
        }
        DataPoint swapChild = _elements[swapIndex];

        // base case
        if (_elements[parentIndex].priority <= swapChild.priority) {
            return;
        }
        // recrusive case
        else {
            _elements[swapIndex] = _elements[parentIndex];
            _elements[parentIndex] = swapChild;
            dequeueHelp(swapIndex);
        }
    } else {
        return;
    }
}

DataPoint PQHeap::dequeue() {
    if (isEmpty()) {
        error("队列为空，无法 .dequeue()");
    }

    DataPoint result = peek();

    _elements[0] = _elements[size() - 1];
    _numFilled--;

    dequeueHelp(0);

    return result;
}

bool PQHeap::isEmpty() const {
    return _numFilled == 0;
}

int PQHeap::size() const {
    return _numFilled;
}

void PQHeap::clear() {
    _numFilled = 0;
}

void PQHeap::printDebugInfoHelp(int layer, int location) const {
    /*
    cout << "│";
    cout << "│";
    cout << "─";
    cout << "└──";
     */

    if (layer == 0) {
        cerr << string((layer) * 4, ' ');
    } else {
        cerr << string((layer - 1) * 4, ' ') << "│   ";
    }

    cerr << "├──" << _elements[location] << endl;
    int leftChindIndex = getLeftChildIndex(location);
    if (leftChindIndex < _numFilled) {
        printDebugInfoHelp(layer + 1, getLeftChildIndex(location));
    }
    int rightChindIndex = getRightChildIndex(location);
    if (rightChindIndex < _numFilled) {
        printDebugInfoHelp(layer + 1, getRightChildIndex(location));
    }
    return;
}

void PQHeap::printDebugInfo(string msg) const {
    cout << endl;
    cerr << "=================" << endl;
    if (msg != "") {
        cerr << msg << endl;
        cerr << "-----------------" << endl;
    }
    cerr << "allocated: " << _numAllocated << endl;
    cerr << "filled: " << _numFilled << endl;
    cerr << "-----------------" << endl;
    printDebugInfoHelp(0, 0);
    cerr << "=================" << endl;
}

void PQHeap::printDebugInfoBasic() const {
    cerr << "{";
    for (int i = 0; i < _numFilled; i++) {
        if (i != 0) {
            cerr << ", ";
        }

        cerr << _elements[i] << " ";
    }
    cerr << "}" << endl;
}

/*
 * which should traverse the heap array and ensure that the heap property
 * holds for all elements in the array. If elements are found that
 * violate the heap property, an error should be thrown.
 */
bool PQHeap::validateInternalStateHelp(int parent) const {
    DataPoint parentNode = _elements[parent];

    bool leftValidationResult = false;
    bool rightValidationResult = false;

    int leftChildIndex = getLeftChildIndex(parent);
    int rightChildIndex = getRightChildIndex(parent);

    if (leftChildIndex > _numFilled - 1) {
        leftValidationResult = true;
    } else {
        DataPoint leftChild = _elements[leftChildIndex];
        if (parentNode.priority <= leftChild.priority) {
            leftValidationResult = validateInternalStateHelp(leftChildIndex);
        }
    }

    if (rightChildIndex > _numFilled - 1) {
        rightValidationResult = true;
    } else {
        DataPoint rightChild = _elements[rightChildIndex];
        if (parentNode.priority <= rightChild.priority) {
            rightValidationResult = validateInternalStateHelp(rightChildIndex);
        }
    }

    // 最终判定
    if (leftValidationResult && rightValidationResult) {
        return true;
    } else {
        return false;
    }
}

void PQHeap::validateInternalState() const {
    if (isEmpty()) {
        return;
    }
    if (!validateInternalStateHelp(0)) {
        printDebugInfo("当前PQheap排序非法");
        error("当前PQheap排序非法");
    }
}

int PQHeap::getParentIndex(int child) const {
    if (child == 0) {
        return NONE;
    }
    return (child - 1) / 2;
}

int PQHeap::getLeftChildIndex(int parent) const {
    return parent * 2 + 1;
}

int PQHeap::getRightChildIndex(int parent) const {
    return parent * 2 + 2;
}

void PQHeap::unSortedAdd(int index, DataPoint elem, bool numAddQues) {
    // expand() if array is full
    if (_numAllocated == _numFilled) {
        expand();
    }

    if (numAddQues) {
        _numFilled++;
    }

    _elements[index] = elem;
}

/* * * * * * Test Cases Below This Point * * * * * */
STUDENT_TEST("validateInternalState() test: two sorted value") {
    cout << endl;
    PQHeap pq;
    EXPECT_EQUAL(pq.size(), 0);
    cerr << "a 4 start" << endl;
    pq.unSortedAdd(0, { "A", 4 }, true);

    EXPECT_EQUAL(pq.size(), 1);
    pq.validateInternalState();

    cerr << "b 5 start" << endl;
    pq.unSortedAdd(1, { "B", 5 }, true);
    pq.validateInternalState();
    EXPECT_EQUAL(pq.size(), 2);
    int de = pq.dequeue().priority;
    EXPECT_EQUAL(de, 4);
    EXPECT_EQUAL(pq.size(), 1);
}

STUDENT_TEST("dequeue() 一次只会减少 1 的size") {
    cout << endl;
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 1 }, { "A", 2 }, { "B", 3 }, { "K", 4 }, { "G", 5 },
        { "V", 6 }, { "T", 7 }, { "O", 8 }, { "S", 9 }
    };

    for (int i = 0; i < input.size(); i++) {
        pq.unSortedAdd(i, input[i], true);
        pq.validateInternalState();
    }

    pq.printDebugInfo("关注size，应该是9");
    pq.dequeue();
    cout << "--------" << endl;
    pq.printDebugInfoBasic();
    // pq.printDebugInfo("关注size，应该是8");
    EXPECT_EQUAL(input.size() - 1, pq.size());
}

STUDENT_TEST("validateInternalState() test: more sorted value") {
    cout << endl;
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 1 }, { "A", 2 }, { "B", 3 }, { "K", 4 }, { "G", 5 },
        { "V", 6 }, { "T", 7 }, { "O", 8 }, { "S", 9 }
    };

    for (int i = 0; i < input.size(); i++) {
        pq.unSortedAdd(i, input[i], true);
        pq.validateInternalState();
    }
    pq.validateInternalState();
}

STUDENT_TEST("validateInternalState() test: unsorted value") {
    cout << endl;
    PQHeap pq;
    Vector<DataPoint> input = {
        { "V", 6 }, { "T", 7 }, { "O", 8 }, { "S", 9 },
        { "R", 1 }, { "A", 2 }, { "B", 3 }, { "K", 4 }, { "G", 5 }
    };

    for (int i = 0; i < input.size(); i++) {
        pq.unSortedAdd(i, input[i], true);
        // EXPECT_ERROR(pq.validateInternalState());
    }
    EXPECT_ERROR(pq.validateInternalState());
}

STUDENT_TEST("printDebugInfo() test: ") {
    cout << endl;
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 }
    };

    for (DataPoint dp : input) {
        pq.enqueue(dp);
    }

    EXPECT(pq.size() == input.size());

    pq.printDebugInfo("");

    EXPECT(true);
}

/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("PQHeap example from writeup, validate each step") {
    PQHeap pq;
    Vector<DataPoint> input = {
        { "R", 4 }, { "A", 5 }, { "B", 3 }, { "K", 7 }, { "G", 2 },
        { "V", 9 }, { "T", 1 }, { "O", 8 }, { "S", 6 }
    };

    for (DataPoint dp : input) {
        pq.enqueue(dp);
        pq.validateInternalState();
    }
    while (!pq.isEmpty()) {
        pq.dequeue();
        pq.validateInternalState();
    }
}

/* * test from pqarray.cpp * */

void pqheap_fillQueue(PQHeap& pq, int n) {
    pq.clear(); // start with empty queue
    for (int i = 0; i < n; i++) {
        pq.enqueue({ "", randomReal(0, 10) });
    }
}

void pqheap_emptyQueue(PQHeap& pq, int n) {
    for (int i = 0; i < n; i++) {
        pq.dequeue();
    }
}

STUDENT_TEST("normal test: ") {
    PQHeap pq;
    for (int i = 0; i < 20; i++) {
        pq.enqueue({ randomColorString(), randomInteger(-1000, 1000) });
    }
    pq.validateInternalState();
}

STUDENT_TEST("simple enqueue() and dequeue() test: ") {
    PQHeap pq;
    pq.enqueue({ "", 1 });
    EXPECT_NO_ERROR(pq.dequeue());
}

STUDENT_TEST("PQHeap timing test, pqheap_fillQueue and pqheap_emptyQueue") {
    cout << endl;
    for (int i = 1; i < 7; i++) {
        cerr << "i: " << i << endl;
        PQHeap pq;
        int bigI = i * 10000;

        TIME_OPERATION(bigI, pqheap_fillQueue(pq, bigI));
        EXPECT(!pq.isEmpty());
        EXPECT_EQUAL(pq.size(), bigI);
        cerr << "mark 1" << endl;
        TIME_OPERATION(bigI, pqheap_emptyQueue(pq, bigI));
        cerr << "mark 2" << endl;
    }
}

PROVIDED_TEST("PQHeap example from writeup") {
    PQHeap pq;

    pq.enqueue({ "Zoe", -3 });
    pq.enqueue({ "Elmo", 10 });
    pq.enqueue({ "Bert", 6 });
    EXPECT_EQUAL(pq.size(), 3);
    pq.printDebugInfo("After enqueue 3 elements");

    pq.enqueue({ "Kermit", 5 });
    EXPECT_EQUAL(pq.size(), 4);
    pq.printDebugInfo("After enqueue one more");

    DataPoint removed = pq.dequeue();
    DataPoint expected = { "Zoe", -3 };
    EXPECT_EQUAL(removed, expected);
    pq.printDebugInfo("After dequeue one");
}

PROVIDED_TEST("PQHeap, enqueue only, validate at every step") {
    PQHeap pq;

    pq.enqueue({ "e", 2.718 });
    pq.validateInternalState();
    pq.enqueue({ "pi", 3.14 });
    pq.validateInternalState();
    pq.enqueue({ "phi", 1.618 });
    pq.validateInternalState();
    EXPECT_EQUAL(pq.size(), 3);
}

PROVIDED_TEST("PQHeap: operations size/isEmpty/clear") {
    PQHeap pq;

    EXPECT(pq.isEmpty());
    pq.clear();
    EXPECT_EQUAL(pq.isEmpty(), pq.size() == 0);
    pq.enqueue({ "", 7 });
    EXPECT_EQUAL(pq.size(), 1);
    pq.enqueue({ "", 5 });
    EXPECT_EQUAL(pq.size(), 2);
    pq.enqueue({ "", 5 });
    EXPECT_EQUAL(pq.size(), 3);
    pq.clear();
    pq.validateInternalState();
    EXPECT(pq.isEmpty());
    EXPECT_EQUAL(pq.size(), 0);
}

PROVIDED_TEST("PQHeap: dequeue or peek on empty queue raises error") {
    PQHeap pq;
    DataPoint point = { "Programming Abstractions", 106 };

    EXPECT(pq.isEmpty());
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());

    pq.enqueue(point);
    pq.dequeue();
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());

    pq.enqueue(point);
    pq.clear();
    EXPECT_ERROR(pq.dequeue());
    EXPECT_ERROR(pq.peek());
}

PROVIDED_TEST("PQHeap, dequeue, validate at every step") {
    PQHeap pq;

    pq.enqueue({ "e", 2.718 });
    pq.enqueue({ "pi", 3.14 });
    pq.enqueue({ "phi", 1.618 });

    for (int i = 0; i < 3; i++) {
        pq.dequeue();
        pq.validateInternalState();
    }
}

PROVIDED_TEST("PQHeap, test enlarge array memory") {
    for (int size = 5; size <= 500; size *= 5) {
        PQHeap pq;

        for (int i = 1; i <= size; i++) {
            pq.enqueue({ "", double(i) });
        }
        pq.validateInternalState();

        for (int i = 1; i <= size; i++) {
            DataPoint expected = { "", double(i) };
            EXPECT_EQUAL(pq.dequeue(), expected);
        }
    }
}

PROVIDED_TEST("PQHeap, sequence of mixed operations") {
    PQHeap pq;
    int size = 30;
    double val = 0;

    for (int i = 0; i < size; i++) {
        pq.enqueue({ "", --val });
    }
    val = 0;
    for (int i = 0; i < pq.size(); i++) {
        DataPoint front = pq.peek();
        EXPECT_EQUAL(pq.dequeue(), front);
        pq.enqueue({ "", ++val });
    }

    EXPECT_EQUAL(pq.size(), size);
    val = 0;
    while (!pq.isEmpty()) {
        DataPoint expected = { "", ++val };
        EXPECT_EQUAL(pq.dequeue(), expected);
    }
}

PROVIDED_TEST("PQHeap stress test, cycle many random elements in and out") {
    PQHeap pq;
    int n = 0, maxEnqueues = 1000;
    double sumEnqueued = 0, sumDequeued = 0;

    setRandomSeed(42); // make test behavior deterministic

    DataPoint mostUrgent = { "", 0 };
    pq.enqueue(mostUrgent);
    while (true) {
        if (++n < maxEnqueues && randomChance(0.9)) {
            DataPoint elem = { "", randomInteger(-10, 10) + 0.5 };
            if (elem.priority < mostUrgent.priority) {
                mostUrgent = elem;
            }
            sumEnqueued += elem.priority;
            pq.enqueue(elem);
        } else {
            DataPoint elem = pq.dequeue();
            sumDequeued += elem.priority;
            EXPECT_EQUAL(elem, mostUrgent);
            if (pq.isEmpty())
                break;
            mostUrgent = pq.peek();
        }
    }
    EXPECT_EQUAL(sumEnqueued, sumDequeued);
}

PROVIDED_TEST("PQHeap timing test, pqheap_fillQueue and pqheap_emptyQueue") {
    PQHeap pq;
    int n = 20000;

    TIME_OPERATION(n, pqheap_fillQueue(pq, n));
    TIME_OPERATION(n, pqheap_emptyQueue(pq, n));
}
