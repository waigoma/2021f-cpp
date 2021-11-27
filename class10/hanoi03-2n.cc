#include "Board.h"

using namespace std;

int main() {
    int diskSize;
    int step = 0;
    cout << "円盤の枚数> "; cin >> diskSize;
    Board boardc(diskSize);
    boardc.initialize();

    string x, y;
    boardc.show_n_str();

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "R" || x == "r") {
            boardc.initialize();
            boardc.show_n_str();
            continue;
        }
        if (x == "H" || x == "h") {
            boardc.printHelp();
            continue;
        }

        cin >> y;
        boardc.move(x, y);
        boardc.show_n_str();
        if (step++ >= 99) break;
    }
}