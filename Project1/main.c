#include <stdio.h>
#include <malloc.h>

#include "test_case_generator.h"
#include "evaluate.h"
#include "sort.h"

int main() {
    int array_size;
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);
    int threshold;
    printf("Enter the threshold: ");
    scanf("%d", &threshold);

    const int times = 5;

    EvaluationResult result1 = evaluate_multiple((SortFunction) mergeSort, times, array_size);
    outputSortingResult("Merge sort", &result1);

    EvaluationResult result2 = evaluate_multiple((SortFunction) mergeSortWithInsertionSort, times, array_size, threshold);
    outputSortingResult("Merge sort with insertion sort threshold", &result2);

    EvaluationResult result3 = evaluate_multiple((SortFunction) mergeSortNoRecursion, times, array_size);
    outputSortingResult("Merge sort no recursion", &result3);

    EvaluationResult result4 = evaluate_multiple((SortFunction) mergeSortNoRecursionWithInsertionSort, times, array_size);
    outputSortingResult("Merge sort no recursion with insertion sort threshold", &result4);

    return 0;
}
