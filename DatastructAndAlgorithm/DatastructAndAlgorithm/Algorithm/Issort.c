//
//  Issort.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/19.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Issort.h"

/* O(n2) */
int issort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2))
{
    char *a = data;
    void *key;
    int i, j;
    
    /* allocate storage for the key element */
    if ((key = (char *)malloc(sizeof(esize))) == NULL) {
        return -1;
    }
    /* repeatedly insert a key element among the sorted elements */
    for (j = 1; j < size; j++) {
        memcpy(key, &a[j * esize], esize);
        i = j - 1;
        /* determine the postion at which to insert the key element */
        while (i >= 0 && compare(&a[i * esize], key) > 0) {
            memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
            i--;
        }
        memcpy(&a[(i + 1) * esize], key, esize);
    }
    free(key);
    return 0;
}
