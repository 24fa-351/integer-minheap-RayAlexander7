#include <stdio.h>
#include <stdlib.h>
#include "some_heap.h"

heap_t *heap_create(int capacity) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (heap_node_t *)malloc(capacity * sizeof(heap_node_t));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_free(heap_t *heap) {
    free(heap->data);
    free(heap);
}

unsigned int heap_size(heap_t *heap) {
    return heap->size;
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap->size == heap->capacity) {
        return; // Heap is full
    }

    heap->data[heap->size].key = key;
    heap->data[heap->size].value = data;
    heap->size++;

    heap_bubble_up(heap, heap->size - 1); // Maintain heap property
}

heap_value_t heap_remove_min(heap_t *heap) {
    if (heap->size == 0) {
        return NULL; // Heap is empty
    }

    heap_value_t min = heap->data[0].value; // Root element
    heap->data[0] = heap->data[heap->size - 1]; // Replace root with last element
    heap->size--;

    heap_bubble_down(heap, 0); // Maintain heap property

    return min;
}

void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0) {
        int parent_index = heap_parent(index);

        if (heap->data[parent_index].key <= heap->data[index].key) {
            break; // Heap property is satisfied
        }

        heap_swap(heap, parent_index, index); // Swap with parent
        index = parent_index;
    }
}

void heap_bubble_down(heap_t *heap, int index) {
    int left_child, right_child, min_child;

    while ((left_child = heap_left_child(index)) < heap->size) {
        right_child = heap_right_child(index);
        min_child = left_child;

        if (right_child < heap->size && heap->data[right_child].key < heap->data[left_child].key) {
            min_child = right_child;
        }

        if (heap->data[index].key <= heap->data[min_child].key) {
            break; // Heap property is satisfied
        }

        heap_swap(heap, index, min_child); // Swap with the smaller child
        index = min_child;
    }
}

void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

unsigned int heap_parent(unsigned int index) {
    return (index - 1) / 2;
}

unsigned int heap_left_child(unsigned int index) {
    return 2 * index + 1;
}

unsigned int heap_right_child(unsigned int index) {
    return 2 * index + 2;
}

void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap->size; ix++) {
        printf("%d : %llu\n", ix, heap->data[ix].key);
    }
    printf("\n");
}

