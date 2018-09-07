#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "HashMap.h"

/*#define INITIAL_HASHMAP_CAPACITY 16*/
#define HASHMAP_LOAD_FACTOR 75
#define HASHMAP_GROW_FACTOR 2
#define ALLOC_FAIL_TEST(pointer, messageString) \
            if (pointer == NULL) \
            {  \
                printf(messageString); \
                return;\
            }


static size_t INITIAL_HASHMAP_CAPACITY = 16;

void HashMap_setInitialCapacity(size_t capacity) {
    INITIAL_HASHMAP_CAPACITY = capacity;
}

void HashMap_init(HashMap *hm)
{
    MapNode *temp = malloc(INITIAL_HASHMAP_CAPACITY * sizeof(MapNode));
    ALLOC_FAIL_TEST(temp, "Out of memory/n");

    int i = 0;
    for (; i < INITIAL_HASHMAP_CAPACITY; i++)
    {
        temp[i].value = NULL;
        temp[i].next = NULL;
    }
    hm->iterator = malloc(sizeof(HashMapIterator));
    ALLOC_FAIL_TEST(hm->iterator, "Out of memory!\n");
    hm->buckets = temp;
    hm->capacity = INITIAL_HASHMAP_CAPACITY;
    hm->size = 0;
    hm->loadFactor = HASHMAP_LOAD_FACTOR;

    //reset to default
    INITIAL_HASHMAP_CAPACITY = 16;
}

uint32_t HashMap_hash(const char* key)
{
    // Jenkins's one_at_a_time hash -> https://en.wikipedia.org/wiki/Jenkins_hash_function
    size_t c = 0;
    uint32_t hash = 0;

    while ((c = *key++))
    {
        hash += c;
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return hash;
}

void HashMap_insert(HashMap *hm, const char *key, void *elem)
{
    if ((int)(hm->capacity * hm->loadFactor / 100) >= hm->size) {

        uint32_t hash = HashMap_hash(key);
        uint32_t index = hash % hm->capacity;
        printf("hash index: %d, hash: %d\n", index, hash);
        //if the bucket is empty
        if ((hm->buckets[index]).value == NULL) {

            (hm->buckets[index]).hashKey = hash;
            (hm->buckets[index]).value = elem;
            (hm->buckets[index]).next = NULL;
            printf("inserted\n");
        } else {  // if the bucket is already occupied
            MapNode *newNode = malloc(sizeof(MapNode));
            ALLOC_FAIL_TEST(newNode, "Out of memory!\n");

            if ((hm->buckets[index]).next == NULL) {
                newNode->hashKey = hash;
                newNode->value = elem;
                newNode->next = NULL;
                (hm->buckets[index]).next = newNode;
            } else {
                MapNode *prevNode = (hm->buckets[index]).next;

                newNode->hashKey = hash;
                newNode->value = elem;
                newNode->next = prevNode;
                (hm->buckets[index]).next = newNode;
            }
            printf("inserted new node to list\n");
        }
        hm->size++;
    } else {
        HashMap_resize(hm);
        HashMap_insert(hm, key, elem);  // insert the element after resize occurred
    }
}


void *HashMap_get(HashMap *hm, const char *key)
{
    uint32_t hash = HashMap_hash(key);
    uint32_t index = hash % hm->capacity;

    if ((hm->buckets[index]).hashKey == hash) {
        return (hm->buckets[index]).value;

    } else {

        MapNode *current = (hm->buckets[index]).next;

        while (current) {
            printf("KEY HASH: %d, current hash: %d\n", hash, current->hashKey);
            if (current->hashKey == hash) {
                return current->value;
            } else {
                current = current->next;
            }
        }
    }

    return NULL;
}


void HashMap_resize(HashMap *hm)  //TODO: free malloc elem
{
    printf("\n++++++++++++++\n");
    size_t newCapacity = hm->capacity * HASHMAP_GROW_FACTOR;
    MapNode *newBuckets = malloc(sizeof(MapNode) * newCapacity);
    ALLOC_FAIL_TEST(newBuckets, "Out of memory!\n");

    int i;
    for (i = 0; i < newCapacity; i++)
    {
        newBuckets[i].value = NULL;
        newBuckets[i].next = NULL;
    }

    for (i = 0; i < hm->capacity; i++) {
        MapNode *node = &hm->buckets[i];

        if (node->value != NULL && node->next == NULL) { // if it is not empty and has no linked list
            //insert node in the new map
            HashMap_reinsert(newCapacity, &newBuckets, node->hashKey, node->value);
        } else if (node->value != NULL && node->next != NULL) { // if it is not empty and has linked list
            //insert node in the new map
            HashMap_reinsert(newCapacity, &newBuckets, node->hashKey, node->value);

            //loop through linked list
            node = node->next;
            while (node != NULL) {
                HashMap_reinsert(newCapacity, &newBuckets, node->hashKey, node->value);
                node = node->next;
            }
        }
    }

    HashMap_free(hm);  // free old buckets (free also iterator)
    // malloc new iterator
    hm->iterator = malloc(sizeof(HashMapIterator));
    ALLOC_FAIL_TEST(hm->iterator, "Out of memory!\n");

    hm->buckets = newBuckets;
    hm->capacity = newCapacity;
    printf("HashMap resized, new capacity: %d\n", hm->capacity);
}

void HashMap_remove(HashMap *hm, const char *key)
{
    uint32_t hash = HashMap_hash(key);
    uint32_t index = hash % hm->capacity;

    if ((hm->buckets[index]).hashKey == hash) {
        MapNode *node = (hm->buckets[index]).next;
        if (node == NULL) {
            (hm->buckets[index]).value = NULL;
            (hm->buckets[index]).hashKey = 0;
            (hm->buckets[index]).next = NULL;
            hm->size--;
        } else {

            (hm->buckets[index]).value = node->value;
            (hm->buckets[index]).hashKey = node->hashKey;
            (hm->buckets[index]).next = node->next;
            free(node);
            hm->size--;
        }
    } else {

        MapNode *current = (hm->buckets[index]).next;

        if (current->hashKey == hash) {  // if it is the first node of the linked list
            (hm->buckets[index]).next = current->next;
            free(current);
            hm->size--;
        } else {
            MapNode *prevNode = current;

            current = current->next;
            while (current) {

                printf("KEY HASH: %d, current hash: %d\n", hash, current->hashKey);
                if (current->hashKey == hash) {
                    prevNode->next = current->next;
                    free(current);
                    hm->size--;
                    break;
                } else {
                    prevNode = current;
                    current = current->next;
                }
            }
        }
    }

}

void HashMap_free(HashMap *hm)
{
    int i;
    for (i = 0; i < hm->capacity; i++) {
        MapNode *current = hm->buckets[i].next;
        if (current == NULL) continue;

        while (current != NULL) {
            MapNode *nodeToDelete = current;
            current = current->next;
            free(nodeToDelete);
        }
    }
    free(hm->buckets);
    free(hm->iterator);
}

MapNode *HashMap_iterator_begin(HashMap *hm)
{
    HashMapIterator *iterator = hm->iterator;
    // reset iterator
    iterator->current = NULL;
    iterator->index = 0;

    size_t i;
    for (i = 0; i < hm->capacity; i++) {
        if (hm->buckets[i].value != NULL) {
            iterator->current = &(hm->buckets[i]);
            iterator->index = i;
            return &(hm->buckets[i]);
        }
    }
    return NULL;
}


MapNode *HashMap_iterator_next(HashMap *hm)
{
    HashMapIterator *iterator = hm->iterator;

    if (iterator->current->next == NULL) {  // reached the end of a linked list or a single-node bucket
        size_t i;
        for (i = ++iterator->index; i < hm->capacity; i++) {
            if (hm->buckets[i].value != NULL) {
                iterator->current = &(hm->buckets[i]);
                iterator->index = i;
                return &(hm->buckets[i]);
            }
        }
        return NULL;
    } else {

        iterator->current = iterator->current->next;
        return iterator->current;
    }

}


//*** PRIVATE ***

static void HashMap_reinsert(size_t newCapacity, MapNode **newBuckets, uint32_t hash, void *elem)
{
    uint32_t index = hash % newCapacity;
    //printf("hash index: %d, hash: %d\n", index, hash);

        //if the bucket is empty
    if ((*newBuckets)[index].value == NULL) {

        (*newBuckets)[index].hashKey = hash;
        (*newBuckets)[index].value = elem;
        (*newBuckets)[index].next = NULL;
        printf("inserted **\n");
    } else {  // if the bucket is already occupied
        MapNode *newNode = malloc(sizeof(MapNode));
        ALLOC_FAIL_TEST(newNode, "Out of memory!\n");

        if ((*newBuckets)[index].next == NULL) {
            newNode->hashKey = hash;
            newNode->value = elem;
            newNode->next = NULL;
            (*newBuckets)[index].next = newNode;
        } else {
            MapNode *prevNode = (*newBuckets)[index].next;

            newNode->hashKey = hash;
            newNode->value = elem;
            newNode->next = prevNode;
            (*newBuckets)[index].next = newNode;
        }
        printf("inserted new node to list**\n");
    }
}
