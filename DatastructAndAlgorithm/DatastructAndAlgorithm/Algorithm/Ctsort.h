//
//  Ctsort.h
//  DatastructAndAlgorithm
//
//  Created by haipeng on 2018/1/20.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Ctsort_h
#define Ctsort_h

/* 计数排序 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* the element in data must be int, O(n + k) n is elements count, k is biggest element plus 1*/
int ctsort(int *data, int size, int k);

#endif /* Ctsort_h */
