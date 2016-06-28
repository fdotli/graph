#ifndef GRAPH_H
#define GRAPH_H

#include "slist.h"
#include "hashtab.h"
#include "node.h"
#include "adjacentab.h"

#define NODE_COUNT_MAX 10

typedef struct edge_s
{
    char * vetexA;
    char * vetexB;
    int    weight;
} edge_t;

typedef struct graph_s
{
    unsigned int      vetex_count;
    unsigned int      edge_count;
    node_pool_t       node_pool;
    hash_table_t      hash_table;
    num_node_table_t  num_node_table;
    adjacent_table_t  adjacent_table;
    adjacent_table_node_pool_t adjacent_table_node_pool;
} graph_t;

typedef struct top_sequence_s
{
    unsigned int top_array[NODE_COUNT_MAX];
    unsigned int cur_pos;
} top_sequence_t;

#endif
