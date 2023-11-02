#include <stdio.h>

#include "knapsack.h"

int main() {
    int n, capacity;
    scanf("%d%d", &n, &capacity);
    Item *items = calloc(n, sizeof(Item));
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &items[i].weight, &items[i].profit);
    }
    printf("%d\n", knapsack_basic(items, items + n, capacity));
    printf("%d\n", knapsack_top_down(items, items + n, capacity));
    printf("%d\n", knapsack_bottom_up_basic(items, items + n, capacity));
    printf("%d\n", knapsack_bottom_up_optimized_1(items, items + n, capacity));
    printf("%d\n", knapsack_bottom_up_optimized_2(items, items + n, capacity));
    return 0;
}
