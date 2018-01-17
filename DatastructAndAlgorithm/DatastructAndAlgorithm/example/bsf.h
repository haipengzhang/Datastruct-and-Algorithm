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

/* public interface */
int bfs(Graph *graph, BfsVertex *start, List *hops);

#endif /* bsf_h */
