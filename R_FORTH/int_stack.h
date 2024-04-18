// int_stack.h - interface to the int_stack

#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <sys/queue.h>

typedef struct int_entry {
    int value;
    SLIST_ENTRY(int_entry) entries;
} int_entry_t;

typedef struct int_stack {
    SLIST_HEAD(stackhead, int_entry) head;
    int size;
    int capacity;
} int_stack_t;

extern void int_stack_init(int_stack_t *stk, int capacity);
extern int intStackPush(int_stack_t *stk, int value);
extern int intStackPop(int_stack_t *stk, int *topValue);
extern int intStackTop(int_stack_t *stk, int *topValue);
extern int int_stack_dup(int_stack_t *stk);
extern int intStackSwap(int_stack_t *stk);
extern int int_stack_over(int_stack_t *stk);
extern int intStackRot(int_stack_t *stk);
extern int intStackDrop(int_stack_t *stk);
extern int intStack2Swap(int_stack_t *stk);
extern int intStack2Drop(int_stack_t *stk);
extern int intStack2Dup(int_stack_t *stk);
extern int intStack2Over(int_stack_t *stk);
extern int intStackAdd(int_stack_t *stk);
extern int intStackSubtract(int_stack_t *stk);
extern int intStackMultiply(int_stack_t *stk);
extern int intStackDivide(int_stack_t *stk);
extern int intStackModAndQuotient(int_stack_t *stk);
extern int intStackModOnly(int_stack_t *stk);
extern void intStackPrint(int_stack_t *stk, FILE *file);
extern int intStackSize(int_stack_t* stk);
extern int intStackCapacity(int_stack_t* stk);

#endif // INT_STACK_H
