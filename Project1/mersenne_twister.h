#ifndef PROJECT1_MERSENNE_TWISTER_H
#define PROJECT1_MERSENNE_TWISTER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MERSENNE_TWISTER_W 32
#define MERSENNE_TWISTER_N 624
#define MERSENNE_TWISTER_M 397
#define MERSENNE_TWISTER_R 31

#define MERSENNE_TWISTER_A 0x9908B0DF

#define MERSENNE_TWISTER_U 11
#define MERSENNE_TWISTER_D 0xFFFFFFFF

#define MERSENNE_TWISTER_S 7
#define MERSENNE_TWISTER_B 0x9D2C5680

#define MERSENNE_TWISTER_T 15
#define MERSENNE_TWISTER_C 0xEFC60000

#define MERSENNE_TWISTER_F 0x6C078965

#define MERSENNE_TWISTER_LOWER_MASK 0x7FFFFFFF
#define MERSENNE_TWISTER_UPPER_MASK 0x80000000

#define MERSENNE_TWISTER_L 18

typedef struct MersenneTwister {
    uint32_t state[MERSENNE_TWISTER_N];
    uint32_t index;
} MersenneTwister;

void initMersenneTwister(MersenneTwister *mt, uint32_t seed) {
    mt->state[0] = seed;
    for (uint32_t i = 1; i < MERSENNE_TWISTER_N; ++i) {
        mt->state[i] = MERSENNE_TWISTER_F * (mt->state[i - 1] ^ (mt->state[i - 1] >> (MERSENNE_TWISTER_W - 2))) + i;
    }
    mt->index = 0;
}

void twist(MersenneTwister *mt) {
    for (uint32_t i = 0; i < MERSENNE_TWISTER_N; ++i) {
        uint32_t x = (mt->state[i] & MERSENNE_TWISTER_UPPER_MASK) + (mt->state[(i + 1) % 624] & MERSENNE_TWISTER_LOWER_MASK);
        uint32_t xA = x >> 1;
        if (x % 2 != 0) {
            xA ^= MERSENNE_TWISTER_A;
        }
        mt->state[i] = mt->state[(i + MERSENNE_TWISTER_M) % MERSENNE_TWISTER_N] ^ xA;
    }
    mt->index = 0;
}

uint32_t extract(MersenneTwister *mt) {
    if (mt->index == MERSENNE_TWISTER_N) {
        twist(mt);
    }
    uint32_t y = mt->state[mt->index];
    y ^= (y >> MERSENNE_TWISTER_U) & MERSENNE_TWISTER_D;
    y ^= (y << MERSENNE_TWISTER_S) & MERSENNE_TWISTER_B;
    y ^= (y << MERSENNE_TWISTER_T) & MERSENNE_TWISTER_C;
    y ^= y >> MERSENNE_TWISTER_L;
    ++mt->index;
    return y;
}

uint32_t randInt() {
    static MersenneTwister mt;
    static int initialized = 0;
    if (!initialized) {
        initMersenneTwister(&mt, (uint32_t) time(NULL));
        initialized = 1;
    }
    return extract(&mt);
}

#endif //PROJECT1_MERSENNE_TWISTER_H
