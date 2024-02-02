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
    int *distances,
    int *predecessors
) {
    for (int i = 0; i < numVertices; i++) {
        predecessors[i] = -1;
    }

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
                predecessors[destination] = selectedVertex;
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

void runDijkstra() {
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
        Data data = { .destination = destination, .weight = weight };
        heads[source] = ll_insertHead(heads[source], data);
    }

    dijkstra(numVertices, heads, source, distances, predecessors);
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
    runDijkstra();
    return 0;
}
