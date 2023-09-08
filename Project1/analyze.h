#ifndef PROJECT1_ANALYZE_H
#define PROJECT1_ANALYZE_H

#include <stdio.h>
#include <stdarg.h>

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
        EvaluationResult result = evaluate_multiple(sortFunction, function_name, times, size, *args);
        fprintf(file, "%d,%llu,%ld\n", size, result.compareCount, result.time);
    }
    fclose(file);
}

#endif //PROJECT1_ANALYZE_H
