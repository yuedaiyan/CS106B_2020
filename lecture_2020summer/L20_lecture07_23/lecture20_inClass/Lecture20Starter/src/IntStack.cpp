#include "IntStack.h"
#include "error.h"
#include "testing/SimpleTest.h"

IntStack::IntStack() {
    top = nullptr;
}

IntStack::~IntStack() {
    while (!this->isEmpty()) {
        Node* temp = this->top;
        this->top = this->top->next;
        delete temp;
    }
}

void IntStack::push(int value) {
    Node* temp = new Node;
    temp->data = value;
    temp->next = this->top;
    this->top = temp;
}

int IntStack::pop() {
    if (isEmpty()) {
        error("Error trying to pop from an empty stack");
    }
    Node* temp = this->top;
    this->top = temp->next;
    int result = temp->data;
    delete temp;
    return result;
}

bool IntStack::isEmpty(){
    return top == nullptr;
}

PROVIDED_TEST("Reverse simple set of values"){
    IntStack stack;
    for (int i = 0; i < 10; i++){
        stack.push(i);
    }
    for (int i = 9; i >= 0; i--){
        EXPECT_EQUAL(i, stack.pop());
    }
}
