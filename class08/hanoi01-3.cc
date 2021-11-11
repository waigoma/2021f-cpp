#include <iostream>
#include <iomanip>

using namespace std;

int A[3] = {3, 2, 1};
int B[3] = {0, 0, 0};
int C[3] = {0, 0, 0};
int step = 1;

void printMsg(const string& x, const string& y) {
    cout << "Step" << right << setw(4) << step << " : move a plate from " << x << " to " << y << endl;
}

void show() {
    cout << "A: ";
    for (int i : A) {
        cout << i << " ";
    }
    cout << endl;
    cout << "B: ";
    for (int i : B) {
        cout << i << " ";
    }
    cout << endl;
    cout << "C: ";
    for (int i : C) {
        cout << i << " ";
    }
    cout << endl;
}

void printHelp() {
    cout  << left << setw(5)<< "X Y" << ": move from pole X to Y" << endl;
    cout  << left << setw(5)<< "H" << ": show this help" << endl;
    cout  << left << setw(5)<< "Q" << ": exit game" << endl;
}

void initialize() {
    for (int i = 0; i < 3; i++) {
        A[i] = 3 - i;
        B[i] = 0;
        C[i] = 0;
    }
    step = 1;
}

bool movePlate(const string& from, const string& to) {
    int aIndex = 3, bIndex = 3, cIndex = 3;
    for (int i = 2; i >= 0; i--) {
        if (A[i] == 0) {
            aIndex = i;
        }
        if (B[i] == 0) {
            bIndex = i;
        }
        if (C[i] == 0) {
            cIndex = i;
        }
    }

    if (from == "A") {
        if (aIndex == 0) {
            cout << "Error: no plate in pole A" << endl;
            return false;
        }
        if (to == "B") {
            if (bIndex == 3) {
                cout << "Error: no space in pole B" << endl;
                return false;
            }

            B[bIndex] = A[aIndex - 1];
            A[aIndex - 1] = 0;
            printMsg("A", "B");
        } else if (to == "C") {
            if (cIndex == 3) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            C[cIndex] = A[aIndex - 1];
            A[aIndex - 1] = 0;
            printMsg("A", "C");
        } else if (to == "A") {
            cout << "Error: can't move to itself" << endl;
            return false;
        }
    } else if (from == "B") {
        if (bIndex == 0) {
            cout << "Error: no plate in pole B" << endl;
            return false;
        }
        if (to == "A") {
            if (aIndex == 3) {
                cout << "Error: no space in pole A" << endl;
                return false;
            }

            A[aIndex] = B[bIndex - 1];
            B[bIndex - 1] = 0;
            printMsg("B", "A");
        } else if (to == "C") {
            if (cIndex == 3) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            C[cIndex] = B[bIndex - 1];
            B[bIndex - 1] = 0;
            printMsg("B", "C");
        } else if (to == "B") {
            cout << "Error: can't move to itself" << endl;
            return false;
        }
    } else if (from == "C") {
        if (cIndex == 0) {
            cout << "Error: no plate in pole C" << endl;
            return false;
        }
        if (to == "A") {
            if (aIndex == 3) {
                cout << "Error: no space in pole A" << endl;
                return false;
            }

            A[aIndex] = C[cIndex - 1];
            C[cIndex - 1] = 0;
            printMsg("C", "A");
        } else if (to == "B") {
            if (bIndex == 3) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            B[bIndex] = C[cIndex - 1];
            C[cIndex - 1] = 0;
            printMsg("C", "B");
        } else if (to == "C") {
            cout << "Error: can't move to itself" << endl;
            return false;
        }
    }
    return true;
}


int main() {
    string x, y;
    initialize();
    show();

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "R" || x == "r") {
            initialize();
            show();
            continue;
        }
        if (x == "H" || x == "h") {
            printHelp();
            continue;
        }

        cin >> y;
        if (movePlate(x, y)) {
            show();
            if (step++ >= 99) break;
        }
    }
}
