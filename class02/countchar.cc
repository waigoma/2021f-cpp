#include <iostream>

using namespace std;

int countByte(const unsigned char c) {
    int bytes = 0;
    if ((c >= 0x00) && (c <= 0x7f)) {
        bytes = 1;
    } else if ((c >= 0xc2) && (c <= 0xdf)) {
        bytes = 2;
    } else if ((c >= 0xe0) && (c <= 0xef)) {
        bytes = 3;
    }

    return bytes;
}

int main() {
    string source;
    int count = 0;
    int bytes = 0;

    cout << "文字列は？: "; cin >> source;

    do {
        unsigned char c = source[bytes];
        bytes += countByte(c);
        count++;
    } while (source[bytes] != '\0');

    cout << "文字数: " << count << endl;
}
