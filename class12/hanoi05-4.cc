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
    boardc.poleBackup();

    string x, y;

    int key;
    bool isMove = false;

    int animInt = 0;
    bool isAnimStart = false;

    while (true) {
        move(0, 0);
        refresh();
        if (isAnimStart) {
            Sleep(1000);
            clear();
            boardc.cursesAnimation(animInt++);
            if (animInt == boardc.getSolutions().size()) {
                isAnimStart = false;
                animInt = 0;
                addstr("Animation Finished.\n何かキーを押して戻る...\n");
                getch();
                clear();
                boardc.poleRestore();
                continue;
            }
            continue;
        }
        boardc.cursesShow_aa();
        addstr("hanoi (h → HELP)> ");
        key = getch();
        clear();
        boardc.cursesShow_aa();
        if (key == KEY_LEFT) {
            if (currentBoard > 0) {
                currentBoard--;
                boardc.move(boards[currentBoard][1], boards[currentBoard][0]);
                addstr("\n1つ前に戻ります。\n");
                continue;
            }
            addstr("\nこれ以上前に戻れません。\n");
            continue;
        } else if (key == KEY_RIGHT) {
            if (!boards.empty()) {
                if (currentBoard < boards.size() - 1) {
                    if (boards[currentBoard][0] == "-1") {
                        addstr("\nこれ以上後ろに進めません。\n");
                        continue;
                    }
                    boardc.move(boards[currentBoard][0], boards[currentBoard][1]);
                    currentBoard++;
                    addstr("\n1つ後ろに進みます。\n");
                    continue;
                }
            }
            addstr("\nこれ以上後ろに進めません。\n");
            continue;
        } else if(key == 'h') {
            addstr("\n");
            boardc.cursesPrintHelp();
            continue;
        } else if (key == 'q') {
            break;
        } else if (key == 'r') {
            boardc.initialize();
            boardc.cursesShow_aa();
            currentBoard = 0;
            vector<vector<string>> tmp(100, vector<string>(100, "-1"));
            boards = tmp;
            clear();
            continue;
        } else if (key == 'a') {
            addstr("From A To > ");
            key = getch();
            addstr("\n");
            x = "A";
            if (key == 'b') y = "B";
            else if (key == 'c') y = "C";
            else {
                addstr("\n無効な入力です。\n");
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
                addstr("\n無効な入力です。\n");
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
                addstr("\n無効な入力です。\n");
                continue;
            }
            boardc.move(x, y);
            isMove = true;
        } else if (key == 'e') {
            boardc.solve();
            isAnimStart = true;
            animInt = 0;
            continue;
        } else if (key == 's') {
            boardc.solveCurses();
            isAnimStart = true;
            animInt = 0;
            continue;
        } else {
            addstr("\n無効な入力です。\n");
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