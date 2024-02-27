#include "sorting.h"

#include <stdbool.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        bool hasSwapped = false;
        for (int j = 0; j < i; j++) {
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
