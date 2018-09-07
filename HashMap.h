#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdint.h>

typedef struct hashmap HashMap;
typedef struct mapnode MapNode;
typedef struct hashmapiter HashMapIterator;

struct mapnode
{
    uint32_t hashKey;
    void *value;
    MapNode *next;
};

struct hashmapiter
{
    size_t index;
    MapNode *current;
};

struct hashmap
{
    MapNode *buckets;
    size_t size;
    size_t capacity;
    int8_t loadFactor;
    HashMapIterator *iterator;
};

void HashMap_init(HashMap *hm);
void HashMap_setInitialCapacity(size_t capacity);
uint32_t HashMap_hash(const char* key);
void HashMap_insert(HashMap *hm, const char *key, void *elem);
void *HashMap_get(HashMap *hm, const char *key);
void HashMap_resize(HashMap *hm);
void HashMap_remove(HashMap *hm, const char *key);
void HashMap_free(HashMap *hm);

// ** Iterator **
MapNode *HashMap_iterator_begin(HashMap *hm);
MapNode *HashMap_iterator_next(HashMap *hm);
//MapNode *HashMap_iterator_end(HashMap *hm);

static void HashMap_reinsert(size_t newCapacity, MapNode **newBuckets, uint32_t hash, void *elem);
#endif // HASHMAP_H
