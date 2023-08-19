#include <stdlib.h> 	/* for allocations */
#include "vector.h" 	/* for the Vector */
#include "heap.h"
#define IND_LEFT_CHILD(index) ((index * 2) + 1)
#define IND_RIGHT_CHILD(index) ((index * 2) + 2)
#define IS_LEAF(heap, index) ((index * 2 + 1) >= heap -> m_heapSize)
#define IND_YOUNG_FATH(ptrHeap) ( (ptrHeap -> m_heapSize > 3) ?\
	((ptrHeap -> m_heapSize) / 2 - 1) : (0) )
#define FALSE (0)
#define TRUE (1)
#define IS_RIGHT_EXIST(ptrHeap) ( (ptrHeap -> m_heapSize % 2 == 0) ?\
	FALSE : TRUE)

static Heap* HeapCreate(Vector* _vector, LessThanComparator _pfLess);

static void Heapify(Heap* _ptrHeap, size_t _index,
	LessThanComparator _pfLess);

static size_t BiggestInFamily(Heap* _ptrHeap, size_t _index,
	LessThanComparator _pfLess);

static void Swap(Heap* _ptrHeap, size_t _indFather, size_t _indSon);
static void BubbleUpRec(Heap* _heap, size_t _index);

struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	LessThanComparator m_pfLess;
};

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
	Heap* ptrHeap = NULL;
	if (NULL == _vector || NULL == _pfLess)
	{
		return NULL;
	}
	ptrHeap = HeapCreate(_vector, _pfLess);
	return ptrHeap;
}

Vector* HeapDestroy(Heap** _heap)
{
	Vector* ptrVec;
	if (NULL == _heap || NULL == *_heap)
	{
		return NULL;
	}
	ptrVec = (*_heap) -> m_vec;
	free(*_heap);
	*_heap = NULL;
	return ptrVec;
}

HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
	VectorResult vecResult;
	if (NULL == _heap || NULL == _element)
	{
		return HEAP_NOT_INITIALIZED;
	}
	vecResult = VectorAppend(_heap -> m_vec, _element);
	if (VECTOR_OK != vecResult)
	{
		if (VECTOR_OVERFLOW_ERROR == vecResult)
		{
			return HEAP_OVERFLOW;
		}
		if (VECTOR_REALOCATION_ERROR == vecResult)
		{
			return HEAP_REALLOCATION_FAILED;
		}
	}
	BubbleUpRec(_heap, _heap -> m_heapSize);
	_heap -> m_heapSize += 1;
	return HEAP_SUCCESS;
}

HeapResultCode HeapPeek(const Heap* _heap, void* _item)
{
	if (NULL == _heap || 0 == _heap -> m_heapSize)
	{
		return HEAP_NOT_INITIALIZED;
	}
	if (NULL == _item)
	{
		return HEAP_INVALID_ITEM;
	}
	VectorGet(_heap -> m_vec, 0, _item);
	return HEAP_SUCCESS;
}

void* HeapExtract(Heap* _heap)
{
	void *PeekElement, *lastElement;
	if (NULL == _heap || 0 == _heap -> m_heapSize)
	{
		return NULL;
	}
	VectorGet(_heap -> m_vec, 0, &PeekElement);
	VectorRemove(_heap -> m_vec, &lastElement);
	VectorSet(_heap -> m_vec, 0, lastElement);
	_heap -> m_heapSize -= 1;
	Heapify(_heap, IND_YOUNG_FATH(_heap), _heap -> m_pfLess);
	return PeekElement;
}

size_t HeapSize(const Heap* _heap)
{
	if (NULL == _heap)
	{
		return 0;
	}
	return _heap -> m_heapSize;
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act,
	void* _context)
{
	size_t i;
	void* elem;
	if (NULL == _heap || NULL == _act) {
		return 0;
	}
	for (i = 0; i < _heap -> m_heapSize; ++i) {
		VectorGet(_heap -> m_vec, i, &elem);
		if (_act(elem, _context) == 0) {
			break;
		}
	}
	return i;
}

/********************* Assistant Functions ***********************/

static Heap* HeapCreate(Vector* _vector, LessThanComparator _pfLess)
{
	size_t _numOfItems, indYoungFath, i;
	Heap* ptrHeap;
	if ( (ptrHeap = (Heap*)malloc(sizeof(Heap))) == NULL)
	{
		return NULL;
	}
	_numOfItems = VectorSize(_vector);
	ptrHeap -> m_vec = _vector;
	ptrHeap -> m_heapSize = _numOfItems;
	ptrHeap -> m_pfLess = _pfLess;
	indYoungFath = IND_YOUNG_FATH(ptrHeap);
	while (indYoungFath > 0)
	{
		Heapify(ptrHeap, indYoungFath, _pfLess);
		--indYoungFath;
	}
	if (indYoungFath == 0)
	{
		Heapify(ptrHeap, indYoungFath, _pfLess);
	}  
	return ptrHeap;
}

static void Heapify(Heap* _ptrHeap, size_t _index,
	LessThanComparator _pfLess)
{
	size_t indBiggest;
	if (IS_LEAF(_ptrHeap, _index) )
	{
		return;
	}
	indBiggest = BiggestInFamily(_ptrHeap, _index, _pfLess);
	if (indBiggest == _index)
	{
		return;
	}
	Swap(_ptrHeap, _index, indBiggest);
	Heapify(_ptrHeap, indBiggest, _pfLess);
}

static size_t BiggestInFamily(Heap* _ptrHeap, size_t _index,
	LessThanComparator _pfLess)
{
	void *leftData, *rightData, *fatherData, *biggestData;
	size_t indBiggest = _index;
	VectorGet(_ptrHeap -> m_vec, IND_LEFT_CHILD(_index), &leftData);
	VectorGet(_ptrHeap -> m_vec, _index, &fatherData);
	biggestData = fatherData;
	indBiggest = _index;
	if (_pfLess(fatherData, leftData))
	{
		biggestData = leftData;
		indBiggest = IND_LEFT_CHILD(_index);
	}
	if (IS_RIGHT_EXIST(_ptrHeap))
	{
		VectorGet(_ptrHeap -> m_vec, IND_RIGHT_CHILD(_index),
			&rightData);
		if (_pfLess(biggestData, rightData))
		{
			biggestData = rightData;
			indBiggest = IND_RIGHT_CHILD(_index);
		}
	}
	return indBiggest;
}

static void Swap(Heap* _ptrHeap, size_t _indFather, size_t _indSon)
{
	void *sonData, *fatherData;
	VectorGet(_ptrHeap -> m_vec, _indSon, &sonData);
	VectorGet(_ptrHeap -> m_vec, _indFather, &fatherData);
	VectorSet(_ptrHeap -> m_vec, _indSon, fatherData);
	VectorSet(_ptrHeap -> m_vec, _indFather, sonData);
}

static void BubbleUpRec(Heap* _heap, size_t _index)
{
	void *fatherData, *childData;
	size_t indFather = (_index - 1) / 2;
	if (_index < 1)
	{
		return;
	}
	VectorGet(_heap -> m_vec, indFather, &fatherData);
	VectorGet(_heap -> m_vec, _index, &childData);
	if (*(int*)childData > *(int*)fatherData )
	{
		Swap(_heap, indFather, _index);
		BubbleUpRec(_heap, indFather);
	}
}

int IsHeapCorrect(const Heap* _heap)
{
	size_t youngestFather = 0;
	void *fatherData, *leftChildData, *rightChildData;
	if (NULL == _heap || _heap -> m_heapSize <= 1)
	{
		return TRUE;
	}
	youngestFather = IND_YOUNG_FATH(_heap);
	while (youngestFather != 0)
	{
		VectorGet(_heap -> m_vec, IND_LEFT_CHILD(youngestFather), &leftChildData);
		VectorGet(_heap -> m_vec, youngestFather, &fatherData);
		if (_heap -> m_pfLess(fatherData, leftChildData))
		{
			return FALSE;
		}
		if (IS_RIGHT_EXIST(_heap))
		{
			VectorGet(_heap -> m_vec, IND_RIGHT_CHILD(youngestFather), &rightChildData);
			if (_heap -> m_pfLess(fatherData, rightChildData))
			{
				return FALSE;
			}
		}
		youngestFather--;
	}
	VectorGet(_heap -> m_vec, 0, &fatherData);
	VectorGet(_heap -> m_vec, 1, &leftChildData);
	VectorGet(_heap -> m_vec, 2, &rightChildData);
	if (_heap -> m_pfLess(fatherData, leftChildData) ||
		_heap -> m_pfLess(fatherData, rightChildData) )
	{
		return FALSE;
	}
	return TRUE;
}
