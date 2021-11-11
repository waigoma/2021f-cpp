#include <iostream>
#include <iomanip>

using namespace std;

void printMsg(int step, const string& x, const string& y) {
    cout << "Step" << right << setw(4) << step << " : move a plate from " << x << " to " << y << endl;
}

void printHelp() {
    cout  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    cout  << left << setw(5)<< "H" << ": show this help" << endl;
    cout  << left << setw(5)<< "Q" << ": exit game" << endl;
}

int main() {
    string x, y;
    int step = 1;

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "R" || x == "r") {
            step = 1;
            continue;
        }
        if (x == "H" || x == "h") {
            printHelp();
            continue;
        }

        cin >> y;
        printMsg(step, x, y);

        if (step++ >= 99) break;
    }
}
