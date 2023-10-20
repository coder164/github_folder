#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>  /* for size_t */

/*Author:	coder164
* Purpose:	To generalize the vector program to handle with all
*			kinds of data types.
* Date:		21-12-22
*/

typedef struct Vector Vector;
typedef int	(*VectorElementAction)(void* _element, size_t _index, void* _context);
typedef enum Vector_Result {
	VECTOR_SUCCESS,
	VECTOR_GENERAL_ERROR,				/* for errors that not mentioned*/
	VECTOR_UNITIALIZED_ERROR,			/* if input pointer is null */
	VECTOR_ALLOCATION_ERROR,			/* if allocation failed */
	VECTOR_REALOCATION_ERROR,			/* if realocation failed */
	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR,
	VECTOR_UNDERFLOW_ERROR,
	VECTOR_OVERFLOW_ERROR,
	VECTOR_WRONG_INDEX,
	VECTOR_OK
} VectorResult;

/*
description:	create a new vector object.
arguments:		_initialCapacity: the initial number of elements that
								   the vector can store.
				_blockSize: the size of extention block if the vector
							 is full. also the size to be removed in 
							 shrinkage of the vector.
return value:	the pointer of the new vector
errors:			NULL - if _initialCapacity = 0 and _blockSize = 0;
					 - if allocation failed.*/
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize);

/*
description:	deallocate the vector and all of its members.
arguments:		_vector: the vector to be destroyed
				_elementDestroy: A function pointer to be used to destroy
								all the elements of vector. it can also be
								null if no such destroy is required.
return value:	none.*/
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void* _item));

/*
description:	add an item to the end of the vector.
arguments:		- _vector: Vector.
				- _item: item to add.
return value:	- VECTOR_OK: if appending succeeded.
errors:			- VECTOR_UNITIALIZED_ERROR - if _vector invalid.
										   - if _item invalid.
				- VECTOR_REALOCATION_ERROR - if realoc failed.
				- VECTOR_OVERFLOW_ERROR - if blocksize defined '0'
										  and the vectur is full.*/
VectorResult VectorAppend(Vector* _vector, void* _item);

/*
description:	deletes the last data of the Vector and saves it in 
				'_pValue'
arguments:		- _vector: Vector
				- _pValue: pointer to pointer of variable for the
							saved data
return value:	- VECTOR_OK - if succeeded
errors:			- VECTOR_UNITIALIZED_ERROR - if 'vector' invalid
										  - if _pValue invalid
				- VECTOR_UNDERFLOW_ERROR - if _vector is empty */
VectorResult VectorRemove(Vector* _vector, void** _pValue);

/*
description:	get the value of element inside the vector by index and save it
				in '_pValue'
arguments:		_vector: Vector
				_index: position inside the vector
				_pValue: pointer to pointer of variable for the
						 saved data
return value:	VECTOR_OK
errors:			VECTOR_UNITIALIZED_ERROR - invalid vector address
				VECTOR_WRONG_INDEX - when _index > number of items */
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue);

/*
description:	set the value of element inside the Vector by index.
arguments:		_vector: Vector.
				_index: position isnside the vector.
				_value: pointer to the new variable to set.
return value:	VECTOR_OK.
errors:			VECTOR_UNITIALIZED_ERROR - invalid vector address
				VECTOR_WRONG_INDEX - when _index > number of items */
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value);

/*
description:	Get the number of actual items currently in the vector.
arguments:		_vector: Vector.
return value:	number of items on success.
error:			0 - if vector is empty or invalid */
size_t VectorSize(const Vector* _vector);

/*
description:	Get the current capacity of the  vector.
arguments:		_vector - Vector.
return value:	the capacity of the vector
error:			0 - if vector is empty or invalid */
size_t VectorCapacity(const Vector* _vector);

/*
description:	Iterate over all elements in the vector and execute the
				provided action.
arguments:		_vector - vector to be iterated over.
				_action - generic function to be invoked at each iteration.
				_context - the pointer to be sent to the _action function.
return value:	the count number of iterations that was done here. 
equivalent to:	for(i = 0; i < VectorSize(v); ++i){
					VectorGet(v, i, &elem);
					if(_action(elem, i, _context) == 0)
					break;} return i} 
error:			0 - if _vector or _action is invalid */
size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context);


#endif /* #ifndef __VECTOR_H__ */
