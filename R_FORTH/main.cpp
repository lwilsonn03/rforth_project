#include <stdio.h>
#include <stdlib.h>
#include "token.c"
#include "int_stack.c"
#include <string.h>
#include <regex.h>



int main(int argc, char * * argv){
    char *user_string = NULL;
    size_t size = 0;
    ssize_t chars_read;
    int keep_accepting_input = 0; //true to forth, 0 = true and -1 = false

    char delim[] = " \t\n\r\f\v";

    //setting up for storage
    FILE *cache_txt;
    cache_txt = fopen("cache.txt", "w");

    //Print tokens:
    // char* tok = strtok(user_string, delim);
    // while (tok != NULL) {
    //     printf("%s %s\n", type_as_string(find_token_type(tok)), tok);
    //     tok = strtok(NULL, delim);
    // }

    int_stack_t theStack;
    int_stack_init(&theStack, 10); //cap at 10 for now

    puts("Welcome to RForth");

    next_line:
    chars_read = getline(&user_string, &size, stdin);

    //core input processing
    void process_one_tok(char* tok) {
        enum token_type_t type = find_token_type(tok);

        //Numbers
        if (type == NUMBER){
            int_stack_push(&theStack, atoi(tok));
        }


        //Operators
        else if (type == OPERATOR){
            *tok = (char)(*tok);
            switch(*tok){
                case '+':
                    int_stack_add(&theStack);
                    break;
                case '-':
                    int_stack_subtract(&theStack);
                    break;
                case '*':
                    int_stack_multiply(&theStack);
                    break;
                case '/':
                    int_stack_divide(&theStack);
                    break;
                case '<':
                    int_stack_less_than(&theStack);
                    break;
                case '>':
                    int_stack_greater_than(&theStack);
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
    char* tok = strtok(user_string, delim);
    while (keep_accepting_input == 0){
        if (tok == NULL){
            goto next_line; //this is my first time using goto, please
            //let me know if this use is inappropriate/better suggestions
        }
        if(strcmp(tok, "bye") == 0){
            keep_accepting_input = -1;
        }
        else {
            while(tok != NULL){
                process_one_tok(tok);
                tok = strtok(NULL, delim);
            }
        }
        if(keep_accepting_input == 0){
            int_stack_print(&theStack, stdout);
        }
 
    }


    free(user_string);
    fclose(cache_txt);
    remove("cache.txt");

    return EXIT_SUCCESS;

}
