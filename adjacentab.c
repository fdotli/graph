#include<assert.h>
#include<stddef.h>

#include "adjacentab.h"
#include "bitops.h"


void  init_adjacent_table(adjacent_table_t * table, unsigned int size)
{
    assert(size <= NODE_POOL_SIZE_MAX);
    table->size = size;
}

void init_adjacent_table_node_pool(adjacent_table_node_pool_t * pool, int size)
{
    assert(size <= EDGE_POOL_SIZE_MAX);
    pool->next_index = 0;
}

adjacent_table_node_t * get_next_node(adjacent_table_node_pool_t * pool, unsigned int num)
{
    assert(pool->next_index < EDGE_POOL_SIZE_MAX);

    adjacent_table_node_t * node;

    node = &pool->nodes_array[pool->next_index];
    node->num = num;
    pool->next_index++;

    return node;
}

void add_edge(adjacent_table_t * table, unsigned int vetexA, adjacent_table_node_t * node_vetexB)
{
    assert((vetexA <= table->size) && (node_vetexB->num <= table->size));
    assert(vetexA != node_vetexB->num);

    insert_list_node(&table->bucket[vetexA], &node_vetexB->anchor);
}

void compute_node_indegree(node_pool_t * pool)
{
    unsigned int current_num;
    int i;

    for (current_num = 1; current_num < pool->node_count + 1; current_num++)
    {
        for (i = 0; i < pool->node_count; i++)
        {
            if (current_num == pool->nodes_array[i].num)
                    continue;

            if (test_bit(current_num, &pool->nodes_array[i].adjacent_tbl_bm))
                pool->nodes_array[current_num - 1].indegree++;
        }
    }
}

void init_num_node_table(num_node_table_t * table, unsigned int size)
{
    int i;

    assert(size <= NODE_POOL_SIZE_MAX);

    table->size = size;

    for (i = 0; i < size; i++)
        table->node_array[i] = NULL;
}

void add_to_num_node_table(num_node_table_t * table, unsigned int num, node_t * node)
{
    assert(num < table->size);

    table->node_array[num] = node;
}


