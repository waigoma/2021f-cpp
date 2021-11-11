#include <iostream>
#include <iomanip>

using namespace std;

void printMsg(const string& x, const string& y) {
    cout << "move a plate from " << x << " to " << y << endl;
}

void printHelp() {
    cout  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    cout  << left << setw(5)<< "H" << ": show this help" << endl;
    cout  << left << setw(5)<< "Q" << ": exit game" << endl;
}

int main() {
    string x, y;

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "H" || x == "h") {
            printHelp();
            continue;
        } else {
            cin >> y;
            printMsg(x, y);
        }
    }
}
