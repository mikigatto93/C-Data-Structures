#include <stdlib.h>
#include <stdio.h>
#include "ArrayList.h"

int main(void)
{
    ArrayList list;
    int data[] = {30,423,6345,10,7,8,9,16,23,4,5};
    ArrayList_init(&list, sizeof(int));

    int i = 0;
    for (i = 0; i < 8; i++)
    {
        ArrayList_push(&list, &(data[i]));
        printf("array[%d] = %d\n", i, *(int*)ArrayList_get(&list, i));
    }

    ArrayList_free(&list, 0);
    return 0;
}

