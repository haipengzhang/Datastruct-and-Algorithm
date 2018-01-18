//
//  bsf.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/17.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef bsf_h
#define bsf_h

/* 广度优先搜索 */
#include <stdio.h>
#include "Graph.h"
#include "LinkList.h"

/* define a structure for a vertices in a breadth-first search */
typedef struct BfsVertex_
{
    void *data;
    VertexColor color;
    int hops;
}BfsVertex;

/* public interface 图里面有adjlists链表，adjlists里面每个元素是一个临界表AdjList和顶点，如果是搜索树顶点时结构体带跳数等 */
int bfs(Graph *graph, BfsVertex *start, List *hops);

#endif /* bsf_h */
