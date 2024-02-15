#include "shortest_path.h"

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

typedef struct heap Heap;

struct heap {
    int *vertices;
    int size;
    int *distances;
    int *indices;
};

void heap__constructor(Heap *heap, int numVertices, int *distances, int sourceVertex) {
    heap->size = numVertices;
    heap->vertices = (int *) malloc((numVertices + 1) * sizeof(int));
    heap->indices = (int *) malloc(numVertices * sizeof(int));

    int j = 2;
    for (int i = 0; i < sourceVertex; i++) {
        heap->vertices[j] = i;
        heap->indices[i] = j;
        j++;
    }

    for (int i = sourceVertex + 1; i < numVertices; i++) {
        heap->vertices[j] = i;
        heap->indices[i] = j;
        j++;
    }

    heap->vertices[1] = sourceVertex;
    heap->indices[sourceVertex] = 1;

    heap->vertices[0] = -1;

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
    }

    distances[sourceVertex] = 0;
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
    heap->indices[lastVertex] = 1;
    heap->indices[firstVertex] = -1;
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

int findShortestPathWeightedGraph(
    const WeightedGraph *graph,
    int sourceVertex,
    int *distances,
    int *predecessors
) {
    int numVertices = graph->numVertices;
    const WeightedGraphListNode **listHeads = graph->listHeads;

    if (sourceVertex < 0 || sourceVertex >= numVertices) {
        return 1;
    }

    for (int i = 0; i < numVertices; i++) {
        predecessors[i] = -1;
    }

    Heap heap;
    heap__constructor(&heap, numVertices, distances, sourceVertex);
    while (!heap_isEmpty(&heap)) {
        int selectedVertex = heap_selectVertex(&heap);
        int currDist = distances[selectedVertex];
        if (currDist == INT_MAX) {
            break;
        }

        for (const WeightedGraphListNode *node = listHeads[selectedVertex]; node != NULL; node = node->next) {
            int destination = node->destination;
            int weight = node->weight;

            int newDist = currDist + weight;
            if (newDist < distances[destination]) {
                heap_decreaseDistance(&heap, destination, newDist);
                predecessors[destination] = selectedVertex;
            }
        }
    }

    heap__destructor(&heap);
    return 0;
}
