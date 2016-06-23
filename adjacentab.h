#ifndef ADJACENTAB_H
#define ADJACENTAB_H

#include "slist.h"
#include "node.h"

#define EDGE_POOL_SIZE_MAX  (NODE_POOL_SIZE_MAX * (NODE_POOL_SIZE_MAX - 1))

typedef struct adjacent_table_node_s
{
    unsigned int  num;
    list_node_t   anchor;
} adjacent_table_node_t;

typedef struct adjacent_table_s
{
    list_node_t * bucket[NODE_POOL_SIZE_MAX];
    unsigned int  size;
} adjacent_table_t;

typedef struct adjacent_table_node_pool_s
{
    adjacent_table_node_t  nodes_array[EDGE_POOL_SIZE_MAX];
    unsigned int next_index;
} adjacent_table_node_pool_t;

typedef struct num_name_table_s
{
   const char * num_name_array[NODE_POOL_SIZE_MAX];
   unsigned int table_size;
} num_name_table_t;

void init_adjacent_table(adjacent_table_t * table, unsigned int size);

void init_adjacent_table_node_pool(adjacent_table_node_pool_t * pool, int size);

adjacent_table_node_t * get_next_node(adjacent_table_node_pool_t * pool, unsigned int num);

void add_edge(adjacent_table_t * table, unsigned int vetexA, adjacent_table_node_t * node_vetexB);

void compute_node_indegree(node_pool_t * pool);

void init_num_name_table(num_name_table_t * table, unsigned int size);

void add_to_num_name_table(num_name_table_t * table, unsigned int num, const char * name);

#endif
