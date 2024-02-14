#include "shortest_path.h"

#include <stdio.h>
#include <stdlib.h>
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

void runShortestPathAlgo(const char *graphFile, int sourceVertex) {
    UnweightedGraph graph;
    int unweightedGraph__constructor_status = unweightedGraph__constructor(&graph, graphFile);
    if (unweightedGraph__constructor_status != 0) {
        printf("error reading graph\n");
        return;
    }

    int numVertices = graph.numVertices;
    int *distances = (int *) malloc(numVertices * sizeof(int));
    int *predecessors = (int *) malloc(numVertices * sizeof(int));

    sourceVertex--;
    int findShortestPathStatus = findShortestPathUnweightedGraph(&graph, sourceVertex, distances, predecessors);
    if (findShortestPathStatus != 0) {
        printf("error finding shortest path\n");
        unweightedGraph__destructor(&graph);
        free(distances);
        free(predecessors);
        return;
    }

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

    unweightedGraph__destructor(&graph);
    free(distances);
    free(predecessors);
    free(path);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("usage: %s [graph file] [source vertex]\n", argv[0]);
        return 0;
    }

    const char *graphFile = argv[1];
    int sourceVertex = argc >= 3 ? atoi(argv[2]) : 1;
    runShortestPathAlgo(graphFile, sourceVertex);

    return 0;
}
