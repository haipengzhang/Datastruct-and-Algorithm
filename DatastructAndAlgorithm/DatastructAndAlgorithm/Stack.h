//
//  Stack.h
//  test
//
//  Created by Jimzhang on 2018/1/11.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <stdio.h>
#include "LinkList.h"

/*Implement stacks as linked lists*/
typedef List Stack;

/*Public Interface*/
#define stack_init list_init
#define stack_destroy list_destroy
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);
//获取栈顶元素的信息而不弹出栈
#define stack_peer(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size

#endif /* Stack_h */
