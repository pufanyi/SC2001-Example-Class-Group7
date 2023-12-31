#ifndef PROJECT1_EVALUATE_H
#define PROJECT1_EVALUATE_H

#include <time.h>
#include <memory.h>
#include <stdarg.h>
#include <inttypes.h>

#include "sort.h"
#include "test_case_generator.h"

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

int roundDoubleToInt(double x) {
    return (int) (x + 0.5);
}

EvaluationResult evaluate_multiple(SortFunction sortFunction, const int times, const int size, ...) {
    int *array = (int *) malloc(sizeof(int) * size);
    int *array_begin = array;
    int *array_end = array + size;

    EvaluationResult finalResult;
    finalResult.correctness = 1;
    finalResult.time = 0;
    finalResult.compareCount = 0;

    va_list args;
    va_start(args, size);

    for (int i = 0; i < times; ++i) {
        printf("Evaluating %d/%d\n", i + 1, times);
        generateRandomArray(array_begin, array_end, 1, size);
        EvaluationResult result = evaluate(sortFunction, array_begin, array_end, *args);
        finalResult.correctness &= result.correctness;
        finalResult.time += result.time;
        finalResult.compareCount += result.compareCount;
    }

    finalResult.time = roundDoubleToInt((double) finalResult.time / times);
    finalResult.compareCount = roundDoubleToInt((double) finalResult.compareCount / times);

    free(array);

    return finalResult;
}

EvaluationResult *evaluate_multiple_with_known_array(SortFunction SortFunction, const int times, int **arrays_begin, int **arrays_end, ...) {
    EvaluationResult *results = (EvaluationResult *) malloc(sizeof(EvaluationResult) * times);
    va_list args;
    va_start(args, arrays_end);
    for (int i = 0; i < times; ++i) {
        EvaluationResult result = evaluate(SortFunction, arrays_begin[i], arrays_end[i], *args);
        results[i] = result;
    }
    return results;
}

void outputSortingResult(const char *algoName, const EvaluationResult *result) {
    printf("========================================\n");
    printf("Algorithm: %s\n", algoName);
    printf("Time: %ld\n", result->time);
    printf("Compare count: %" PRIu64 "\n", result->compareCount);
    printf("Correctness: %s\n", result->correctness ? "true" : "false");
    printf("========================================\n");
}

void outputSortingResultWithoutName(const EvaluationResult *result) {
    printf("========================================\n");
    printf("Time: %ld\n", result->time);
    printf("Compare count: %" PRIu64 "\n", result->compareCount);
    printf("Correctness: %s\n", result->correctness ? "true" : "false");
    printf("========================================\n");
}

#endif //PROJECT1_EVALUATE_H
