#ifndef PROJECT1_ANALYZE_H
#define PROJECT1_ANALYZE_H

#include "evaluate.h"
#include "sort.h"

void
analyze_with_diff_n(SortFunction sortFunction, const int times, const int min_size, const int max_size, const int step,
                    const int threshold, const char *file_name) {
    FILE *file = fopen(file_name, "w");
    fprintf(file, "n,compareCount,time\n");
    for (int size = min_size; size <= max_size; size += step) {
        EvaluationResult result = evaluate_multiple(sortFunction, times, size, threshold);
        fprintf(file, "%d,%llu,%ld\n", size, result.compareCount, result.time);
    }
    fclose(file);
}

#endif //PROJECT1_ANALYZE_H
