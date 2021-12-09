#include "Board.h"

using namespace std;

int main() {
    int diskSize;
    int step = 0;
    cout << "円盤の枚数> "; cin >> diskSize;
    Board boardc(diskSize);
    boardc.initialize();

    string x, y;
    boardc.show_aa();

    while (true) {
        cout << "hanoi> "; cin >> x;
        if (x == "Q" || x == "q") break;
        if (x == "R" || x == "r") {
            boardc.initialize();
            boardc.show_aa();
            continue;
        }
        if (x == "H" || x == "h") {
            boardc.printHelp();
            continue;
        }
        if (x == "W" || x == "w") {
            boardc.solve();
            continue;
        }

        cin >> y;
        boardc.move(x, y);
        boardc.show_aa();
        if (step++ >= 99) break;
    }
}