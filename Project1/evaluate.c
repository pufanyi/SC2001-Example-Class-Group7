#include "evaluate.h"
#include "check.h"

#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdarg.h>

EvaluationResult evaluate(SortFunction sortFunction, const int *array_begin, const int *array_end, ...) {
    size_t array_size = array_end - array_begin;
    int *array_copy = (int *) calloc(array_size, sizeof(int));
    memcpy(array_copy, array_begin, sizeof(int) * array_size);
    clock_t begin = clock();

    va_list args;
    va_start(args, array_end);

    compare_count_t compareCount = sortFunction(array_copy, array_copy + array_size, *args);
    clock_t end = clock();
    EvaluationResult result;
    result.time = end - begin;
    result.compareCount = compareCount;
    result.correctness = isSorted(array_copy, array_copy + array_size);
    free(array_copy);
    return result;
}

void outputSortingResult(const char* algoName, const EvaluationResult *result) {
    printf("========================================\n");
    printf("Algorithm: %s\n", algoName);
    printf("Time: %ld\n", result->time);
    printf("Compare count: %llu\n", result->compareCount);
    printf("Correctness: %s\n", result->correctness ? "true" : "false");
    printf("========================================\n");
}
