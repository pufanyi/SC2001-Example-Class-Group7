#ifndef PROJECT2_HEAP_H
#define PROJECT2_HEAP_H

#include <stdlib.h>

typedef uint64_t compare_count_t;

typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

typedef struct Heap {
    int capacity;
    HeapNode *nodes;
    int *pos; // pos[i] is the index of vertex i in the heap
} Heap;

Heap *create_heap(int capacity) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->capacity = capacity;
    heap->nodes = (HeapNode *) malloc(capacity * sizeof(HeapNode));
    for (int i = 0; i < capacity; i++) {
        heap->nodes[i].vertex = i;
        heap->nodes[i].distance = INT_MAX;
    }
    heap->pos = (int *) malloc(capacity * sizeof(int));
    for (int i = 0; i < capacity; i++) {
        heap->pos[i] = i;
    }
    return heap;
}

void swap(Heap *heap, int index1, int index2) {
    HeapNode temp = heap->nodes[index1];
    heap->nodes[index1] = heap->nodes[index2];
    heap->nodes[index2] = temp;
    heap->pos[heap->nodes[index1].vertex] = index1;
    heap->pos[heap->nodes[index2].vertex] = index2;
}

int push_up(Heap *heap, int index, compare_count_t *compare_count) {
    if (index == 0) {
        return index;
    }
    int parent = (index - 1) / 2;
    if (heap->nodes[parent].distance > heap->nodes[index].distance) {
        swap(heap, parent, index);
        push_up(heap, parent, compare_count);
        index = parent;
    }
    return index;
}

int push_down(Heap *heap, int index, compare_count_t *compare_count) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    if (left < heap->capacity && (++(*compare_count)) &&
        heap->nodes[left].distance < heap->nodes[smallest].distance) {
        smallest = left;
    }
    if (right < heap->capacity && (++(*compare_count)) &&
        heap->nodes[right].distance < heap->nodes[smallest].distance) {
        smallest = right;
    }
    if (smallest != index) {
        swap(heap, smallest, index);
        push_down(heap, smallest, compare_count);
    }
    return smallest;
}

void update(Heap *heap, int vertex, int distance, compare_count_t *compare_count) {
    int index = heap->pos[vertex];
    heap->nodes[index].distance = distance;
    int next_index = push_up(heap, index, compare_count);
    while (next_index != index) {
        index = next_index;
        next_index = push_up(heap, index, compare_count);
    }
    next_index = push_down(heap, index, compare_count);
    while (next_index != index) {
        index = next_index;
        next_index = push_down(heap, index, compare_count);
    }
}

HeapNode top(Heap *heap) {
    return heap->nodes[0];
}

void destroy_heap(Heap *heap) {
    free(heap->nodes);
    free(heap->pos);
    free(heap);
}

#endif //PROJECT2_HEAP_H
