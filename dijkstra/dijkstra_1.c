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

typedef struct listNode ListNode;

struct listNode {
    int destination;
    int weight;
    const struct listNode *next;
};

void findShortestPath(
    int numVertices,
    const ListNode **heads,
    int source,
    int *distances,
    int *predecessors
) {
    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
        predecessors[i] = -1;
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
            int destination = node->destination;
            int newDistance = distances[selectedVertex] + node->weight;
            if (newDistance < distances[destination]) {
                distances[destination] = newDistance;
                predecessors[destination] = selectedVertex;
            }
        }
    }

    free(hasSelected);
}

const ListNode *ll_insertHead(const ListNode *head, int destination, int weight) {
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->destination = destination;
    newNode->weight = weight;
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

void runShortestPathAlgo(void) {
    int source = 0;
    int numVertices, numEdges;
    scanf("%d%d", &numVertices, &numEdges);

    int *distances = (int *) malloc(numVertices * sizeof(int));
    int *predecessors = (int *) malloc(numVertices * sizeof(int));

    const ListNode **heads = (const ListNode **) malloc(numVertices * sizeof(ListNode *));
    for (int i = 0; i < numVertices; i++) {
        heads[i] = NULL;
    }

    for (int j = 0; j < numEdges; j++) {
        int source, destination, weight;
        scanf("%d%d%d", &source, &destination, &weight);
        source--;
        destination--;
        heads[source] = ll_insertHead(heads[source], destination, weight);
    }

    findShortestPath(numVertices, heads, source, distances, predecessors);
    int *path = (int *) malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        printf("[%d]\n", i + 1);
        if (distances[i] == INT_MAX) {
            printf("vertex is unreachable\n");
        } else {
            printf("distance: %d\n", distances[i]);
            printf("path: ");

            int pathLength = 0;
            for (int v = i; v >= 0; v = predecessors[v]) {
                path[pathLength] = v;
                pathLength++;
            }

            reverse(path, pathLength);
            for (int j = 0; j < pathLength; j++) {
                printf("%d%c", path[j] + 1, j == pathLength - 1 ? '\n' : ' ');
            }
        }
    }

    free(path);

    free(distances);
    free(predecessors);

    for (int i = 0; i < numVertices; i++) {
        ll_releaseMemory(heads[i]);
    }

    free(heads);
}

int main(void) {
    runShortestPathAlgo();
    return 0;
}
