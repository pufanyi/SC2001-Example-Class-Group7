#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>

#include "test_case_generator.h"
#include "check.h"
#include "merge_sort.h"

int main() {
    setUpRandom();
    int array_size;
    printf("Enter the size of the array: ");
    scanf("%d", &array_size);
    int threshold;
    printf("Enter the threshold: ");
    scanf("%d", &threshold);
    int *array = (int *) malloc(sizeof(int) * array_size);
    int *array_copy = (int *) malloc(sizeof(int) * array_size);
    generateRandomPermutation(array, array + array_size);
    memcpy(array_copy, array, sizeof(int) * array_size);
    int compareCountMergeSort = mergeSort(array_copy, array_copy + array_size);
    printf("Number of comparisons in merge sort: %d\n", compareCountMergeSort);
    int compareCountMergeSortWithInsertionSortThreshold = mergeSortWithInsertionSortThreshold(array, array + array_size, threshold);
    printf("Number of comparisons in merge sort with insertion sort threshold: %d\n", compareCountMergeSortWithInsertionSortThreshold);
    assert(isSorted(array, array + array_size));
    assert(isSorted(array_copy, array_copy + array_size));
    return 0;
}
