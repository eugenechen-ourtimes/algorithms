#include "sorting.h"

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(int *a, int low, int high) {
    int pivot = a[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            swap(&a[i], &a[j]);
            i++;
        }
    }

    swap(&a[i], &a[high]);
    return i;
}

static void quickSort(int *a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

void sort(int *a, int n) {
    quickSort(a, 0, n - 1);
}
