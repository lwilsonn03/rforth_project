#include <iostream>
#include <string>
#include "int_stack.hpp"

using namespace std;


void processOneTok(string tok){
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
    string userString;
    int size = 0;
    int charsRead;
    int keepAcceptingInput = 0; //true to forth, 0 = true and -1 = false

    char delim[] = " \t\n\r\f\v";

    Stack theStack(10);

    cout << "Welcome to RForth\n";

    /* 
        I think I will need to rewrite this section
        in more detail to get it to work in c++.
        please hold
    */
        //core terminal handling

    while (keepAcceptingInput == 0){
        cin >> userString;
        char* tok = strtok(userString, delim);
        if (tok == NULL){ //MUST FIX
            
        }
        if(tok.compare("bye") == 0){
            keepAcceptingInput = -1;
        }
        else {
            while(tok != NULL){ //MUST FIX THIS LINE
                processOneTok(tok);
                tok = strtok(NULL, delim);
            }
        }
        if(keepAcceptingInput == 0){
            theStack.intStackPrint();
        }

    }
    return EXIT_SUCCESS;
}
