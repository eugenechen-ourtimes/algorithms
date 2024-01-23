#include "heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    MinHeap heap;   
} KthLargest;

int kthLargestAdd(KthLargest *kthLargest, int val) {
    MinHeap *heap = &kthLargest->heap;
    minHeap_increaseKey(heap, 1, val);

    int result;
    minHeap_minimum(heap, &result);
    return result;
}

KthLargest *kthLargestCreate(int k, int *nums, int numsSize) {
    KthLargest *kthLargest = (KthLargest *) malloc(sizeof(KthLargest));
    MinHeap *heap = &kthLargest->heap;
    if (k >= numsSize) {
        int *newNums = (int *) malloc(k * sizeof(int));
        for (int i = 0; i < numsSize; i++) {
            newNums[i] = nums[i];
        }

        for (int i = numsSize; i < k; i++) {
            newNums[i] = INT_MIN;
        }

        minHeap__constructor_2(heap, newNums, k);
        free(newNums);
    } else {
        minHeap__constructor_2(heap, nums, k);
        for (int i = k; i < numsSize; i++) {
            kthLargestAdd(kthLargest, nums[i]);
        }
    }

    return kthLargest;
}

void kthLargestFree(KthLargest *kthLargest) {
    minHeap__destructor(&kthLargest->heap);
    free(kthLargest);
}

int main(void) {
    int nums[] = {4, 5, 8, 2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 3;

    KthLargest *kthLargest = kthLargestCreate(k, nums, numsSize);
    int y_1 = kthLargestAdd(kthLargest, 3);
    int y_2 = kthLargestAdd(kthLargest, 5);
    int y_3 = kthLargestAdd(kthLargest, 10);
    int y_4 = kthLargestAdd(kthLargest, 9);
    int y_5 = kthLargestAdd(kthLargest, 4);
    kthLargestFree(kthLargest);

    printf("%d %d %d %d %d\n", y_1, y_2, y_3, y_4, y_5);
    return 0;
}
