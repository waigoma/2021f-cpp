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
    string output;

    int n_gram = 2;
    int n_bytes = 0;

    int count = 0;
    int bytes = 0;

    cout << "文字列は？: "; cin >> source;

    do {
        unsigned char c = source[bytes];
        output += source.substr(bytes, countByte(c));
        bytes += countByte(c);
        if (n_gram == ++count) {
            if (source[bytes] == '\0') break;
            unsigned char c1 = source[n_bytes];
            n_bytes += countByte(c1);
            bytes = n_bytes;
            output += "\n";
            count = 0;
        }
    } while (source[bytes] != '\0');

    cout << output << endl;
}

