#ifndef PROJECT2_DIJKSTRA_H
#define PROJECT2_DIJKSTRA_H

#include <limits.h>

#include "graph.h"
#include "heap.h"


int *dijkstra_adj_matrix(Graph *graph, compare_count_t *compare_count) {
    if (graph->type != ADJ_MATRIX) {
        return NULL;
    }

    GraphAdjMatrix *adjMatrix = graph->graph.adjMatrix;
    int numVertices = graph->numVertices;
    int *distances = (int *) malloc(numVertices * sizeof(int));
    int *visited = (int *) malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; ++i) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    distances[0] = 0;
    for (int i = 1; i < numVertices; ++i) {
        int min = INT_MAX;
        int min_index = -1;
        for (int j = 0; j < numVertices; ++j) {
            ++(*compare_count);
            if (!visited[j] && distances[j] < min) {
                min = distances[j];
                min_index = j;
            }
        }
        if (min == INT_MAX) {
            break;
        }
        visited[min_index] = 1;
        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && (++(*compare_count)) && adjMatrix->adjMatrix[min_index][j] != INT_MAX &&
                (distances[j] == INT_MAX ||
                 distances[min_index] + adjMatrix->adjMatrix[min_index][j] < distances[j])) {
                distances[j] = distances[min_index] + adjMatrix->adjMatrix[min_index][j];
            }
        }
    }

    free(visited);
    return distances;
}

int *dijkstra_adj_list(Graph *graph, compare_count_t *compare_count) {
    if (graph->type != ADJ_LIST) {
        return NULL;
    }

    GraphAdjList *adjList = graph->graph.adjList;
    int numVertices = graph->numVertices;
    int *distances = (int *) malloc(numVertices * sizeof(int));
    int *visited = (int *) malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; ++i) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    distances[0] = 0;

    Heap *heap = create_heap(numVertices);
    update(heap, 0, 0, compare_count);

    while (heap->nodes[0].distance != INT_MAX) {
        int min_index = heap->nodes[0].vertex;
        visited[min_index] = 1;

        update(heap, min_index, INT_MAX, compare_count);

        for (ListNode *node = adjList->adjLists[min_index]; node != NULL; node = node->next) {
            if (!visited[node->vertex] && (++(*compare_count)) &&
                (distances[node->vertex] == INT_MAX ||
                 distances[min_index] + node->weight < distances[node->vertex])) {
                distances[node->vertex] = distances[min_index] + node->weight;
                update(heap, node->vertex, distances[node->vertex], compare_count);
            }
        }
    }

    free(visited);
    destroy_heap(heap);

    return distances;
}

#endif //PROJECT2_DIJKSTRA_H
