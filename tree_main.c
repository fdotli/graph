#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "tree_main.h"


void add_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp)
{
    bstree_node_t * find_node;
    integer_element_t * head_element, * node_element;


    assert(root && node);

    find_node = bstree_find_node(root, node, cmp);

    head_element = bstree_node_to_element(find_node, integer_element_t, bstree_node);
    node_element = bstree_node_to_element(node,      integer_element_t, bstree_node);

    if (!cmp(find_node, node) && (find_node != node))
    {
        insert_list_node(&head_element->list_node.next, &node_element->list_node);
    }

    if (find_node != node)
    {
        bstree_add_node(find_node, node, cmp);
    }
}

void delete_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp)
{
    bstree_node_t * find_node, * next_node;
    integer_element_t * head_element, * node_element;


    assert(root && node);

    find_node = bstree_find_node(root, node, cmp);

    head_element = bstree_node_to_element(find_node, integer_element_t, bstree_node);
    node_element = bstree_node_to_element(node,      integer_element_t, bstree_node);

    if(!cmp(find_node, node) && (find_node != node))
    {
        delete_list_node(&head_element->list_node.next, &node_element->list_node);
    }

    if (find_node == node)
    {
        if (!head_element->list_node.next)
            bstree_delete_node(find_node, node, cmp);
        else
        {
            node_element = list_entry(head_element->list_node.next, integer_element_t, list_node);
            next_node    = &node_element->bstree_node;

            next_node->parent = find_node->parent;
            next_node->left   = find_node->left;
            next_node->right  = find_node->right;

            find_node->left->parent = find_node->left->parent = next_node;

            if (find_node == find_node->parent->left)
                find_node->parent->left = next_node;

            if (find_node == find_node->parent->right)
                find_node->parent->right = next_node;
        }
    }
}

int cmp(bstree_node_t * a, bstree_node_t * b)
{
    integer_element_t * A, * B;

    A = bstree_node_to_element(a, integer_element_t, bstree_node);
    B = bstree_node_to_element(b, integer_element_t, bstree_node);

    if (A->integer > B->integer)
        return 1;
    else if (A->integer < B->integer)
        return -1;
    else return 0;
}

int tree_main(int argc, char ** argv)
{
    int i;

    bstree_node_t  root = {0};

    integer_element_t element_array[100] = {{0}};

    srand(1);

    for(i = 0; i < 100; i++)
    {
        element_array[i].integer = rand() % 100;
        add_node(&root, &element_array[i].bstree_node, cmp);
    }

    for(i = 0; i < 100; i++)
    {
        delete_node(&root, &element_array[i].bstree_node, cmp);
    }

    return 0;
}
