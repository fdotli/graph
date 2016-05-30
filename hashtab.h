#ifndef HASHTAB_H
#define HASHTAB_H

#include <string.h>
#include "slist.h"

#define HASH_TABLE_MAX_SIZE 10

typedef struct hash_table_s
{ 
   list_node_t * buckets[HASH_TABLE_MAX_SIZE];
   unsigned int size;
   unsigned int (* hash_func)(const char *, unsigned int);
} hash_table_t;
 
unsigned int hash(const char * key, unsigned int table_size);

void hash_table_init(hash_table_t * table, unsigned int table_size);

void hash_table_add(hash_table_t * hash_table, list_node_t * node, const char *key);

list_node_t ** hash_table_get_list(hash_table_t * table, const char * key);

#endif
