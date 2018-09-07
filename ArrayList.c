#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArrayList.h"

#define GROW_FACTOR 2
#define ALLOC_FAIL_TEST(pointer, messageString) \
            if (pointer == NULL) \
            {  \
                printf(messageString); \
                return;\
            }

void ArrayList_init(ArrayList *a, size_t capacity)
{
	void **temp = malloc(capacity * sizeof(void*));
    //printf("data size: %d\n", sizeof(void*));

    ALLOC_FAIL_TEST(temp, "Out of memory!\n");
    a->array = temp;
    a->capacity = capacity;
    a->length = 0;
}

void ArrayList_insert(ArrayList *a, int index, void *elem)
{
    if ((internal_inBoundIndexCheck(a, index)) == 1) {
        if (a->length + 1 == a->capacity) {
            void **temp = realloc(a->array, GROW_FACTOR * a->capacity * sizeof(void*));
            ALLOC_FAIL_TEST(temp, "Out of memory!\n");
            a->array = temp;
            a->capacity *= GROW_FACTOR;
            (a->array)[index] = elem;
            a->length++;
            //printf("Reallocation occurred, capacity: %d, length: %d\n", a->capacity, a->length);
        } else {
            (a->array)[index] = elem;
            a->length++;
        }
    }
}

void *ArrayList_get(ArrayList *a, int index)
{
    if ((internal_inBoundIndexCheck(a, index)) == 1) {
        void* p;
        p = (a->array)[index];
        return p;
    }
    return NULL;
}

_Bool internal_inBoundIndexCheck(ArrayList *a, int index)
{
    if (index < 0 || index  >= a->capacity){
        printf("Index out of bound!\n");
        return 0;
    } else
        return 1;
}

void ArrayList_shrink_to_fit(ArrayList *a)
{
    void **temp = realloc(a->array, a->length * sizeof(void*));
    ALLOC_FAIL_TEST(temp, "Memory error!\n");
    a->array = temp;
    a->capacity = a->length;
}

void ArrayList_remove(ArrayList *a, int index)
{
    int i;
    for (i = index; i < a->capacity - 1; i++) {
        a->array[i] = a->array[i + 1];
    }
    a->array[a->length] = NULL;
    a->length--;
}

void ArrayList_free(ArrayList *a, _Bool isAllocated)
{
    if (isAllocated == 1) {
        for (int i = 0; i < a->length; i++) {
            free((a->array)[i]);
        }
    }
    free(a->array);
}

void ArrayList_append(ArrayList *a, void* elem)
{
    ArrayList_insert(a, a->length, elem);
}





