#include "check.h"

int isSorted(const int *begin, const int *end) {
    for (const int *p = begin; p != end - 1; ++p) {
        if (*p > *(p + 1)) {
            return 0;
        }
    }
    return 1;
}