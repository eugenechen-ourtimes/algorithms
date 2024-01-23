#include "heap.h"

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void minHeapify(int *a, int n, int i) {
    while (true) {
        int j = 2 * i;
        int l = j + 1;
        int r = j + 2;
        int smallest = i;

        if (l < n && a[l] < a[smallest]) {
            smallest = l;
        }

        if (r < n && a[r] < a[smallest]) {
            smallest = r;
        }

        if (smallest != i) {
            swap(&a[i], &a[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

static void maxHeapify(int *a, int n, int i) {
    while (true) {
        int j = 2 * i;
        int l = j + 1;
        int r = j + 2;
        int largest = i;

        if (l < n && a[l] > a[largest]) {
            largest = l;
        }

        if (r < n && a[r] > a[largest]) {
            largest = r;
        }

        if (largest != i) {
            swap(&a[i], &a[largest]);
            i = largest;    
        } else {
            break;
        }
    }
}

int minHeap__constructor_1(MinHeap *heap) {
    heap->size = 0;
    heap->capacity = 1;
    heap->a = (int *) malloc(heap->capacity * sizeof(int));

    return 0;
}

int minHeap__constructor_2(MinHeap *heap, const int *a, int n) {
    heap->size = n;
    heap->capacity = n + 1;
    heap->a = (int *) malloc(heap->capacity * sizeof(int));
    for (int i = 0; i < n; i++) {
        heap->a[i] = a[i];
    }

    for (int j = n / 2 - 1; j >= 0; j--) {
        minHeapify(heap->a, n, j);
    }

    return 0;
}

int minHeap__destructor(MinHeap *heap) {
    free(heap->a);
    return 0;
}

int minHeap_minimum(const MinHeap *heap, int *minimum) {
    if (heap->size == 0) {
        return 1;
    }

    *minimum = heap->a[0];
    return 0;
}

int minHeap_extractMin(MinHeap *heap, int *minimum) {
    if (heap->size == 0) {
        return 1;
    }

    *minimum = heap->a[0];
    heap->size--;
    heap->a[0] = heap->a[heap->size];

    int threshold = heap->capacity * 3 / 10;
    if (heap->size <= threshold) {
        heap->a = (int *) realloc(heap->a, threshold * sizeof(int));
        heap->capacity = threshold;
    }

    minHeapify(heap->a, heap->size, 0);
    return 0;
}

int minHeap_decreaseKey(MinHeap *heap, int i, int key) {
    if (i >= heap->size) {
        return 1;
    }

    int *a = heap->a;
    if (key > a[i]) {
        return 2;
    }

    a[i] = key;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (a[i] < a[parent]) {
            swap(&a[i], &a[parent]);
            i = parent;
        } else {
            break;
        }
    }

    return 0;
}

int minHeap_insert(MinHeap *heap, int key) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->a = (int *) realloc(heap->a, heap->capacity * sizeof(int));
    }

    heap->a[heap->size] = INT_MAX;
    heap->size++;
    minHeap_decreaseKey(heap, heap->size - 1, key);
    return 0;
}

int maxHeap__constructor_1(MaxHeap *heap) {
    heap->size = 0;
    heap->capacity = 1;
    heap->a = (int *) malloc(heap->capacity * sizeof(int));

    return 0;
}

int maxHeap__constructor_2(MaxHeap *heap, const int *a, int n) {
    heap->size = n;
    heap->capacity = n + 1;
    heap->a = (int *) malloc(heap->capacity * sizeof(int));
    for (int i = 0; i < n; i++) {
        heap->a[i] = a[i];
    }

    for (int j = n / 2 - 1; j >= 0; j--) {
        maxHeapify(heap->a, n, j);
    }

    return 0;
}

int maxHeap__destructor(MaxHeap *heap) {
    free(heap->a);
    return 0;
}

int maxHeap_maximum(const MaxHeap *heap, int *maximum) {
    if (heap->size == 0) {
        return 1;
    }

    *maximum = heap->a[0];
    return 0;
}

int maxHeap_extractMax(MaxHeap *heap, int *maximum) {
    if (heap->size == 0) {
        return 1;
    }

    *maximum = heap->a[0];
    heap->size--;
    heap->a[0] = heap->a[heap->size];

    int threshold = heap->capacity * 3 / 10;
    if (heap->size <= threshold) {
        heap->a = (int *) realloc(heap->a, threshold * sizeof(int));
        heap->capacity = threshold;
    }

    maxHeapify(heap->a, heap->size, 0);
    return 0;
}

int maxHeap_increaseKey(MaxHeap *heap, int i, int key) {
    if (i >= heap->size) {
        return 1;
    }

    int *a = heap->a;
    if (key < a[i]) {
        return 2;
    }

    a[i] = key;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (a[i] > a[parent]) {
            swap(&a[i], &a[parent]);
            i = parent;
        } else {
            break;
        }
    }

    return 0;
}

int maxHeap_insert(MaxHeap *heap, int key) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->a = (int *) realloc(heap->a, heap->capacity * sizeof(int));
    }

    heap->a[heap->size] = INT_MIN;
    heap->size++;
    maxHeap_increaseKey(heap, heap->size - 1, key);
    return 0;
}



int minHeap_increaseKey(MinHeap *heap, int i, int key) {
    if (i >= heap->size) {
        return 1;
    }

    int *a = heap->a;
    if (key < a[i]) {
        return 2;
    }

    a[i] = key;
    minHeapify(a, heap->size, i);
    return 0;
}

int maxHeap_decreaseKey(MaxHeap *heap, int i, int key) {
    if (i >= heap->size) {
        return 1;
    }

    int *a = heap->a;
    if (key > a[i]) {
        return 2;
    }

    a[i] = key;
    maxHeapify(a, heap->size, i);
    return 0;
}
