#ifndef PROJECT1_EVALUATE_H
#define PROJECT1_EVALUATE_H

#include <time.h>

#include "general_sort.h"

typedef struct EvaluationResult {
    int correctness;
    clock_t time;
    compare_count_t compareCount;
} EvaluationResult;

EvaluationResult evaluate(SortFunction sortFunction, const int *array_begin, const int *array_end, ...);

void outputSortingResult(const char* algoName, const EvaluationResult *result);

#endif //PROJECT1_EVALUATE_H
