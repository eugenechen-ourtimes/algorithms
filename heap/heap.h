#ifndef HEAP_H
#define HEAP_H

typedef struct minHeap MinHeap;
typedef struct maxHeap MaxHeap;

struct minHeap {
    int *a;
    int size;
    int capacity;
};

struct maxHeap {
    int *a;
    int size;
    int capacity;
};

int minHeap__constructor_1(MinHeap *heap);
int minHeap__constructor_2(MinHeap *heap, const int *a, int n);
int minHeap__destructor(MinHeap *heap);

int minHeap_minimum(const MinHeap *heap, int *minimum);
int minHeap_extractMin(MinHeap *heap, int *minimum);
int minHeap_decreaseKey(MinHeap *heap, int i, int key);
int minHeap_insert(MinHeap *heap, int key);

int maxHeap__constructor_1(MaxHeap *heap);
int maxHeap__constructor_2(MaxHeap *heap, const int *a, int n);
int maxHeap__destructor(MaxHeap *heap);

int maxHeap_maximum(const MaxHeap *heap, int *maximum);
int maxHeap_extractMax(MaxHeap *heap, int *maximum);
int maxHeap_increaseKey(MaxHeap *heap, int i, int key);
int maxHeap_insert(MaxHeap *heap, int key);



int minHeap_increaseKey(MinHeap *heap, int i, int key);
int maxHeap_decreaseKey(MaxHeap *heap, int i, int key);

#endif
