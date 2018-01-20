//
//  Issort.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/19.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Issort_h
#define Issort_h

/* 插入排序 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int issort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2));

#endif /* Issort_h */
