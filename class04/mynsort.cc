#include "utf8.h"
#include "mysort.cc"
#include <iostream>
#include <sstream>

using namespace std;

typedef struct {
    int n;
    string str;
} mynsort;

int compare(const void* myA, const void* myB) {
    if (((mynsort*) myA)->n > ((mynsort*) myB)->n) {
        return -1;
    } else if (((mynsort*) myA)->n < ((mynsort*) myB)->n) {
        return 1;
    } else {
        return 0;
    }
}

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

    int ssSize = 0;

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
        ssSize++;
    }

    mynsort str[ssSize + 1];
    string buf;

    int i = 0;

    while (getline(ss, buf, '\n')) {
        int pos = buf.find(' ');
        basic_string<char> c1 = buf.substr(0, pos);
        basic_string<char> c2 = buf.substr(pos + 1);
        str[i++] = {stoi(c1), c2};
    }

    qsort(str, ssSize, sizeof(mynsort), compare);

    for (int j = 0; j < ssSize; j++) {
        cout << str[j].n << str[j].str << endl;
    }
}