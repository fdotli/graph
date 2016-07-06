#include <assert.h>
#include <stddef.h>
#include "bstree.h"


bstree_node_t * bstree_find_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp)
{
    assert(root && node);

    if (cmp(root, node) > 0)
    {
        if (root->left)
            return bstree_find_node(root->left, node, cmp);
        else
            return root;
    }
    else if (cmp(root, node) < 0)
    {
        if (root->right)
            return bstree_find_node(root->right, node, cmp);
        else
            return root;
    }
    else return root;
}

bstree_node_t * bstree_find_node_max(bstree_node_t * root)
{
    assert(root);

    if (root->right)
        return bstree_find_node_max(root->right);
    else
        return root;
}

bstree_node_t * bstree_find_node_min(bstree_node_t * root)
{
     assert(root);

     if (root->left)
         return bstree_find_node_min(root->left);
     else
         return root;
}

void bstree_add_node(bstree_node_t * find_node, bstree_node_t * node, cmp_t cmp)
{
    assert(find_node && node);


    if (cmp(find_node, node) > 0)
    {
        find_node->left = node;
        node->parent    = find_node;
    }
    else if (cmp(find_node, node) < 0)
    {
        find_node->right = node;
        node->parent    = find_node;
    }
}

int bstree_exist(bstree_node_t * root, bstree_node_t * node, cmp_t cmp)
{
    bstree_node_t * find_node;

    assert(root && node);

    find_node = bstree_find_node(root, node, cmp);

    if (!cmp(find_node, node) && (find_node != node))
        return 0;

    if (cmp(find_node, node))
        return 0;

    return 1;
}

void bstree_delete_node(bstree_node_t * root, bstree_node_t * node, cmp_t cmp)
{
    bstree_node_t * find_node;

    assert(root && node);

    if (!node->left && !node->right)
    {
        node->parent = NULL;
    }
    else if (!node->left)
    {
        if (node == node->parent->left)
        {
            node->parent->left  = node->right;
            node->right->parent = node->parent;
        }
        else
        {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
    }
    else if (!node->right)
    {
        if (node == node->parent->left)
        {
            node->parent->left  = node->left;
            node->left->parent  = node->parent;
        }
        else
        {
            node->parent->right = node->left;
            node->left->parent  = node->parent;
        }
    }
    else
    {
        find_node = bstree_find_node_min(node->right);

        find_node->parent->left = NULL;

        find_node->left   = node->left;
        find_node->right  = node->right;
        find_node->parent = node->parent;

        find_node->left->parent  = find_node;
        find_node->right->parent = find_node;

        node->left = node->right = node->parent = NULL;
    }
}


