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

#endif //PROJECT3_KNAPSACK_H
