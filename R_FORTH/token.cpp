#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef TOKEN_H_
#define TOKEN_H_

enum token_type_t{NUMBER = 0, OPERATOR = 1, SYMBOL = 2, WORD = 3};


struct token_t{
    enum token_type_t t_class;
    char *content;
};

int is_operator(char *s){
    //assumes isn't num
    char op_list[] = "+-/*<>;:";
    int list_size, str_size;
    list_size = sizeof(op_list)/sizeof(op_list[0]);
    str_size = strlen(s);

    if (str_size == 1){
        for (int i = 0; i < list_size; i++){
            if (op_list[i] == s[0]){
                return 1;
            }
        }
    }
    return 0;
}

int is_symbol(char *s){
    //assumes isn't num or operator
    //was having trouble with regex, so I just wrote out the alphabet
    char alpha_list[] = "abcdefghijklmnopqrstuvqwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    int alpha_list_size, string_size;
    alpha_list_size = sizeof(alpha_list)/sizeof(alpha_list[0]);
    string_size = strlen(s);
    if (string_size == 1){
        for (int i = 0; i < alpha_list_size; i++){
            if (s[0] == alpha_list[i]){
                break;
            }
            if (i == alpha_list_size - 1){ //end of all possible alpha chars
                return 1;
            }
        }
    }
    return 0;
}

enum token_type_t find_token_type(char *s){
    enum token_type_t type;
    int size = strlen(s);
    char copy[size];
    strcpy(copy, s);

    for (int i = 0; i < size; i++){
        if (!isdigit(copy[i])){ //if any character isn't a digit, can't be number
            break;
        } else if (i == size - 1){
            return NUMBER;
        }
    }
    
    if (is_operator(copy)){
        return OPERATOR;
    } else if (is_symbol(copy)){
        return SYMBOL;
    }

    return WORD;
}


char * type_as_string(enum token_type_t type){
    switch(type){
        case 0: 
            return "Number";
            break;
        case 1:
            return "Operator";
            break;
        case 2:
            return "Symbol";
            break;
        case 3:
            return "Word";
            break;
    }
}

void println_token(struct token_t token){
    printf("%s %s\n",type_as_string(token.t_class), token.content);
}

void print_token(struct token_t token){
    printf("%s %s",type_as_string(token.t_class), token.content);
}

#endif