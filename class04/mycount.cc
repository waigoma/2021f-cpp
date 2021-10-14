#include <iostream>
#include <sstream>

using namespace std;

int main() {
    string source;

    string tmp;

    int count = 1;

    while (cin >> source) {
        if (source == tmp) {
            count++;
        } else {
            if (!tmp.empty())  cout << count << " " << tmp << endl;
            tmp = source;
            count = 1;
        }
    }

}
