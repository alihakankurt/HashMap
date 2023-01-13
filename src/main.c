#include <stdio.h>
#include "include/hashMap.h"

int main(void)
{
    HashMap *hashMap = HashMap_Create(0);
    HashMap_Free(hashMap, 1);
    return 0;
}