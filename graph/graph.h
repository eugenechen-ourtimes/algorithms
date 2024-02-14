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

typedef struct unweightedEdge UnweightedEdge;

struct unweightedEdge {
    int src;
    int dst;
};

int unweightedGraph__constructor(UnweightedGraph *graph, const char *graphFile);
void unweightedGraph__destructor(UnweightedGraph *graph);

#endif
