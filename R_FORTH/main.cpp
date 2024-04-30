#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include "int_stack.hpp"

using namespace std;

Stack theStack(10);

void processOneTok(char* tok){
    enum TokenTypeT type = findTokenType(tok);

    //Numbers
    if (type == NUMBER){
        theStack.intStackPush(stoi(tok));
    }

    //Operators
    else if (type == OPERATOR){
        *tok = (char)(*tok);
        switch(*tok){
            case '+':
                theStack.intStackAdd();
                break;
            case '-':
                theStack.intStackSubtract();
                break;
            case '*':
                theStack.intStackMultiply();
                break;
            case '/':
                theStack.intStackDivide();
                break;
            case '<':
                theStack.intStackLessThan();
                break;
            case '>':
                theStack.intStackGreaterThan();
                break;
            case ';':
                //functions unimplemented
                break;
            case ':':
                //functions unimplemented
                break;
            default: 
                cout << "Unrecognized operator\n";
        }
    }
    //Words
    else if (type == WORD){ //sincerist apologies for the else if monster, couldn't easily get switch to work here
        if (strcmp(tok, "/mod") == 0){
            theStack.intStackModAndQuotient();
        }
        else if (strcmp(tok, "mod") == 0){
            theStack.intStackModOnly();
        }
        else if (strcmp(tok, "dup") == 0){
            theStack.intStackDup();
        }
        else if (strcmp(tok, "swap") == 0){
            theStack.intStackSwap();
        }
        else if (strcmp(tok, "over") == 0){
            theStack.intStackOver();
        }
        else if (strcmp(tok, "rot") == 0){
            theStack.intStackRot();
        }
        else if (strcmp(tok, "drop") == 0){
            theStack.intStackDrop();
        }
        else if (strcmp(tok, "2swap") == 0){
            theStack.intStack2Swap();
        }
        else if (strcmp(tok, "2drop") == 0){
            theStack.intStack2Drop();
        }
        else if (strcmp(tok, "2dup") == 0){
            theStack.intStack2Dup();
        }
        else if (strcmp(tok, "2over") == 0){
            theStack.intStack2Over();
        }
    }
    //Unrecognized
    else {
        cerr << "Error: unrecognized symbol" << endl;
    }
} 


int main(int argc, char * * argv){
    string userString;
    int size = 0;
    int charsRead;
    bool keepAcceptingInput = true;

    char delim[] = " \t\n\r\f\v";

    cout << "Welcome to RForth" << endl;




    while(keepAcceptingInput){
        getline(cin, userString);
        charsRead = userString.length(); 

        //array copy of userString created to use strtok()
        char userArray[charsRead + 1];
        strcpy(userArray, userString.c_str());
        char* tok = strtok(userArray, delim);

        if (strcmp(tok, "bye") == 0){
            keepAcceptingInput = false;
            continue;
        }

        while(tok != NULL){
            if (strcmp(tok, "variable") == 0){
                //here's where we'll make the terminal process the command
            }
            processOneTok(tok);
            tok = strtok(NULL, delim); 
        }
        theStack.intStackPrint();
    }

    cout << "See you!" << endl;
    return 0;
}
