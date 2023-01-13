#include "include/hashMap.h"

#include <string.h>
#include <assert.h>

// The djb2 algorithm written by Daniel J. Bernstein
size_t _Hash(char *s)
{
    size_t hash = 5381;
    while (*s) hash = ((hash << 5) + hash) + *s++;
    return hash;
}

HashMap * HashMap_Create(size_t initialCapacity)
{
    HashMap *hashMap = calloc(1, sizeof(HashMap));
    assert(hashMap && "Could not allocate enough memory for hash map");
    initialCapacity = initialCapacity ? initialCapacity : INITIAL_HASH_MAP_SIZE;
    hashMap->capacity = initialCapacity;
    hashMap->entries = calloc(initialCapacity, sizeof(HashMapEntry));
    assert(hashMap->entries && "Could not allocate enough memory for entries");
    return hashMap;
}

void HashMap_Free(HashMap *hashMap, int freeValues)
{
    assert(hashMap && "Could not free hash map because it was null");
    if (hashMap->entries)
    {
        for (size_t i = 0; i < hashMap->size; i++)
        {
            free((hashMap->entries + i)->key);
            if (freeValues) free((hashMap->entries + i)->value);
        }
        free(hashMap->entries);
    }
    free(hashMap);
}

void _HashMap_Extend(HashMap **hashMap)
{
    HashMap *newHashMap = HashMap_Create((*hashMap)->capacity * 2);
    for (size_t i = 0; i < (*hashMap)->size; i++)
    {
        HashMap_Insert(newHashMap, ((*hashMap)->entries + i)->key, ((*hashMap)->entries + i)->value);
    }
    HashMap_Free(*hashMap, 0);
    *hashMap = newHashMap;
}

#include <stdio.h>
void * HashMap_Insert(HashMap *hashMap, char *key, void *value)
{
    assert(hashMap && "Could not insert entry to hash map because it was null");
    assert(key && value && "Could not insert entry to hash map because provided key or value was null");

    size_t hashValue = _Hash(key);
    size_t hashIndex = hashValue % hashMap->capacity;
    if ((hashMap->entries + hashIndex)->used && !strcmp((hashMap->entries + hashIndex)->key, key))
    {
        void *tmp = (hashMap->entries + hashIndex)->value;
        (hashMap->entries + hashIndex)->value = value;
        return tmp;
    }

    if (hashMap->size == hashMap->capacity)
    {
        _HashMap_Extend(&hashMap);
        hashIndex = hashValue % hashMap->capacity;
    }

    if ((hashMap->entries + hashIndex)->used)
        for (hashIndex = 0; hashIndex < hashMap->capacity && (hashMap->entries + hashIndex)->used; hashIndex++);
    
    (hashMap->entries + hashIndex)->hash = hashValue;
    (hashMap->entries + hashIndex)->key = strdup(key);
    (hashMap->entries + hashIndex)->value = value;
    (hashMap->entries + hashIndex)->used = 1;

    if ((hashValue % hashMap->capacity) != hashIndex)
        (hashMap->entries + (hashValue % hashMap->capacity))->next = (hashMap->entries + hashIndex);
    
    return NULL;
}

void * HashMap_Remove(HashMap *hashMap, char *key)
{
    assert(hashMap && "Could not remove entry from hash map because it was null");
    assert(key && "Could not remove entry from hash map because provided key was null");

    size_t hashValue = _Hash(key);
    size_t hashIndex = hashValue % hashMap->capacity;

    if (!(hashMap->entries + hashIndex)->used)
        return NULL;
    
    HashMapEntry *entry = hashMap->entries + hashIndex;
    if (!strcmp(entry->key, key))
    {
        void *value = entry->value;
        free(entry->key);
        memset(entry, 0, sizeof(HashMapEntry));
        return value;
    }
    
    while (entry->next && strcmp(entry->next->key, key))
        entry = entry->next;

    if (!entry->next)
        return NULL;
    
    HashMapEntry *tmp = entry->next;
    entry->next = entry->next->next;
    void *value = tmp->value;
    free(tmp->key);
    memset(tmp, 0, sizeof(HashMapEntry));
    return value;
}

void * HashMap_Get(HashMap *hashMap, char *key)
{
    assert(hashMap && "Could not get value from hash map because it was null");
    assert(key && "Could not get value from hash map because provided key was null");

    size_t hashIndex = _Hash(key) % hashMap->capacity;

    if (!(hashMap->entries + hashIndex)->used)
        return NULL;
    
    HashMapEntry *entry = hashMap->entries + hashIndex;
    while (entry && strcmp(entry->key, key))
        entry = entry->next;
    
    return entry ? entry->value : NULL;
}
