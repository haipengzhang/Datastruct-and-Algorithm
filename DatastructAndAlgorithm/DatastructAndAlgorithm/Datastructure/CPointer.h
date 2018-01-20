//
//  CPointer.h
//  test
//
//  Created by Jimzhang on 2018/1/8.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#ifndef CPointer_h
#define CPointer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b);
int f(int **iptr);
int g(int **iptr);
int swap2(void *x, void *y, int size);

#endif /* CPointer_h */
