// int_stack_demo.cpp
#include "int_stack.hpp"
#include <iostream>


int main() {
    Stack myStack(5);

    // Push values onto the stack.
    for (int i = 0; i < capacity; i++) {
        int success = myStack.intStackPush(i);
        if (!success) {
            cerr << "Stack overflow\n";
        }
    }

    // Print the stack (top to bottom)
    myStack.intStackPrint();

    // Pop values from the stack and print them.
    for (int i = 0; i < capacity; i++) {
        int topValue;
        int success = intStackPop(&topValue);
        if (!success) {
            cerr << "Stack empty\n";
        }
    }

    //Print the stack (top to bottom)
    intStackPrint();

    // Quick tests for swap, dup, and add.

    intStackPush(7);
    intStackPush(8);
    intStackPrint();
    intStackSwap();
    intStackPrint();
    intStackAdd();
    intStackPrint(); // hopefully, 15 only item on stack!
    intStackDup();
    intStackPrint(); // hopefully, 15 only item on stack!
    intStackAdd();
    intStackPrint(); // hopefully, 30 only item on stack!
    return 0;
}
