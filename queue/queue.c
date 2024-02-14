#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int queue__constructor(Queue *queue) {
    queue->head = NULL;
    queue->tail = NULL;

    return 0;
}

int queue__destructor(Queue *queue) { 
    QueueListNode *node = queue->head;
    while (node != NULL) {
        QueueListNode *next = node->next;
        free(node);
        node = next;
    }

    return 0;
}

int queue_empty(const Queue *queue, bool *empty) {
    *empty = queue->head == NULL;
    return 0;
}

int queue_enqueue(Queue *queue, int data) {
    QueueListNode *newNode = (QueueListNode *) malloc(sizeof(QueueListNode));
    newNode->data = data;
    newNode->next = NULL;

    QueueListNode *tail = queue->tail;
    if (tail == NULL) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        tail->next = newNode;
        queue->tail = newNode;
    }

    return 0;
}

int queue_dequeue(Queue *queue, int *data) {
    QueueListNode *head = queue->head;
    if (head == NULL) {
        return 1;
    }

    *data = head->data;
    queue->head = head->next;
    free(head);

    return 0;
}
