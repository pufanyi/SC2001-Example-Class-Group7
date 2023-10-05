#ifndef PROJECT1_TEST_CASE_GENERATOR_H
#define PROJECT1_TEST_CASE_GENERATOR_H

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "mersenne_twister.h"

int randRange(int min, int max) {
    return randPositiveInt() % (max - min + 1) + min;
}

void randomShuffle(int *begin, const int *end) {
    size_t size = end - begin;
    for (size_t i = 0; i < size; ++i) {
        size_t j = i + randPositiveInt() % (size - i);
        int temp = begin[i];
        begin[i] = begin[j];
        begin[j] = temp;
    }
}

void generateRandomArray(int *begin, const int *end, int min, int max) {
    for (int *p = begin; p != end; ++p) {
        *p = randRange(min, max);
    }
}

void generateRandomPermutation(int *begin, const int *end) {
    size_t size = end - begin;
    for (size_t i = 0; i < size; ++i) {
        begin[i] = (int) i;
    }
    randomShuffle(begin, end);
}

#endif //PROJECT1_TEST_CASE_GENERATOR_H
