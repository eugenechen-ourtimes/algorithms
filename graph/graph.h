#ifndef GRAPH_H
#define GRAPH_H

typedef struct unweightedGraphListNode UnweightedGraphListNode;

struct unweightedGraphListNode {
    int destination;
    const struct unweightedGraphListNode *next;
};

typedef struct unweightedGraph UnweightedGraph;

struct unweightedGraph {
    int numVertices;
    const UnweightedGraphListNode **listHeads;
};

int unweightedGraph__constructor(UnweightedGraph *graph, const char *graphFile);
void unweightedGraph__destructor(UnweightedGraph *graph);

typedef struct weightedGraphListNode WeightedGraphListNode;

struct weightedGraphListNode {
    int destination;
    int weight;
    const struct weightedGraphListNode *next;
};

typedef struct weightedGraph WeightedGraph;

struct weightedGraph {
    int numVertices;
    const WeightedGraphListNode **listHeads;
};

int weightedGraph__constructor(WeightedGraph *graph, const char *graphFile);
void weightedGraph__destructor(WeightedGraph *graph);

#endif
