#ifndef __GENSORT_H__
#define __GENSORT_H__

/*
description:	definition for pointer function that sorts generic
				elements by a specified criteria.
arguments:		_first - the first value to compare.
				_second - the second value to compare.*/
typedef int(*Scriteria)(const void* _first, const void* _second);

/*
description:	generic sort function.
arguments:		_arr - the array.
				_elementSize - size of each element in the array.
				_size - the legth of the array.
				_cfunc - soring criteria by pointer function.
return value:	OK.
errors:			ERR_NULL - if _arr invalid.
				ALLOCATION_FAIL - if malloc failed.*/
int GenSort(void* _arr, size_t _elementSize, size_t _size,
			Scriteria _cfunc);

#endif /* #define __GENSORT_H__ */




