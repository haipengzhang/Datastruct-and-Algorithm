//
//  BiSTree.h
//  test
//
//  Created by Jimzhang on 2018/1/12.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#ifndef BiSTree_h
#define BiSTree_h

#include <stdio.h>
#include "BiTree.h"

/* Define balance factors for AVL trees */
#define AVL_LET_HEAVY   1
#define AVL_BALANCED    0
#define AVL_RGT_HEAVY   -1

/* Define a structure for nodes in AVL trees */
typedef struct AvlNode_{
    void *data;
    int hidden;
    int factor;
}AvlNode;

/* Implement binary search trees as binary trees */
typedef BiTree BisTree;

/* Public Interface */
void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));
void bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bistree_lookup(BisTree *tree, void **data);

#define bistree_size(tree) ((tree)->size)

#endif /* BiSTree_h */
