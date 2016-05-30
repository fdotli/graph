#include <stddef.h>
#include <assert.h>
#include "node.h"

void init_node(node_t * node)
{
    node->name = NULL;
    node->num  = 0;
    LIST_NODE_INIT(&node->adjacent_table_node);
    LIST_NODE_INIT(&node->hash_table_node);
}

void set_node_name(node_t * node, const char * name)
{
    node->name = name;
}

void set_node_num(node_t * node, unsigned int num)
{
    node->num = num;
}

void init_nodes_pool(node_pool_t * pool, unsigned int size)
{
    int i;

    assert(size <= NODE_POOL_SIZE_MAX);
 
    pool->node_count = size;

    for(i = 0; i < pool->node_count; i++)
        init_node(&pool->nodes_array[i]); 
}


