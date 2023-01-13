#include <stdio.h>
#include "include/hashMap.h"

int main(void)
{
    HashMap *hashMap = HashMap_Create(0);
    HashMap_Insert(hashMap, "A", "A");
    HashMap_Insert(hashMap, "A", "a");
    HashMap_Insert(hashMap, "B", "b");
    HashMap_Insert(hashMap, "C", "c");
    HashMap_Insert(hashMap, "D", "d");

    char *val = HashMap_Get(hashMap, "D");
    printf("%s\n", val ? val : "null");
    val = HashMap_Remove(hashMap, "C");
    printf("%s\n", val ? val : "null");
    val = HashMap_Remove(hashMap, "C");
    printf("%s\n", val ? val : "null");
    val = HashMap_Get(hashMap, "A");
    printf("%s\n", val ? val : "null");
    val = HashMap_Get(hashMap, "B");
    printf("%s\n", val ? val : "null");

    HashMap_Free(hashMap, 1);
    printf("Succeed\n");
    return 0;
}