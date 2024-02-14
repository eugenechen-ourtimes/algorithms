#include "shortest_path.h"

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct queueListNode QueueListNode;

struct queueListNode {
    int vertex;
    int distance;
    struct queueListNode *next;
};

typedef struct queue Queue;

struct queue {
    QueueListNode *head;
    QueueListNode *tail;
};

void queue__constructor(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;
}

void queue__destructor(Queue *queue) { 
    QueueListNode *node = queue->head;
    while (node != NULL) {
        QueueListNode *next = node->next;
        free(node);
        node = next;
    }
}

bool queue_empty(const Queue *queue) {
    return queue->head == NULL;
}

void queue_enqueue(Queue *queue, int vertex, int distance) {
    QueueListNode *newNode = (QueueListNode *) malloc(sizeof(QueueListNode));
    newNode->vertex = vertex;
    newNode->distance = distance;
    newNode->next = NULL;

    QueueListNode *tail = queue->tail;
    if (tail == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        tail->next = newNode;
        queue->tail = newNode;
    }
}

void queue_dequeue(Queue *queue, int *vertex, int *distance) {
    QueueListNode *head = queue->head;

    *vertex = head->vertex;
    *distance = head->distance;

    queue->head = head->next;
    if (queue->tail == head) {
        queue->tail = NULL;
    }

    free(head);
}

int findShortestPathUnweightedGraph(
    const UnweightedGraph *graph,
    int sourceVertex,
    int *distances,
    int *predecessors
) {
    int numVertices = graph->numVertices;
    const UnweightedGraphListNode **listHeads = graph->listHeads;
    if (sourceVertex < 0 || sourceVertex >= numVertices) {
        return 1;
    }

    bool *hasVisited = (bool *) malloc(numVertices * sizeof(bool));
    for (int i = 0; i < numVertices; i++) {
        hasVisited[i] = false;
    }

    hasVisited[sourceVertex] = true;
    predecessors[sourceVertex] = -1;

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
    }

    distances[sourceVertex] = 0;

    Queue queue;
    queue__constructor(&queue);
    queue_enqueue(&queue, sourceVertex, 0);

    while (!queue_empty(&queue)) {
        int src, distance;
        queue_dequeue(&queue, &src, &distance);
        distances[src] = distance; 

        for (const UnweightedGraphListNode *node = listHeads[src]; node != NULL; node = node->next) {
            int dst = node->destination;
            if (!hasVisited[dst]) {
                hasVisited[dst] = true;
                predecessors[dst] = src;
                queue_enqueue(&queue, dst, distance + 1);
            }
        }
    }

    queue__destructor(&queue);
    free(hasVisited);

    return 0;
}
