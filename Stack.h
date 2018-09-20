#ifndef STACK_H
#define STACK_H

typedef struct stacknode StackNode;
typedef struct stack Stack;

struct stacknode
{
    StackNode *next;
    void *data;
};

struct stack
{
    size_t length;
    StackNode *head;
};

void Stack_init(Stack *s);

void Stack_push(Stack *s, void *data);
void Stack_pop(Stack *s, _Bool isAlloc);
StackNode *Stack_top(Stack *s);
void Stack_free(Stack *s, _Bool isAlloc);

#endif // STACK_H
