#ifndef PROJECT1_EVALUATE_H
#define PROJECT1_EVALUATE_H

#include <time.h>
#include <memory.h>
#include <stdarg.h>

#include "sort.h"

typedef struct EvaluationResult {
    int correctness;
    clock_t time;
    compare_count_t compareCount;
} EvaluationResult;

int isSorted(const int *begin, const int *end) {
    for (const int *p = begin; p != end - 1; ++p) {
        if (*p > *(p + 1)) {
            return 0;
        }
    }
    return 1;
}

EvaluationResult evaluate(SortFunction sortFunction, const int *array_begin, const int *array_end, ...) {
    size_t array_size = array_end - array_begin;
    int *array_copy = (int *) calloc(array_size, sizeof(int));
    memcpy(array_copy, array_begin, sizeof(int) * array_size);

    va_list args;
    va_start(args, array_end);

    clock_t begin = clock();
    compare_count_t compareCount = sortFunction(array_copy, array_copy + array_size, *args);
    clock_t end = clock();

    EvaluationResult result;
    result.time = end - begin;
    result.compareCount = compareCount;
    result.correctness = isSorted(array_copy, array_copy + array_size);
    free(array_copy);
    return result;
}

void outputSortingResult(const char *algoName, const EvaluationResult *result) {
    printf("========================================\n");
    printf("Algorithm: %s\n", algoName);
    printf("Time: %ld\n", result->time);
    printf("Compare count: %llu ms\n", result->compareCount);
    printf("Correctness: %s\n", result->correctness ? "true" : "false");
    printf("========================================\n");
}

#endif //PROJECT1_EVALUATE_H
