#ifndef GRAPH_H
#define GRAPH_H

#include "slist.h"
#include "hashtab.h"
#include "node.h"
#include "adjacentab.h"

#define NODE_COUNT_MAX 10 
#define NODE_COUNT     7

typedef struct edge_s
{
    char * vetexA;
    char * vetexB;
    int    weight;
} edge_t;

typedef struct graph_s
{
    node_pool_t      node_pool;
    hash_table_t      hash_table;
    adjacent_table_t  adjacent_table;
    num_name_table_t  num_name_table; 
} graph_t;


#endif
