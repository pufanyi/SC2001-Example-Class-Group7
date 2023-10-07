#include <stdio.h>

#include "graph_generator.h"
#include "dijkstra.h"

int main() {
    Graph *graph = random_graph_adj_list(3, 5);
    Graph *graph2 = adj_graph_to_matrix(graph);
    int compare_count = 0;
    int *dist = dijkstra_adj_list(graph, &compare_count);
    print_graph(graph);
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("%d ", dist[i]);
    }
    printf("\n");
    printf("Compare count: %d\n", compare_count);
    compare_count = 0;
    dist = dijkstra_adj_matrix(graph2, &compare_count);
    for (int i = 0; i < graph->numVertices; ++i) {
        printf("%d ", dist[i]);
    }
    printf("\n");
    printf("Compare count: %d\n", compare_count);
    return 0;
}
