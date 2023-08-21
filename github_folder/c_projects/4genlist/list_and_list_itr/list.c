#include "listinternal.h"
#define OK 0

static void FreeNodes(List** _pList, void (*_elementDestroy)(void* _item));
static ListResult CheckParamsPush(List* _list, void* _item);
static ListResult CheckParamsPop(List* _list, void** _pItem);

List* ListCreate(void) {
	List* ptrNewList;
	ptrNewList = (List *)malloc(sizeof(List));
	if (NULL == ptrNewList)
	{
		return NULL;
	}
	ptrNewList -> m_tail.m_prev = &(ptrNewList -> m_head);
	ptrNewList -> m_head.m_next = &(ptrNewList -> m_tail);
	ptrNewList -> m_head.m_prev = NULL;
	ptrNewList -> m_tail.m_next = NULL;
	return ptrNewList;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	if (NULL == _pList || NULL == *_pList) {
		return;
	}
	FreeNodes(_pList, _elementDestroy);
	free(*_pList);
	*_pList = NULL;
}

ListResult ListPushHead(List* _list, void* _item) {
	Node* newNode;
	ListResult resultCheckParams = CheckParamsPush(_list, _item);
	if (resultCheckParams != OK) {
		return resultCheckParams;
	}
	newNode = CreateNode(_item);
	if (newNode == NULL) {
		return LIST_ALLOCATION_ERROR;
	}
	InsertFunc(newNode, _list -> m_head.m_next);
	return LIST_SUCCESS;
}
ListResult ListPushTail(List* _list, void* _item) {
	Node* newNode;
	ListResult resultCheckParams = CheckParamsPush(_list, _item);
	if (resultCheckParams != OK) {
		return resultCheckParams;
	}
	newNode = CreateNode(_item);
	if (newNode == NULL) {
		return LIST_ALLOCATION_ERROR;
	}
	InsertFunc(newNode, &_list -> m_tail);
	return LIST_SUCCESS;
}

ListResult ListPopHead(List* _list, void** _pItem) {
	ListResult resultCheckParams = CheckParamsPop(_list, _pItem);
	if (resultCheckParams != OK) {
		return resultCheckParams;
	}
	*_pItem = _list -> m_head.m_next -> m_data;
	RemoveFunc(_list -> m_head.m_next);
	return LIST_SUCCESS;
}

ListResult ListPopTail(List* _list, void** _pItem) {
	ListResult resultCheckParams = CheckParamsPop(_list, _pItem);
	if (resultCheckParams != OK) {
		return resultCheckParams;
	}
	*_pItem = _list -> m_tail.m_prev -> m_data;
	RemoveFunc(_list -> m_tail.m_prev);
	return LIST_SUCCESS;
}

size_t ListSize(const List* _list) {
	Node* iNode;
	const register Node* tail = &(_list -> m_tail);
	size_t size = 0;
	if (NULL == _list) {
		return 0;
	}
	iNode = _list -> m_head.m_next;
	while (iNode != tail)
	{
		iNode = iNode -> m_next;
		size++;
	}
	return size;
}

/******************** Assistance Functions ********************/

void RemoveFunc(Node* _node)
{
	_node -> m_next -> m_prev = _node -> m_prev;
	_node -> m_prev -> m_next = _node -> m_next;
	free(_node);
}

Node* CreateNode(void* _item) {
	Node* newNode = (Node *)malloc(sizeof(Node));
	if (NULL == newNode)
	{
		return NULL;
	}
	newNode -> m_data = _item;
	return newNode;
}

void InsertFunc(Node* _p, Node* _t)
{
	_p -> m_prev = _t -> m_prev;
	_p -> m_next = _t;
	_t -> m_prev -> m_next = _p;
	_t -> m_prev = _p;
}

static ListResult CheckParamsPop(List* _list, void** _pItem) {
	if (NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if (NULL == _pItem)
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if (_list -> m_head.m_next == &(_list -> m_tail))
	{
		return LIST_EMPTY;
	}
	return OK;
}

static ListResult CheckParamsPush(List* _list, void* _item) {
	if (NULL == _list) 
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	if (NULL == _item) {
		return LIST_NULL_ELEMENT_ERROR;
	}
	return OK;
}

static void FreeNodes(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* iNode = (*_pList) -> m_head.m_next;
	register Node* tail = &((*_pList) -> m_tail);
	while (iNode != tail)
	{
		if (NULL != _elementDestroy)
		{
			_elementDestroy(iNode -> m_data);
		}
		iNode = iNode -> m_next;
		free(iNode -> m_prev);
	}
}

void* GetHead(List* _list)
{
	return (NULL == _list) ?
		NULL : _list -> m_head.m_next -> m_data;
}

void* GetTail(List* _list)
{
	return (NULL == _list) ?
		NULL : _list -> m_tail.m_prev -> m_data;
}



