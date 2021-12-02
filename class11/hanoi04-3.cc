#include "Board.h"

#include <ncurses.h>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    char *diskSize;
    int diskNum;
    int step = 1;

    vector<vector<string>> boards(100, vector<string>(100, "-1"));
    int currentBoard = 0;

    addstr("円盤の枚数> ");
    getstr(diskSize);
    string str(diskSize);
    diskNum = stoi(str);

    Board boardc(diskNum);
    boardc.initialize();

    string x, y;

    int key;
    bool isMove = false;

    while (true) {
        move(0, 0);
        refresh();
        clear();
        boardc.show_aa();
        addstr("hanoi (h → HELP)> ");
        key = getch();
        addstr("\n");
//        clear();
        if (key == KEY_LEFT) {
            if (currentBoard > 0) {
                currentBoard--;
                boardc.move(boards[currentBoard][1], boards[currentBoard][0]);
                addstr("1つ前に戻ります。\n");
                continue;
            }
            addstr("これ以上前に戻れません。\n");
            continue;
        } else if (key == KEY_RIGHT) {
            if (!boards.empty()) {
                if (currentBoard < boards.size() - 1) {
                    if (boards[currentBoard][0] == "-1") {
                        addstr("これ以上後ろに進めません。\n");
                        continue;
                    }
                    boardc.move(boards[currentBoard][0], boards[currentBoard][1]);
                    currentBoard++;
                    addstr("1つ後ろに進みます。\n");
                    continue;
                }
            }
            addstr("これ以上後ろに進めません。\n");
            continue;
        } else if(key == 'h') {
            boardc.printHelp();
            continue;
        } else if (key == 'q') {
            break;
        } else if (key == 'r') {
            boardc.initialize();
            boardc.show_aa();
            continue;
        } else if (key == 'a') {
            addstr("From A To > ");
            key = getch();
            addstr("\n");
            x = "A";
            if (key == 'b') y = "B";
            else if (key == 'c') y = "C";
            else {
                addstr("無効な入力です。\n");
                continue;
            }
            boardc.move(x, y);
            isMove = true;
        } else if (key == 'b') {
            x = "B";
            addstr("From B To > ");
            key = getch();
            addstr("\n");
            if (key == 'a') y = "A";
            else if (key == 'c') y = "C";
            else {
                addstr("無効な入力です。\n");
                continue;
            }
            boardc.move(x, y);
            isMove = true;
        } else if(key == 'c') {
            x = "C";
            addstr("From C To > ");
            key = getch();
            addstr("\n");
            if (key == 'a') y = "A";
            else if (key == 'b') y = "B";
            else {
                addstr("無効な入力です。\n");
                continue;
            }
            boardc.move(x, y);
            isMove = true;
        } else {
            addstr("無効な入力です。\n");
            continue;
        }

        if (step++ >= 99) break;
        if (isMove) {
            boards[currentBoard++] = vector<string>{x, y};
        }
    }
    addstr("終了します。\n何かキーを押して続行...");
    getch();
    endwin();
    return 0;
}