//
//  traverse.c
//  test
//
//  Created by Jimzhang on 2018/1/12.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "traverse.h"

// 前序遍历
int pre_order(const BiTreeNode *node, List *list)
{
    if (!bitree_is_eob(node)) {
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) {
            return -1;
        }
        if (!bitree_is_eob(bitree_left(node))) {
            if (pre_order(bitree_left(node), list) != 0) return -1;
        }
        if (!bitree_is_eob(bitree_right(node))) {
            if (pre_order(bitree_right(node), list) != 0) return -1;
        }
    }
    return 0;
}

// 中序遍历
int inorder(const BiTreeNode *node, List *list)
{
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            if (pre_order(bitree_left(node), list) != 0) return -1;
        }
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) return -1;
        if (!bitree_is_eob(bitree_right(node))) {
            if (pre_order(bitree_right(node), list) != 0) return -1;
        }
    }
    return 0;
}

// 后序遍历
int posorder(const BiTreeNode *node, List *list)
{
    if (!bitree_is_eob(node)) {
        if (!bitree_is_eob(bitree_left(node))) {
            if (pre_order(bitree_left(node), list) != 0) return -1;
        }
        if (!bitree_is_eob(bitree_right(node))) {
            if (pre_order(bitree_right(node), list) != 0) return -1;
        }
        if (list_ins_next(list, list_tail(list), bitree_data(node)) != 0) return -1;
    }
    return 0;
}
