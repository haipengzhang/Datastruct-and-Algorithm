//
//  Bisearch.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/25.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Bisearch.h"

int bisearch(void *sorted, const void *target, int size, int esize, int(*compare)(const void *key1, const void *key2))
{
    int left, middle, right;
    
    /* continue searching until the left and right indices cross */
    left = 0;
    right = size - 1;
    while (left <= right) {
        middle = (right + left) / 2;
        switch (compare(((char *)sorted + (esize * middle)), target)) {
            case -1:
                /* prepare to search to the right of the middle index */
                left = middle + 1;
                break;
            case 1:
                /* prepare to search to the left of the middle index */
                right = middle - 1;
                break;
            case 0:
                /* return the exact index where the data has been fount */
                return middle;
        }
    }
    return -1;
}
