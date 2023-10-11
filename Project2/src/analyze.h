#ifndef PROJECT2_ANALYZE_H
#define PROJECT2_ANALYZE_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "graph.h"
#include "graph_generator.h"
#include "dijkstra.h"

typedef long long time_t;

typedef struct AnalysisResult {
    int num_vertices;
    int num_edges;
    int compare_count;
} AnalysisResult;

typedef struct AnalysisResultList {
    AnalysisResult *results;
    int size;
    int capacity;
} AnalysisResultList;

AnalysisResultList *init_result_list() {
    AnalysisResultList *result_list = (AnalysisResultList *) malloc(sizeof(AnalysisResultList));
    result_list->size = 0;
    result_list->capacity = 10;
    result_list->results = (AnalysisResult *) malloc(result_list->capacity * sizeof(AnalysisResult));
    return result_list;
}

void add_result(AnalysisResultList *result_list, AnalysisResult result) {
    if (result_list->size == result_list->capacity) {
        result_list->capacity *= 2;
        result_list->results = (AnalysisResult *) realloc(result_list->results,
                                                          result_list->capacity * sizeof(AnalysisResult));
        if (result_list->results == NULL) {
            fprintf(stderr, "Error: realloc failed\n");
            exit(EXIT_FAILURE);
        }
    }
    result_list->results[result_list->size++] = result;
}

void export_result(AnalysisResultList *result_list, const char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    fprintf(file, "num_vertices,num_edges,compare_count\n");
    for (int i = 0; i < result_list->size; ++i) {
        fprintf(file, "%d,%d,%d\n", result_list->results[i].num_vertices, result_list->results[i].num_edges,
                result_list->results[i].compare_count);
    }
    fclose(file);
}

int analyze_adj_matrix(int num_vertices, int num_edges) {
    Graph *graph = random_graph_adj_matrix(num_vertices, num_edges);
    compare_count_t compare_count = 0;
    dijkstra_adj_matrix(graph, &compare_count);
    destroy_graph(graph);
    return compare_count;
}

int analyze_adj_list(int num_vertices, int num_edges) {
    Graph *graph = random_graph_adj_list(num_vertices, num_edges);
    compare_count_t compare_count = 0;
    dijkstra_adj_list(graph, &compare_count);
    destroy_graph(graph);
    return compare_count;
}

time_t analyze_time_adj_matrix(int num_vertices, int num_edges) {

    Graph *graph = random_graph_adj_matrix(num_vertices, num_edges);
    struct timespec start, end;
    compare_count_t compare_count = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    dijkstra_adj_matrix(graph, &compare_count);
    clock_gettime(CLOCK_MONOTONIC, &end);

    destroy_graph(graph);

    return (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
}

time_t analyze_time_adj_list(int num_vertices, int num_edges) {
    Graph *graph = random_graph_adj_list(num_vertices, num_edges);
    struct timespec start, end;
    compare_count_t compare_count = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    dijkstra_adj_list(graph, &compare_count);
    clock_gettime(CLOCK_MONOTONIC, &end);

    destroy_graph(graph);

    return (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
}

typedef int (*AnalyzeFunction)(int, int);

void analyze_with_different_edges(int num_vertices, int num_edges_start, int num_edges_end,
                                  int num_edges_step, int num_trials,
                                  AnalysisResultList *result_list, AnalyzeFunction analyze) {
    for (int i = num_edges_start; i <= num_edges_end; i += num_edges_step) {
        printf("num_vertices: %d, num_edges: %d\n", num_vertices, i);
        fflush(stdout);
        for (int j = 0; j < num_trials; ++j) {
            AnalysisResult result;
            result.num_edges = i;
            result.compare_count = analyze(num_vertices, i);
            add_result(result_list, result);
        }
    }
}

void analyze_with_different_method(int num_vertices_start,
                                   int num_vertices_end,
                                   int num_vertices_step,
                                   int num_edges_start,
                                   int num_edges_end,
                                   int num_edges_step,
                                   int num_trials,
                                   AnalysisResultList *result_list,
                                   AnalyzeFunction analyze) {
    for (int i = num_vertices_start; i <= num_vertices_end; i += num_vertices_step) {
        printf("num_vertices: %d\n", i);
        fflush(stdout);
        analyze_with_different_edges(i, num_edges_start, num_edges_end, num_edges_step, num_trials, result_list,
                                     analyze);
    }
}

void analyze_diff_edge_matrix() {
    const char *file_name = "../data/diff_edge_matrix.csv";
    const int NUM_VERTICES = 1000;
    const int NUM_EDGES_START = 10000;
    const int NUM_EDGES_END = 1000000;
    const int NUM_EDGES_STEP = 10000;
    const int NUM_TRIALS = 10;
    AnalysisResultList *result_list = init_result_list();
    analyze_with_different_edges(NUM_VERTICES, NUM_EDGES_START, NUM_EDGES_END, NUM_EDGES_STEP, NUM_TRIALS,
                                 result_list, analyze_adj_matrix);
    export_result(result_list, file_name);
}

void analyze_diff_vertex_matrix() {
    const char *file_name = "../data/diff_vertex_matrix.csv";
    const int NUM_VERTICES_START = 100;
    const int NUM_VERTICES_END = 5000;
    const int NUM_VERTICES_STEP = 100;
    const int NUM_EDGES = 10000;
    const int NUM_TRIALS = 100;
    AnalysisResultList *result_list = init_result_list();
    analyze_with_different_method(NUM_VERTICES_START, NUM_VERTICES_END, NUM_VERTICES_STEP, NUM_EDGES, NUM_EDGES,
                                  NUM_EDGES, NUM_TRIALS, result_list, analyze_adj_matrix);
    export_result(result_list, file_name);
}

void analyze_diff_edge_list() {
    const char *file_name = "../data/diff_edge_list.csv";
    const int NUM_VERTICES = 10000;
    const int NUM_EDGES_START = 10000;
    const int NUM_EDGES_END = 1000000;
    const int NUM_EDGES_STEP = 10000;
    const int NUM_TRIALS = 10;
    AnalysisResultList *result_list = init_result_list();
    analyze_with_different_edges(NUM_VERTICES, NUM_EDGES_START, NUM_EDGES_END, NUM_EDGES_STEP, NUM_TRIALS,
                                 result_list, analyze_adj_list);
    export_result(result_list, file_name);
}

void analyze_diff_vertex_list() {
    const char *file_name = "../data/diff_vertex_list.csv";
    const int NUM_VERTICES_START = 1000;
    const int NUM_VERTICES_END = 100000;
    const int NUM_VERTICES_STEP = 1000;
    const int NUM_EDGES = 200000;
    const int NUM_TRIALS = 100;
    AnalysisResultList *result_list = init_result_list();
    analyze_with_different_method(NUM_VERTICES_START, NUM_VERTICES_END, NUM_VERTICES_STEP, NUM_EDGES, NUM_EDGES,
                                  NUM_EDGES, NUM_TRIALS, result_list, analyze_adj_list);
    export_result(result_list, file_name);
}

typedef time_t (*AnalyzeTimeFunction)(int, int);

void analyze_time_with_different_edges(int num_vertices, int num_edges_start, int num_edges_end,
                                       int num_edges_step, int num_trials,
                                       const char *output_file, AnalyzeTimeFunction analyze) {
    FILE *file = fopen(output_file, "w");
    fprintf(file, "num_vertices,num_edges,time\n");
    for (int times = 0; times < num_trials; ++times) {
        printf("Trial %d\n", times);
        fflush(stdout);
        for (int i = num_edges_start; i <= num_edges_end; i += num_edges_step) {
            // printf("num_vertices: %d, num_edges: %d\n", num_vertices, i);
            // fflush(stdout);
            int num_edges = i;
            time_t compare_count = analyze(num_vertices, i);
            fprintf(file, "%d,%d,%lld\n", num_vertices, num_edges, compare_count);
            fflush(file);
        }
    }
    fclose(file);
}

void analyze_time_diff_edge_matrix() {
    const char *file_name = "../data/time_diff_edge_matrix.csv";
    const int NUM_VERTICES = 1000;
    const int NUM_EDGES_START = 10000;
    const int NUM_EDGES_END = 1000000;
    const int NUM_EDGES_STEP = 10000;
    const int NUM_TRIALS = 100;
    analyze_time_with_different_edges(NUM_VERTICES, NUM_EDGES_START, NUM_EDGES_END, NUM_EDGES_STEP, NUM_TRIALS,
                                      file_name, analyze_time_adj_matrix);
}

void analyze_time_diff_edge_list() {
    const char *file_name = "../data/time_diff_edge_list.csv";
    const int NUM_VERTICES = 1000;
    const int NUM_EDGES_START = 10000;
    const int NUM_EDGES_END = 1000000;
    const int NUM_EDGES_STEP = 10000;
    const int NUM_TRIALS = 100;
    analyze_time_with_different_edges(NUM_VERTICES, NUM_EDGES_START, NUM_EDGES_END, NUM_EDGES_STEP, NUM_TRIALS,
                                      file_name, analyze_time_adj_list);
}

void analyze() {
    analyze_diff_edge_matrix();
    analyze_diff_vertex_matrix();
    analyze_diff_edge_list();
    analyze_diff_vertex_list();
    analyze_time_diff_edge_matrix();
    analyze_time_diff_edge_list();
}

void test() {
    Graph *graph = random_graph_adj_list(100, 1000);
    Graph *newGraph = adj_graph_to_matrix(graph);
    compare_count_t compare_count = 0;
    int *distances = dijkstra_adj_matrix(newGraph, &compare_count);
    compare_count = 0;
    int *distances2 = dijkstra_adj_list(graph, &compare_count);
    for (int i = 0; i < graph->numVertices; ++i) {
        if (distances[i] != distances2[i]) {
            printf("Error: %d %d %d\n", i, distances[i], distances2[i]);
            printf("Adjacency Matrix:\n");
            print_graph(newGraph);
            for (int j = 0; j < graph->numVertices; ++j) {
                printf("%d ", distances[j]);
            }
            printf("\n");
            printf("Adjacency List:\n");
            print_graph(graph);
            for (int j = 0; j < graph->numVertices; ++j) {
                printf("%d ", distances2[j]);
            }
            printf("\n");
            exit(EXIT_FAILURE);
        }
    }
    destroy_graph(graph);


    // Graph *graph = create_graph(ADJ_LIST, 5);

    // add_edge(graph, 0, 3, 18);
    // add_edge(graph, 0, 4, 27);
    // add_edge(graph, 0, 0, 36);
    // add_edge(graph, 0, 4, 77);
    // add_edge(graph, 1, 1, 84);
    // add_edge(graph, 2, 1, 40);
    // add_edge(graph, 3, 3, 38);
    // add_edge(graph, 3, 0, 90);
    // add_edge(graph, 3, 3, 12);
    // add_edge(graph, 4, 4, 60);

    // compare_count_t compare_count = 0;
    // int *distances = dijkstra_adj_list(graph, &compare_count);
    // for (int i = 0; i < graph->numVertices; ++i) {
    //     printf("%d ", distances[i]);
    // }
    // printf("\n");
    // printf("%llu\n", compare_count);

    // exit(EXIT_SUCCESS);
}

#endif //PROJECT2_ANALYZE_H
