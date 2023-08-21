#include <stdio.h>
#include "listinternal.h"

static void TestCreate(void);
static void TestDestroy(void);
static void TestPushHead(void);
static void TestPushTail(void);
static void TestPopHead(void);
static void TestPopTail(void);
static void TestSize(void);

int main()
{
	TestCreate();
	TestDestroy();
	TestPushHead();
	TestPushTail();
	TestPopHead();
	TestPopTail();
	TestSize();
	return 0;
}

static void TestCreate(void)
{
	List* ptrList = NULL;
	printf("Test for ListCreate()\n");
	ptrList = ListCreate();
	ptrList != NULL ? printf("PASS ") : printf("FAIL ");
	ListDestroy(&ptrList, NULL);
	putchar('\n');
}

static void TestDestroy(void)
{
	List* ptrList = NULL;
	ptrList = ListCreate();
	printf("Test ListDestroy() for single destroy ");
	ListDestroy(&ptrList, NULL);
	(NULL == ptrList) ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListDestroy() for double destroy ");
	ListDestroy(&ptrList, NULL);
	printf("- PASS\n");
	printf("Test ListDestroy() for NULL, NULL ");
	ListDestroy(NULL, NULL);
	printf("- PASS\n");
}

static void TestPushHead(void)
{
	List* ptrList = NULL;
	void* item1, *item2, *resultNode;
	int intValue1 = 3, value2 = 8;
	printf("Test ListPushHead() for status LIST_SUCCESS ");
	ptrList = ListCreate();
	item1 = &intValue1, item2 = &value2;
	ListPushHead(ptrList, item1) == LIST_SUCCESS ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushHead() for correct insertion ");
	resultNode = GetHead(ptrList);
	(*(int*)resultNode == *(int*)item1) ? 
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushHead() for correct second insertion ");
	ListPushHead(ptrList, item2);
	resultNode = GetHead(ptrList);
	(*(int*)resultNode == value2) ? 
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushHead() for NULL, item1 ");
	ListPushHead(NULL, item1) == LIST_UNINITIALIZED_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushHead() for ptrList, NULL ");
	ListPushHead(ptrList, NULL) == LIST_NULL_ELEMENT_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	ListDestroy(&ptrList, NULL);
}

static void TestPushTail(void)
{
	List* ptrList = NULL;
	void* item1, *item2, *resultNode;
	int intValue1 = 3, value2 = 8;
	printf("Test ListPushTail() for status LIST_SUCCESS ");
	ptrList = ListCreate();
	item1 = &intValue1, item2 = &value2;
	ListPushTail(ptrList, item1) == LIST_SUCCESS ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushTail() for correct insertion ");
	resultNode = GetTail(ptrList);
	(*(int*)resultNode == *(int*)item1) ? 
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushTail() for correct second insertion ");
	ListPushTail(ptrList, item2);
	resultNode = GetTail(ptrList);
	(*(int*)resultNode == value2) ? 
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushTail() for NULL, item1 ");
	ListPushTail(NULL, item1) == LIST_UNINITIALIZED_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPushTail() for ptrList, NULL ");
	ListPushTail(ptrList, NULL) == LIST_NULL_ELEMENT_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	ListDestroy(&ptrList, NULL);
}

static void TestPopHead(void) {
	List* ptrList = NULL;
	int intValue1 = 3, value2 = 8;
	void* item1 = &intValue1, *item2 = &value2;
	void* itemResult = NULL;
	printf("Test ListPushHead() for empty list ");
	ptrList = ListCreate();
	(ListPopHead(ptrList, &itemResult) == LIST_EMPTY &&
		NULL == itemResult) ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopHead() for status LIST_SUCCESS ");
	ListPushHead(ptrList, item1);
	ListPopHead(ptrList, &itemResult) == LIST_SUCCESS ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopHead() for correct item result");
	item1 == itemResult ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopHead() for another correct item result ");
	ListPushHead(ptrList, item2);
	ListPushTail(ptrList, item1);
	ListPopHead(ptrList, &itemResult);
	itemResult == item2 ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopHead() for NULL, itemResult ");
	ListPopHead(NULL, &itemResult) == LIST_UNINITIALIZED_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopHead() for ptrList, NULL ");
	ListPopHead(ptrList, NULL) == LIST_NULL_ELEMENT_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	ListDestroy(&ptrList, NULL);
}

static void TestPopTail(void) {
	List* ptrList = NULL;
	int intValue1 = 3, value2 = 8;
	void* item1 = &intValue1, *item2 = &value2;
	void* itemResult = NULL;
	printf("Test ListPushTail() for empty list ");
	ptrList = ListCreate();
	(ListPopTail(ptrList, &itemResult) == LIST_EMPTY &&
		NULL == itemResult) ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopTail() for status LIST_SUCCESS ");
	ListPushHead(ptrList, item1);
	ListPopTail(ptrList, &itemResult) == LIST_SUCCESS ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopTail() for correct item result");
	item1 == itemResult ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopTail() for another correct item result ");
	ListPushHead(ptrList, item2);
	ListPushTail(ptrList, item1);
	ListPopTail(ptrList, &itemResult);
	itemResult == item1 ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopTail() for NULL, itemResult ");
	ListPopTail(NULL, &itemResult) == LIST_UNINITIALIZED_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListPopTail() for ptrList, NULL ");
	ListPopTail(ptrList, NULL) == LIST_NULL_ELEMENT_ERROR ?
		printf("- PASS\n") : printf("- FAIL\n");
	ListDestroy(&ptrList, NULL);
}

static void TestSize(void) {
	List* ptrList = NULL;
	int intValue1 = 3, value2 = 8;
	void* item1 = &intValue1, *item2 = &value2;
	void* itemResult = NULL;
	printf("Test LListSize() for empty list ");
	ptrList = ListCreate();
	0 == ListSize(ptrList) ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListSize() for NULL ");
	0 == ListSize(NULL) ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListSize() for ptrList with one element ");
	ListPushHead(ptrList, item1);
	1 == ListSize(ptrList) ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListSize() for ptrList with two elements ");
	ListPushTail(ptrList, item2);
	2 == ListSize(ptrList) ? printf("- PASS\n") : printf("- FAIL\n");
	printf("Test ListSize() for ptrList with three elements ");
	ListPushHead(ptrList, item2);
	3 == ListSize(ptrList) ? printf("- PASS\n") : printf("- FAIL\n");
	ListDestroy(&ptrList, NULL);
}



