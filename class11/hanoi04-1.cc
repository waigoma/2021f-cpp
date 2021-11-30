#include <ncurses.h>
#include <string>

using namespace std;

int main() {
    initscr();
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 0 || j == 0 || j == 1) mvaddstr(i, 5 + 11 * j, "|");
            else {
                string tmp = string(1 + 2 * (i - 1), ' ');
                attron(A_REVERSE);
                mvaddstr(i, (5 + 11 * j) - (i - 1), tmp.c_str());
                attroff(A_REVERSE);
            }
        }
        addstr("\n");
    }
    addstr("-----+----------+----------+-----\n");
    addstr("     A          B          C\n");
    getch();
    endwin();
    return 0;
}