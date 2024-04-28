// int_stack.hpp - interface to the int_stack


#ifndef INT_STACK_HPP
#define INT_STACK_HPP

#include <iostream>
#include <queue>

enum TokenTypeT{NUMBER = 0, OPERATOR = 1, SYMBOL = 2, WORD = 3};

class Stack{
    protected:
        int capacity;
        int size;
        int contents[];
    public:
        int intStackPush(int value);
        int intStackPop(int *topValue);
        int intStackTop(int *topValue);
        int int_stack_dup();
        int intStackSwap();
        int int_stack_over();
        int intStackRot();
        int intStackDrop();
        int intStack2Swap();
        int intStack2Drop();
        int intStack2Dup();
        int intStack2Over();
        int intStackAdd();
        int intStackSubtract();
        int intStackMultiply();
        int intStackDivide();
        int intStackModAndQuotient();
        int intStackModOnly();
        void intStackPrint();
        int intStackSize();
        int intStackCapacity();

};

#endif // INT_STACK_H
