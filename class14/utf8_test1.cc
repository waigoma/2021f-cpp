#include <iostream>
#include <sstream>
#include <windows.h>

#include "utf8.h"

using namespace std;

int main() {
    stringstream ss;
    utf8 uc;

//    ss << "5";
//    ss << "m";
//    ss << "の";
    ss << "字"; // 検証する文字を入れる。
    ss >> uc;

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER start, end;
    double sum_avg = 0;

    for (int i = 0; i < 10; i++) {
        QueryPerformanceCounter(&start);
        for (int j = 0; j < 1000000; j++) {
            uc.countBytes();
        }
        QueryPerformanceCounter(&end);
        double time = static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0  / freq.QuadPart;
        cout << "1,000,000 回判定にかかった平均時間: " << time << "ms" << endl;
        sum_avg += time;
    }

    cout << "1,000,000 * 10 回実行した countBytes() の平均時間: " << sum_avg / 10.0 << "ms" << endl;
}