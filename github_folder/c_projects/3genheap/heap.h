#ifndef __GENHEAP_H__
#define __GENHEAP_H__
#include "vector.h" 

typedef enum HeapResultCode {
	HEAP_SUCCESS = 0,
	HEAP_NOT_INITIALIZED,
	HEAP_OVERFLOW,
	HEAP_REALLOCATION_FAILED,
	HEAP_INVALID_ITEM
} HeapResultCode;

typedef struct Heap Heap;
typedef int	(*ActionFunction)(const void *_elem, void *_context);
typedef int	(*LessThanComparator)(const void *_left,
	const void *_right);

/**  
 * @brief Dynamically create a new heap.
 * 			the creation of the heap is of of empty vector is O(nlogn).
 * 			when there are a given vector of elements then it only needs to
 * 			heapify and the complexity of heapify is of O(n).
 * @param[in] _vector - Vector that holds the elements, must be initialized.
 * @param[in] _pfLess - generic function to be used to compare elements .
 * @return Heap * - on success.
 * @retval NULL on fail .
 * @warning allocating and freeing the underlying vector is user
 * 			responsibility. */
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess);

/**  
 * @brief Deallocate a previously allocated heap.
 * @details Frees the heap but not the underlying vector.
 * @param[in] _heap - Heap to be deallocated.  On success will be nulled.
 * @return Underlying vector. */
Vector* HeapDestroy(Heap** _heap);

/**  
 * @brief Add an element to the Heap preserving heap property.
 * 			the insertion complexity is of O(log2n) 
 * @param[in] _heap - Heap to insert element to.
 * @param[in] _element - Element to insert.
 * @return success or error code.
 * @retval HEAP_OK, on success.
 * @retval HEAP_NOT_INITIALIZED error, heap not initilized.
 * @retval HEAP_OVERFLOW error, the item could not be inserted because
 * 			of vector overflow.
 * @retval HEAP_REALLOCATION_FAILED error, heap could not reallocate
 * 			the underlying vector. */
HeapResultCode HeapInsert(Heap* _heap, void* _element);

/**  
 * @brief copy the max (or min) value in the heap to the given item.  
 * @param[in] _heap - the heap.
 * @param[in] _item - the item to store the copy of the peek element.
 * @return success or error code. */
HeapResultCode HeapPeek(const Heap* _heap, void* _item);

/**  
 * @brief Extract element on top of heap and remove it.  
 * 			the extraction complexity is of O(nlogn)
 * @param[in] _heap - Heap to extract from.
 * @return pointer to element, can be null if heap is empty. */
void* HeapExtract(Heap* _heap);

/**  
 * @brief Get the current size (number of elements) in the heap.  
 * @param[in] _heap - Heap to extract from.
 * @return the number of total elements in the heap.
 * @retval zero if empty or NULL. */
size_t HeapSize(const Heap* _heap);

/**  
 * @brief Iterate over all elements in the heap from top to bottom.
 * @details The user provides an ActionFunction, _act will be called
 * 			for each element.
 * @param[in] _heap - Heap to iterate over.
 * @param[in] _act - User provides function pointer to be avoked for
 * 					each element.
 * @param[in] _context - pointer to be sent to the _action function.
 * @returns number of times the user functions was invoked.
 * @retval 0 if _heap is invalid or _act is invalid. */
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context);


#endif /*__GENHEAP_H__*/
