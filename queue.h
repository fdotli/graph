#ifndef QUEUE_H
#define QUEUE_H

#include "slist.h"


typedef struct queue_s
{
list_node_t * head;
list_node_t * tail;
} queue_t;

void initqueue(queue_t * queue);

int isempty(queue_t * queue);

void enqueue(queue_t * queue, list_node_t * node);

list_node_t * dequeue(queue_t * queue);


#endif
