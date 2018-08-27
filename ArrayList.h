#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct al ArrayList;

struct al
{
    size_t length;
    size_t capacity;
    void **array;
};


void ArrayList_init(ArrayList *a, size_t capacity);
void ArrayList_insert(ArrayList *a, int index, void* elem);
void *ArrayList_get(ArrayList *a, int index);
void ArrayList_shrink_to_fit(ArrayList *a);
void ArrayList_erase(ArrayList *a, int index, _Bool isAllocated);
void ArrayList_push(ArrayList *a, void* elem);

void ArrayList_free(ArrayList *a, _Bool isAllocated);

_Bool internal_inBoundIndexCheck(ArrayList *a, int index);
#endif // ARRAYLIST_H
