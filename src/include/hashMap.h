#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <stdlib.h>

typedef struct HashMapEntry
{
    size_t hash;
    char *key;
    void *value;
    int used;
    struct HashMapEntry *next;
} HashMapEntry;

typedef struct HashMap
{
    size_t capacity;
    size_t size;
    HashMapEntry *entries;
} HashMap;

HashMap * HashMap_Create(size_t initialCapacity);
void HashMap_Free(HashMap *hashMap, int freeValues);
void * HashMap_Insert(HashMap *hashMap, char *key, void *value);
void * HashMap_Get(HashMap *hashMap, char *key);

#endif