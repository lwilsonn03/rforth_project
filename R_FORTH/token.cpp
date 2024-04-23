//Initial scan for cpp formatting complete

#include <iostream>

using namespace std;

#ifndef TOKEN_H_
#define TOKEN_H_

enum TokenTypeT{NUMBER = 0, OPERATOR = 1, SYMBOL = 2, WORD = 3};

Class Token{
    enum TokenTypeT tType;
    char *content;
}


int isOperator(char *s){
    //assumes isn't num
    char opList[] = "+-/*<>;:";
    int listSize, strSize;
    listSize = sizeof(op_list)/sizeof(op_list[0]);
    strSize = strlen(s);

    if (strSize == 1){
        for (int i = 0; i < listSize; i++){
            if (op_list[i] == s[0]){
                return 1;
            }
        }
    }
    return 0;
}

int isSymbol(char *s){
    //assumes isn't num or operator
    //was having trouble with regex, so I just wrote out the alphabet
    char alphaList[] = "abcdefghijklmnopqrstuvqwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    int alphaListSize, stringSize;
    alphaListSize = sizeof(alphaList)/sizeof(alphaList[0]);
    stringSize = strlen(s);
    if (stringSize == 1){
        for (int i = 0; i < alphaListSize; i++){
            if (s[0] == alphaList[i]){
                break;
            }
            if (i == alphaListSize - 1){ //end of all possible alpha chars
                return 1;
            }
        }
    }
    return 0;
}

enum TokenTypeT findTokenType(char *s){
    enum TokenTypeT type;
    int size = strlen(s);
    char copy[size];
    strcpy(copy, s);

    for (int i = 0; i < size; i++){
        if (!isdigit(copy[i])){ //if any character isn't a digit, can't be number
            break;
        } else if (i == size - 1){
            return TokenTypeT::NUMBER;
        }
    }
    
    if (is_operator(copy)){
        return TokenTypeT::OPERATOR;
    } else if (is_symbol(copy)){
        return TokenTypeT::SYMBOL;
    }

    return TokenTypeT::WORD;
}


char * typeAsString(enum TokenTypeT type){
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

void printlnToken(struct token_t token){
    cout << ("%s %s\n",typeAsString(token.t_class), token.content);
}

void printToken(struct token_t token){
    cout << ("%s %s",typeAsString(token.t_class), token.content);
}

#endif