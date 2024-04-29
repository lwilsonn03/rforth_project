#include <iostream>
#include <string>
#include <string.h>
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
    else if (type == WORD){
        if (strcmp(tok, "/mod") == 0){
            theStack.intStackModAndQuotient();
        }
        else if (strcmp(tok, "mod") == 0){
            theStack.intStackModOnly();
        }
    }
    //Unrecognized
    else {
        printf("Error: unrecognized symbol\n");
    }
} 


int main(int argc, char * * argv){
    char* userString;
    int size = 0;
    int charsRead;
    int keepAcceptingInput = 0; //true to forth, 0 = true and -1 = false
    int exitProgramNow = -1;

    char delim[] = " \t\n\r\f\v";

    cout << "Welcome to RForth\n";

    /* 
        I think I will need to rewrite this section
        in more detail to get it to work in c++.
        please hold
    */
        //core terminal handling

    while (exitProgramNow == -1){
        cin >> userString;


        while (keepAcceptingInput == 0){
            char* tok = strtok(userString, delim);
            string tokString(tok);
            if (tok == NULL){
                continue;
            }
            if(tokString.compare("bye") == 0){
                keepAcceptingInput = -1;
                exitProgramNow = 0;
            }
            else {
                while(tok != NULL){
                    processOneTok(tok);
                    tok = strtok(NULL, delim);
                }
            }
            if(keepAcceptingInput == 0){
                theStack.intStackPrint();
            }

        }
    }

    return EXIT_SUCCESS;
}
