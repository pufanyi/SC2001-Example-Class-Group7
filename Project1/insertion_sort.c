#include "insertion_sort.h"

int insertionSort(int *begin, const int *end) {
    int compareCount = 0;
    for (int *now = begin + 1; now != end; ++now) {
        int key = *now;
        int *p = now - 1;
        while (p >= begin && ++compareCount && *p > key) {
            *(p + 1) = *p;
            --p;
        }
        *(p + 1) = key;
    }
    return compareCount;
}
