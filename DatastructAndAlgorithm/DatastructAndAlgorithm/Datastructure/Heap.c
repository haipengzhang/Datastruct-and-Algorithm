//
//  Heap.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/15.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Heap.h"
#include <string.h>

// 二叉树的逻辑
#define heap_parent(npos) ((int)(((npos)-1) / 2))
#define heap_left(npos) (((npos) * 2) + 1)
#define heap_right(npos) (((npos) * 2) + 2)

void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;
    return;
}

void heap_destroy(Heap *heap)
{
    int i;
    if (heap->destroy != NULL) {
        for (i = 0; i < heap_size(heap); i++) {
            heap->destroy(heap->tree[i]);
        }
    }
    free(heap->tree);
    memset(heap, 0, sizeof(Heap));
    return;
}

int heap_insert(Heap *heap, const void *data)
{
    void *temp;
    int ipos, ppos;
    /* alloc stroage for the node */
    temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *));
    if (temp == NULL) {
        return -1;
    } else {
        heap->tree = temp;
    }
    /* insert the node after the last node */
    heap->tree[heap_size(heap)] = (void *)data;
    
    ipos = heap_size(heap);
    ppos = heap_parent(ipos);
    while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {
        /* swap the contents of the current node and its parent */
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;
        
        /* move up one level in the tree to continue heapifying(数组堆化) */
        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    heap->size++;
    return 0;
}

// extract:提取
int heap_extract(Heap *heap, void **data)
{
    void *save, *temp;
    int ipos, lpos, rpos, mpos;
    
    /* do not extraction from an empty heap */
    if (heap_size(heap) == 0) {
        return -1;
    }
    
    /* extract the node at the top of the heap */
    *data = heap->tree[0];
    /* adjust the storeage used by the heap */
    save = heap->tree[heap_size(heap) - 1];
    if (heap_size(heap) - 1 > 0) {
        temp = (void **)realloc(heap->tree, (heap_size(heap) - 1) * sizeof(void *));
        if (temp == NULL) {
            return -1;
        } else {
            heap->tree = temp;
        }
        heap->size--;
    } else {
        /* manage the heap when extracting the last node */
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }
    /* copy the last node to the top */
    heap->tree[0] = save;
    /* heapify the tree by pushing the contents of the new top downward */
    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);
    while (1) {
        /* select the child to swap with the current node */
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);
        if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0) {
            mpos = lpos;
        } else {
            mpos = ipos;
        }
        if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0) {
            mpos = rpos;
        }
        if (mpos == ipos) {
            break;
        } else {
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;
            ipos = mpos;
        }
    }
    return 0;
}





