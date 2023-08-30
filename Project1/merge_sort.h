#ifndef PROJECT1_MERGE_SORT_H
#define PROJECT1_MERGE_SORT_H

int merge(int *begin, const int *mid, const int *end);
int mergeSort(int *begin, const int *end);
int mergeSortWithThreshold(int *begin, const int *end, int threshold, int (*sortFunction)(int *begin, const int *end));
int mergeSortWithInsertionSortThreshold(int *begin, const int *end, int threshold);

#endif //PROJECT1_MERGE_SORT_H
