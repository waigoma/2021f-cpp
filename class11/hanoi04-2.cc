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

}