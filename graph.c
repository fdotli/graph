#include <stddef.h>
#include <assert.h>
#include "graph.h"
#include "bitmap.h"
#include "queue.h"



edge_t edges[] =
{
{"v1one",   "v2two",   0},
{"v1one",   "v4four",  0},
{"v2two",   "v4four",  0},
{"v2two",   "v5five",  0},
{"v3three", "v1one",   0},
{"v3three", "v6six",   0},
{"v4four",  "v3three", 0},
{"v4four",  "v5five",  0},
{"v4four",  "v6six",   0},
{"v4four",  "v7seven", 0},
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

void init_graph(graph_t * graph, unsigned int node_count, unsigned int edge_count)
{
    init_nodes_pool(&graph->node_pool, node_count);
    hash_table_init(&graph->hash_table, node_count);
    init_adjacent_table(&graph->adjacent_table, node_count + 1);
    init_adjacent_table_node_pool(&graph->adjacent_table_node_pool, edge_count);
    init_num_node_table(&graph->num_node_table, node_count + 1);
}

node_t * find_node_by_key(graph_t * graph, const char * key)
{
    node_t * node = NULL;

    if (!(node = get_node_in_hash_table(&graph->hash_table, key)))
    {
        node = get_node_in_node_pool(&graph->node_pool, key);
        graph->vetex_count++;
        hash_table_add(&graph->hash_table, &node->hash_table_node, key);
        add_to_num_node_table(&graph->num_node_table, node->num, node);
    }

    return node;
}

void top_sort(graph_t * graph, queue_t * queue, top_sequence_t * top_sequence)
{
    int i;

    for (i = 0; i < graph->vetex_count; i++)
    {
        node_t * node = &graph->node_pool.nodes_array[i];

        if (!node->indegree)
        enqueue(queue, &node->queue_node);
    }

    while(!isempty(queue))
    {
        node_t * dequeue_node;
        list_node_t * adjacent_anchor;

        dequeue_node = list_entry(dequeue(queue), node_t, queue_node);
        top_sequence->top_array[top_sequence->cur_pos++] = dequeue_node->num;

        adjacent_anchor = graph->adjacent_table.bucket[dequeue_node->num];

        while(adjacent_anchor)
        {
            adjacent_table_node_t * adjacent_table_node;
            node_t * node;

            adjacent_table_node = list_entry(adjacent_anchor, adjacent_table_node_t, anchor);

            node = graph->num_node_table.node_array[adjacent_table_node->num];
            if(!--node->indegree)
                enqueue(queue, &node->queue_node);

            adjacent_anchor = adjacent_anchor->next;
        }
    }
}

void compute_shortest_path(graph_t * graph, queue_t * queue, const char * start)
{
    adjacent_table_node_t * adjacent_table_node;
    node_t * node = NULL;

    assert(start);


    node = find_node_by_key(graph, start);

    if(node)
    {
        node->known = true;
        node->distance = 0;
        node->pre_num = 0;
    }

    enqueue(queue, &node->queue_node);

    while(!isempty(queue))
    {
        unsigned int pre_num = 0;
        list_node_t * dequeue_list_node;
        unsigned int distance;

        dequeue_list_node = dequeue(queue);
        node = list_entry(dequeue_list_node, node_t, queue_node);
        pre_num = node->num;
        distance = node->distance;

        adjacent_table_node = list_entry(graph->adjacent_table.bucket[node->num], adjacent_table_node_t, anchor);
        while(adjacent_table_node)
        {
            list_node_t * next;
            node = graph->num_node_table.node_array[adjacent_table_node->num];

            if (!node->known || node->distance > (distance + 1))
            {
                node->known = true;
                node->distance = distance + 1;
                node->pre_num = pre_num;

                enqueue(queue, &node->queue_node);
            }

            next = adjacent_table_node->anchor.next;

            adjacent_table_node = list_entry(next, adjacent_table_node_t, anchor);
        }
    }
}

graph_t graph;

queue_t queue = {NULL, NULL};

top_sequence_t top_sequence = {{0}, 0};

int main(int argc, char ** argv)
{
    unsigned int i;
    node_t * nodeA = NULL;
    node_t * nodeB = NULL;
    adjacent_table_node_t * adjacent_node;

    init_graph(&graph, 7, 48);
    for(i = 0; i < sizeof(edges)/sizeof(edges[0]); i++)
    {
       nodeA = find_node_by_key(&graph, edges[i].vetexA);
       nodeB = find_node_by_key(&graph, edges[i].vetexB);

       bitmap_set(&nodeA->adjacent_tbl_bm, nodeB->num, 1);
       nodeB->indegree++;

       adjacent_node = get_next_node(&graph.adjacent_table_node_pool, nodeB->num);
       add_edge(&graph.adjacent_table, nodeA->num, adjacent_node);
       graph.edge_count++;
    }

    //top_sort(&graph, &queue, &top_sequence);

    //compute_node_indegree(&graph.node_pool);

    compute_shortest_path(&graph, &queue, "v3three");

    return 0;
}
