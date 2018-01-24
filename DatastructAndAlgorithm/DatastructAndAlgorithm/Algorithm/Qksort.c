//
//  Qksort.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/19.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Qksort.h"
#include "Issort.h"

/* O(nlgn)  */
static int compare_int(const void *int1, const void *int2)
{
    /* compare two integers */
    if (*(const int *)int1 > *(const int *)int2) {
        return 1;
    } else if (*(const int *)int1 < *(const int *)int2) {
        return -1;
    } else {
        return 0;
    }
}

/* partition */
static int partition(void *data, int esize, int i, int k, int (*compare)(const void *key1, const void *key2))
{
    char *a = data;
    void *pval, *temp;
    int r[3];
    
    /* allocate storage for the partition value and swapping */
    if ((pval = malloc(esize)) == NULL) {
        return -1;
    }
    if ((temp = malloc(esize)) == NULL) {
        free(pval);
        return -1;
    }
    
    /* use the median-of-three method to find the partition value */
    r[0] = (rand() % (k-i+1)) + i;
    r[1] = (rand() % (k-i+1)) + i;
    r[2] = (rand() % (k-i+1)) + i;
    issort(r, 3, sizeof(int), compare_int);
    memcpy(pval, &a[r[1] * esize], esize);
    
    /* create two partitions around the partition value */
    i--;
    k++;
    
    while (1) {
        /* move left until an element is found int the wrong partition */
        do {
            k--;
        } while (compare(&a[k*esize], pval) > 0);
        
        /* move right until an element is found int the wrong partition */
        do {
            i++;
        } while (compare(&a[i*esize], pval) < 0);
        
        if (i >= k) {
            /* stop partitioning when the left and right counters cross */
            break;
        } else {
            /* swap the elements now under the left and right counters */
            memcpy(temp, &a[i * esize], esize);
            memcpy(&a[i * esize], &a[k * esize], esize);
            memcpy(&a[k * esize], temp, esize);
        }
    }
    
    /* free the storage allocated for partitioning */
    free(pval);
    free(temp);
    
    /* return the position dividing the two partitions */
    return k;
}

int qksort(void *data, int size, int esize, int i, int k, int (*compare)(const void *key1, const void *key2))
{
    int j;
    /* stop the recursion when it is not possible to partition further */
    while (i < k) {
        /* determine where ti partition the elements */
        if ((j = partition(data, esize, i, k, compare)) < 0) {
            return -1;
        }
        /* recursively sort the left partition */
        if (qksort(data, size, esize, i, j, compare) < 0) {
            return -1;
        }
        /* interate and sort the left partition */
        i = j +1;
    }
    return 0;
}
