#include "sorting.h"

#include <stdbool.h>

static int swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify(int *a, int n, int i) {
    while (true) {
        int l = 2 * i + 1;
        int r = l + 1;
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

void sort(int *a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (int j = n - 1; j > 0; j--) {
        swap(&a[0], &a[j]);
        heapify(a, j, 0);
    }
}
