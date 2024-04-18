// main.c
#include "int_stack.h"
#include <stdio.h>


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

    intStackPush(&myStack, 7);
    intStackPush(&myStack, 8);
    intStackPrint(&myStack, stdout);
    intStackSwap(&myStack);
    intStackPrint(&myStack, stdout);
    intStackAdd(&myStack);
    intStackPrint(&myStack, stdout); // hopefully, 15 only item on stack!
    int_stack_dup(&myStack);
    intStackPrint(&myStack, stdout); // hopefully, 15 only item on stack!
    intStackAdd(&myStack);
    intStackPrint(&myStack, stdout); // hopefully, 30 only item on stack!
    return 0;
}
