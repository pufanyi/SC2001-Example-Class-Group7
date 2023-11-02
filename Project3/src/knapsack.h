#ifndef PROJECT3_KNAPSACK_H
#define PROJECT3_KNAPSACK_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    int weight;
    int profit;
} Item;

int max(const int a, const int b) {
    return a > b ? a : b;
}

int knapsack_recursive(const Item *items_begin, const Item *items_end,
                       const int capacity, const int *f_last) {
    if (items_begin == items_end) {
        return f_last[capacity];
    }
    int *f_current = calloc(capacity + 1, sizeof(int));
    for (int i = 0; i <= capacity; ++i) {
        if (i >= items_begin->weight) {
            f_current[i] = max(f_last[i], f_last[i - items_begin->weight] + items_begin->profit);
        } else {
            f_current[i] = f_last[i];
        }
    }
    int ans = knapsack_recursive(items_begin + 1, items_end, capacity, f_current);
    free(f_current);
    return ans;
}

int knapsack_top_down(const Item *items_begin, const Item *items_end, const int capacity) {
    int *f = calloc((capacity + 1) * (items_end - items_begin + 1), sizeof(int));
    memset(f, 0, (capacity + 1) * (items_end - items_begin + 1) * sizeof(int));
    int ans = knapsack_recursive(items_begin, items_end, capacity, f);
    free(f);
    return ans;
}

int knapsack_bottom_up_basic(const Item *items_begin, const Item *items_end, const int capacity) {
    int **f = calloc((items_end - items_begin + 1), sizeof(int *));
    for (int i = 0; i <= items_end - items_begin; ++i) {
        f[i] = calloc(capacity + 1, sizeof(int));
    }
    memset(f[0], 0, (capacity + 1) * sizeof(int));
    for (const Item *item = items_begin; item != items_end; ++item) {
        for (int i = 0; i <= capacity; ++i) {
            if (i >= item->weight) {
                f[item - items_begin + 1][i] = max(f[item - items_begin][i],
                                                   f[item - items_begin][i - item->weight] + item->profit);
            } else {
                f[item - items_begin + 1][i] = f[item - items_begin][i];
            }
        }
    }
    return f[items_end - items_begin][capacity];
}

int knapsack_bottom_up_optimized_1(const Item *items_begin, const Item *items_end, const int capacity) {
    int **f = calloc(2, sizeof(int *));
    for (int i = 0; i < 2; ++i) {
        f[i] = calloc(capacity + 1, sizeof(int));
    }
    memset(f[0], 0, (capacity + 1) * sizeof(int));
    for (const Item *item = items_begin; item != items_end; ++item) {
        size_t i = (item - items_begin + 1) & 1;
        for (int j = 0; j <= capacity; ++j) {
            if (j >= item->weight) {
                f[i][j] = max(f[i ^ 1][j], f[i ^ 1][j - item->weight] + item->profit);
            } else {
                f[i][j] = f[i ^ 1][j];
            }
        }
    }
    return f[(items_end - items_begin) & 1][capacity];
}

int knapsack_bottom_up_optimized_2(const Item *items_begin, const Item *items_end, const int capacity) {
    int *f = calloc(capacity + 1, sizeof(int));
    memset(f, 0, (capacity + 1) * sizeof(int));
    for (const Item *item = items_begin; item != items_end; ++item) {
        for (int i = capacity; i >= item->weight; --i) {
            f[i] = max(f[i], f[i - item->weight] + item->profit);
        }
    }
    return f[capacity];
}

#endif //PROJECT3_KNAPSACK_H
