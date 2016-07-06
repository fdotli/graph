#include "bstree.h"
#include "slist.h"

typedef struct integer_element_s
{
    unsigned int  integer;
    bstree_node_t bstree_node;
    list_node_t   list_node;
} integer_element_t;

int tree_main(int argc, char ** argv);
