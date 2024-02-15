#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

int unweightedGraph__constructor(UnweightedGraph *graph, const char *graphFile) {
    if (graphFile == NULL) {
        return 1;
    }

    FILE *fp = fopen(graphFile, "r");
    if (fp == NULL) {
        return 2;
    }

    int numVertices, numEdges;
    fscanf(fp, "%d%d", &numVertices, &numEdges);

    graph->numVertices = numVertices;
    graph->listHeads = (const UnweightedGraphListNode **) malloc(numVertices * sizeof(UnweightedGraphListNode *));
    for (int i = 0; i < numVertices; i++) {
        graph->listHeads[i] = NULL;
    }

    for (int j = 0; j < numEdges; j++) {
        int src, dst;
        fscanf(fp, "%d%d", &src, &dst);
        src--;
        dst--;

        UnweightedGraphListNode *newNode = (UnweightedGraphListNode *) malloc(sizeof(UnweightedGraphListNode));
        newNode->destination = dst;
        newNode->next = graph->listHeads[src];
        graph->listHeads[src] = newNode;
    }

    fclose(fp);
    return 0;
}

void unweightedGraph__destructor(UnweightedGraph *graph) {
    int numVertices = graph->numVertices;
    for (int i = 0; i < numVertices; i++) {
        const UnweightedGraphListNode *node = graph->listHeads[i];
        while (node != NULL) {
            const UnweightedGraphListNode *next = node->next;
            free((void *) node);
            node = next;
        }
    }
}

int weightedGraph__constructor(WeightedGraph *graph, const char *graphFile) {
    if (graphFile == NULL) {
        return 1;
    }

    FILE *fp = fopen(graphFile, "r");
    if (fp == NULL) {
        return 2;
    }

    int numVertices, numEdges;
    fscanf(fp, "%d%d", &numVertices, &numEdges);

    graph->numVertices = numVertices;
    graph->listHeads = (const WeightedGraphListNode **) malloc(numVertices * sizeof(WeightedGraphListNode *));
    for (int i = 0; i < numVertices; i++) {
        graph->listHeads[i] = NULL;
    }

    for (int j = 0; j < numEdges; j++) {
        int src, dst, weight;
        fscanf(fp, "%d%d%d", &src, &dst, &weight);
        src--;
        dst--;

        WeightedGraphListNode *newNode = (WeightedGraphListNode *) malloc(sizeof(WeightedGraphListNode));
        newNode->destination = dst;
        newNode->weight = weight;
        newNode->next = graph->listHeads[src];
        graph->listHeads[src] = newNode;
    }

    fclose(fp);
    return 0;
}

void weightedGraph__destructor(WeightedGraph *graph) {
    int numVertices = graph->numVertices;
    for (int i = 0; i < numVertices; i++) {
        const WeightedGraphListNode *node = graph->listHeads[i];
        while (node != NULL) {
            const WeightedGraphListNode *next = node->next;
            free((void *) node);
            node = next;
        }
    }
}
