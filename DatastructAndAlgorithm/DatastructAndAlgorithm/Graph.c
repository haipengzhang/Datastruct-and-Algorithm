//
//  Graph.c
//  DatastructAndAlgorithm
//
//  Created by Jimzhang on 2018/1/17.
//  Copyright © 2018年 haipeng. All rights reserved.
//

#include "Graph.h"
#include <stdlib.h>
#include <string.h>

void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;
    list_init(&graph->adjlists, NULL);
    return;
}

void graph_destroy(Graph *graph)
{
    AdjList *adjlist;
    /* remove each adjacency-list structure and destroy its adjacency list */
    while (list_size(&graph->adjlists) > 0) {
        if (list_rem_next(&graph->adjlists, NULL, (void **)&adjlist) == 0) {
            set_destroy(&adjlist->adjacent);
            if (graph->destroy != NULL) {
                graph->destroy(adjlist->vertex);
            }
            free(adjlist);
        }
    }
    
    /* destroy the list of the adjacency-list structure, which is now empty */
    list_destroy(&graph->adjlists);
    memset(graph, 0, sizeof(Graph));
    return;
}

int graph_ins_vertex(Graph *graph, const void *data)
{
    ListElmt *element;  //data part is AdjList type;
    AdjList *adjlist;
    int retval;
    
    /* do not insert duplicate vertices */
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data, ((AdjList *)list_data(element))->vertex)) {
            return 1;
        }
    }
    /* insert the vertex */
    if ((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL) {
        return -1;
    }
    adjlist->vertex = (void *)data;
    set_init(&adjlist->adjacent, graph->match, NULL);
    if ((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists), adjlist)) != 0) {
        return retval;
    }
    graph->vcount++;
    return 0;
}

int graph_ins_edge(Graph *graph, const void *data1, const void *data2)
{
    ListElmt *element;  //data part is AdjList type;
    int retval;
    
    /* do not insert an edge without both its vertices in the graph */
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data2, ((AdjList *)list_data(element))->vertex)) {
            break;
        }
    }
    if (element == NULL) {
        return -1;
    }
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data1, ((AdjList *)list_data(element))->vertex)) {
            break;
        }
    }
    if (element == NULL) {
        return -1;
    }
    /* insert the second vertex into the adjacency list of the first vertex */
    if ((retval = set_insert(&((AdjList *)list_data(element))->adjacent, data2)) != 0) {
        return retval;
    }
    graph->ecount++;
    return 0;
}

int graph_rem_vertex(Graph *graph, void **data)
{
    ListElmt *element, *temp, *prev;
    AdjList *adjlist;
    int found;
    
    /* traverse each adjacency list and the vertices it contains */
    prev = NULL;
    found = 0;
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        /* do not allow removal of the vertex if it is in an adjacency list */
        if (set_is_member(&((AdjList *)list_data(element))->adjacent, *data)) {
            return -1;
        }
        /* keep a pointer to the vertex to be removed */
        if (graph->match(*data, ((AdjList *)list_data(element))->vertex)) {
            temp = element;
            found = 1;
        }
        /* keep a pointer to the vertex before the vertex to be removed */
        if (!found) {
            prev = element;
        }
    }
    
    if (!found) {
        return -1;
    }
    /* do not removal of the vertex if its adjacency list is not empty */
    if (set_size(&((AdjList *)list_data(element))->adjacent) > 0) {
        return -1;
    }
    if (list_rem_next(&graph->adjlists, prev, (void **)&adjlist) != 0) {
        return -1;
    }
    *data = adjlist->vertex;
    free(adjlist);
    graph->vcount--;
    return 0;
}

int graph_rem_edge(Graph *graph, void *data1, void **data2)
{
    ListElmt *element;
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data1, ((AdjList *)list_data(element))->vertex)) {
            break;
        }
    }
    if (element == NULL) {
        return -1;
    }
    /* remove the second vertex from the adjacency list of the first vertex */
    if (set_remove(&((AdjList *)list_data(element))->adjacent, data2) != 0) {
        return -1;
    }
    graph->ecount--;
    return 0;
}

int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist)
{
    ListElmt *element, *prev;
    prev = NULL;
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data, ((AdjList *)list_data(element))->vertex)) {
            break;
        }
        prev = element;
    }
    if (element == NULL) {
        return -1;
    }
    *adjlist = list_data(element);
    return 0;
}

int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2)
{
    ListElmt *element, *prev;
    prev = NULL;
    for (element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if (graph->match(data1, ((AdjList *)list_data(element))->vertex)) {
            break;
        }
        prev = element;
    }
    return set_is_member(&((AdjList *)list_data(element))->adjacent, data2);
}
