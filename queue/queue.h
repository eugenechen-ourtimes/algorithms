#ifndef QUEUE_H
#define QUEUE_H

typedef struct queueListNode QueueListNode;

struct queueListNode {
    int data;
    struct queueListNode *next;
};

typedef struct queue Queue;

struct queue {
    QueueListNode *head;
    QueueListNode *tail;
};

#include <stdbool.h>

int queue__constructor(Queue *queue);
int queue__destructor(Queue *queue);

int queue_empty(const Queue *queue, bool *empty);
int queue_enqueue(Queue *queue, int data);
int queue_dequeue(Queue *queue, int *data);

#endif
