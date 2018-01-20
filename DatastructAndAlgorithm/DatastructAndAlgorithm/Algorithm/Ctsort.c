//
//  Ctsort.c
//  DatastructAndAlgorithm
//
//  Created by haipeng on 2018/1/20.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Ctsort.h"

int ctsort(int *data, int size, int k)
{
    int *counts, *temp;
    int i, j;
    
    /* allocate storage for the counts */
    if ((counts = (int *)malloc(k * sizeof(int))) == NULL) {
        return -1;
    }
    
    /* allocate storage for the sorted elements */
    if ((temp = (int *)malloc(size * sizeof(int))) == NULL) {
        return -1;
    }
    
    /* initialize the counts */
    for (i = 0; i < k; i++) {
        counts[i] = 0;
    }
    
    /* count the occurrences of each elements */
    for (j = 0; j < size; j++) {
        counts[data[j]] += 1;
    }
    
    /* adjust each count to reflect the counts before it */
    for (i = 1; i < k; i++) {
        counts[i] += counts[i - 1];
    }
    
    /* use the counts to position each element where it belongs */
    for (j = size - 1; j >= 0; j--) {
        temp[counts[data[j]] - 1] = data[j];
        counts[data[j]] = counts[data[j]] - 1;
    }
    
    /* prepare to pass back the sorted data */
    memcpy(data, temp, size * sizeof(int));
    free(counts);
    return 0;
}
