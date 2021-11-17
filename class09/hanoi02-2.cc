#include <iostream>
#include <iomanip>

using namespace std;

const int DISK_SIZE = 5;
int plate_num[3];
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

void showPlate(int i) {
    for (int j = 0; j < 3; j++) {
        int fill = (2 * board[j][i] - 1) < 0 ? 0 : (2 * board[j][i] - 1);
        int padding = (2 * DISK_SIZE + 1 - fill) / 2;
        if (plate_num[j] == 0 || board[j][i] == 0) cout << right << setfill(' ') << setw(padding) << "" << setfill('|') << setw(1) << "" << setfill(' ') << setw(padding) << "";
        else cout << right << setfill(' ') << setw(padding) << "" << setfill('x') << setw(fill) << "" << setfill(' ') << setw(padding) << "";
    }
    cout << endl;
}

void showArt() {
    cout << right << setfill(' ') << setw(DISK_SIZE + 1) << "|" << setw(2 * DISK_SIZE + 1) << "|" << setw(2 * DISK_SIZE + 1) << "|" << endl;
    for (int i = DISK_SIZE - 1; i >= 0; i--) {
        showPlate(i);
    }
    cout << right << setfill('-') << setw(DISK_SIZE + 1)  << "+" << setfill('-') << setw(2 * DISK_SIZE + 1) << "+" << setfill('-') << setw(2 * DISK_SIZE + 1) << "+" << setfill('-') << setw(DISK_SIZE + 1) << "\n";
    cout << right << setfill(' ') << setw(DISK_SIZE + 1)  << "A" << setw(2 * DISK_SIZE + 1) << "B" << setw(2 * DISK_SIZE + 1) << "C" << setw(DISK_SIZE + 1) << "\n";
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
    plate_num[0] = DISK_SIZE;
    plate_num[1] = 0;
    plate_num[2] = 0;
    step = 1;
}

void movePlate(const string& from, const string& to) {
    if (from == "A") {
        if (to == "B") {
            board[1][plate_num[1]++] = board[0][plate_num[0] - 1];
            board[0][plate_num[0]-- - 1] = 0;
            printMsg("A", "B");
        } else if (to == "C") {
            board[2][plate_num[2]++] = board[0][plate_num[0] - 1];
            board[0][plate_num[0]-- - 1] = 0;
            printMsg("A", "C");
        }
    } else if (from == "B") {
        if (to == "A") {
            board[0][plate_num[0]++] = board[1][plate_num[1] - 1];
            board[1][plate_num[1]-- - 1] = 0;
            printMsg("B", "A");
        } else if (to == "C") {
            board[2][plate_num[2]++] = board[1][plate_num[1] - 1];
            board[1][plate_num[1]-- - 1] = 0;
            printMsg("B", "C");
        }
    } else if (from == "C") {
        if (to == "A") {
            board[0][plate_num[0]++] = board[2][plate_num[2] - 1];
            board[2][plate_num[2]-- - 1] = 0;
            printMsg("C", "A");
        } else if (to == "B") {
            board[1][plate_num[1]++] = board[2][plate_num[2] - 1];
            board[2][plate_num[2]-- - 1] = 0;
            printMsg("C", "B");
        }
    }
}

string move(const string& from, const string& to) {
    if (from == "A") {
        if (plate_num[0] == 0) {
            return "Error: no plate in pole A";
        }
        if (to == "B") {
            if (plate_num[1] == DISK_SIZE) {
                return "Error: no space in pole B";
            }

            int bp = plate_num[1] == 0 ? 0 : board[1][plate_num[1] - 1];
            if (board[0][plate_num[0] - 1] > bp && bp != 0) {
                return "Error: can't move A to B";
            }

            movePlate("A", "B");
        } else if (to == "C") {
            if (plate_num[2] == DISK_SIZE) {
                return "Error: no space in pole C";
            }

            int cp = plate_num[2] == 0 ? 0 : board[2][plate_num[2] - 1];
            if (board[0][plate_num[0] - 1] > cp && cp != 0) {
                return "Error: can't move A to C";
            }

            movePlate("A", "C");
        } else if (to == "A") {
            return "Error: can't move to itself";
        }
    } else if (from == "B") {
        if (plate_num[1] == 0) {
            return "Error: no plate in pole B";
        }
        if (to == "A") {
            if (plate_num[0] == DISK_SIZE) {
                return "Error: no space in pole A";
            }

            int ap = plate_num[0] == 0 ? 0 : board[0][plate_num[0] - 1];
            if (board[1][plate_num[1] - 1] > ap && ap != 0) {
                return "Error: can't move B to A";
            }

            movePlate("B", "A");
        } else if (to == "C") {
            if (plate_num[2] == DISK_SIZE) {
                return "Error: no space in pole C";
            }

            int cp = plate_num[2] == 0 ? 0 : board[2][plate_num[2] - 1];
            if (board[1][plate_num[1] - 1] > cp && cp != 0) {
                return "Error: can't move B to C";
            }

            movePlate("B", "C");
        } else if (to == "B") {
            return "Error: can't move to itself";
        }
    } else if (from == "C") {
        if (plate_num[2] == 0) {
            return "Error: no plate in pole C";
        }
        if (to == "A") {
            if (plate_num[0] == DISK_SIZE) {
                return "Error: no space in pole A";
            }

            int ap = plate_num[0] == 0 ? 0 : board[0][plate_num[0] - 1];
            if (board[2][plate_num[2] - 1] > ap && ap != 0) {
                return "Error: can't move C to A";
            }

            movePlate("C", "A");
        } else if (to == "B") {
            if (plate_num[1] == DISK_SIZE) {
                return "Error: no space in pole B";
            }

            int bp = plate_num[1] == 0 ? 0 : board[1][plate_num[1] - 1];
            if (board[2][plate_num[2] - 1] > bp && bp != 0) {
                return "Error: can't move C to B";
            }

            movePlate("C", "B");
        } else if (to == "C") {
            return "Error: can't move to itself";
        }
    }
    return "OK";
}


int main() {
    string x, y;
    initialize();
    showArt();

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "R" || x == "r") {
            initialize();
            showArt();
            continue;
        }
        if (x == "H" || x == "h") {
            printHelp();
            continue;
        }

        cin >> y;
        string result = move(x, y);
        if (result == "OK") {
            showArt();
            if (step++ >= 99) break;
        } else {
            cout << result << endl;
        }
    }
}
