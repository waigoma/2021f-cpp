#include <iostream>

using namespace std;

int countByte(const char* c) {
    int bytes = 0;
    if ((*c & 0x80) == 0) {
        bytes = 1;
    } else if ((*c & 0xe0) == 0xc0) {
        bytes = 2;
    } else if ((*c & 0xf0) == 0xe0) {
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
        char* c = &source[bytes];
        bytes += countByte(c);
        count++;
    } while (source[bytes] != '\0');

    cout << "文字数: " << count << endl;
}
