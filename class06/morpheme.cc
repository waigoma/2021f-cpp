#include <iostream>
#include <random>
#include <vector>
#include <sstream>

#include "utf8.h"

using namespace std;

int main() {
    // 開始文字を聞く2
    string str;
    cout << "文字を入力: "; cin >> str;

    const char* sp(str.c_str());

    // utf8 vectorに文字格納
    vector<utf8> uv;
    int offset = 0;

    while (true) {
        utf8 utmp(sp + offset);
        if (utmp.is_null()) break;
        uv.push_back(utmp);
        offset += utmp.countBytes();
    }

    utf8 tmp = uv[0];

    for (auto it : uv) {
        if (it.characterType() != tmp.characterType()) cout << "\n";
        cout << it;
        tmp = it;
    }
}
