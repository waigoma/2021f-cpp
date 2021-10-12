#include "utf8.h"
#include "mysort.cc"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
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

    // sort
    sortUtf8(u2, utf8count);

    stringstream ss;

    for (int i = 0; i < utf8count; i++) {
        int count = 1;
        if (u2[i] == u2[i + 1]) {
            for (int j = i + 1; j < utf8count; j++) {
                if (u2[i] == u2[j]) count++;
                else break;
            }
            i += count - 1;
        }
        ss << count << " " << u2[i] << endl;
    }

    cout << ss.str() << endl;
}
