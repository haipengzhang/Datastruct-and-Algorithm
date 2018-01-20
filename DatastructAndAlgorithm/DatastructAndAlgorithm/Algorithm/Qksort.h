//
//  Qksort.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/19.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Qksort_h
#define Qksort_h

/* 快速排序 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int qksort(void *data, int size, int esize, int i, int k, int (*compare)(const void *key1, const void *key2));

#endif /* Qksort_h */
