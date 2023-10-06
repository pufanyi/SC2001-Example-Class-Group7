#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include <stdlib.h>

typedef struct ListNode {
    int vertex;
    int weight;
    struct ListNode *next;
} ListNode;

typedef struct GraphAdjList {
    int numVertices;
    ListNode **adjLists;
} Graph;

typedef struct GraphAdjMatrix {
    int numVertices;
    int **adjMatrix;
} GraphMatrix;

typedef enum GraphType {
    ADJ_LIST,
    ADJ_MATRIX
} GraphType;

typedef struct Graph {
    GraphType type;

    union {
        GraphAdjList *adjList;
        GraphAdjMatrix *adjMatrix;
    } graph;
} Graph;

Graph *create_graph(GraphType type, int numVertices) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->type = type;

    if (type == ADJ_LIST) {
        graph->graph.adjList = (GraphAdjList *) malloc(sizeof(GraphAdjList));
        graph->graph.adjList->numVertices = numVertices;
        graph->graph.adjList->adjLists = (ListNode **) malloc(numVertices * sizeof(ListNode *));
        for (int i = 0; i < numVertices; i++) {
            graph->graph.adjList->adjLists[i] = NULL;
        }
    } else if (type == ADJ_MATRIX) {
        graph->graph.adjMatrix = (GraphAdjMatrix *) malloc(sizeof(GraphAdjMatrix));
        graph->graph.adjMatrix->numVertices = numVertices;
        graph->graph.adjMatrix->adjMatrix = (int **) malloc(numVertices * sizeof(int *));
        for (int i = 0; i < numVertices; i++) {
            graph->graph.adjMatrix->adjMatrix[i] = (int *) malloc(numVertices * sizeof(int));
            for (int j = 0; j < numVertices; j++) {
                graph->graph.adjMatrix->adjMatrix[i][j] = 0;
            }
        }
    }

    return graph;
}

void add_edge_list(GraphAdjList *graph, int src, int dest, int weight) {
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->vertex = dest;
    newNode->weight = weight;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void add_edge_matrix(GraphAdjMatrix *graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
}

void add_edge(Graph *graph, int src, int dest, int weight) {
    if (graph->type == ADJ_LIST) {
        add_edge_list(graph->graph.adjList, src, dest, weight);
    } else if (graph->type == ADJ_MATRIX) {
        add_edge_matrix(graph->graph.adjMatrix, src, dest, weight);
    }
}

void destroy_graph(Graph *graph) {
    if (graph->type == ADJ_LIST) {
        for (int i = 0; i < graph->graph.adjList->numVertices; i++) {
            ListNode *node = graph->graph.adjList->adjLists[i];
            while (node != NULL) {
                ListNode *temp = node;
                node = node->next;
                free(temp);
            }
        }
        free(graph->graph.adjList->adjLists);
        free(graph->graph.adjList);
    } else if (graph->type == ADJ_MATRIX) {
        for (int i = 0; i < graph->graph.adjMatrix->numVertices; i++) {
            free(graph->graph.adjMatrix->adjMatrix[i]);
        }
        free(graph->graph.adjMatrix->adjMatrix);
        free(graph->graph.adjMatrix);
    }
    free(graph);
}

#endif //PROJECT2_GRAPH_H
