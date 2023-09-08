#include <stdio.h>
#include <malloc.h>

#include "file.h"
#include "analyze.h"
#include "sort.h"

int main() {
    mkdir_func("data");
    int start = 0;
    int end = 5000000;
    int step = 1000000;
    analyze_with_diff_n((SortFunction) mergeSortWithInsertionSort, 5, start + step, end, step, 16,
                        "./data/merge_sort_with_insertion_sort.csv");
    return 0;
}
