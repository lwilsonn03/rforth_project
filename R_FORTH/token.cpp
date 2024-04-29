//Initial scan for cpp formatting complete

#include <iostream>
#include <string>
#include "int_stack.hpp"

using namespace std;

#ifndef TOKEN_H_
#define TOKEN_H_


class Token{
    enum TokenTypeT tType;
    string content;

    public:
        enum TokenTypeT getType(){return tType;}
        string getContent(){return content;}
};


int isOperator(string s){
    //assumes isn't num
    char opList[] = "+-/*<>;:";
    int listSize, strSize;
    listSize = sizeof(opList)/sizeof(opList[0]);
    strSize = s.length();

    if (strSize == 1){
        for (int i = 0; i < listSize; i++){
            if (opList[i] == s[0]){
                return 1;
            }
        }
    }
    return 0;
}

int isSymbol(string s){
    //assumes isn't num or operator
    //was having trouble with regex, so I just wrote out the alphabet
    char alphaList[] = "abcdefghijklmnopqrstuvqwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    int alphaListSize, stringSize;
    alphaListSize = sizeof(alphaList)/sizeof(alphaList[0]);
    stringSize = s.length();
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

enum TokenTypeT findTokenType(string s){
    enum TokenTypeT type;
    int size = s.length();
    string copy = s;

    for (int i = 0; i < size; i++){
        if (!isdigit(copy[i])){ //if any character isn't a digit, can't be number
            break;
        } else if (i == size - 1){
            return TokenTypeT::NUMBER;
        }
    }
    
    if (isOperator(copy)){
        return TokenTypeT::OPERATOR;
    } else if (isSymbol(copy)){
        return TokenTypeT::SYMBOL;
    }

    return TokenTypeT::WORD;
}


string typeAsString(enum TokenTypeT type){
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
    return "error";
}

void printlnToken(Token token){
    cout << (typeAsString(token.getType()) + token.getContent());
}

void printToken(Token token){
    cout << (typeAsString(token.getType()) + token.getContent());
}

#endif