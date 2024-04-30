// int_stack.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "int_stack.hpp"

using namespace std;

 
Stack::Stack(int c){
    capacity = c;
    size = 0;
}

//Thoughts on how we might intergrate variables: 
// - storage & retrieval 
// - add a function to create the variables (need to figure out how to store variable names and their values)
// - store variables within stack class (need to figure out how to do this)


/* ---CURRENT STORAGE METHOD--- */

//The position in the stack as stored in the vector is 
//currently contents[0] = first stack item 
int Stack::intStackPush(int v){
    if (size >= capacity){ 
        cout << "Stack is at full capacity." << endl;
        return 0; //fail
    }
    contents.push_back(v);
    size++;
    return 1; //success
}


int Stack::intStackPop(int *topValue) {
    if (size <= 0) {
        cout << "Stack is empty.\n";
        return 0; // fail
    }
    *topValue = contents[--size];
    contents.pop_back();
    return 1; // success
}


int Stack::intStackTop(int *topValue) {
    if (size <= 0) {
        cout << "Stack is empty." << endl;
        return 0;
    }
    *topValue = contents[size - 1];
    return 1; 
}

/* Functions for FORTH langauge stack operators */


int Stack::intStackDup(){
    if (size < 1){ //no value to dup
        return 0; //fail
    }
    int topValue;
    intStackTop(&topValue); //subject to change, assumes intStackTop needs no arguments
    return intStackPush(topValue); //will return 1 if push success
}


int Stack::intStackSwap() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPush(topValue);
    return intStackPush(nextToTopValue); 
}


int Stack::intStackOver() {
    if (size < 2){
        return 0; //must have 2 values to do over
    }
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPush(nextToTopValue);
    intStackPush(topValue);
    return intStackPush(nextToTopValue);
}


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


int Stack::intStackDrop() {
    if (size < 1)
        return 0;
    int topValue, nextToTopValue;
    return intStackPop(&topValue);
}


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


int Stack::intStack2Drop() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    return intStackPop(&nextToTopValue);
}


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


int Stack::intStackAdd() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(topValue + nextToTopValue);
}


int Stack::intStackSubtract() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(nextToTopValue - topValue);
}


int Stack::intStackMultiply() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(topValue * nextToTopValue);
}


int Stack::intStackDivide() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(nextToTopValue / topValue);
}


int Stack::intStackModAndQuotient() { // /mod
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    intStackPush(nextToTopValue / topValue);
    return intStackPush(nextToTopValue % topValue);
}


int Stack::intStackModOnly() {
    if (size < 2)
        return 0;
    int topValue, nextToTopValue;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    return intStackPush(nextToTopValue % topValue);
}


int Stack::intStackGreaterThan() { //>
    if (size < 2)
        return 0;
    int topValue, nextToTopValue, result;
    intStackPop(&topValue);
    intStackPop(&nextToTopValue);
    if (topValue > nextToTopValue){ //Changed the condition to check if topValue is greater than nextToTopValue
        result = 1; //Return 1 if topValue is greater than nextToTopValue
    }
    else {
        result = 0; //Otherwise, return 0
    }
    return intStackPush(result);
}


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

 
void Stack::intStackPrint() {
    cout << "Stack:";
    for (int i = size - 1; i >= 0; --i) {
        int v = contents[i];
        cout << " " << v;
    }
    cout << endl;
}

int Stack::intStackSize() {
    return size;
}

int Stack::intStackCapacity() {
    return capacity;
}

bool Stack::createMapEntry(const string& varName){
    
}

void Stack::createVariable(const string& varName, int value){
    variables[varName] = value;

}

bool Stack::getVariable(const string& varName, int& value){
     auto it = variables.find(varName);
    if (it != variables.end()) {
        value = it->second;
        return true;
    }
    return false;
} 




