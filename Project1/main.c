#include <stdio.h>

#include "test_case_generator.h"

int main() {
    setUpRandom();
    int a[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }
    randomShuffle(a, a + 10);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    generateRandomArray(a, a + 10, 0, 100);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    generateRandomPermutation(a, a + 10);
    for (int i = 0; i < 10; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
