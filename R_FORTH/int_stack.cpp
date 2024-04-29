// int_stack.cpp

#include <iostream>
#include <string>
#include "int_stack.hpp"

using namespace std;

 
Stack::Stack(int c){
    capacity = c;
    size = 0;
    int arr[c];
    *contents = arr;
}

// void int_stack_init(, int capacity) {
//     SLIST_INIT(&stk->head);
//     size = 0;
//     capacity = capacity;
// }



/* ---CURRENT STORAGE METHOD--- */

//The position in the stack as stored in the array is 
//currently arr[0] = first stack item 
int Stack::intStackPush(int v){
    if (size >= capacity){ 
        cout << "Stack is at full capacity.\n";
        return 0; //fail
    }
    *contents[size - 1] = v;
    size++;
    return 1; //success
}

//TODO
//Note: to preserve inportant functionality, please keep it
//so that intStackPop takes an argument that allows the
//value popped to be stored for later. Ex:
//intStackPop(&topValue) should allow the popped int to 
//be stored in topValue.
//int Stack::intStackPop(int *topValue = 0) {
   // int valueOnTop = *contents[size - 1];
   // *topValue = valueOnTop;
    //*contents[size - 1] = 0;
  //  size--;
    //return 1;

//Rewritten by Emilie
int Stack::intStackPop(int *topValue) {
    if (size <= 0) {
        cout << "Stack is empty.\n";
        return 0; // fail
    }
    *topValue = contents[--size];
    return 1; // success
}

//TODO
int Stack::intStackTop(int *topValue = 0) {
    int valueOnTop = *contents[size - 1];
    *topValue = valueOnTop;
    return 1;
}

/* Functions for FORTH langauge stack operators */

//REWRITTEN
int Stack::intStackDup(){
    if (size < 1){ //no value to dup
        return 0; //fail
    }
    int topValue;
    intStackTop(&topValue); //subject to change, assumes intStackTop needs no arguments
    return intStackPush(topValue); //will return 1 if push success
}

//REWRITTEN
int Stack::intStackSwap() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPush(topValue);
    return intStackPush(nextToTopValue); 
}

//REWRITTEN
int Stack::intStackOver() {
    if (size < 2){
        return 0; //must have 2 values to do over
    }
    int topValue, nextToTopValue;
    intStackPop(&topValue); //TODO: once pop is rewritten, ensure this works
    intStackPop(&nextToTopValue);
    intStackPush(nextToTopValue);
    intStackPush(topValue);
    return intStackPush(nextToTopValue);
}

//REWRITTEN
int Stack::intStackRot() {
    if (size < 3)
        return 0;
    int topValue, nextToTopValue, thirdValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPop(&thirdValue);
    intStackPush(nextToTopValue);
    intStackPush(topValue);
    return intStackPush(thirdValue);
}

//REWRITTEN
int Stack::intStackDrop() {
    if (size < 1)
        return 0;
    int topValue, nextToTopValue;
    return intStackPop(&topValue);
}

//REWRITTEN
int Stack::intStack2Swap() {
    if (size < 4)
        return 0;
    int topValue, nextToTopValue, thirdValue, fourthValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPop(&thirdValue);
    intStackPop(&fourthValue);
    intStackPush(thirdValue);
    intStackPush(fourthValue);
    intStackPush(topValue);
    return intStackPush(nextToTopValue); 
}

//REWRITTEN
int Stack::intStack2Drop() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    return intStackPop(&nextToTopValue);
}

//REWRITTEN
int Stack::intStack2Dup() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPush(nextToTopValue);
    intStackPush(topValue);
    intStackPush(nextToTopValue);
    return intStackPush(topValue);
}

//REWRITTEN
int Stack::intStack2Over() {
    if (size < 4)
        return 0;
    int topValue, nextToTopValue, thirdValue, fourthValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPop(&thirdValue);
    intStackPop(&fourthValue);
    intStackPush(fourthValue);
    intStackPush(thirdValue);
    intStackPush(nextToTopValue);
    intStackPush(topValue);
    intStackPush(thirdValue);
    return intStackPush(fourthValue);
}

/* Example of how to create a binary operator that works o top two elements (if present) */

//REWRITTEN
int Stack::intStackAdd() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(topValue + nextToTopValue);
}

//REWRITTEN
int Stack::intStackSubtract() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(nextToTopValue - topValue);
}

//REWRITTEN
int Stack::intStackMultiply() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(topValue * nextToTopValue);
}

//REWRITTEN
int Stack::intStackDivide() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(nextToTopValue / topValue);
}

//REWRITTEN
int Stack::intStackModAndQuotient() { // /mod
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPush(nextToTopValue / topValue);
    return intStackPush(nextToTopValue % topValue);
}

//REWRITTEN
int Stack::intStackModOnly() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(nextToTopValue % topValue);
}

//TODO
int Stack::intStackGreaterThan() { //>
    if (size < 2)
        return 0;
    int topValue, nextToTopValue, result;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    if (topValue >= nextToTopValue){
        result = 0;
    }
    else {
        result = -1;
    }
    return intStackPush(result);
}

//REWRITTEN
int Stack::intStackLessThan() { //<
    if (size < 2)
        return 0;
    int topValue, nextToTopValue, result;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    if (topValue <= nextToTopValue){
        result = 0;
    }
    else {
        result = -1;
    }
    return intStackPush(result);
}

//TODO
void Stack::intStackPrint() {
    string printString = "i:  v: \n";
    for (int i = 0; i < size; i++){
        string appendMe = to_string(i) + " | " + to_string(*contents[i]);
        printString += appendMe;
    }
    cout << printString;
}


//REWRITTEN
int Stack::intStackSize() {
    return size;
}
//REWRITTEN
int Stack::intStackCapacity() {
    return capacity;
}


