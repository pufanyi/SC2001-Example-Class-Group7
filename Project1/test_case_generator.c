#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "test_case_generator.h"

int randInt(int min, int max) {
    if (max <= min) {
        fprintf(stderr, "Error: Invalid range in randInt function.\n");
        exit(EXIT_FAILURE);
    }

    return min + rand() % (max - min + 1);
}

void randomShuffle(int *begin, const int *end) {
    size_t size = end - begin;
    for (size_t i = 0; i < size; ++i) {
        size_t j = i + rand() % (size - i);
        int temp = begin[i];
        begin[i] = begin[j];
        begin[j] = temp;
    }
}

void generateRandomArray(int *begin, const int *end, int min, int max) {
    for (int *p = begin; p != end; ++p) {
        *p = randInt(min, max);
    }
}

void generateRandomPermutation(int *begin, const int *end) {
    size_t size = end - begin;
    for (size_t i = 0; i < size; ++i) {
        begin[i] = (int) i;
    }
    randomShuffle(begin, end);
}

void setUpRandom() {
    srand((unsigned int) time(NULL));
}
