#include <stdio.h>
#include "list_functions.h"
#include "listinternal.h"

static void TestFindFirst(void);
static void TestCountIf(void);
static void TestForEach(void);
static int PredicateFound(void* _data, void* _context);
static int PredicateCount(void* _data, void* _context);
static int ActionPrint(void* _itr, void* _context);

int main()
{
    TestFindFirst();
    TestCountIf();
    TestForEach();
    return 0;
}

static void TestFindFirst(void) {
    List* ptrList = NULL;
    int item1 = 10, item2 = 20, item3 = 30, item4 = 40;
    void *begin, *end, *itr;
    printf("Test ListItrFindFirst() for found item ");
	ptrList = ListCreate();
    ListPushHead(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item3);
    begin = ListItrBegin(ptrList);
    end = ListItrEnd(ptrList);
    itr = ListItrFindFirst(begin, end, PredicateFound, &item2);
    *(int*)ListItrGet(itr) == item2 ?
        printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrFindFirst() for not found item ");
    itr = ListItrFindFirst(begin, end, PredicateFound, &item4);
    itr == end ? printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrFindFirst() for _begin NULL ");
    ListItrFindFirst(NULL, end, PredicateFound, &item2) == NULL ?
    printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrFindFirst() for _end NULL ");
    ListItrFindFirst(begin, NULL, PredicateFound, &item2) == NULL ?
    printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrFindFirst() for PredicateFound NULL ");
    ListItrFindFirst(begin, end, NULL, &item2) == NULL ?
    printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrFindFirst() for _context NULL ");
    ListItrFindFirst(begin, end, PredicateFound, NULL) == NULL ?
    printf("PASS\n") : printf("FAIL\n");
    putchar('\n');
    ListDestroy(&ptrList, NULL);
}

static void TestCountIf(void) {
    List* ptrList = NULL;
    int item1 = 1, item2 = 2, item3 = 3, item4 = 4;
    void *begin, *end;
    printf("Test ListItrCountIf() for correctness count 3 ");
	ptrList = ListCreate();
    ListPushHead(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item3);
    begin = ListItrBegin(ptrList);
    end = ListItrEnd(ptrList);
    ListItrCountIf(begin, end, PredicateCount, &item2) == 3 ?
        printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrCountIf() for correct count 0 ");
    ListItrCountIf(begin, end, PredicateCount, &item4) == 0 ?
        printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrCountIf() for _begin NULL ");
    ListItrCountIf(NULL, end, PredicateCount, &item2) == 0 ?
    printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrCountIf() for _end NULL ");
    ListItrCountIf(begin, NULL, PredicateCount, &item2) == 0 ?
    printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrCountIf() for PredicateCount NULL ");
    ListItrCountIf(begin, end, NULL, &item2) == 0 ?
    printf("PASS\n") : printf("FAIL\n");
    putchar('\n');
    ListDestroy(&ptrList, NULL);
}

static void TestForEach(void) {
    List* ptrList = NULL;
    int item1 = 11, item2 = 12, item3 = 13, item4 = 14;
    int item5 = 15;
    void *begin, *end;

    printf("Test ListItrForEach() for print action:\n");
	ptrList = ListCreate();
    ListPushHead(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item3);
    ListPushTail(ptrList, &item4);
    ListPushTail(ptrList, &item5);
    begin = ListItrBegin(ptrList);
    end = ListItrEnd(ptrList);
    ListItrForEach(begin, end, ActionPrint, NULL) == end ?
        printf("PASS\n") : printf("FAIL\n");

    printf("Test ListItrForEach() for _begin NULL ");
    begin = NULL;
    ListItrForEach(begin, end, ActionPrint, NULL) == begin ?
        printf("PASS\n") : printf("FAIL\n");
    
    printf("Test ListItrForEach() for _end NULL ");
    begin = ListItrBegin(ptrList);
    end = NULL;
    ListItrForEach(begin, end, ActionPrint, NULL) == begin ?
        printf("PASS\n") : printf("FAIL\n");
    
    printf("Test ListItrForEach() for _action NULL ");
    begin = ListItrBegin(ptrList);
    end = ListItrEnd(ptrList);
    ListItrForEach(begin, end, NULL, NULL) == begin ?
        printf("PASS\n") : printf("FAIL\n");

    putchar('\n');
    ListDestroy(&ptrList, NULL);
}

/*------------ assistant functions --------------------*/

static int PredicateFound(void* _data, void* _context)
{
    return (*(int*)_data == *(int*)_context) ? (0) : (1);
}

static int PredicateCount(void* _data, void* _context)
{
    return *(int*)_data == *(int*)_context;
}

static int ActionPrint(void* _data, void* _context)
{
    printf("number: %d\n", *(int*)_data);
    return 1;
}
