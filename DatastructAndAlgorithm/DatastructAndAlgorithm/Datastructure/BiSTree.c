//
//  BiSTree.c
//  test
//
//  Created by Jimzhang on 2018/1/12.
//  Copyright © 2018年 Jimzhang. All rights reserved.
//

#include "BiSTree.h"
#include <string.h>

/* rotate left */
static void rotate_left(BiTreeNode **node)
{
    BiTreeNode *left, *grandchild;
    AvlNode *dataNode = bitree_data(*node);
    left = bitree_left(*node);
    AvlNode *dataLeft = bitree_data(left);
    
    if (dataLeft->factor == AVL_LET_HEAVY) {
        //如果左节点长度factor = +1，执行LL旋转
        //根节点的左节点变成左节点的右节点
        bitree_left(*node) = bitree_right(left);
        //左节点的右节点变成根节点
        bitree_right(left) = *node;
        dataLeft->factor = AVL_BALANCED;
        dataNode->factor = AVL_BALANCED;
        *node = left;
    } else {
        //如果左节点长度factor = -1，执行LR旋转
        //根节点的左节点指向孙子节点的左节点（新插入导致不平衡的节点）的左节点
        grandchild = bitree_right(left);
        bitree_right(left) = bitree_left(grandchild);
        bitree_left(grandchild) = left;
        bitree_left(*node) = bitree_right(grandchild);
        bitree_right(grandchild) = *node;
        
        AvlNode *grandchildData = bitree_data(grandchild);
        switch (grandchildData->factor) {
            case AVL_LET_HEAVY:
                dataNode->factor = AVL_RGT_HEAVY;
                dataLeft->factor = AVL_BALANCED;
                break;
            case AVL_BALANCED:
                dataNode->factor = AVL_BALANCED;
                dataLeft->factor = AVL_BALANCED;
                break;
            case AVL_RGT_HEAVY:
                dataNode->factor = AVL_BALANCED;
                dataLeft->factor = AVL_LET_HEAVY;
                break;
            default:
                break;
        }
        grandchildData->factor = AVL_BALANCED;
        *node = grandchild;
    }
    return;
}

/* rotate right */
static void rotate_right(BiTreeNode **node)
{
    BiTreeNode *right, *grandchild;
    right = bitree_right(*node);
    AvlNode *dataRightNode = bitree_data(right);
    AvlNode *dataNode = bitree_data(*node);
    if (dataRightNode->factor == AVL_RGT_HEAVY) {
        /* Perform an RR rotation */
        bitree_right(*node) = bitree_left(right);
        bitree_left(right) = *node;
        dataRightNode->factor = AVL_BALANCED;
        dataNode->factor = AVL_BALANCED;
        *node = right;
    } else {
        /* Perform an RL rotation */
        grandchild = bitree_left(right);
        bitree_left(right) = bitree_right(grandchild);
        bitree_right(grandchild) = right;
        bitree_right(*node) = bitree_left(grandchild);
        bitree_left(grandchild) = *node;
        
        AvlNode *dataGrandNode = bitree_data(grandchild);
        switch (dataGrandNode->factor) {
            case AVL_LET_HEAVY:
                dataNode->factor = AVL_BALANCED;
                dataRightNode->factor = AVL_RGT_HEAVY;
                break;
            case AVL_BALANCED:
                dataNode->factor = AVL_BALANCED;
                dataRightNode->factor = AVL_BALANCED;
                break;
            case AVL_RGT_HEAVY:
                dataNode->factor = AVL_LET_HEAVY;
                dataRightNode->factor = AVL_BALANCED;
                break;
            default:
                break;
        }
        dataGrandNode->factor = AVL_BALANCED;
    }
    return;
}

/* destroy_left */
static void destroy_right(BisTree *tree, BiTreeNode *node);
static void destroy_left(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    if (bitree_size(tree) == 0) {
        return;
    }
    if (node == NULL) {
        position = &tree->root;
    } else {
        position = &node->left;
    }
    /* destroy nodes */
    if (*position != NULL) {
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        if (tree->destroy != NULL) {
            BiTreeNode *positionNode = (*position)->data;
            AvlNode *avlPostionNode = positionNode->data;
            tree->destroy(avlPostionNode->data);
        }
        free((*position)->data);
        free(*position);
        *position = NULL;
        tree->size--;
    }
    return;
}
/* destroy_right */
static void destroy_right(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    if (bitree_size(tree) == 0) {
        return;
    }
    if (node == NULL) {
        position = &tree->root;
    } else {
        position = &node->right;
    }
    /* destroy nodes */
    if (*position != NULL) {
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        if (tree->destroy != NULL) {
            BiTreeNode *positionNode = (*position)->data;
            AvlNode *avl_data = positionNode->data;
            tree->destroy(avl_data->data);
        }
        free((*position)->data);
        free(*position);
        *position = NULL;
        tree->size--;
    }
    return;
}


/* insert */
static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balance)
{
    AvlNode *avl_data;
    int cmpval, retval;
    if (bitree_is_eob(*node)) {
        /* handle insertion into an empty tree */
        if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL) {
            return -1;
        }
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;
        return bitree_ins_left(tree, *node, avl_data);
    } else {
        /* handle insertion into a tree that is not empty */
        cmpval = tree->compare(data, ((AvlNode *)bitree_data(*node))->data);
        if (cmpval < 0) {
            /* move to the left */
            if (bitree_is_eob(bitree_left(*node))) {
                if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL) {
                    return -1;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;
                if (bitree_ins_left(tree, *node, avl_data) != 0) {
                    return -1;
                }
                *balance = 0;
            } else {
                // left is not NULL, call self recursively
                if ((retval = insert(tree, &bitree_left(*node), data, balance)) != 0) {
                    return retval;
                }
            }
            /* ensure that the tree remains balanced */
            if (!*balance) {
                switch (((AvlNode *)bitree_data(*node))->factor) {
                    case AVL_LET_HEAVY:
                        rotate_left(node);
                        *balance = 1;
                        break;
                    case AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_LET_HEAVY;
                        break;
                    case AVL_RGT_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balance = 1;
                        break;
                }
            }
        } else if (cmpval > 0) {
            /* move to the right */
            if (bitree_is_eob(bitree_right(*node))) {
                if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL) {
                    return -1;
                }
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;
                if (bitree_ins_right(tree, *node, avl_data) != 0) {
                    return -1;
                }
                *balance = 0;
            } else {
                // left is not NULL, call self recursively
                if ((retval = insert(tree, &bitree_right(*node), data, balance)) != 0) {
                    return retval;
                }
            }
            /* ensure that the tree remains balanced */
            if (!*balance) {
                switch (((AvlNode *)bitree_data(*node))->factor) {
                    case AVL_LET_HEAVY:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balance = 1;
                        break;
                    case AVL_BALANCED:
                        ((AvlNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
                        break;
                    case AVL_RGT_HEAVY:
                        rotate_right(node);
                        *balance = 1;
                        break;
                }
            }
        } else {
            // equal the node
            if (!((AvlNode *)bitree_data(*node))->hidden) {
                // already exist
                return 1;
            } else {
                // insert the new data and mark it as not hidden
                if (tree->destroy != NULL) {
                    tree->destroy(((AvlNode *)bitree_data(*node))->data);
                }
                ((AvlNode *)bitree_data(*node))->data = (void *)data;
                ((AvlNode *)bitree_data(*node))->hidden = 0;
                // do not rebalance because the tree structure is unchanged;
                *balance = 1;
            }
        }
    }
    return 0;
}

/* hide */
static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{
    int cmpval, retval;
    if (bitree_is_eob(node)) {
        return -1;
    }
    cmpval = tree->compare(data, ((AvlNode *)bitree_data(node))->data);
    if (cmpval < 0) {
        retval = hide(tree, bitree_right(node), data);
    } else if (cmpval > 0) {
        retval = hide(tree, bitree_left(node), data);
    } else {
        ((AvlNode *)bitree_data(node))->hidden = 1;
        retval = 0;
    }
    return retval;
}

/* lookup */
static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
    int cmpval, retval;
    if (bitree_is_eob(node)) {
        return -1;
    }
    cmpval = tree->compare(data, ((AvlNode *)bitree_data(node))->data);
    if (cmpval < 0) {
        retval = lookup(tree, bitree_right(node), data);
    } else if (cmpval > 0) {
        retval = lookup(tree, bitree_left(node), data);
    } else {
        if(!((AvlNode *)bitree_data(node))->hidden) {
            *data = ((AvlNode *)bitree_data(node))->data;
            retval = 0;
        } else {
            return -1;
        }
        retval = 0;
    }
    return retval;
}

void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    bitree_init(tree, destroy);
    tree->compare = compare;
    return;
}

void bistree_destroy(BisTree *tree)
{
    destroy_left(tree, NULL);
    memset(tree, 0, sizeof(BisTree));
    return;
}

int bistree_insert(BisTree *tree, const void *data)
{
    int balance = 0;
    return insert(tree, &bitree_root(tree), data, &balance);
}
int bistree_remove(BisTree *tree, const void *data)
{
    return hide(tree, bitree_root(tree), data);
}
int bistree_lookup(BisTree *tree, void **data)
{
    return lookup(tree, bitree_root(tree), data);
}
