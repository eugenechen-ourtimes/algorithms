#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "../graph/graph.h"

int findShortestPathUnweightedGraph(
    const UnweightedGraph *graph,
    int sourceVertex,
    int *distances,
    int *predecessors
);

int findShortestPathWeightedGraph(
    const WeightedGraph *graph,
    int sourceVertex,
    int *distances,
    int *predecessors
);

#endif
