#include <stdlib.h>
#include <stdio.h>
#include "HashMap.h"

int main(void)
{

    //printf("hash: %d\n", (int)HashMap_hash("ciao"));
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    HashMap hm;

    HashMap_init(&hm);
    HashMap_insert(&hm, "first", &a[1]);
    HashMap_insert(&hm, "second", &a[2]);
    HashMap_insert(&hm, "third", &a[3]);

    HashMap_insert(&hm, "fourth", &a[4]);

    HashMap_insert(&hm, "fifth", &a[5]);
    HashMap_insert(&hm, "sixth", &a[6]);

    HashMap_insert(&hm, "seventh", &a[7]);
    HashMap_insert(&hm, "eigth", &a[8]);
    HashMap_insert(&hm, "asdf", &a[9]);

    HashMap_insert(&hm, "wert", &a[10]);

    HashMap_insert(&hm, "ubhrt", &a[11]);
    HashMap_insert(&hm, "six123th", &a[12]);

    //printf("cap: %d\n", INITIAL_HASHMAP_CAPACITY);
    //int *val = HashMap_get(&hm, "first");
    //printf("key: %s, value: %p\n", "first", val);
    /*printf("key: %s, value: %d\n", "eigth", *(int*) HashMap_get(&hm, "eigth"));
    printf("key: %s, value: %d\n", "third", *(int*) HashMap_get(&hm, "third"));
    printf("key: %s, value: %d\n", "wert", *(int*) HashMap_get(&hm, "wert"));
    printf("key: %s, value: %d\n", "second", *(int*) HashMap_get(&hm, "second"));
    printf("key: %s, value: %d\n", "six123th", *(int*) HashMap_get(&hm, "six123th"));*/

    //printf("key: %s, value: %d\n", "fifth", *(int*) HashMap_get(&hm, "fifth"));
    printf("\n****capacity: %d\n\n\n", hm.capacity);

    MapNode *node;
    for (node = HashMap_iterator_begin(&hm); node != NULL; node = HashMap_iterator_next(&hm)) {

        printf("index: %d\n", hm.iterator->index);

        printf("key: %d, value: %d\n", node->hashKey, *(int*)node->value);
    }

    HashMap_remove(&hm, "six123th");
    HashMap_remove(&hm, "fourth");
    HashMap_remove(&hm, "first");
    HashMap_remove(&hm, "second");
    HashMap_remove(&hm, "eigth");


    printf("\n---------------\n");

    for (node = HashMap_iterator_begin(&hm); node != NULL; node = HashMap_iterator_next(&hm)) {
        printf("key: %d, value: %d\n", node->hashKey, *(int*)node->value);
    }

    HashMap_free(&hm);
    return 0;
}
