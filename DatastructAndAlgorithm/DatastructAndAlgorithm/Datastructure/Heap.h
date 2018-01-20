//
//  Heap.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/15.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Heap_h
#define Heap_h
#include <stdlib.h>
#include <stdio.h>
typedef struct Heap_
{
    int size;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    void **tree;    //堆中存储节点的数组
} Heap;

/* Public Interface */
void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));
void heap_destroy(Heap *heap);
int heap_insert(Heap *heap, const void *data);
int heap_extract(Heap *heap, void **data);
#define heap_size(heap) ((heap)->size)
#endif /* Heap_h */
