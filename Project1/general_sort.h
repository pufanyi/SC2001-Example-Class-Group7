#ifndef PROJECT1_GENERAL_SORT_H
#define PROJECT1_GENERAL_SORT_H

#include <stdint.h>

typedef uint64_t compare_count_t;

typedef compare_count_t (*SortFunction)(int *begin, const int *end, ...);

#endif //PROJECT1_GENERAL_SORT_H
