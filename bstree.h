#ifndef BSTREE_H
#define BSTREE_H

#include "slist.h"


typedef struct bstree_node_s
{
    struct bstree_node_s * parent;
    struct bstree_node_s * left;
    struct bstree_node_s * right;
} bstree_node_t;

typedef int (* cmp_t)(bstree_node_t * a, bstree_node_t * b);

#define bstree_node_to_element(ptr, type, member) container_of(ptr, type, member)

bstree_node_t * bstree_find_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp);

bstree_node_t * bstree_find_node_max(bstree_node_t * root);

bstree_node_t * bstree_find_node_min(bstree_node_t * root);

void bstree_add_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp);

void bstree_delete_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp);

#endif
