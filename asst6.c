#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "some_heap.h"  // Make sure this is the correct header file

unsigned long long rand_between(unsigned long long min, unsigned long long max) {
    unsigned long long range = max - min;
    return min + (rand() % range);
}

void test_heap(void) {
    heap_t *heap = heap_create(200);  // Create a heap with capacity 200

    // Insert 20 random numbers into the heap
    for (heap_key_t ix = 0; ix < 20; ix++) {
        heap_key_t key = rand_between(0, 1000);  // Random key between 0 and 1000
        heap_insert(heap, key, (heap_value_t)key);  // Insert the key into the heap
        heap_print(heap);  // Print heap after insertion
    }

    // Remove 10 minimum elements from the heap
    for (int ix = 0; ix < 10; ix++) {
        heap_key_t key = (heap_key_t)heap_remove_min(heap);  // Remove the min element
        printf("Removed %llu\n", key);  // Print the removed element
        heap_print(heap);  // Print heap after removal
    }

    // Free the heap after testing
    heap_free(heap);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));  // Seed random number generator
    test_heap();  // Run heap test
    return 0;
}

