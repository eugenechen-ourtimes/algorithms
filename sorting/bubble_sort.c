#include "sorting.h"

#include <stdbool.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool hasSwapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                hasSwapped = true;
            }
        }

        if (!hasSwapped) {
            break;
        }
    }
}
