#include "sorting.h"

#include <stdio.h>

void testSorting(void) {
    int a[] = {3, 5, 4, 1, 2};
    int n = sizeof(a) / sizeof(a[0]);

    sort(a, n);
    for (int i = 0; i < n; i++) {
        printf("%d%c", a[i], i == n - 1 ? '\n' : ' ');
    }
}

int main(void) {
    testSorting();
    return 0;
}
