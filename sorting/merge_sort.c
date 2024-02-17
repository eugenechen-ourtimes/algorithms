#include "sorting.h"

#include <stdlib.h>

void _merge(int *a, int p, int q, int r, int *bl, int *br) {
    int nl = q - p + 1;
    int nr = r - q;
    int i, j, k;

    for (i = 0; i < nl; i++) {
        bl[i] = a[p + i];
    }

    for (j = 0; j < nr; j++) {
        br[j] = a[q + 1 + j];
    }

    i = 0;
    j = 0;
    k = p;
    while (i < nl || j < nr) {
        if (i == nl) {
            a[k] = br[j];
            j++;
            k++;
            continue;
        }

        if (j == nr) {
            a[k] = bl[i];
            i++;
            k++;
            continue;
        }

        if (bl[i] < br[j]) {
            a[k] = bl[i];
            i++;
            k++;
        } else {
            a[k] = br[j];
            j++;
            k++;
        }
    }
}

void _mergeSort(int *a, int p, int r, int *bl, int *br) {
    if (p >= r) {
        return;
    }

    int q = (p + r) / 2;
    _mergeSort(a, p, q, bl, br);
    _mergeSort(a, q + 1, r, bl, br);
    _merge(a, p, q, r, bl, br);
}

void sort(int *a, int n) {
    int *bl = (int *) malloc((n + 1) / 2 * sizeof(int));
    int *br = (int *) malloc(n / 2 * sizeof(int));

    _mergeSort(a, 0, n - 1, bl, br);

    free(bl);
    free(br);
}
