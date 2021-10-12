#include "utf8.h"
#include <cstdlib>

using namespace std;

int utf8_cmp(const utf8 *a, const utf8 *b) {
    return *a > *b ? -1 : *a < *b ? 1 : 0;
}

void sortUtf8(utf8* a, int len) {
    qsort(a, len, sizeof(utf8), reinterpret_cast<int (*)(const void *, const void *)>(utf8_cmp));
}
