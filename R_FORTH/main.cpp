#include <iostream>
#include "int_stack.hpp"

int main(int argc, char * * argv){
    char *userString = NULL;
    size_t size = 0;
    ssize_t charsRead;
    int keepAcceptingInput = 0; //true to forth, 0 = true and -1 = false

    char delim[] = " \t\n\r\f\v";


    //Print tokens:
    // char* tok = strtok(userString, delim);
    // while (tok != NULL) {
    //     printf("%s %s\n", typeAsString(findTokenType(tok)), tok);
    //     tok = strtok(NULL, delim);
    // }

    int_stack_t theStack;
    int_stack_init(&theStack, 10); //cap at 10 for now

    puts("Welcome to RForth");

    next_line:
    charsRead = getline(&userString, &size, stdin);

    //core input processing
    void process_one_tok(char* tok) {
        enum TokenTypeT type = findTokenType(tok);

        //Numbers
        if (type == NUMBER){
            intStackPush(&theStack, atoi(tok));
        }


        //Operators
        else if (type == OPERATOR){
            *tok = (char)(*tok);
            switch(*tok){
                case '+':
                    intStackAdd(&theStack);
                    break;
                case '-':
                    intStackSubtract(&theStack);
                    break;
                case '*':
                    intStackMultiply(&theStack);
                    break;
                case '/':
                    intStackDivide(&theStack);
                    break;
                case '<':
                    intStackLessThan(&theStack);
                    break;
                case '>':
                    intStackGreaterThan(&theStack);
                    break;
                case ';':
                    //functions unimplemented
                    break;
                case ':':
                    //functions unimplemented
                    break;
                default: 
                    printf("Unrecognized operator\n");
            }
        }
        //Words
        else if (type == WORD){
            if (strcmp(tok, "hello") == 0){ //writes to file and reads it back
                fputs("hello file", cache_txt);
                fclose(cache_txt);
                cache_txt = fopen("cache.txt", "r");
                char tempString[100];
                printf("%s\n", fgets(tempString, 100, cache_txt));
            }
        }


        //Unrecognized
        else {
            printf("Error: neither number nor operator\n");
        }
    } 

    //core terminal handling
    char* tok = strtok(userString, delim);
    while (keepAcceptingInput == 0){
        if (tok == NULL){
            goto next_line; //this is my first time using goto, please
            //let me know if this use is inappropriate/better suggestions
        }
        if(strcmp(tok, "bye") == 0){
            keepAcceptingInput = -1;
        }
        else {
            while(tok != NULL){
                process_one_tok(tok);
                tok = strtok(NULL, delim);
            }
        }
        if(keepAcceptingInput == 0){
            intStackPrint(&theStack, stdout);
        }
 
    }


    free(userString);
    return EXIT_SUCCESS;

}
