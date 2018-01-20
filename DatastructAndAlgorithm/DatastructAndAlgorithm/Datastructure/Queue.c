//
//  Queue.c
//  test
//
//  Created by Jimzhang on 2018/1/11.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "Queue.h"
#include "LinkList.h"

int queue_enqueue(Queue *queue, const void *data)
{
    return list_ins_next(queue, list_tail(queue), data);
}

int queue_dequeue(Queue *queue, void **data)
{
    return list_rem_next(queue, list_tail(queue), data);
}
