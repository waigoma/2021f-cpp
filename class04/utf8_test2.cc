#include "utf8.h"
#include <iostream>

using namespace std;

void compare1(utf8 &a, utf8 &b) {
    if (a > b) {
        cout << a << " is greater than " << b << endl;
    } else if (a < b) {
        cout << a << " is less than " << b << endl;
    } else {
        cout << a << " is equal to " << b << endl;
    }
}

void compare2(utf8 &a, utf8 &b) {
    if (a >= b) {
        if (a == b) {
            cout << a << " is equal to " << b << endl;
        } else {
            cout << a << " is greater than " << b << endl;
        }
    } else {
        cout << a << " is less than " << b << endl;
    }
}

int main() {
    utf8 uc1("法");
    utf8 uc2("政");
    utf8 uc3("大");
    utf8 uc4("学");
    utf8 uc5("法");

    compare1(uc1, uc2);
    compare1(uc3, uc4);
    compare2(uc2, uc4);
    compare2(uc2, uc3);
    compare2(uc1, uc5);
}