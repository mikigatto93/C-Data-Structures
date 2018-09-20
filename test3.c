#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Queue.h"

int main(void)
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Queue q;

    Queue_init(&q);

    int i;
    for (i = 0; i < 6; i++) {
        Queue_enqueue(&q, &data[i]);
    }

    /*for (i = 0; i < 6; i++) {
        QueueNode *n = Queue_peek(&q);
        printf("Queue: %d\n", *(int*)n->data);
        Queue_dequeue(&q, false);

    }*/

    Queue_free(&q, false);
    printf("Len: %d\n", q.length);

    return 0;
}
