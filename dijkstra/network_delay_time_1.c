#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(int *a, int n) {
    for (int i = 0; i < n / 2; i++) {
        swap(&a[i], &a[n - 1 - i]);
    }
}

typedef struct data Data;

struct data {
    int destination;
    int weight;
};

typedef struct listNode ListNode;

struct listNode {
    Data data;
    const struct listNode *next;
};

void dijkstra(
    int numVertices,
    const ListNode **heads,
    int source,
    int *distances
) {
    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
    }

    distances[source] = 0;

    bool *hasSelected = (bool *) malloc(numVertices * sizeof(bool));
    for (int i = 0; i < numVertices; i++) {
        hasSelected[i] = false;
    }

    for (int i = 0; i < numVertices; i++) {
        int selectedVertex = -1;
        int minDistance = INT_MAX;
        for (int j = 0; j < numVertices; j++) {
            if (!hasSelected[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                selectedVertex = j;
            }
        }

        if (selectedVertex < 0) {
            break;
        }

        hasSelected[selectedVertex] = true;
        for (const ListNode *node = heads[selectedVertex]; node != NULL; node = node->next) {
            int destination = node->data.destination;
            int newDistance = distances[selectedVertex] + node->data.weight;
            if (newDistance < distances[destination]) {
                distances[destination] = newDistance;
            }
        }
    }

    free(hasSelected);
}

const ListNode *ll_insertHead(const ListNode *head, Data data) {
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->data = data;
    newNode->next = head;

    return newNode;
}

void ll_releaseMemory(const ListNode *head) {
    const ListNode *curr = head;
    const ListNode *next;
    while (curr != NULL) {
        next = curr->next;
        free((void *) curr);
        curr = next;
    }
}

int networkDelayTime(int **times, int timesSize, int *timesColSize, int n, int k) {
    int source = k - 1;
    int numVertices = n;

    int *distances = (int *) malloc(numVertices * sizeof(int));

    const ListNode **heads = (const ListNode **) malloc(numVertices * sizeof(ListNode *));
    for (int i = 0; i < numVertices; i++) {
        heads[i] = NULL;
    }

    for (int j = 0; j < timesSize; j++) {
        int *timesCol = times[j];
        int source = timesCol[0] - 1;
        int destination = timesCol[1] - 1;
        int weight = timesCol[2];
        Data data = { .destination = destination, .weight = weight };
        heads[source] = ll_insertHead(heads[source], data);
    }

    dijkstra(numVertices, heads, source, distances);

    int maxDist = -1;
    for (int i = 0; i < numVertices; i++) {
        int currDist = distances[i];
        if (currDist > maxDist) {
            maxDist = currDist;
        }
    }

    free(distances);

    for (int i = 0; i < numVertices; i++) {
        ll_releaseMemory(heads[i]);
    }

    free(heads);

    return maxDist == INT_MAX ? -1 : maxDist;
}

void networkDelayTimeTest() {
    int n = 2;
    int k = 2;

    int timesSize = 1;
    int **times = (int **) malloc(timesSize * sizeof(int *));
    for (int i = 0; i < timesSize; i++) {
        times[i] = (int *) malloc(3 * sizeof(int));
    }

    times[0][0] = 1;
    times[0][1] = 2;
    times[0][2] = 1;

    int result = networkDelayTime(times, timesSize, NULL, n, k);
    printf("%d\n", result);

    for (int i = 0; i < timesSize; i++) {
        free(times[i]);
    }

    free(times);
}

int main(void) {
    networkDelayTimeTest();
    return 0;
}
