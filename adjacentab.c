#include<assert.h>
#include<stddef.h>

#include "adjacentab.h"

void init_adjacent_table(adjacent_table_t * table, unsigned int size)
{
    int i;

    assert(size  < NODE_POOL_SIZE_MAX);

    table->table_size = size;

    for (i = 0; i < size; i++)
        table->adjacent_array[i] = NULL;
}

void add_to_adjacent_table(adjacent_table_t * table, unsigned int num, list_node_t * node)
{
    insert_list_node(&table->adjacent_array[num], node);
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


