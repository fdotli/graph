#include <stddef.h>
#include "slist.h"

void init_list_node(list_node_t * node)
{
    node->next = NULL;
}

void insert_list_node(list_node_t ** list, list_node_t * node)
{
    if ((!list) || (!node))
        return;

    if (!*list)
    {
        *list = node;
    }
    else
    {
    node->next = *list;
    *list = node;
    }
}

void delete_list_node(list_node_t ** list, list_node_t * node)
{
    list_node_t * iter, * prev;

    if ((!list) || (!node))
        return;

    iter = *list;
    prev = (list_node_t *)list;

    while(iter)
    {
         if (iter == node)
         {
            prev->next = iter->next;
            break;
         }

         prev = iter;
         iter = iter->next;
    }
}
