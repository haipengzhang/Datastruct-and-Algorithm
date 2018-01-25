//
//  Bisearch.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/25.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Bisearch_h
#define Bisearch_h

#include <stdio.h>
#include <string.h>

/* 二分查找 */
int bisearch(void *sorted, const void *target, int size, int esize, int(*compare)(const void *key1, const void *key2));

#endif /* Bisearch_h */
