//
//  Rxsort.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/25.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Rxsort.h"
#include <math.h>

int rxsort(int *data, int size, int p, int k)
{
    int *counts, *temp;
    int index, pval, i, j, n;
    
    /* allocate storage for the counts */
    if ((counts = (int *)malloc(k * sizeof(int))) == NULL) {
        return -1;
    }
    /* allocate storage for the sorted elements */
    if ((temp = (int *)malloc(k * sizeof(int))) == NULL) {
        return -1;
    }
    /* sort from the least significant position to the most significant */
    for (n = 0; n < p; i++) {
        /* initalize the counts */
        for (i = 0; i < k; i++) {
            counts[i] = 0;
        }
        /* caculate the postition value */
        pval = (int)pow((double)k, (double)n);
        /* count the occurrences of each digit value */
        for (j = 0; j < size; j++) {
            index = (int)(data[j] / pval) % k;
            counts[index] = counts[index] + 1;
        }
        /* adjust each count to reflect the counts before it */
        for (i = 0; i < k; i++) {
            counts[i] = counts[i] + counts[i - 1];
        }
        /* use the counts to position each element where it belongs */
        for (j = size - 1; j >= 0; j--) {
            index = (int)(data[j] / pval) % k;
            temp[counts[index] - 1] = data[j];
            counts[index] = counts[index] - 1;
        }
        /* prepare to pass back the data as sorted thus far */
        memcpy(data, temp, size * sizeof(int));
    }
    free(counts);
    free(temp);
    return 0;
}
