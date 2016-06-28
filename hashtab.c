#include <assert.h>
#include <stddef.h>

#include "hashtab.h"
#include "slist.h"

unsigned int hash(const char * key, unsigned int table_size)
{
    unsigned int hash_val = 0;

    key++;
    while( *key != '\0')
    {
        hash_val = (hash_val << 5) + *key++;
    }

    return hash_val % table_size;
}

void hash_table_init(hash_table_t * table, unsigned int size)
{
    int i;

    assert(size < HASH_TABLE_MAX_SIZE);

    table->size = size;
    table->hash_func = hash;

    for(i = 0; i < table->size; i++)
        table->buckets[i] = NULL;
}

void hash_table_add(hash_table_t * table, list_node_t * node, const char *key)
{
    insert_list_node(&table->buckets[table->hash_func(key, table->size)], node);
}

list_node_t ** hash_table_get_list(hash_table_t * table, const char * key)
{
    return &table->buckets[table->hash_func(key, table->size)];
}
