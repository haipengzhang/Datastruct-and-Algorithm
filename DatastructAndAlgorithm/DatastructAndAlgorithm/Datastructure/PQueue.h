//
//  PQueue.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/15.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef PQueue_h
#define PQueue_h
#include "Heap.h"

/* 优先队列 */
#include <stdio.h>

/* implement priority queues as heaps */
typedef Heap PQueue;

/* public interface */
#define pqueue_init heap_init
#define pqueue_destroy heap_destroy
#define pqueue_insert heap_insert
#define pqueue_extract heap_extract
#define pqueue_peek ((queue)->tree == NULL ? NULL : (queue)->tree[0])
#define pqueue_size heap_size
#endif /* PQueue_h */
