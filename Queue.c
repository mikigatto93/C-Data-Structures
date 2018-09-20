#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Queue.h"
#define ALLOC_FAIL_TEST(pointer, messageString) \
            if (pointer == NULL) \
            {  \
                printf(messageString); \
                return;\
            }

void Queue_init(Queue *q)
{
    q->length = 0;
    q->head = NULL;
    q->tail = NULL;
}

void Queue_enqueue(Queue *q, void *data)
{
    QueueNode *node = malloc(sizeof(QueueNode));
    ALLOC_FAIL_TEST(node, "Out of memory!\n");

    node->data = data;

    if (q->tail == NULL && q->head == NULL) {
        node->next = NULL;
        q->head = node;
        q->tail = node;
        q->length++;
    } else {
        q->tail->next = node;
        node->next = NULL;
        q->tail = node;
        q->length++;
    }
}

void Queue_dequeue(Queue *q, bool isAlloc)
{
    if (q->length == 1) {
        if (isAlloc) {
            free(q->head->data);
            free(q->head);
            q->head = NULL;
            q->tail = NULL;
        } else {
            free(q->head);
            q->head = NULL;
            q->tail = NULL;
        }
        q->length--;
    } else if (q->length > 1) {
        QueueNode *nodeToDelete = q->head;
        q->head = q->head->next;
        if (isAlloc) {
            free(nodeToDelete->data);
            free(nodeToDelete);
        } else {
            free(nodeToDelete);
        }
        q->length--;
    }
}


QueueNode *Queue_peek(Queue *q)
{
    if (q->length <= 0) {
        return NULL;
    } else {
        return q->head;
    }
}


void Queue_free(Queue *q, bool isAlloc)
{
    int i, len;
    for (i = 0, len = q->length; i < len; i++) {
        Queue_dequeue(q, isAlloc);
    }
}

