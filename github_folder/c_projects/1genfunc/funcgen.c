#include <stdlib.h>
#include <string.h>
#include "gensort.h"
#define ALLOCATION_FAIL -1
#define ERR_NULL - 2
#define OK 0

static void GenSwap(void* _first, void* _second,
					void* _allocationPtr, size_t _elementSize);

int GenSort(void* _arr, size_t _elementSize, size_t _size,
			Scriteria _cfunc)
{
	size_t i, j, flag;
	char* array = _arr;
	void* allocationPtr = malloc(_size * sizeof(_elementSize));
	if (NULL == _arr) {
		return ERR_NULL;
	}
	if (NULL == allocationPtr) {
		return ALLOCATION_FAIL;
	}
	for (i = 0; i < (_size * _elementSize); i += _elementSize) {
		for(j = 0; j < ((_size - 1)* _elementSize); j += _elementSize) {
			if (_cfunc(array + j, array + (j + _elementSize)))
			{
				GenSwap((array + j), (array + j + _elementSize),
					allocationPtr, _elementSize);
			}
		}
	}
	free(allocationPtr);
	return OK;
}

static void GenSwap(void* _first, void* _second,
					void* _allocationPtr, size_t _elementSize)
{
	memcpy(_allocationPtr, _first, _elementSize);
	memcpy(_first, _second, _elementSize);
	memcpy(_second, _allocationPtr, _elementSize);
}