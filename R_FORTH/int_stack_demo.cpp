// main.c
#include "int_stack.h"
#include <iostream>


int main() {
    int_stack_t myStack;
    const int capacity = 5;

    // Initialize the stack with a capacity of 5.
    int_stack_init(&myStack, capacity);

    // Push values onto the stack.
    for (int i = 0; i < capacity; i++) {
        int success = intStackPush(&myStack, i);
        if (!success) {
            fprintf(stderr, "Stack overflow: %d\n", i);
        }
    }

    // Print the stack (top to bottom)
    intStackPrint(&myStack, stdout);

    // Pop values from the stack and print them.
    for (int i = 0; i < capacity; i++) {
        int topValue;
        int success = intStackPop(&myStack, &topValue);
        if (!success) {
            fprintf(stderr, "Stack empty\n");
        }
    }

    //Print the stack (top to bottom)
    intStackPrint(&myStack, stdout);

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
