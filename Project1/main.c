#include <stdio.h>
#include <malloc.h>

#include "file.h"
#include "analyze.h"
#include "sort.h"

void eval_diff_n() {
    const int start = 0;
    const int end = 50000000;
    const int step = 1000000;
    const int times = 5;
    const int threshold = 16;
    analyze_with_diff_n((SortFunction) mergeSort, times, start + step, end, step,
                        "./data/merge_sort_diff_n.csv", "merge sort");
    analyze_with_diff_n((SortFunction) mergeSortWithInsertionSort, times, start + step, end, step,
                        "./data/merge_sort_with_insertion_sort_diff_n.csv", "merge sort with insertion sort",
                        threshold);
}

void eval_diff_s() {
    const int start = 1;
    const int end = 126;
    const int step = 1;
    const int times = 3;
    const int size = 20000000;
    analyze_with_diff_s((SortFunction) mergeSortWithInsertionSort, times, size, start, end, step,
                        "./data/merge_sort_with_insertion_sort_diff_s.csv", "merge sort with insertion sort");
}

void eval_diff_n_and_s() {
    const int start = 10000000;
    const int end =50000000;
    const int step = 10000000;
    const int times = 3;
    const int start_s = 1;
    const int end_s = 128;
    const int step_s = 1;
    for (int n = start; n <= end; n += step) {
        char file_name[100];
        char function_name[100];
        sprintf(file_name, "./data/merge_sort_with_insertion_sort_diff_n_and_s_%d.csv", n);
        sprintf(function_name, "merge sort with insertion sort, n = %d", n);
        analyze_with_diff_s((SortFunction) mergeSortWithInsertionSort, times, n, start_s, end_s, step_s, file_name, function_name);
    }
}

int main() {
    mkdir_func("data");
    eval_diff_n_and_s();
    // eval_diff_s();
    // eval_diff_n();
    return 0;
}
