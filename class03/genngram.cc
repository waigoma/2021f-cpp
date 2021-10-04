#include "utf8.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    int n_gram = 2;

    if (argc > 1) {
        n_gram = strtol(argv[1], NULL, 0);
    }

    string source;

    cout << "文字列は？: "; cin >> source;

    // 文字数
    int utf8count = 0;
    int offset = 0;
    utf8 u1;
    const char* sp = source.c_str();

    while (true) {
        u1 = utf8(sp + offset);
        offset += u1.countBytes();
        if (u1.is_null()) break;
        utf8count++;
    }

    // utf8 配列に文字格納
    utf8 u2[utf8count];
    offset = 0;

    for (int i = 0; i < utf8count; i++) {
        u2[i] = utf8(sp + offset);
        offset += u2[i].countBytes();
    }

    // 出力
    int count = 0;
    stringstream outss;
    bool isContinue = false;

    while (true) {
        int n = 0;
        int forCount = 0;
        stringstream tmpss;
        for (utf8 u3 : u2) {
            // 2つ選出する1つめまでskip
            if (count > forCount++) continue;
            // tmpに代入
            tmpss << u3;
            // 2つ選出してたら終了
            if (++n == n_gram) {
                outss << tmpss.str() << endl;
                break;
            }
        }

        if (++count == utf8count) break;
    }

    cout << outss.str() << endl;

    return 0;
}

