//
//  BiSTree.c
//  test
//
//  Created by Jimzhang on 2018/1/12.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "BiSTree.h"

void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    bitree_init(tree, destroy);
    tree->compare = compare;
    return;
}

void bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bistree_lookup(BisTree *tree, void **data);
