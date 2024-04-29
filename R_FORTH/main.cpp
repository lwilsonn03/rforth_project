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
    string userString;
    int size = 0;
    int charsRead;
    bool keepAcceptingInput = true;
    bool exitProgramNow = false;

    char delim[] = " \t\n\r\f\v";

    cout << "Welcome to RForth" << endl;
    // getline(cin, userString);


    // charsRead = userString.length(); //potentially unecessary to convert userString to char[] but might be needed for strtok()
    // char userArray[charsRead + 1];
    // strcpy(userArray, userString.c_str());

    cout << theStack.intStackPush(1) << endl;
    cout << "reached here" << endl;
    theStack.intStackPrint();


    /* 
        I think I will need to rewrite this section
        in more detail to get it to work in c++.
        please hold
    */
    //core terminal handling

    // while (!exitProgramNow){
    //     cin >> userString;

    //     while (keepAcceptingInput){
    //         char* tok = strtok(userString, delim);
    //         string tokString(tok);
    //         if (tok == NULL){
    //             continue;
    //         }
    //         if(tokString.compare("bye") == 0){
    //             keepAcceptingInput = false;
    //             exitProgramNow = true;
    //         }
    //         else {
    //             while(tok != NULL){
    //                 processOneTok(tok);
    //                 tok = strtok(NULL, delim);
    //             }
    //         }
    //         if(keepAcceptingInput){
    //             theStack.intStackPrint();
    //         }

    //     }
    // }

    return 0;
}
