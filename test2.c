#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

int main(void)
{
    int data[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    Stack s;

    Stack_init(&s);

    int i;
    for (i = 0; i < 11; i++) {
        Stack_push(&s, &data[i]);
    }

    //printf("Stack length: %d\n", s.length);

    /*for (i = 0; i < 11; i++) {
        StackNode *node = Stack_top(&s);
        printf("stack val: %d\n", *(int*)node->data);
        Stack_pop(&s, false);
        printf("Stack length: %d\n", s.length);
    }*/

    Stack_free(&s, false);
    /*printf("len: %d\n", s.length);
    if (s.head == NULL)
        printf("null");*/


    return 0;
}
