#include <iostream>
#include <string>
#include "int_stack.hpp"

using namespace std;

int main(int argc, char * * argv){
    string userString;
    int size = 0;
    int charsRead;
    int keepAcceptingInput = 0; //true to forth, 0 = true and -1 = false

    char delim[] = " \t\n\r\f\v";


    //Print tokens:
    // char* tok = strtok(userString, delim);
    // while (tok != NULL) {
    //     printf("%s %s\n", typeAsString(findTokenType(tok)), tok);
    //     tok = strtok(NULL, delim);
    // }

    Stack theStack(10);

    cout << "Welcome to RForth\n";

    nextLine:
    cin >> userString;

    //core input processing
    void processOneTok(string tok){
        enum TokenTypeT type = findTokenType(tok);

        //Numbers
        if (type == NUMBER){
            theStack.intStackPush(to_string(tok));
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
            printf("Error: neither number nor operator\n");
        }
    } 

    //core terminal handling
    string tok = strtok(userString, delim);
    while (keepAcceptingInput == 0){
        if (true){ //MUST FIX
            goto nextLine;
        }
        if(tok.compare("bye") == 0){
            keepAcceptingInput = -1;
        }
        else {
            while(true){ //MUST FIX THIS LINE
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
