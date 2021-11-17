#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int DISK_SIZE = 5;
vector<vector<int>> board;
int plate_num[3];
int step = 1;

void printMsg(const string& x, const string& y) {
    cout << "Step" << right << setw(4) << step << " : move a plate from " << x << " to " << y << endl;
}

void show() {
    cout << "A: ";
    for (auto i : board[0]) {
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
    for (int i = 0; i < 3; i++) {
        vector<int> temp;
        for (int j = 0; j < DISK_SIZE; j++) {
            if (i == 0) temp.push_back(DISK_SIZE - j);
            else temp.push_back(0);
        }
        board.push_back(temp);
    }
    plate_num[0] = DISK_SIZE;
    plate_num[1] = 0;
    plate_num[2] = 0;
    step = 1;
}

bool movePlate(const string& from, const string& to) {
    if (from == "A") {
        if (plate_num[0] == 0) {
            cout << "Error: no plate in pole A" << endl;
            return false;
        }
        if (to == "B") {
            if (plate_num[1] == DISK_SIZE) {
                cout << "Error: no space in pole B" << endl;
                return false;
            }

            board[1][plate_num[1]++] = board[0][plate_num[0] - 1];
            board[0][plate_num[0]-- - 1] = 0;
            printMsg("A", "B");
        } else if (to == "C") {
            if (plate_num[2] == DISK_SIZE) {
                cout << "Error: no space in pole board[2]" << endl;
                return false;
            }

            board[2][plate_num[2]++] = board[0][plate_num[0] - 1];
            board[0][plate_num[0]-- - 1] = 0;
            printMsg("A", "C");
        } else if (to == "A") {
            cout << "Error: can't move to itself" << endl;
            return false;
        }
    } else if (from == "B") {
        if (plate_num[1] == 0) {
            cout << "Error: no plate in pole B" << endl;
            return false;
        }
        if (to == "A") {
            if (plate_num[0] == DISK_SIZE) {
                cout << "Error: no space in pole A" << endl;
                return false;
            }

            board[0][plate_num[0]++] = board[1][plate_num[1] - 1];
            board[1][plate_num[1]-- - 1] = 0;
            printMsg("B", "A");
        } else if (to == "C") {
            if (plate_num[2] == DISK_SIZE) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            board[2][plate_num[2]++] = board[1][plate_num[1] - 1];
            board[1][plate_num[1]-- - 1] = 0;
            printMsg("B", "C");
        } else if (to == "B") {
            cout << "Error: can't move to itself" << endl;
            return false;
        }
    } else if (from == "C") {
        if (plate_num[2] == 0) {
            cout << "Error: no plate in pole C" << endl;
            return false;
        }
        if (to == "A") {
            if (plate_num[0] == DISK_SIZE) {
                cout << "Error: no space in pole A" << endl;
                return false;
            }

            board[0][plate_num[0]++] = board[2][plate_num[2] - 1];
            board[2][plate_num[2]-- - 1] = 0;
            printMsg("C", "A");
        } else if (to == "B") {
            if (plate_num[1] == DISK_SIZE) {
                cout << "Error: no space in pole C" << endl;
                return false;
            }

            board[1][plate_num[1]++] = board[2][plate_num[2] - 1];
            board[2][plate_num[2]-- - 1] = 0;
            printMsg("C", "B");
        } else if (to == "C") {
            cout << "Error: can't move to itself" << endl;
            return false;
        }
    }
    return true;
}


int main() {
    cout << "円盤の枚数> "; cin >> DISK_SIZE;

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
