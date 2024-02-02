#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

typedef struct heap Heap;

struct heap {
    int *vertices;
    int size;
    int *distances;
    int *indices;
};

void heap__constructor(Heap *heap, int numVertices, int *distances, int source) {
    heap->size = numVertices;
    heap->vertices = (int *) malloc((numVertices + 1) * sizeof(int));
    heap->indices = (int *) malloc(numVertices * sizeof(int));

    int j = 2;
    for (int i = 0; i < source; i++) {
        heap->vertices[j] = i;
        heap->indices[i] = j;
        j++;
    }

    for (int i = source + 1; i < numVertices; i++) {
        heap->vertices[j] = i;
        heap->indices[i] = j;
        j++;
    }

    heap->vertices[1] = source;
    heap->indices[source] = 1;

    heap->vertices[0] = -1;

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
    }

    distances[source] = 0;
    heap->distances = distances;
}

void heap__destructor(Heap *heap) {
    free(heap->vertices);
    free(heap->indices);
}

void heapify(int n, int *vertices, int *distances, int *indices, int i) {
    while (true) {
        int l = 2 * i;
        int r = l + 1;
        int smallest = i;

        if (l <= n && distances[vertices[l]] < distances[vertices[smallest]]) {
            smallest = l;
        }

        if (r <= n && distances[vertices[r]] < distances[vertices[smallest]]) {
            smallest = r;
        }

        if (smallest != i) {
            swap(&indices[vertices[i]], &indices[vertices[smallest]]);
            swap(&vertices[i], &vertices[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

int heap_selectVertex(Heap *heap) {
    int firstVertex = heap->vertices[1];
    int lastVertex = heap->vertices[heap->size];
    heap->vertices[1] = lastVertex;
    heap->vertices[heap->size] = -1;
    heap->indices[firstVertex] = -1;
    heap->indices[lastVertex] = 1;
    heap->size--;

    heapify(heap->size, heap->vertices, heap->distances, heap->indices, 1);
    return firstVertex;
}

void heap_decreaseDistance(Heap *heap, int vertex, int distance) {
    int *vertices = heap->vertices;
    int *distances = heap->distances;
    int *indices = heap->indices;

    distances[vertex] = distance;
    int i = indices[vertex];
    while (i > 1) {
        int parent = i / 2;
        if (distances[vertices[i]] < distances[vertices[parent]]) {
            swap(&indices[vertices[i]], &indices[vertices[parent]]);
            swap(&vertices[i], &vertices[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

bool heap_isEmpty(const Heap *heap) {
    return heap->size == 0;
}

void dijkstra(
    int numVertices,
    const ListNode **heads,
    int source,
    int *distances
) {
    Heap heap;
    heap__constructor(&heap, numVertices, distances, source);
    while (!heap_isEmpty(&heap)) {
        int selectedVertex = heap_selectVertex(&heap);
        int currDist = distances[selectedVertex];
        if (currDist == INT_MAX) {
            break;
        }

        for (const ListNode *node = heads[selectedVertex]; node != NULL; node = node->next) {
            int destination = node->data.destination;
            int weight = node->data.weight;

            int newDist = currDist + weight;
            if (newDist < distances[destination]) {
                heap_decreaseDistance(&heap, destination, newDist);
            }
        }
    }

    heap__destructor(&heap);
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
