//
//  Graph.h
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/17.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"
#include "Set.h"

/* define a structure for adjacency lists(邻接表) */
typedef struct AdjList_
{
    void *vertex;
    Set adjacent;
} AdjList;

/* define a structure for graphs */
typedef struct graphs_
{
    int vcount;
    int ecount;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    List adjlists;  //not pointer (element is AdjList, and set in AdjList)
} Graph;

/* define colors for vertices in graphs */
typedef enum VertexColor_{
    white,
    gray,
    black
}VertexColor;

/* public interface */
void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));
void graph_destroy(Graph *graph);
int graph_ins_vertex(Graph *graph, const void *data);
int graph_ins_edge(Graph *graph, const void *data1, const void *data2);
int graph_rem_vertex(Graph *graph, void **data);
int graph_rem_edge(Graph *graph, void *data1, void **data2);
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);

#define graph_adjlists(graph) ((graph)->adjlists)
#define graph_vcount(graph) ((graph)->vcount)
#define graph_ecount(graph) ((graph)->ecount)

#endif /* Graph_h */
