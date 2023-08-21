#ifndef __LIST_ITR_H__
#define __LIST_ITR_H__

#include "listinternal.h"

typedef void* ListItr;

/** 
 * @brief Get itertator to the list's beginning
 * @param[in] _list: list to return begin iterator, pointing at 
 *                   first element or at the end if list is empty.
 * @return iterator pointing at the list's beginning.
 * @retval NULL if the _list is not initialized. */
ListItr ListItrBegin(const List* _list);

/** 
 * @brief Get itertator to the list end.
 * @param[in] _list: list to return end iterator
 * @return an iterator pointing at the list's end.
 * @retval NULL if the _list is not initialized. */
ListItr ListItrEnd(const List* _list);

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node */
int ListItrEquals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned.
 * @retval NULL if the _itr is not initialized. */
ListItr ListItrNext(ListItr _itr);

/** 
 * @brief Get itertator to the previous element
 * @warning if _itr is begin iterator it will be returned.
 * @retval NULL if the _itr is not initialized. */
ListItr ListItrPrev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 * @param[in] _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing
 *           to the end
 * @retval NULL if the _itr is not initialized. */
void* ListItrGet(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at.
 * @return the data from the node to be changed 
 * @retval NULL if the _itr is not initialized. */
void* ListItrSet(ListItr _itr, void* _element);

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error */
ListItr ListItrInsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 * @param[in] _itr : A list iterator
 * @return the removed data.
 * @retval NULL if the _itr is not initialized. */
void* ListItrRemove(ListItr _itr);


#endif /* __LIST_ITR_H__ */
