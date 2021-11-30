#include "Board.h"

#include <ncurses.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    initscr();
    char *diskSize;
    int diskNum;
    int step = 0;
    cbreak();
    addstr("円盤の枚数> ");
    getstr(diskSize);
    string str(diskSize);
    diskNum = stoi(str);
//    cout << "円盤の枚数> "; cin >> diskSize;
    Board boardc(diskNum);
    boardc.initialize();

    string x, y;
    boardc.show_aa();

    getch();
    endwin();
    return 0;

//    while (true) {
//        cout << "hanoi> "; cin >> x;
//        if (x == "Q" || x == "q") break;
//        if (x == "R" || x == "r") {
//            boardc.initialize();
//            boardc.show_aa();
//            continue;
//        }
//        if (x == "H" || x == "h") {
//            boardc.printHelp();
//            continue;
//        }
//
//        cin >> y;
//        boardc.move(x, y);
//        boardc.show_aa();
//        if (step++ >= 99) break;
//    }
}