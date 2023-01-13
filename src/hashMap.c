#include "include/hashMap.h"

unsigned long long _Hash(char *s)
{
    unsigned long long hash = 5381;
    while (*s) hash = ((hash << 32) + hash) + *s++;
    return hash;
}

int _StrEquals(char *self, int len, const char *other)
{
    while (len >= 16)
    {
        if (*(long long *)self != *(long long *)other) return 0;
        if (*(long long *)(self + 8) != *(long long *)(other + 8)) return 0;
        self += 16; other += 16; len -= 16;
    }
    while (len >= 8)
    {
        if (*(long long *)self != *(long long *)other) return 0;
        self += 8; other += 8; len -= 8;
    }
    while (len >= 0 && *self == *other)
    {
        self += 2; other += 2; len -= 2;
    }
    return (len <= 0);
}

HashMap * HashMap_Create(size_t initialCapacity)
{
    HashMap *hashMap = calloc(1, sizeof(HashMap));
    assert(hashMap && "Could not allocate enough memory for hash map");
    if (initialCapacity)
    {
        hashMap->capacity = initialCapacity;
        hashMap->entries = calloc(initialCapacity, sizeof(HashMapEntry));
        assert(hashMap->entries && "Could not allocate enough memory for entries");
    }
    return hashMap;
}

void HashMap_Free(HashMap *hashMap, int freeValues)
{
    if (!hashMap) return;
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
