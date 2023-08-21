#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include "listinternal.h"

static void TestBegin(void);
static void TestEnd(void);
static void TestNext(void);
static void TestEquals(void);
static void TestPrev(void);
static void TestGet(void);
static void TestSet(void);
static void TestInsertBefore(void);
static void TestRemove(void);

int main()
{
    TestBegin();
    TestEnd();
    TestEquals();
    TestNext();
    TestPrev();
    TestGet();
    TestSet();
    TestInsertBefore();
    TestRemove();
    return 0;
}

static void TestBegin(void)
{
    List* ptrList;
    int *item1, *item2;
    item1 = (int*)malloc(sizeof(int));
    *item1 = 5;
    item2 = (int*)malloc(sizeof(int));
    *item2 = 10;
    ptrList = ListCreate();
    printf("Test ListItrBegin() for empty ptrList ");
    (void*)ListItrBegin(ptrList) == ptrList -> m_head.m_next ?
        printf("- PASS\n") : printf("- FAIL\n");
    printf("Test ListItrBegin() for input NULL - ");
    ListItrBegin(NULL) == NULL ? printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrBegin() for correctness of output ");
    ListPushHead(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    (void*)ListItrBegin(ptrList) == ptrList -> m_head.m_next ?
        printf("PASS\n") : printf("FAIL\n");
    free(item1); free(item2);
    ListDestroy(&ptrList, NULL);
}

static void TestEnd(void)
{
    List* ptrList;
    int *item1, *item2;
    item1 = (int*)malloc(sizeof(int));
    *item1 = 5;
    item2 = (int*)malloc(sizeof(int));
    *item2 = 10;
    ptrList = ListCreate();
    printf("Test ListItrEnd() for empty ptrList ");
    ListItrEnd(ptrList) == &(ptrList -> m_tail) ?
        printf("- PASS\n") : printf("- FAIL\n");
    printf("Test ListItrEnd() for input NULL - ");
    ListItrEnd(NULL) == NULL ? printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrEnd() for correctness of output ");
    ListPushHead(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    (void*)ListItrEnd(ptrList) == (void*)&(ptrList -> m_tail) ?
        printf("PASS\n") : printf("FAIL\n");
    free(item1); free(item2);
    ListDestroy(&ptrList, NULL);
}

static void TestEquals(void)
{
    List* ptrList = NULL;
    int item1 = 1, item2 = 2;
    printf("Test ListItrEquals for equal values - ");
    ListItrEquals(&item1, &item1) == 1 ?
        printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrEquals for not equal values - ");
    ListItrEquals(&item1, &item2) == 0 ?
        printf("PASS\n") : printf("FAIL\n");
}

static void TestNext(void)
{
    List* ptrList;
    int *item1, *item2, *item3;
    void *resultNext;
    item1 = (int*)malloc(sizeof(int));
    item2 = (int*)malloc(sizeof(int));
    item3 = (int*)malloc(sizeof(int));
    *item1 = 5, *item2 = 10, *item3 = 15;
    ptrList = ListCreate();
    printf("Test ListItrNext() for empty ptrList ");
    ListItrNext(ptrList) == &(ptrList -> m_tail) ?
        printf("- PASS\n") : printf("- FAIL\n");
    printf("Test ListItrNext() for input NULL - ");
    ListItrNext(NULL) == NULL ? printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrNext() for correctness of output ");
    ListPushHead(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item3);
    resultNext = ListItrBegin(ptrList);
    resultNext = ListItrNext(resultNext);
    resultNext = ListItrNext(resultNext);
    resultNext == ptrList -> m_head.m_next -> m_next -> m_next ? 
        printf("PASS\n") : printf("FAIL\n");
    free(item1); free(item2); free(item3);
    ListDestroy(&ptrList, NULL);
}

static void TestPrev(void)
{
    List* ptrList = NULL;
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4;
    void* resultPrev;
    printf("Test ListItrPrev for input NULL - ");
    ListItrPrev(NULL) == NULL ? printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrPrev for input empty ptrList - ");
    ptrList = ListCreate();
    ListItrPrev(ptrList) == NULL ? printf("PASS\n") : printf("FAIL\n");
    printf("Test the correctness of ListItrPrev - ");
    ListPushHead(ptrList, &val1);
    ListPushTail(ptrList, &val2);
    ListPushTail(ptrList, &val3);
    ListPushTail(ptrList, &val4);
    resultPrev = ListItrEnd(ptrList);
    resultPrev = ListItrPrev(resultPrev);
    resultPrev = ListItrPrev(resultPrev);
    resultPrev == ptrList -> m_tail.m_prev -> m_prev ?
        printf("PASS\n") : printf("FAIL\n");
    ListDestroy(&ptrList, NULL);
}

static void TestGet(void)
{
    List* ptrList = NULL;
    int val1 = 1, val2 = 2, val3 = 3, val4 = 4;
    void *resulNext;
    printf("Test ListItrGet for input NULL - ");
    ListItrGet(NULL) == NULL ? printf("PASS\n") : printf("FAIL\n");
    printf("Test correctness of ListItrGet - ");
    ptrList = ListCreate();
    ListPushHead(ptrList, &val1);
    ListPushTail(ptrList, &val2);
    resulNext = ListItrBegin(ptrList);
    resulNext = ListItrNext(resulNext);
    ListItrGet(resulNext) == &val2 ? printf("PASS\n") : printf("FAIL\n");
    ListDestroy(&ptrList, NULL);
}

static void TestSet(void)
{
    List* ptrList;
    int *item1, *item2, *item3, *item4;
    void *resultNext, *resultSet, *resultGet;
    item1 = (int*)malloc(sizeof(int));
    item2 = (int*)malloc(sizeof(int));
    item3 = (int*)malloc(sizeof(int));
    item4 = (int*)malloc(sizeof(int));
    *item1 = 5, *item2 = 10, *item3 = 15, *item4 = 20;
    ptrList = ListCreate();
    printf("Test ListItrSet() for input NULL, &item4 ");
    (NULL == ListItrSet(NULL, &item4)) ?
        printf("PASS\n") : printf("FAIL\n");
    printf("Test ListItrSet() for correctness of returned data ");
    ListPushHead(ptrList, item1);
    ListPushTail(ptrList, item2);
    ListPushTail(ptrList, item3);
    resultNext = ListItrBegin(ptrList);
    resultNext = ListItrNext(resultNext);
    resultGet = ListItrGet(resultNext);
    resultSet = ListItrSet(resultNext, item4);
    resultSet == resultGet ? printf("- PASS\n") : printf("- FAIL\n");
    printf("Test ListItrSet() for correctness set data ");
    resultGet = ListItrGet(resultNext);
    resultGet == item4 ? printf("- PASS\n") : printf("- FAIL\n");
    free(item1); free(item2); free(item3); free(item4);
    ListDestroy(&ptrList, NULL);
}

static void TestInsertBefore(void)
{
    List* ptrList;
    int *item1, *item2, *item3, *item4;
    void *resultNext, *resultPrev, *resultGet;
    item1 = (int*)malloc(sizeof(int));
    item2 = (int*)malloc(sizeof(int));
    item3 = (int*)malloc(sizeof(int));
    item4 = (int*)malloc(sizeof(int));
    *item1 = 5, *item2 = 10, *item3 = 15, *item4 = 20;
    ptrList = ListCreate();
    printf("Test ListItrInsertBefore() for input NULL, &item4 ");
    NULL == ListItrInsertBefore(NULL, item3) ?
        printf("- PASS\n") : printf("- FAIL\n");
    ListPushHead(ptrList, item1);
    ListPushTail(ptrList, item2);
    ListPushTail(ptrList, item4);
    resultNext = ListItrBegin(ptrList);
    resultNext = ListItrNext(resultNext);
    resultNext = ListItrNext(resultNext);
    printf("Test ListItrInsertBefore() for input 'resultNext', NULL ");
    NULL == ListItrInsertBefore(resultNext, NULL) ?
        printf("- PASS\n") : printf("- FAIL\n");
    printf("Test ListItrInsertBefore() for correct insertion ");
    ListItrInsertBefore(resultNext, item3);
    resultPrev = ListItrPrev(resultNext);
    resultGet = ListItrGet(resultPrev);
    resultGet == item3 ? printf("- PASS\n") : printf("- FAIL\n");
    free(item1); free(item2); free(item3); free(item4);
    ListDestroy(&ptrList, NULL);
}

static void TestRemove(void)
{
    List* ptrList;
    int *item1, *item2, *item3, *item4;
    void *resultNext, *resultPrev, *resultGet, *itemRemoved;
    item1 = (int*)malloc(sizeof(int));
    item2 = (int*)malloc(sizeof(int));
    item3 = (int*)malloc(sizeof(int));
    item4 = (int*)malloc(sizeof(int));
    *item1 = 5, *item2 = 10, *item3 = 15, *item4 = 20;
    ptrList = ListCreate();
    printf("Test ListItrRemove() for input NULL ");
    NULL == ListItrRemove(NULL) ?
        printf("- PASS\n") : printf("- FAIL\n");
    ListPushHead(ptrList, item1);
    ListPushTail(ptrList, item2);
    ListPushTail(ptrList, item3);
    ListPushTail(ptrList, item4);
    resultNext = ListItrBegin(ptrList);
    resultNext = ListItrNext(resultNext);
    resultNext = ListItrNext(resultNext);
    printf("Test ListItrRemove() for correctness of item removed ");
    itemRemoved = ListItrRemove(resultNext);
    itemRemoved == item3 ?
        printf("- PASS\n") : printf("- FAIL\n");
    printf("Test ListItrRemove() if the item is phisically removed ");
    resultNext = ListItrBegin(ptrList);
    resultNext = ListItrNext(resultNext);
    resultNext = ListItrNext(resultNext);
    resultGet = ListItrGet(resultNext); 
    resultGet == item4 ? printf("- PASS\n") : printf("- FAIL\n");
    free(item1); free(item2); free(item3); free(item4);
    ListDestroy(&ptrList, NULL);
}




