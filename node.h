#ifndef NODE_H
#define NODE_H

#include "slist.h"

#define NODE_POOL_SIZE_MAX 10


typedef struct node_s
{
    const char * name;
    unsigned int num;
    int        indegree;
    unsigned long adjacent_tbl_bm;
    list_node_t hash_table_node;
    list_node_t queue_node;
} node_t;

typedef struct node_pool_s
{
    node_t nodes_array[NODE_POOL_SIZE_MAX];
    unsigned int node_count;
} node_pool_t;

void init_node(node_t * node);

void set_node_name(node_t * node, const char * name);

void set_node_num(node_t * node, unsigned int num);

void init_nodes_pool(node_pool_t * pool, unsigned int size);


#endif
