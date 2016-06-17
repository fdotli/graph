#include <stddef.h>
#include "queue.h"


void initqueue(queue_t * queue)
{
    queue->head = queue->tail = NULL;
}

void enqueue(queue_t * queue, list_node_t * node)
{
    assert(queue && node);

    if (!queue->head)
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        node->next = NULL;
        queue->tail.next = node;
        queue->tail = node;
    }
}

int isempty(queue_t * queue)
{
    assert(queue);

    return(((queue->head == queue->tail) && !queue->head) ? 1 : 0);
}

list_node_t * dequeue(queue_t * queue)
{
    assert(queue);

    list_node_t * head;

    head = queue->head;

    if (head->next)
        queue->head = head->next;
    else
        queue->head = queue->tail = NULL;

    return head;  
}
