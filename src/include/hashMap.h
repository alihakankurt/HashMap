#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <stdlib.h>
#include <assert.h>

typedef struct HashMapEntry
{
    unsigned long long hash;
    int used;
    char *key;
    void *value;
} HashMapEntry;

typedef struct HashMap
{
    size_t capacity;
    size_t size;
    HashMapEntry *entries;
} HashMap;

HashMap * HashMap_Create(size_t initialCapacity);
void HashMap_Free(HashMap *hashMap, int freeValues);

#endif