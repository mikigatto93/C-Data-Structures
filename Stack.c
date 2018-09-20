#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"
#define ALLOC_FAIL_TEST(pointer, messageString) \
            if (pointer == NULL) \
            {  \
                printf(messageString); \
                return;\
            }

void Stack_init(Stack *s)
{
    s->head = NULL;
    s->length = 0;
}

void Stack_push(Stack *s, void *data)
{
    StackNode *node = malloc(sizeof(StackNode));
    ALLOC_FAIL_TEST(node, "Out of memory!/n");

    node->data = data;

    if (s->head == NULL) {
        node->next = NULL;
        s->head = node;
        s->length++;
    } else {
        node->next = s->head;
        s->head = node;
        s->length++;
    }
}


void Stack_pop(Stack *s, bool isAlloc)
{
    if (s->length == 1) {
        if (isAlloc) {
            free(s->head->data);
            free(s->head);
            s->head == NULL;
        } else {
            free(s->head);
            s->head = NULL;
        }
        s->length--;
    } else if (s->length > 1) {
        StackNode *nodeToDelete = s->head;
        s->head = s->head->next;

        if (isAlloc) {
            free(nodeToDelete->data);
            free(nodeToDelete);
        } else {
            free(nodeToDelete);
        }
        s->length--;
    }
}

StackNode *Stack_top(Stack *s)
{
    if (s->head == NULL) {
        return NULL;
    } else {
        return s->head;
    }
}

void Stack_free(Stack *s, bool isAlloc)
{
    int i, len;
    for (i = 0, len = s->length; i < len; i++) {
        Stack_pop(s, isAlloc);
    }
}
