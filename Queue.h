#ifndef QUEUE_H
#define QUEUE_H

typedef struct queuenode QueueNode;
typedef struct queue Queue;

struct queuenode
{
    void *data;
    QueueNode *next;
};

struct queue
{
    size_t length;
    QueueNode *head;
    QueueNode *tail;
};

void Queue_init(Queue *q);
void Queue_enqueue(Queue *q, void *data);
void Queue_dequeue(Queue *q, _Bool isAlloc);
QueueNode *Queue_peek(Queue *q);
void Queue_free(Queue *q, _Bool isAlloc);

#endif // QUEUE_H
