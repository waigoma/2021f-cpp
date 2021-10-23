#include "utf8.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

void deleteCRLF(string &targetStr)
{
    const char CR = '\r';
    const char LF = '\n';
    string destStr;
    for (const auto c : targetStr) {
        if (c != CR && c != LF) {
            destStr += c;
        }
    }
    targetStr = move(destStr);
}

int main(int argc, char* argv[]) {
    int n_gram = 2;

    if (argc > 1) {
        n_gram = strtol(argv[1], NULL, 0);
    }

    string tmp;
    string source;

//    cout << "文字列は？: ";
    while (getline(cin, tmp)) source += tmp;
    deleteCRLF(source);
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
        utf8 utmp(sp + offset);
        u2[i] = utf8(sp + offset);
        offset += u2[i].countBytes();
    }

    // sort
//    sortUtf8(u2, utf8count);

    // 出力
    int count = 0;
    stringstream outss;

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
                outss << tmpss.str() << "\n";
                break;
            }
        }

        if (++count == utf8count) break;
    }

    cout << outss.str() << endl;

    return 0;
}

