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
    mynsort mynTmp[2048];

    int i = 0;

    while (getline(cin, source)) {
        int pos = source.find(' ');
        basic_string<char> c1 = source.substr(0, pos);
        basic_string<char> c2 = source.substr(pos + 1);
        mynTmp[i++] = {stoi(c1), c2};
    }

    mynsort mynstruct[i];
    for (int j = 0; j < i; j++) mynstruct[j] = mynTmp[j];

    qsort(mynstruct, i, sizeof(mynsort), compare);

    for (const auto& myn : mynstruct) {
        cout << myn.n << " " << myn.str << endl;
    }
}