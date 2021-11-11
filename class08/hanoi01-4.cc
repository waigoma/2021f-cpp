#include <iostream>
#include <iomanip>

using namespace std;

const int DISK_SIZE = 5;
int board[3][DISK_SIZE];
int step = 1;

void printMsg(const string& x, const string& y) {
    cout << "Step" << right << setw(4) << step << " : move a plate from " << x << " to " << y << endl;
}

void show() {
    cout << "A: ";
    for (int i : board[0]) {
        cout << i << " ";
    }
    cout << endl;
    cout << "B: ";
    for (int i : board[1]) {
        cout << i << " ";
    }
    cout << endl;
    cout << "C: ";
    for (int i : board[2]) {
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
    for (int i = 0; i < DISK_SIZE; i++) {
        board[0][i] = DISK_SIZE - i;
        board[1][i] = 0;
        board[2][i] = 0;
    }
    step = 1;
}

bool movePlate(const string& from, const string& to) {
    int aIndex = DISK_SIZE, bIndex = DISK_SIZE, cIndex = DISK_SIZE;
    for (int i = DISK_SIZE - 1; i >= 0; i--) {
        if (board[0][i] == 0) {
            aIndex = i;
        }
        if (board[1][i] == 0) {
            bIndex = i;
        }
        if (board[2][i] == 0) {
            cIndex = i;
        }
    }

    if (from == "A") {
        if (aIndex == 0) {
            cout << "Error: no plate in pole A" << endl;
            return false;
        }
        if (to == "B") {
            if (bIndex == DISK_SIZE) {
                cout << "Error: no space in pole B" << endl;
                return false;
            }

            board[1][bIndex] = board[0][aIndex - 1];
            board[0][aIndex - 1] = 0;
            printMsg("A", "B");
        } else if (to == "C") {
            if (cIndex == DISK_SIZE) {
                cout << "Error: no space in pole board[2]" << endl;
                return false;
            }

            board[2][cIndex] = board[0][aIndex - 1];
            board[0][aIndex - 1] = 0;
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
            if (aIndex == DISK_SIZE) {
                cout << "Error: no space in pole A" << endl;
                return false;
            }

            board[0][aIndex] = board[1][bIndex - 1];
            board[1][bIndex - 1] = 0;
            printMsg("B", "A");
        } else if (to == "C") {
            if (cIndex == DISK_SIZE) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            board[2][cIndex] = board[1][bIndex - 1];
            board[1][bIndex - 1] = 0;
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
            if (aIndex == DISK_SIZE) {
                cout << "Error: no space in pole A" << endl;
                return false;
            }

            board[0][aIndex] = board[2][cIndex - 1];
            board[2][cIndex - 1] = 0;
            printMsg("C", "A");
        } else if (to == "B") {
            if (bIndex == DISK_SIZE) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            board[1][bIndex] = board[2][cIndex - 1];
            board[2][cIndex - 1] = 0;
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
