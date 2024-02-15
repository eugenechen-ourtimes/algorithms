#include "shortest_path.h"

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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
        distances[i] = INT_MAX;
        predecessors[i] = -1;
    }

    distances[sourceVertex] = 0;

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
        for (const WeightedGraphListNode *node = listHeads[selectedVertex]; node != NULL; node = node->next) {
            int destination = node->destination;
            int newDistance = distances[selectedVertex] + node->weight;
            if (newDistance < distances[destination]) {
                distances[destination] = newDistance;
                predecessors[destination] = selectedVertex;
            }
        }
    }

    free(hasSelected);
    return 0;
}
