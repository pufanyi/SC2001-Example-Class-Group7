#ifndef PROJECT2_HEAP_H
#define PROJECT2_HEAP_H

#include <stdlib.h>

typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

typedef struct Heap {
    int size;
    int capacity;
    HeapNode *nodes;
    int *pos; // pos[i] is the index of vertex i in the heap
} Heap;

Heap *create_heap(int capacity) {
    Heap *heap = (Heap *) malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (HeapNode *) malloc(capacity * sizeof(HeapNode));
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

int push_up(Heap *heap, int index) {
    if (index == 0) {
        return index;
    }
    int parent = (index - 1) / 2;
    if (heap->nodes[parent].distance > heap->nodes[index].distance) {
        swap(heap, parent, index);
        push_up(heap, parent);
        index = parent;
    }
    return index;
}

int push_down(Heap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    if (left < heap->size && heap->nodes[left].distance < heap->nodes[smallest].distance) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right].distance < heap->nodes[smallest].distance) {
        smallest = right;
    }
    if (smallest != index) {
        swap(heap, smallest, index);
        push_down(heap, smallest);
    }
    return smallest;
}

void update(Heap *heap, int vertex, int distance) {
    int index = heap->pos[vertex];
    heap->nodes[index].distance = distance;
    int next_index = push_up(heap, index);
    while (next_index != index) {
        index = next_index;
        next_index = push_up(heap, index);
    }
    next_index = push_down(heap, index);
    while (next_index != index) {
        index = next_index;
        next_index = push_down(heap, index);
    }
}

#endif //PROJECT2_HEAP_H
