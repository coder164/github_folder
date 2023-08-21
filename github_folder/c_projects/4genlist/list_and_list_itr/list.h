#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h> /* for size_t */

typedef struct List List;
typedef enum ListResult {
	LIST_SUCCESS,
	LIST_UNINITIALIZED_ERROR,	/* Uninitialized list */
	LIST_ALLOCATION_ERROR,
	LIST_NULL_ELEMENT_ERROR,
	LIST_EMPTY
} ListResult;

/** 
 * @brief Create a new list.
 * @param[in] none.
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure. */
List* ListCreate(void);

/** 
 * @brief Destroy list
 * @details Destroys the list completely. Optionally destroys
 * 			elements using user provided function.
 * @param[in] _pList - A pointer to previously created List returned
 * 				via ListCreate on completion *_pList will be null.
 * @param[in] _elementDestroy - A function pointer to be used to
 * 				destroy elements inserted into the list. Or a null
 * 				if no such destroy is required. */
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));

/** 
 * @brief Add element to the head of the list.
 * @details time complexity: O(1).
 * @param _list A previously created List.
 * @param _item An item to add to the list.
 * @returns error code.
 * @retval LIST_SUCCESS on success.
 * @retval LIST_UNINITIALIZED_ERROR if the _list is not initialized.
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL.
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure. */
ListResult ListPushHead(List* _list, void* _item);

/** 
 * @brief Add element to the list's tail.
 * @details time complexity O(1).
 * @param _list A previously created List.
 * @param _item An item to add to the list.
 * @returns error code.
 * @retval LIST_SUCCESS on success.
 * @retval LIST_UNINITIALIZED_ERROR if the _list is not
 * 			initialized.
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL.
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure. */
ListResult ListPushTail(List* _list, void* _item);

/*
description:	Remove element from list's head.
detailes:		if successfull, stores a pointer to the removed
				item in _item. time complexity O(1).
arguments: 		- _list - address of the list.
				- _pItem - pointer to pointer to store the data.
return value: 	- LIST_SUCCESS
errors: 		- LIST_UNINITIALIZED_ERROR - if _list is invalid.
				- LIST_NULL_ELEMENT_ERROR - if _pItem is invalid.
				- LIST_EMPTY - if the list is empty.
*/
ListResult ListPopHead(List* _list, void** _pItem);

/*
description:	Remove element from list's tail.
detailes:		if successfull, stores a pointer to the removed
				item in _item. time complexity O(1).
arguments: 		- _list - address of the list.
				- _pItem - pointer to pointer to store the data.
return value: 	- LIST_SUCCESS
errors: 		- LIST_UNINITIALIZED_ERROR - if _list is invalid.
				- LIST_NULL_ELEMENT_ERROR -  if _pItem is invalid.
				- LIST_EMPTY - if the list is empty.
*/
ListResult ListPopTail(List* _list, void** _pItem);

/*
description:	Count all the members in the list.
details:		Average time complexity O(n).
arguments: 		- _list - address of the list
return value:	The amount of total members
errors: 		- LIST_UNINITIALIZED_ERROR - if _list is invalid */
size_t ListSize(const List* _list);


#endif /* __LIST_H__ */
