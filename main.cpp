#include <iostream>
using namespace std;

int main() {
    string x;
    cout << "Welcome to RForth\n";
    cin >> x;
    while (true){
        if (x == "bye"){
            return 0;
        }
        else {
            cout << "hi :)\n";
            cin >> x;
        }
    }
}