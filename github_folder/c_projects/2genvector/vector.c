#include <stdio.h> /* for size_t */
#include <stdlib.h> /* for allocations */
#include "vector.h"
#define DECREASE_FACTOR 2

/* declaring assistant functions for testing */
size_t GetVecOrigSize(Vector* _vector);
size_t GetVecSize(Vector* _vector);
size_t GetVecNItems(Vector* _vector);
size_t GetVecBlockSize(Vector* _vector);

/* declaring other assistant functions */
static Vector* ExecuteCreate(size_t _initialCapacity, size_t _blockSize);
VectorResult ReallocateVectorAdd(Vector *_vector);
void RealocateVectorDelete(Vector *_vector);

struct Vector {
	void** m_items;
	size_t m_originalSize;	/* original allocated space for items */
	size_t m_size;			/* actual allocated space for items */
	size_t m_nItems;		/* actual number of items */
	size_t m_blockSize;		/* the additional or srinkage size to be 
							   allocated or freed when needed*/
};

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize) {
	Vector* newVector;
	if (_initialCapacity == 0 && _blockSize == 0)
	{
		return NULL;
	}
	newVector = ExecuteCreate(_initialCapacity, _blockSize);
	return newVector;
}

void VectorDestroy(Vector** _vector,
	void (*_elementDestroy)(void* _item))
{
	size_t i;
	if (NULL == _vector || NULL == (*_vector))
	{
		return;
	}
	if (_elementDestroy != NULL)
	{
		for (i = 0; i < ((*_vector) -> m_nItems); ++i)
		{
			_elementDestroy((*_vector) -> m_items[i]);
		}
	}
	free((*_vector) -> m_items);
	free(*_vector);
	*_vector = NULL;
}

VectorResult VectorAppend(Vector* _vector, void* _item)
{
	VectorResult status;
	if (NULL == _vector || NULL == _item) 
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if (_vector -> m_size == _vector -> m_nItems) 
	{
		status = ReallocateVectorAdd(_vector);
		if (VECTOR_OK != status) 
		{
			return status;
		}
	}
	_vector -> m_items[_vector -> m_nItems] = _item;
	_vector -> m_nItems++;
	
	return VECTOR_OK;
}

VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	if (NULL == _vector || NULL == _pValue) {
		return VECTOR_UNITIALIZED_ERROR;
	}
	if (0 == _vector -> m_nItems)
	{
		return VECTOR_UNDERFLOW_ERROR;
	} 
	_vector -> m_nItems -= 1;
	*_pValue = _vector -> m_items[_vector -> m_nItems];
	if (_vector -> m_size > _vector -> m_originalSize &&
		(_vector -> m_blockSize * DECREASE_FACTOR) <=
		(_vector -> m_size - _vector -> m_nItems))
	{
			RealocateVectorDelete(_vector);
	}
	return VECTOR_OK;
}

VectorResult VectorGet(const Vector* _vector, size_t _index,
	void** _pValue)
{
	if ( NULL == _vector || NULL == _pValue) {
		return VECTOR_UNITIALIZED_ERROR;
	}
	if (_index >= (_vector -> m_nItems) || _index < 0 ) {
		return VECTOR_WRONG_INDEX;
	}
	*_pValue = _vector -> m_items[_index];
	return VECTOR_OK;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void* _value)
{
	if (NULL == _vector || NULL == _value) {
		return VECTOR_UNITIALIZED_ERROR;
	}
	if (_index >= _vector -> m_nItems) {
		return VECTOR_WRONG_INDEX;
	}
	_vector -> m_items[_index] = _value;
	return VECTOR_OK;
}

size_t VectorSize(const Vector* _vector)
{
	if (_vector == NULL) {
		return 0;
	}
	return _vector -> m_nItems;
}

size_t VectorCapacity(const Vector* _vector)
{
	if (_vector == NULL) {
		return 0;
	}
	return _vector -> m_size;
}

size_t VectorForEach(const Vector* _vector,
	VectorElementAction _action, void* _context)
{
	size_t i, size;
	if (NULL == _vector || NULL == _action) {
		return 0;
	}
	size = _vector -> m_nItems;
	for (i = 0; i < size; ++i)
	{
		_action(_vector -> m_items[i], i, _context);
	}
	return i;
}
/******************************************************************/

static Vector* ExecuteCreate(size_t _initialCapacity, size_t _blockSize)
{
	Vector* newVector;
	void** arrayPointers = NULL;
	newVector = (Vector*)malloc(sizeof(Vector));
	if (NULL == newVector)
	{
		return NULL;
	}
	arrayPointers = (void**)malloc(_initialCapacity * sizeof(void*));
	if (NULL == arrayPointers) 
	{
		free(newVector);
		return NULL;
	}
	newVector -> m_items = arrayPointers;
	newVector -> m_originalSize = _initialCapacity;
	newVector -> m_size = _initialCapacity;
	newVector -> m_nItems = 0;
	newVector -> m_blockSize = _blockSize;
	return newVector;
}

VectorResult ReallocateVectorAdd(Vector *_vector) {
	void** temp = NULL;
	if (_vector -> m_blockSize == 0) {
		return VECTOR_OVERFLOW_ERROR;
	}
	temp = (void**)realloc(_vector -> m_items,
			(_vector -> m_size + _vector -> m_blockSize) *
			sizeof(void*));
	if (NULL == temp) {
		return VECTOR_REALOCATION_ERROR;
	}
	_vector -> m_items = temp;
	_vector -> m_size += _vector -> m_blockSize;
	return VECTOR_OK;
}

void RealocateVectorDelete(Vector *_vector) 
{
	void* temp;
	if (0 == _vector -> m_blockSize)
	{
		return;
	}
	temp = (void*)realloc(_vector -> m_items,
						 (_vector -> m_size - _vector -> m_blockSize) *
						 sizeof(void*));			 
	if (NULL == temp)
	{
		return;
	}
	_vector -> m_items = temp;
	_vector -> m_size -= _vector -> m_blockSize;
}

/* assistant functions for testing from the main */
size_t GetVecOrigSize(Vector* _vector) {
	return _vector -> m_originalSize;
}
size_t GetVecSize(Vector* _vector) {
	return _vector -> m_size;
}
size_t GetVecNItems(Vector* _vector) {
	return _vector -> m_nItems;
}
size_t GetVecBlockSize(Vector* _vector) {
	return _vector -> m_blockSize;
}
