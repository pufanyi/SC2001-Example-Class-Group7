#include <stdlib.h>
#include <memory.h>

#include "insertion_sort.h"

int merge(int *begin, int *mid, const int *end) {
    int compareCount = 0;
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

int mergeSort(int *begin, const int *end) {
    int compareCount = 0;
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

int mergeSortWithThreshold(int *begin, const int *end, int threshold, int (*sortFunction)(int *begin, const int *end)) {
    int compareCount = 0;
    size_t size = end - begin;
    if (size <= threshold) {
        compareCount += sortFunction(begin, end);
    } else {
        int *mid = begin + size / 2;
        compareCount += mergeSortWithThreshold(begin, mid, threshold, sortFunction);
        compareCount += mergeSortWithThreshold(mid, end, threshold, sortFunction);
        compareCount += merge(begin, mid, end);
    }
    return compareCount;
}

int mergeSortWithInsertionSortThreshold(int *begin, const int *end, int threshold) {
    return mergeSortWithThreshold(begin, end, threshold, insertionSort);
}
