#include<assert.h>
#include<stddef.h>

#include "adjacentab.h"
#include "bitops.h"

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

void init_num_name_table(num_name_table_t * table, unsigned int size)
{
    int i;

    assert(size < NODE_POOL_SIZE_MAX);

    table->table_size = size;

    for (i = 0; i < size; i++)
        table->num_name_array[i] = NULL;
}

void add_to_num_name_table(num_name_table_t * table, unsigned int num, const char * name)
{
    assert(num < table->table_size);

    table->num_name_array[num] = name;
}


