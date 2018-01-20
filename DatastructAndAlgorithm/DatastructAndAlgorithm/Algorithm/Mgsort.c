//
//  Mgsort.c
//  DatastructAndAlgorithm
//
//  Created by haipeng on 2018/1/20.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Mgsort.h"

/* merge */
static int merge(void *data, int esize, int i, int j, int k, int(*compare)(const void *key1, const void *key2))
{
    char *a = data, *m;
    int ipos, jpos, mpos;
    
    /* initialize the counters userd in merging */
    ipos = i;
    jpos = j + 1;
    mpos = 0;
    
    /* allocte storeage for the merged elements */
    if ((m = (char *)malloc(esize * ((k - i) + 1))) == NULL) {
        return -1;
    }
    
    /* continue while either division has elements to merge */
    while (ipos <= j || jpos <= k) {
        if (ipos > j) {
            /* the left division has no more elements to merge */
            while (jpos <= k) {
                memcpy(&m[mpos * esize], &a[jpos * esize], esize);
                jpos++;
                mpos++;
            }
            continue;
        } else if (jpos > k) {
            /* the right division has no more elements to merge */
            while (ipos <= j) {
                memcpy(&m[mpos * esize], &a[ipos * esize], esize);
                ipos++;
                mpos++;
            }
            continue;
        }
        
        /* append the next ordered element to the merged elements */
        if (compare(&a[ipos * esize], &a[jpos * esize]) < 0) {
            memcpy(&m[mpos * esize], &a[ipos * esize], esize);
            ipos++;
            mpos++;
        } else {
            memcpy(&m[mpos * esize], &a[jpos * esize], esize);
            jpos++;
            mpos++;
        }
    }
    
    /* prepare to pass back the merged data */
    memcpy(&a[i * esize], m, esize * ((k - i) + 1));
    free(m);
    return 0;
}

int mgsort(void *data, int size, int esize, int i, int k, int(*compare)(const void *key1, const void *key2))
{
    int j;
    
    /* stop the recursion when no more divisions can be made */
    if (i < k) {
        /* determine where to divide the elements */
        j = (int)((i + k - 1) / 2);
        
        /* recursively sort the two divisions */
        if (mgsort(data, size, esize, i, j, compare) < 0) {
            return -1;
        }
        if (mgsort(data, size, esize, j + 1, k, compare) < 0) {
            return -1;
        }
        /* merge the two sorted divisions into a single sorted set */
        if (merge(data, esize, i, j, k, compare) < 0) {
            return -1;
        }
        return 0;
    }
    return 0;
}
