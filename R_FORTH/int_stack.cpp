// int_stack.cpp

#include <iostream>

//possibly unecessary, just copying c structure
Class IntEntry{
    int value;
    //original has "SLIST_ENTRY(int_entry) entries;"
}


//current main dilemma is how to manage the contents of the stack.
//an array seems like a simple solution, until you realize you can't
//create the array until a stack object is made, since arrays have
//immutable size. Decided to just replace contents with new array
//on object creation.

Class Stack{
    int capacity;
    int size;
    //head- original reads "SLIST_HEAD(stackhead, int_entry) head"
    int contents[1];

    public:  


        Stack(int c){
            capacity = c;
            size = 0;
            int arr[c];
            contents = arr;
        }

        // void int_stack_init(int_stack_t *stk, int capacity) {
        //     SLIST_INIT(&stk->head);
        //     size = 0;
        //     capacity = capacity;
        // }



        /* ---CURRENT STORAGE METHOD--- */

        //The position in the stack as stored in the array is 
        //currently arr[0] = first stack item 
        int intStackPush(int v){
            if (size >= capacity){ 
                cout << "Stack is at full capacity.\n";
                return 0; //fail
            }
            arr[size - 1] = v;
            size++;
            return 1; //success
        }

        //TODO
        int intStackPop(int_stack_t *stk, int *topValue) {
            int_entry_t *entry = SLIST_FIRST(&stk->head);
            if (entry) {
                int value = entry->value;
                SLIST_REMOVE_HEAD(&stk->head, entries);
                free(entry);
                size--;
                *topValue = value;
                return 1; // success
            }
            return 0; // fail
        }

        //TODO
        int intStackTop(int_stack_t *stk, int *topValue) {
            int_entry_t *entry = SLIST_FIRST(&stk->head);
            if (entry) {
                *topValue = entry->value;
                return 1; // success
            }
            return 0; // fail
        }

        /* Functions for FORTH langauge stack operators */

        //REWRITTEN
        int intStackDup(){
            if (size < 1){ //no value to dup
                return 0; //fail
            }
            int topValue = intStackTop(); //subject to change, assumes intStackTop needs no arguments
            return intStackPush(topValue); //will return 1 if push success
        }

        //REWRITTEN
        int intStackSwap() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            intStackPush(topValue);
            return intStackPush(nextToTopValue); 
        }

        //REWRITTEN
        int intStackOver() {
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
        int intStackRot() {
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
        int intStackDrop() {
            if (size < 1)
                return 0;
            int topValue, nextToTopValue;
            return intStackPop(&topValue);
        }

        //REWRITTEN
        int intStack2Swap() {
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
        int intStack2Drop() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            return intStackPop(&nextToTopValue);
        }

        //REWRITTEN
        int intStack2Dup() {
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
        int intStack2Over() {
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
        int intStackAdd() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            return intStackPush(topValue + nextToTopValue);
        }

        //REWRITTEN
        int intStackSubtract() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            return intStackPush(nextToTopValue - topValue);
        }

        //REWRITTEN
        int intStackMultiply() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            return intStackPush(topValue * nextToTopValue);
        }

        //REWRITTEN
        int intStackDivide() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            return intStackPush(nextToTopValue / topValue);
        }

        //REWRITTEN
        int intStackModAndQuotient() { // /mod
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            intStackPush(nextToTopValue / topValue);
            return intStackPush(nextToTopValue % topValue);
        }

        //REWRITTEN
        int intStackModOnly() {
            if (size < 2)
                return 0;
            int topValue, nextToTopValue;
            intStackPop(&topValue);
            intStackPop(&nextToTopValue);
            return intStackPush(nextToTopValue % topValue);
        }

        //TODO
        int intStackGreaterThan(int_stack_t *stk) { //>
            if (size < 2)
                return 0;
            int topValue, nextToTopValue, result;
            intStackPop(stk, &topValue);
            intStackPop(stk, &nextToTopValue);
            if (topValue >= nextToTopValue){
                result = 0;
            }
            else {
                result = -1;
            }
            return intStackPush(stk, result);
        }

        //REWRITTEN
        int intStackLessThan() { //<
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
        void intStackPrint() {
            int_entry_t *entry;
            int pos = 0;
            if (size == 0) {
                fprintf(file, "empty stack\n");
            }

            SLIST_FOREACH(entry, &stk->head, entries) {
                fprintf(file, "%d: %d\n", pos, entry->value);
                pos++;
            }
            printf("\n");
        }


        //REWRITTEN
        int intStackSize() {
            return size;
        }
        //REWRITTEN
        int intStackCapacity() {
            return capacity;
        }
}

