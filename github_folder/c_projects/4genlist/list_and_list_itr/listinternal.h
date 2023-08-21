#ifndef __LIST_INTERNAL_H__
#define __LIST_INTERNAL_H__

#include "list.h"
#include "list_itr.h"

typedef struct Node Node;

struct Node {
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List {
	Node m_head;	/* gatekeeper from left */
	Node m_tail;	/* gatekeeper from right */
};

/******************* additional help functions ********************/

Node* CreateNode(void* _item);

void* GetHead(List* _list);

void* GetTail(List* _list);

void InsertFunc(Node* _t, Node* _p);

void RemoveFunc(Node* _node);

/*
description:	get the node at the head of the list for tests.
arguments: 		- _list - address to the list.
return value:	the node at the head of the list.
errors: 		- NULL - if _list is invalid */
void* GetHead(List* _list);

/*
description:	get the node at the tail of the list for tests.
arguments: 		- _list - address to the list.
return value:	the node at the tail of the list.
errors: 		- NULL - if _list is invalid */
void* GetTail(List* _list);


#endif /* __LIST_INTERNAL_H__ */
