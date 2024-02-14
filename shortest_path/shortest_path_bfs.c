#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

typedef struct graphListNode GraphListNode;

struct graphListNode {
    int destination;
    const struct graphListNode *next;
};

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

bool queue_empty(Queue *queue) {
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

void findShortestPath(
    int numVertices,
    const GraphListNode **heads,
    int source,
    int *distances,
    int *predecessors
) {
    bool *hasVisited = (bool *) malloc(numVertices * sizeof(bool));
    for (int i = 0; i < numVertices; i++) {
        hasVisited[i] = false;
    }

    hasVisited[source] = true;
    predecessors[source] = -1;

    for (int i = 0; i < numVertices; i++) {
        distances[i] = INT_MAX;
    }

    distances[source] = 0;

    Queue queue;
    queue__constructor(&queue);
    queue_enqueue(&queue, source, 0);

    while (!queue_empty(&queue)) {
        int src;
        int distance;
        queue_dequeue(&queue, &src, &distance);
        distances[src] = distance; 

        for (const GraphListNode *node = heads[src]; node != NULL; node = node->next) {
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
}

const GraphListNode *ll_insertHead(const GraphListNode *head, int destination) {
    GraphListNode *newNode = (GraphListNode *) malloc(sizeof(GraphListNode));
    newNode->destination = destination;
    newNode->next = head;

    return newNode;
}

void ll_releaseMemory(const GraphListNode *head) {
    const GraphListNode *node = head;
    while (node != NULL) {
        const GraphListNode *next = node->next;
        free((void *) node);
        node = next;
    }
}

void runShortestPathAlgo(void) {
    int source = 0;
    int numVertices, numEdges;
    scanf("%d%d", &numVertices, &numEdges);

    int *distances = (int *) malloc(numVertices * sizeof(int));
    int *predecessors = (int *) malloc(numVertices * sizeof(int));

    const GraphListNode **heads = (const GraphListNode **) malloc(numVertices * sizeof(GraphListNode *));
    for (int i = 0; i < numVertices; i++) {
        heads[i] = NULL;
    }

    for (int j = 0; j < numEdges; j++) {
        int source, destination;
        scanf("%d%d", &source, &destination);
        source--;
        destination--;
        heads[source] = ll_insertHead(heads[source], destination);
    }

    findShortestPath(numVertices, heads, source, distances, predecessors);

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
    runShortestPathAlgo();
    return 0;
}
