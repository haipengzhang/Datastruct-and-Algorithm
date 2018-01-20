//
//  Queue.h
//  test
//
//  Created by Jimzhang on 2018/1/11.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include "LinkList.h"

/*Implement stacks as linked lists*/
typedef List Queue;

/*Public Interface*/
#define queue_init list_init
#define queue_destroy list_destroy
int queue_enqueue(Queue *queue, const void *data);
int queue_dequeue(Queue *queue, void **data);
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
#define queue_size list_size
#endif /* Queue_h */
