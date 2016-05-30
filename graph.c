#include <stddef.h>
#include "graph.h"

                                          
unsigned int top_sequece[NODE_COUNT];     
                                          
edge_t edges[] =                
{                                         
{"v1one",   "v2two",   0},                
{"v1one",   "v3three", 0},                
{"v1one",   "v4four",  0},                
{"v2two",   "v4four",  0},                
{"v2two",   "v5five",  0},                
{"v3three", "v6six",   0},                
{"v4four",  "v3three", 0},                
{"v4four",  "v6six",   0},                
{"v4four",  "v7seven", 0},                
{"v5five",  "v4four",  0},                
{"v5five",  "v7seven", 0},                
{"v7seven", "v6six",   0}                 
};                                        
                                          
node_t * get_node_in_hash_table(hash_table_t * table, const char * key)
{
    node_t * node = NULL;
    list_node_t * head = NULL;
    list_node_t * pos = NULL;

    head = (list_node_t *)hash_table_get_list(table, key);

    if (head)
    {
        list_for_each(pos, head)
        {
            if (list_entry_key(pos, node_t, hash_table_node, name) == key)
            {
                node = list_entry(pos, node_t, hash_table_node);
                break; 
            }    
        }
    }
    
    return node;
}

node_t * get_node_in_node_pool(node_pool_t * pool, const char * key)
{
    static unsigned int index = 0;
    node_t * node = NULL;

    if (index < pool->node_count)
    {
        node = &pool->nodes_array[index];
        node->name = key;
        node->num  = index + 1;
        index++;
    }
    
    return node; 
}

void init_graph(graph_t * graph, unsigned int node_count)
{
    init_nodes_pool(&graph->node_pool, node_count);
    hash_table_init(&graph->hash_table, node_count);
    init_adjacent_table(&graph->adjacent_table, node_count + 1);
    init_num_name_table(&graph->num_name_table, node_count + 1);
}

node_t * find_node_by_key(graph_t * graph, const char * key)
{
    node_t * node = NULL;

    if (!(node = get_node_in_hash_table(&graph->hash_table, key)))
    {
        node = get_node_in_node_pool(&graph->node_pool, key);
        hash_table_add(&graph->hash_table, &node->hash_table_node, key);
        add_to_num_name_table(&graph->num_name_table, node->num, key); 
    }

    return node;
}

graph_t graph;

int main(int argc, char ** argv)                                                                           
{                                                                                                          
    unsigned int i;  
    node_t * nodeA = NULL;
    node_t * nodeB = NULL;

    init_graph(&graph, 7);
    for(i = 0; i < sizeof(edges)/sizeof(edges[0]); i++)
    {
       nodeA = find_node_by_key(&graph, edges[i].vetexA);
       nodeB = find_node_by_key(&graph, edges[i].vetexB);

       add_to_adjacent_table(&graph.adjacent_table, nodeA->num, &nodeB->adjacent_table_node); 
    } 

    return 0;
}
