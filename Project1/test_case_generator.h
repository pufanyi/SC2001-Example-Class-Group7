#ifndef PROJECT1_TEST_CASE_GENERATOR_H
#define PROJECT1_TEST_CASE_GENERATOR_H

void setUpRandom(void);
int randInt(int min, int max);
void randomShuffle(int *begin, const int *end);
void generateRandomArray(int *begin, const int *end, int min, int max);
void generateRandomPermutation(int *begin, const int *end);

#endif //PROJECT1_TEST_CASE_GENERATOR_H
