#include <iostream>
#include <sstream>
#include <windows.h>

#include "utf8.h"

using namespace std;

int main() {
    // 表6-1
//    string source = "あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをん、アカサタナハマヤラワ。日本語、英語。戸を左近円舞え色田をンイ野疎眠ウイ。をこぶんも余りレソ王ト国、または。";

    // 表6-2
//    string source = "abcdefghijklmnopqrstuvwxyz.awsksfdkwksejfnosjhnf2938674918437197346yKJNEOSAJALOKSJDAKIsdoaKjsdjnasdo";

    // 表6-3
//    string source = "せそたちつてとなにぬ4a6sdね日本語、英語。のはひふへほまみむめもやゆよらりるれろwASd1わをん、アカサタナあらもハマ1Ad6ヤラワ。戸を左Wad65w近円余りレソ王ト国舞え色田をンイ野疎眠ウイ。";

    // 表6-4
//    string source = "abcdefghijklmnowksejfno7197346yKJNEOSAJALOKSJDA戸を左近円KIsdにぬね語。oaKj疎眠ウイぶsdjnaすせsdoそとなsjhnf293867491843";

    // 表6-5
    string source = "a戸をbcd左近円にefeqwぬねgh196yK語。疎眠ウイぶすせijJDA5そとなサタnoksejナ語、本近円ぶklmfnんも余は。つてとなをo719734EOLKSンイソ王ト疎眠。あらJN30もs";

    utf8 uc;
    int offset = 0;
    const char* sp = source.c_str();

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    LARGE_INTEGER start, end;
    double sum_avg = 0;

    for (int i = 0; i < 10; i++) {
        QueryPerformanceCounter(&start);
        for (int j = 0; j < 100000; j++) {
            offset = 0;
            sp = source.c_str();
            while (true) {
                uc = utf8(sp + offset);
                if (uc.is_null()) break;
                offset += uc.countBytes();
            }
        }
        QueryPerformanceCounter(&end);
        double time = static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0  / freq.QuadPart;
        cout << "100,000 回判定にかかった平均時間: " << time << "ms" << endl;
        sum_avg += time;
    }

    cout << "100,000 * 10 回実行した countBytes() の平均時間: " << sum_avg / 10.0 << "ms" << endl;
}