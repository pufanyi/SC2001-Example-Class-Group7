#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

#include "insertion_sort.h"

#include "general_sort.h"

compare_count_t merge(int *begin, int *mid, const int *end) {
    compare_count_t compareCount = 0;
    int *left = begin;
    int *right = mid;
    size_t baseSize = sizeof(int) * (end - begin);
    int *temp = (int *) malloc(baseSize);
    int *p = temp;
    while (left != mid && right != end) {
        if (*left <= *right) {
            *p++ = *left++;
        } else {
            *p++ = *right++;
        }
        ++compareCount;
    }
    while (left != mid) {
        *p++ = *left++;
    }
    while (right != end) {
        *p++ = *right++;
    }
    memcpy(begin, temp, baseSize);
    free(temp);
    return compareCount;
}

compare_count_t mergeSort(int *begin, const int *end) {
    compare_count_t compareCount = 0;
    size_t size = end - begin;
    if (size == 1) {
        return 0;
    }
    int *mid = begin + size / 2;
    compareCount += mergeSort(begin, mid);
    compareCount += mergeSort(mid, end);
    compareCount += merge(begin, mid, end);
    return compareCount;
}

compare_count_t mergeSortWithInsertionSort(int *begin, const int *end, int threshold) {
    compare_count_t compareCount = 0;
    size_t size = end - begin;
    if (size <= threshold) {
        compareCount += insertionSort(begin, end);
    } else {
        int *mid = begin + size / 2;
        compareCount += mergeSortWithInsertionSort(begin, mid, threshold);
        compareCount += mergeSortWithInsertionSort(mid, end, threshold);
        compareCount += merge(begin, mid, end);
    }
    return compareCount;
}
