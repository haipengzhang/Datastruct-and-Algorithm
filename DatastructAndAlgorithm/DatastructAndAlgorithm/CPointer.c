//
//  CPointer.c
//  test
//
//  Created by Jimzhang on 2018/1/8.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "CPointer.h"

#pragma mark - c pointer test method

// 作为函数参数的指针
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 内存空间分配：直接声明变量，动态创建
int f(int **iptr) {
    // 一个*是变量指针，两个*是变量指针的指针
    int a = 100;
    printf("tempa=%i\n", a);
    *iptr = &a;
    // 函数返回a变量回收，iptr变成悬空指针
    return 0;
}

int g(int **iptr) {
    void *tempPoint = malloc(sizeof(int));
    if ((*iptr = (int *)tempPoint) == NULL) {
        return -1;
    }
    return 0;
}

// 数组的操作
int array_01() {
    int a[10], *iptr;
    iptr = a;
    iptr[0] = 5;    //等价于 *iptr = 5;
    iptr[4] = 10;   //等价于 *(iptr + 4)
    // 多维数组 a[i][j] 等价于 *(*(a + i) + j) i代表行
    return 0;
}

// 泛型指针
int swap2(void *x, void *y, int size) {
    void *temp;
    if ((temp = malloc(size)) == NULL) {
        return -1;
    }
    memcpy(temp, x, size);
    memcpy(x, y, size);
    memcpy(y, temp, size);
    free(temp);
    return 0;
}

