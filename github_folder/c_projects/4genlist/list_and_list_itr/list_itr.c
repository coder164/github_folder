#include <stdlib.h> /* for malloc() in ListItrInsertBefore() */
#include "listinternal.h"

#define IS_EQUALS(a, b) (a == b)

ListItr ListItrBegin(const List* _list)
{
    if (NULL == _list)
    {
        return NULL;
    }
    return _list -> m_head.m_next;
}

ListItr ListItrEnd(const List* _list)
{
    if (NULL == _list)
    {
        return NULL;
    }
    /*return _list -> m_tail.m_prev;*/
    return (void*)&(_list -> m_tail);
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
    return IS_EQUALS(_a, _b);
}

ListItr ListItrNext(ListItr _itr)
{
    if (NULL == _itr) {
        return NULL;
    }
    return ((Node*)_itr) -> m_next;
}

ListItr ListItrPrev(ListItr _itr)
{
    if (NULL == _itr)
    {
        return NULL;
    }
    /* means we are at the begin itr */
    if (((Node*) _itr) == ((Node*)_itr) -> m_prev)
    {
        return _itr;
    }
    return ((Node*)_itr) -> m_prev;
}

void* ListItrGet(ListItr _itr)
{
    if (NULL == _itr || ((Node*)_itr) -> m_next == _itr)
    {
        return NULL;
    }
    return ((Node*)_itr) -> m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
    void* tempData;
    if (NULL == _itr || ((Node*)_itr) -> m_next == _itr ||
        NULL == _element)
    {
        return NULL;
    }
    tempData = ((Node*)_itr) -> m_data;
    ((Node*)_itr) -> m_data = _element;
    return tempData;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node* newNode;
    if (NULL == _itr || NULL == _element)
    {
        return NULL;
    }
	newNode = CreateNode(_element);
	if (NULL == newNode)
    {
		return NULL;
	}
	InsertFunc(newNode, (Node*)_itr);
    return newNode;
}

void* ListItrRemove(ListItr _itr)
{
    void* dataRemoved;
    if (NULL == _itr)
    {
        return NULL;
    }
    if (((Node*)_itr) -> m_next == NULL) /* list is empty */
    {
        return NULL;
    }
    dataRemoved = ((Node*)_itr) -> m_data;
    RemoveFunc((Node*)_itr);
    return dataRemoved;
}





