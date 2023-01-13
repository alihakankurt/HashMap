#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <stdlib.h>

#define INITIAL_HASH_MAP_SIZE 4

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

// Creates a new hash map with provided capacity. If initialCapacity is 0, then it is assigned to INITIAL_HASH_MAP_CAPACITY.
HashMap * HashMap_Create(size_t initialCapacity);
// Frees the hash map and frees the values if freeValues flag is set to 1.
void HashMap_Free(HashMap *hashMap, int freeValues);
// Inserts value to hash map in the index of the provided key. Replaces the value and returns the old one if there is already exists a entry with this key.
void * HashMap_Insert(HashMap *hashMap, char *key, void *value);
// Removes the entry from hash map that stored in the index of the key and returns the value.
void * HashMap_Remove(HashMap *hashMap, char *key);
// Returns the value that stored in the index of the key. If it is not exists then returns NULL.
void * HashMap_Get(HashMap *hashMap, char *key);

#endif