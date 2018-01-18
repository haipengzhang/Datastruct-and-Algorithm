//
//  dfs.h
//  DatastructAndAlgorithm
//
//  Created by Mini on 2018/1/18.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef dfs_h
#define dfs_h

/* 深度优先搜索 */
#include <stdio.h>
#include "LinkList.h"
#include "Graph.h"

/* define a structure for vertices in a depth-first search */
typedef struct DfsVertext_{
    void *data;
    VertexColor color;
}DfsVertext;

/* public interface */
int dfs(Graph *graph, List *ordered);

#endif /* dfs_h */
