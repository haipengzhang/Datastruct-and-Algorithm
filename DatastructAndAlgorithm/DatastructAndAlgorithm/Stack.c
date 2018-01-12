//
//  Stack.c
//  test
//
//  Created by Jimzhang on 2018/1/11.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "Stack.h"
#include <stdlib.h>

int stack_push(Stack *stack, const void *data)
{
    return list_ins_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data)
{
    return list_rem_next(stack, NULL, data);
}
