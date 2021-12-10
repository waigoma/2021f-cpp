#include "Board.h"

using namespace std;

const int WIDTH = 80;
const int HEIGHT = 24;

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
        if (x == "E" || x == "e") {
            boardc.solve();
            boardc.animation();
            cout << "Animation finished" << endl;
            continue;
        }
        if (x == "S" || x == "s") {
            boardc.solveCurses();
            boardc.animation();
            cout << "Animation finished" << endl;
            continue;
        }

        cin >> y;
        boardc.move(x, y);
        boardc.show_aa();
        if (step++ >= 99) break;
    }
}