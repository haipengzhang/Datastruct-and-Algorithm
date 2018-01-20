//
//  Mgsort.h
//  DatastructAndAlgorithm
//
//  Created by haipeng on 2018/1/20.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Mgsort_h
#define Mgsort_h

/* 归并排序 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mgsort(void *data, int size, int esize, int i, int k, int(*compare)(const void *key1, const void *key2));

#endif /* Mgsort_h */
