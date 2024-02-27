#include "sorting.h"

#include <stdlib.h>

static void merge(int *a, int p, int q, int r, int *b_l, int *b_r) {
    int n_l = q - p + 1;
    int n_r = r - q;
    int i, j, k;

    for (i = 0; i < n_l; i++) {
        b_l[i] = a[p + i];
    }

    for (j = 0; j < n_r; j++) {
        b_r[j] = a[q + 1 + j];
    }

    i = 0;
    j = 0;
    k = p;
    while (i < n_l && j < n_r) {
        if (b_l[i] < b_r[j]) {
            a[k] = b_l[i];
            i++;
            k++;
        } else {
            a[k] = b_r[j];
            j++;
            k++;
        }        
    }

    while (i < n_l) {
        a[k] = b_l[i];
        i++;
        k++;
    }

    while (j < n_r) {
        a[k] = b_r[j];
        j++;
        k++;
    }
}

static void mergeSort(int *a, int p, int r, int *b_l, int *b_r) {
    if (p >= r) {
        return;
    }

    int q = (p + r) / 2;
    mergeSort(a, p, q, b_l, b_r);
    mergeSort(a, q + 1, r, b_l, b_r);
    merge(a, p, q, r, b_l, b_r);
}

void sort(int *a, int n) {
    int *b_l = (int *) malloc((n + 1) / 2 * sizeof(int));
    int *b_r = (int *) malloc(n / 2 * sizeof(int));

    mergeSort(a, 0, n - 1, b_l, b_r);

    free(b_l);
    free(b_r);
}
