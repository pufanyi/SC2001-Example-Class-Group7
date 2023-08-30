#include <stdio.h>
#include <malloc.h>

#include "test_case_generator.h"
#include "evaluate.h"
#include "sort.h"

int main() {
    setUpRandom();
    int array_size;
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);
    int threshold;
    printf("Enter the threshold: ");
    scanf("%d", &threshold);
    int *array = (int *) malloc(sizeof(int) * array_size);
    generateRandomPermutation(array, array + array_size);

    EvaluationResult result1 = evaluate((SortFunction) mergeSort, array, array + array_size);
    outputSortingResult("Merge sort", &result1);

    EvaluationResult result2 = evaluate((SortFunction) mergeSortWithInsertionSort, array,
                                       array + array_size, threshold);
    outputSortingResult("Merge sort with insertion sort threshold", &result2);
    return 0;
}
