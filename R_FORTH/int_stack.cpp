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
        //     stk->size = 0;
        //     stk->capacity = capacity;
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

        int intStackPop(int_stack_t *stk, int *top_value) {
            int_entry_t *entry = SLIST_FIRST(&stk->head);
            if (entry) {
                int value = entry->value;
                SLIST_REMOVE_HEAD(&stk->head, entries);
                free(entry);
                stk->size--;
                *top_value = value;
                return 1; // success
            }
            return 0; // fail
        }

        int intStackTop(int_stack_t *stk, int *top_value) {
            int_entry_t *entry = SLIST_FIRST(&stk->head);
            if (entry) {
                *top_value = entry->value;
                return 1; // success
            }
            return 0; // fail
        }

        /* Functions for FORTH langauge stack operators */


        int intStackDup(){
            if (size < 1){ //no value to dup
                return 0; //fail
            }
            int topValue = intStackTop(); //subject to change, assumes intStackTop needs no arguments
            return intStackPush(topValue); //will return 1 if push success
        }

        int intStackSwap(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            intStackPush(stk, top_value);
            return intStackPush(stk, next_to_top_value); // success only if last operation succeeds
        }

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

        int int_stack_rot(int_stack_t *stk) {
            if (stk->size < 3)
                return 0;
            int top_value, next_to_top_value, third_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            intStackPop(stk, &third_value);
            intStackPush(stk, next_to_top_value);
            intStackPush(stk, top_value);
            return intStackPush(stk, third_value); // success only if last operation succeeds
        }

        int int_stack_drop(int_stack_t *stk) {
            if (stk->size < 1)
                return 0;
            int top_value, next_to_top_value;
            return intStackPop(stk, &top_value);
        }

        int intStack2Swap(int_stack_t *stk) {
            if (stk->size < 4)
                return 0;
            int top_value, next_to_top_value, third_value, fourth_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            intStackPop(stk, &third_value);
            intStackPop(stk, &fourth_value);
            intStackPush(stk, third_value);
            intStackPush(stk, fourth_value);
            intStackPush(stk, top_value);
            return intStackPush(stk, next_to_top_value); // success only if last operation succeeds
        }

        int intStack2Drop(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            return intStackPop(stk, &next_to_top_value);
        }

        int intStack2Dup(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            intStackPush(stk, next_to_top_value);
            intStackPush(stk, top_value);
            intStackPush(stk, next_to_top_value);
            return intStackPush(stk, top_value);
        }

        int intStack2Over(int_stack_t *stk) {
            if (stk->size < 4)
                return 0;
            int top_value, next_to_top_value, third_value, fourth_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            intStackPop(stk, &third_value);
            intStackPop(stk, &fourth_value);
            intStackPush(stk, fourth_value);
            intStackPush(stk, third_value);
            intStackPush(stk, next_to_top_value);
            intStackPush(stk, top_value);
            intStackPush(stk, third_value);
            return intStackPush(stk, fourth_value);
        }

        /* Example of how to create a binary operator that works o top two elements (if present) */

        int intStackAdd(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            return intStackPush(stk, top_value + next_to_top_value);
        }

        int intStackSubtract(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            return intStackPush(stk, next_to_top_value - top_value);
        }

        int intStackMultiply(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            return intStackPush(stk, top_value * next_to_top_value);
        }

        int int_stack_divide(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            return intStackPush(stk, next_to_top_value / top_value);
        }

        int int_stack_mod_and_quotient(int_stack_t *stk) { // /mod
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            intStackPush(stk, next_to_top_value / top_value);
            return intStackPush(stk, next_to_top_value % top_value);
        }

        int int_stack_mod_only(int_stack_t *stk) {
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            return intStackPush(stk, next_to_top_value % top_value);
        }

        int int_stack_greater_than(int_stack_t *stk) { //>
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value, result;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            if (top_value >= next_to_top_value){
                result = 0;
            }
            else {
                result = -1;
            }
            return intStackPush(stk, result);
        }

        int int_stack_less_than(int_stack_t *stk) { //<
            if (stk->size < 2)
                return 0;
            int top_value, next_to_top_value, result;
            intStackPop(stk, &top_value);
            intStackPop(stk, &next_to_top_value);
            if (top_value <= next_to_top_value){
                result = 0;
            }
            else {
                result = -1;
            }
            return intStackPush(stk, result);
        }

        int int_stack_function(int_stack_t *stk) {
            
        }

        void int_stack_print(int_stack_t *stk, FILE *file) {
            int_entry_t *entry;
            int pos = 0;
            if (stk->size == 0) {
                fprintf(file, "empty stack\n");
            }

            SLIST_FOREACH(entry, &stk->head, entries) {
                fprintf(file, "%d: %d\n", pos, entry->value);
                pos++;
            }
            printf("\n");
        }



        int intStackSize() {
            return size;
        }

        int int_stack_capacity(int_stack_t* stk) {
            return stk->capacity;
        }
}

