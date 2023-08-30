#ifndef PROJECT1_SORT_H
#define PROJECT1_SORT_H

#include <stdint.h>

typedef uint64_t compare_count_t;

typedef compare_count_t (*SortFunction)(int *begin, const int *end, ...);

compare_count_t insertionSort(int *begin, const int *end);

compare_count_t mergeSort(int *begin, const int *end);
compare_count_t mergeSortWithInsertionSort(int *begin, const int *end, int threshold);

#endif //PROJECT1_SORT_H
