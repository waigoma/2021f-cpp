#include "utf8.h"
#include <cstdlib>
#include <sstream>

using namespace std;

int utf8_cmp(const utf8 *a, const utf8 *b) {
    return *a > *b ? 1 : *a < *b ? -1 : 0;
}

void sortUtf8(utf8* a, int len) {
    qsort(a, len, sizeof(utf8), reinterpret_cast<int (*)(const void *, const void *)>(utf8_cmp));
}

int main(int argc, char* argv[]) {
    int n_gram = 2;

    if (argc > 1) {
        n_gram = strtol(argv[1], NULL, 0);
    }

    utf8 strTmp[2048];
    string source;

    int len = 0;
    int tmp = 0;

    while (cin >> source) {
        int offset = 0;
        utf8 u1;
        const char* sp = source.c_str();

        tmp = 0;

        while (true) {
            u1 = utf8(sp + offset);
            offset += u1.countBytes();
            if (u1.is_null()) break;
            strTmp[len++] = u1;
            tmp++;
        }
    }

    n_gram = tmp;

    utf8 str[len];
    for (int j = 0; j < len; j++) {
        str[j] = strTmp[j];
    }

    sortUtf8(str, len);

    // 出力
    stringstream outss;

    int n = 0;
    stringstream tmpss;
    for (utf8 u3 : str) {
        // tmpに代入
        tmpss << u3;
        // 2つ選出してたら終了
        if (++n == n_gram) {
            outss << tmpss.str() << endl;
            n = 0;
            tmpss.str("");
            tmpss.clear(stringstream::goodbit);
        }
    }

    cout << outss.str() << endl;
}