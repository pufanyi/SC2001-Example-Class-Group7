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
            f_current[i] = max(f_last[i], f_current[i - items_begin->weight] + items_begin->profit);
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
                                                   f[item - items_begin + 1][i - item->weight] + item->profit);
            } else {
                f[item - items_begin + 1][i] = f[item - items_begin][i];
            }
        }
    }
    int ans = f[items_end - items_begin][capacity];
    for (int i = 0; i <= items_end - items_begin; ++i) {
        free(f[i]);
    }
    free(f);
    return ans;
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
                f[i][j] = max(f[i ^ 1][j], f[i][j - item->weight] + item->profit);
            } else {
                f[i][j] = f[i ^ 1][j];
            }
        }
    }
    int ans = f[(items_end - items_begin) & 1][capacity];
    for (int i = 0; i < 2; ++i) {
        free(f[i]);
    }
    free(f);
    return ans;
}

int knapsack_bottom_up_optimized_2(const Item *items_begin, const Item *items_end, const int capacity) {
    int *f = calloc(capacity + 1, sizeof(int));
    memset(f, 0, (capacity + 1) * sizeof(int));
    for (const Item *item = items_begin; item != items_end; ++item) {
        for (int i = item->weight; i <= capacity; ++i) {
            f[i] = max(f[i], f[i - item->weight] + item->profit);
        }
    }
    int ans = f[capacity];
    return ans;
}

#endif //PROJECT3_KNAPSACK_H
