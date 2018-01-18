//
//  dfs.c
//  DatastructAndAlgorithm
//
//  Created by Mini on 2018/1/18.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "dfs.h"
#include <stdlib.h>

/* dfs_main */
static int dfs_main(Graph *graph, AdjList *adjlist, List *ordered)
{
    AdjList *crl_adjlist;
    DfsVertext *crl_vertex, *adj_vertex;
    ListElmt *member;
    
    /* color the vertex gray and traverse its adjacency list */
    ((DfsVertext *)adjlist->vertex)->color = gray;
    for (member = list_head(&adjlist->adjacent); member != NULL; member = list_next(member)) {
        /* determine the color of the next adjacent vertex */
        adj_vertex = list_data(member);
        if (graph_adjlist(graph, adj_vertex, &crl_adjlist) != 0) {
            return -1;
        }
        crl_vertex = crl_adjlist->vertex;
        /* move one vertex deeper when the next adjacent vertex is white */
        if (crl_vertex->color == white) {
            if (dfs_main(graph, crl_adjlist, ordered) != 0) {
                return -1;
            }
        }
    }
    
    /* color the current vertex black and make it first in the list */
    ((DfsVertext *)adjlist->vertex)->color = black;
    if (list_ins_next(ordered, NULL, (DfsVertext *)adjlist->vertex) != 0) {
        return -1;
    }
    return 0;
}


int dfs(Graph *graph, List *ordered)
{
    DfsVertext *vertex;
    ListElmt *element;
    
    /* initialize all of the vertices in the graph */
    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {
        vertex = ((AdjList*)list_data(element))->vertex;
        vertex->color = white;
    }
    
    /* perform depth-first search */
    list_init(ordered, NULL);
    for (element = list_head(&graph_adjlists(graph)); element != NULL; element = list_next(element)) {
        /* ensure that every component of unconnected graphs is searched */
        vertex = ((AdjList*)list_data(element))->vertex;
        if (vertex->color == white) {
            if (dfs_main(graph, (AdjList*)list_data(element), ordered) != 0) {
                list_destroy(ordered);
                return -1;
            }
        }
    }
    return 0;
}
