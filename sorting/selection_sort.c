#include "sorting.h"

#include <stdbool.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int selectedIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[selectedIndex]) {
                selectedIndex = j;
            }
        }

        swap(&a[i], &a[selectedIndex]);
    }
}
