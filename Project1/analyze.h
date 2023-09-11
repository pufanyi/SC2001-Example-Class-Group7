#ifndef PROJECT1_ANALYZE_H
#define PROJECT1_ANALYZE_H

#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>

#include "evaluate.h"
#include "sort.h"

void
analyze_with_diff_n(SortFunction sortFunction, const int times, const int min_size, const int max_size, const int step,
                    const char *file_name, const char *function_name, ...) {
    FILE *file = fopen(file_name, "w");
    fprintf(file, "n,compareCount,time\n");
    va_list args;
    va_start(args, function_name);
    for (int size = min_size; size <= max_size; size += step) {
        printf("Evaluating %s with n = %d\n", function_name, size);
        fflush(stdout);
        EvaluationResult result = evaluate_multiple(sortFunction, times, size, *args);
        fprintf(file, "%d,%" PRIu64 ",%ld\n", size, result.compareCount, result.time);
        fflush(file);
    }
    fclose(file);
}

void analyze_with_diff_s(SortFunction sortFunction, const int times, const int size, const int min_threshold,
                         const int max_threshold, const int step, const char *file_name, const char *function_name,
                         ...) {
    FILE *file = fopen(file_name, "w");
    fprintf(file, "threshold");
    for (int i = 0; i < times; ++i) {
        fprintf(file, ",CompareCount%d,time%d", i + 1, i + 1);
        fflush(file);
    }
    fprintf(file, "\n");
    fflush(file);
    va_list args;
    va_start(args, function_name);

    int **arrays_begin = (int **) malloc(sizeof(int *) * times);
    int **arrays_end = (int **) malloc(sizeof(int *) * times);
    for (int i = 0; i < times; ++i) {
        arrays_begin[i] = (int *) malloc(sizeof(int) * size);
        arrays_end[i] = arrays_begin[i] + size;
        generateRandomArray(arrays_begin[i], arrays_end[i], 1, size);
    }


    for (int threshold = min_threshold; threshold <= max_threshold; threshold += step) {
        printf("Evaluating %s with threshold = %d\n", function_name, threshold);
        fflush(stdout);
        EvaluationResult *results = evaluate_multiple_with_known_array(sortFunction, times, arrays_begin, arrays_end, threshold);
        EvaluationResult finalResult;
        finalResult.correctness = 1;
        finalResult.time = 0;
        finalResult.compareCount = 0;
        for (int i = 0; i < times; ++i) {
            finalResult.correctness &= results[i].correctness;
            finalResult.time += results[i].time;
            finalResult.compareCount += results[i].compareCount;
        }
        finalResult.time = roundDoubleToInt((double) finalResult.time / times);
        finalResult.compareCount = roundDoubleToInt((double) finalResult.compareCount / times);
        fprintf(file, "%d", threshold);
        for (int i = 0; i < times; ++i) {
            fprintf(file, ",%" PRIu64 ",%ld", results[i].compareCount, results[i].time);
            fflush(file);
        }
        fprintf(file, "\n");
        fflush(file);
        free(results);
    }

    fclose(file);
}

#endif //PROJECT1_ANALYZE_H
