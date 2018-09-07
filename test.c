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
        ArrayList_append(&list, &(data[i]));
        printf("array[%d] = %d\n", i, *(int*)ArrayList_get(&list, i));
    }

    printf("\n\n----------\n\n");

    ArrayList_remove(&list, 2, 0);

    for (i = 0; i < list.length; i++)
    {
        //ArrayList_append(&list, &(data[i]));
        printf("array[%d] = %d\n", i, *(int*)ArrayList_get(&list, i));
    }

    //ArrayList_get(&list, 100);
    ArrayList_free(&list, 0);
    return 0;
}

