#ifndef ADJACENTAB_H
#define ADJACENTAB_H

#include "slist.h"
#include "node.h"

typedef struct adjacent_table_s
{
   list_node_t * adjacent_array[NODE_POOL_SIZE_MAX];
   unsigned int table_size; 
} adjacent_table_t;

typedef struct num_name_table_s
{
   const char * num_name_array[NODE_POOL_SIZE_MAX];
   unsigned int table_size; 
} num_name_table_t;

void init_adjacent_table(adjacent_table_t * table, unsigned int size);

void add_to_adjacent_table(adjacent_table_t * table, unsigned int num, list_node_t * node);

void init_num_name_table(num_name_table_t * table, unsigned int size);

void add_to_num_name_table(num_name_table_t * table, unsigned int num, const char * name);
#endif
