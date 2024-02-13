#include "queue.h"

#include <stdio.h>
#include <stdbool.h>

void testQueue(void) {
    Queue queue;
    queue__constructor(&queue);

    queue_enqueue(&queue, 1);
    queue_enqueue(&queue, 2);
    queue_enqueue(&queue, 3);
    queue_enqueue(&queue, 4);
    queue_enqueue(&queue, 5);

    while (true) {
        bool empty;
        queue_empty(&queue, &empty);
        if (empty) {
            break;
        }

        int data;
        queue_dequeue(&queue, &data);
        printf("%d\n", data);
    }

    queue__destructor(&queue);
}

int main(void) {
    testQueue();
}
