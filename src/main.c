#include <stdio.h>
#include "include/hashMap.h"

int main(void)
{
    HashMap *hashMap = HashMap_Create(0);
    HashMap_Insert(hashMap, "A", "A");
    HashMap_Insert(hashMap, "A", "a");
    HashMap_Insert(hashMap, "B", "b");
    HashMap_Insert(hashMap, "C", "c");

    char *val = HashMap_Get(hashMap, "A");
    if (val) printf("%s\n", val);
    val = HashMap_Get(hashMap, "B");
    if (val) printf("%s\n", val);
    val = HashMap_Get(hashMap, "C");
    if (val) printf("%s\n", val);

    HashMap_Free(hashMap, 1);
    printf("Succeed\n");
    return 0;
}