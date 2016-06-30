#ifndef SLIST_H
#define SLIST_H

typedef struct list_node_t
{
    struct list_node_t * next;
} list_node_t;

void init_list_node(list_node_t * node);

void insert_list_node(list_node_t ** list, list_node_t * node);

#ifndef offsetof

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif

#ifndef container_of

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#endif

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos ; pos = pos->next)

#define list_entry(ptr, type, member) ((ptr) ? container_of(ptr,type,member) : 0)

#define list_entry_key(ptr, type, member, key) (list_entry(ptr, type, member)->key)

#define LIST_NODE_INIT(node) init_list_node(node)


#endif
