// int_stack.hpp - interface to the int_stack


#ifndef INT_STACK_HPP
#define INT_STACK_HPP

#include <iostream>
#include <queue>
#include <string>

using namespace std;

enum TokenTypeT{NUMBER = 0, OPERATOR = 1, SYMBOL = 2, WORD = 3};

class Stack{
    protected:
        int capacity;
        int size;
        int *contents[]; //should we get rid of the '[]' so it matches the declaration in int_stack.cpp?
    public:
        Stack(int c);
        int intStackPush(int value);
        int intStackPop(int *topValue);
        int intStackTop(int *topValue);
        int intStackDup();
        int intStackSwap();
        int intStackOver();
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
        int intStackGreaterThan();
        int intStackLessThan();
        void intStackPrint();
        int intStackSize();
        int intStackCapacity();
};

enum TokenTypeT findTokenType(string s);

#endif // INT_STACK_H
