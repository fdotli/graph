#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_s
{
list_node_t * head;
list_node_t * tail;
} queue_t;

void enqueue(queue_t * queue, list_node_t * node);

list_node_t * dequeue(queue_t * queue);


#endif
