#include <stdio.h>
#include "heap.h"
#define VEC_SIZE 10
#define VEC_BL_SIZE 2

static void TestBuild(void);
static void TestDestroy(void);
static void TestInsert(void);
static void TestPeek(void);
static void TestExtract(void);
static void TestSize(void);
static void TestForEach(void);
static int IsLower(const void *_first, const void *_second);
static int PrintInt(const void *_elem, void * _context);
static int IsHigher(const void *_first, const void *_second);

int main()
{
	TestBuild();
	TestDestroy();
	TestInsert();
	TestPeek();
	TestExtract();
	TestSize();
	TestForEach();
	return 0;
}

static void TestBuild(void)
{
	Vector* ptrVec = NULL;
	Heap* ptrHeap = NULL;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	void *get0, *get1, *get2, *get3, *get4, *get5;
	printf("Test HeapBuild()\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	VectorGet(ptrVec, 0, &get0); VectorGet(ptrVec, 1, &get1);
	VectorGet(ptrVec, 2, &get2); VectorGet(ptrVec, 3, &get3);
	VectorGet(ptrVec, 4, &get4); VectorGet(ptrVec, 5, &get5);
	printf("%d %d %d %d %d %d --> ", val0, val1, val2, val3, val4, val5);
	printf("%d %d %d %d %d %d \n", *(int*)get0, *(int*)get1, *(int*)get2,
		*(int*)get3, *(int*)get4, *(int*)get5);
	printf("PASS ");
	HeapDestroy(&ptrHeap);
	printf("\nTest for sorting of min value at the top\n");
	ptrHeap = HeapBuild(ptrVec, IsHigher);
	VectorGet(ptrVec, 0, &get0); VectorGet(ptrVec, 1, &get1);
	VectorGet(ptrVec, 2, &get2); VectorGet(ptrVec, 3, &get3);
	VectorGet(ptrVec, 4, &get4); VectorGet(ptrVec, 5, &get5);
	printf("%d %d %d %d %d %d --> ", val0, val1, val2, val3, val4, val5);
	printf("%d %d %d %d %d %d \n", *(int*)get0, *(int*)get1, *(int*)get2,
		*(int*)get3, *(int*)get4, *(int*)get5);
	printf("PASS ");
	HeapDestroy(&ptrHeap);
	ptrHeap = HeapBuild(NULL, IsLower);
	ptrHeap == NULL ? printf("PASS ") : printf("FAIL ");
	ptrHeap = HeapBuild(ptrVec, NULL);
	ptrHeap == NULL ? printf("PASS ") : printf("FAIL ");
	ptrHeap = HeapBuild(NULL, NULL);
	ptrHeap == NULL ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	printf("\n\n");
}

static void TestDestroy(void)
{
	Vector *ptrVec = NULL, *resHeapDestroy = NULL;
	Heap* ptrHeap = NULL;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	printf("Test HeapDestroy()\n");
	ptrHeap = HeapBuild(ptrVec, IsLower);
	resHeapDestroy = HeapDestroy(NULL);
	resHeapDestroy == NULL ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrVec, NULL);
	resHeapDestroy = HeapDestroy(&ptrHeap);
	resHeapDestroy != NULL ? printf("PASS ") : printf("FAIL ");
	resHeapDestroy = HeapDestroy(&ptrHeap);
	resHeapDestroy == NULL ? printf("PASS ") : printf("FAIL ");
	printf("PASS ");
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	printf("\n\n");
}

static void TestInsert(void)
{
	Vector *ptrVec = NULL;
	Heap* ptrHeap = NULL;
	HeapResultCode resHeap;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	int val6 = 40, val7 = 3;
	void *get0, *get1, *get2, *get3, *get4, *get5, *get6, *get7;
	printf("Test HeapInsert()\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	printf("Check if heap is correct\n");
	IsHeapCorrect(ptrHeap) ? printf("PASS\n") : printf("FAIL\n");
	get6 = &val6;
	printf("Check result status of valid input  ");
	HEAP_SUCCESS == HeapInsert(ptrHeap, get6) ? printf("PASS\n") : printf("FAIL\n");
	printf("Check if heap is correct\n");
	IsHeapCorrect(ptrHeap) ? printf("PASS\n") : printf("FAIL\n");
	VectorGet(ptrVec, 0, &get0); VectorGet(ptrVec, 1, &get1);
	VectorGet(ptrVec, 2, &get2); VectorGet(ptrVec, 3, &get3);
	VectorGet(ptrVec, 4, &get4); VectorGet(ptrVec, 5, &get5);
	VectorGet(ptrVec, 6, &get6);
	printf("%d %d %d %d %d %d %d ", *(int*)get0, *(int*)get1,
		*(int*)get2, *(int*)get3, *(int*)get4, *(int*)get5, *(int*)get6);
	printf(" Insert high value PASS\n");
	get7 = &val7;
	HeapInsert(ptrHeap, get7);
	VectorGet(ptrVec, 0, &get0); VectorGet(ptrVec, 1, &get1);
	VectorGet(ptrVec, 2, &get2); VectorGet(ptrVec, 3, &get3);
	VectorGet(ptrVec, 4, &get4); VectorGet(ptrVec, 5, &get5);
	VectorGet(ptrVec, 6, &get6); VectorGet(ptrVec, 7, &get7);
	printf("%d %d %d %d %d %d %d %d ", *(int*)get0, *(int*)get1,
		*(int*)get2, *(int*)get3, *(int*)get4, *(int*)get5,
		*(int*)get6, *(int*)get7);
	printf("Insert low value PASS\n");
	printf("Check if heap is correct\n");
	IsHeapCorrect(ptrHeap) ? printf("PASS\n") : printf("FAIL\n");
	printf("Check result status of invalid inputs\n");
	resHeap = HeapInsert(NULL, get6);
	resHeap == HEAP_NOT_INITIALIZED ? printf("PASS ") : printf("FAIL ");
	resHeap = HeapInsert(ptrHeap, NULL);
	resHeap == HEAP_NOT_INITIALIZED ? printf("PASS ") : printf("FAIL ");
	resHeap = HeapInsert(NULL, NULL);
	resHeap == HEAP_NOT_INITIALIZED ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	printf("\n\n");
}

static void TestPeek(void)
{
	Vector* ptrVec = NULL;
	Heap* ptrHeap = NULL;
	void* item;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	HeapResultCode resPeek1, resPeek2, resPeek3;
	printf("Test HeapPeek() for valid inputs\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	resPeek1 = HeapPeek(ptrHeap, &item);
	if (HEAP_SUCCESS == resPeek1 && val4 == *(int*)item)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
	}
	printf("Test HeapPeek() for invalid inputs\n");
	resPeek1 = HeapPeek(NULL, NULL);
	resPeek2 = HeapPeek(NULL, &item);
	resPeek3 = HeapPeek(ptrHeap, NULL);
	if (HEAP_NOT_INITIALIZED == resPeek1 &&
		HEAP_NOT_INITIALIZED == resPeek2 &&
		HEAP_INVALID_ITEM == resPeek3 )
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
	}
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	putchar('\n');
}

static void TestExtract(void) {
	Vector* ptrVec = NULL;
	Heap* ptrHeap = NULL;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	void *resExtract, *get0, *get1, *get2, *get3, *get4, *get5;
	printf("Test HeapExtract()\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	resExtract = HeapExtract(ptrHeap);
	*(int*)resExtract == val4 ? printf("PASS ") : printf("FAIL ");
	NULL == HeapExtract(NULL) ? printf("PASS ") : printf("FAIL ");
	5 == HeapSize(ptrHeap) ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	printf("\nTest HeapExtract() for single element\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	resExtract = HeapExtract(ptrHeap);
	if (0 == HeapSize(ptrHeap) && *(int*)resExtract == val0)
	{
		printf("PASS");
	}
	else
	{
		printf("FAIL");
	}
	printf("\nCheck if heap is correct\n");
	IsHeapCorrect(ptrHeap) ? printf("PASS\n") : printf("FAIL\n");
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	putchar('\n');
}

static void TestSize(void) {
	Vector* ptrVec = NULL;
	Heap* ptrHeap = NULL;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	void *get0, *get1, *get2, *get3, *get4, *get5;
	printf("Test HeapSize()\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	VectorGet(ptrVec, 0, &get0); VectorGet(ptrVec, 1, &get1);
	VectorGet(ptrVec, 2, &get2); VectorGet(ptrVec, 3, &get3);
	VectorGet(ptrVec, 4, &get4); VectorGet(ptrVec, 5, &get5);
	HeapSize(ptrHeap) == 6 ? printf("PASS ") : printf("FAIL ");
	HeapSize(NULL) == 0 ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
	printf("\n\n");
}
static void TestForEach(void) {
	Vector* ptrVec = NULL;
	Heap* ptrHeap = NULL;
	int val0 = 7, val1 = 5, val2 = 6, val3 = 20, val4 = 31, val5 = 2;
	void *get0, *get1, *get2, *get3, *get4, *get5;
	int resIsHeapCorrect = 0;
	printf("Test TestForEach()\n");
	ptrVec = VectorCreate(VEC_SIZE, VEC_BL_SIZE);
	VectorAppend(ptrVec, &val0); VectorAppend(ptrVec, &val1);
	VectorAppend(ptrVec, &val2); VectorAppend(ptrVec, &val3);
	VectorAppend(ptrVec, &val4); VectorAppend(ptrVec, &val5);
	ptrHeap = HeapBuild(ptrVec, IsLower);
	VectorGet(ptrVec, 0, &get0); VectorGet(ptrVec, 1, &get1);
	VectorGet(ptrVec, 2, &get2); VectorGet(ptrVec, 3, &get3);
	VectorGet(ptrVec, 4, &get4); VectorGet(ptrVec, 5, &get5);
	printf("for valid input:\n");
	HeapForEach(ptrHeap, PrintInt, NULL);
	printf("PASS ");
	printf("\nCheck if heap is correct\n");
	resIsHeapCorrect = IsHeapCorrect(ptrHeap);
	if (resIsHeapCorrect)
	{
		printf("PASS\n");
	}
	else 
	{
		printf("FAIL\n");
	}
	printf("for invalid inputs: \n");
	HeapForEach(ptrHeap, NULL, NULL);
	printf("PASS ");
	HeapForEach(NULL, PrintInt, NULL);
	printf("PASS ");
	HeapForEach(NULL, NULL, NULL);
	printf("PASS ");
	putchar('\n');
	VectorDestroy(&ptrVec, NULL);
	HeapDestroy(&ptrHeap);
}

/******************************************************************/

static int IsLower(const void *_first, const void *_second)
{
	if ( (*(int*)_first) < (*(int*)_second) )
	{
		return 1;
	}
	return 0;
}

static int PrintInt(const void *_elem, void *_context)
{
	printf("%d\n", *(int*)_elem);
	return 1;
}

static int IsHigher(const void *_first, const void *_second)
{
	if ( (*(int*)_first) > (*(int*)_second) )
	{
		return 1;
	}
	return 0;
}

