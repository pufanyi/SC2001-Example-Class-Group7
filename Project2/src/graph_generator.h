#ifndef PROJECT2_GRAPH_GENERATOR_H
#define PROJECT2_GRAPH_GENERATOR_H

#include <stdint.h>

#include "graph.h"
#include "mersenne_twister.h"

#define MAX_WEIGHT 100

int randint(int min, int max) {
    return min + (randInt() % (max - min + 1));
}

void random_graph(Graph *graph, int numEdges) {
    int numVertices = graph->graph.adjList->numVertices;

    for (int i = 0; i < numEdges; ++i) {
        int vertex1 = randint(0, numVertices - 1);
        int vertex2 = randint(0, numVertices - 1);
        int weight = randint(1, MAX_WEIGHT);

        add_edge(graph, vertex1, vertex2, weight);
    }
}

Graph *random_graph_adj_matrix(int numVertices, int numEdges) {
    Graph *graph = create_graph(ADJ_MATRIX, numVertices);
    random_graph(graph, numEdges);
    return graph;
}

Graph *random_graph_adj_list(int numVertices, int numEdges) {
    Graph *graph = create_graph(ADJ_LIST, numVertices);
    random_graph(graph, numEdges);
    return graph;
}

#endif //PROJECT2_GRAPH_GENERATOR_H
