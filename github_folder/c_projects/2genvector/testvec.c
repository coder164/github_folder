#include <stdio.h>
#include "vector.h"

/* declaring test functions */
void ChecksForVectorCreate(void);
void ChecksForVectorDestroy(void);
void TestVectorAppend(void);
void TestVectorRemove(void);
void ChecksForVectorGet(void);
void ChecksForVectorSet(void);
void TestVectorForEach(void);
void TestAction(void* _element, size_t _index, void* _context);
int main(void) 
{
	ChecksForVectorCreate();
	ChecksForVectorDestroy();
	TestVectorAppend();
	TestVectorRemove();
	ChecksForVectorGet();
	ChecksForVectorSet();
	/*
	TestVectorForEach();
	*/
	
}

/******************************************************************/

void ChecksForVectorCreate(void)
{
	Vector* vecResult = NULL;
	int* resultItmes;
	size_t resultMember;
	int resultMagicNum;
	printf("Tests for VectorCreate() for correct inputs:\n");
	vecResult = VectorCreate(5, 2);
	vecResult != NULL ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecOrigSize(vecResult);
	resultMember > 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecSize(vecResult);
	resultMember > 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecNItems(vecResult);
	resultMember == 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecBlockSize(vecResult);
	resultMember > 0 ? printf("PASS\n") : printf("FAIL\n");
	vecResult = VectorCreate(2, 0);
	vecResult != NULL ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecOrigSize(vecResult);
	resultMember > 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecSize(vecResult);
	resultMember > 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecNItems(vecResult);
	resultMember == 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecBlockSize(vecResult);
	resultMember == 0 ? printf("PASS\n") : printf("FAIL\n");
	vecResult = VectorCreate(0, 2);
	vecResult != NULL ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecOrigSize(vecResult);
	resultMember == 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecSize(vecResult);
	resultMember == 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecNItems(vecResult);
	resultMember == 0 ? printf("PASS ") : printf("FAIL\n");
	resultMember = GetVecBlockSize(vecResult);
	resultMember > 0 ? printf("PASS\n") : printf("FAIL\n");
	printf("Test for VectorCreate() for incorrect inputs:\n");
	vecResult = VectorCreate(0, 0);
	vecResult == NULL ? printf("PASS\n") : printf("FAIL\n");
	printf("Test for VectorCreate() for malloc failure:\n");
	vecResult = VectorCreate(-2, 5);
	vecResult == NULL ? printf("PASS\n") : printf("FAIL\n");
	VectorDestroy(&vecResult, NULL);
	putchar('\n');
}

void ChecksForVectorDestroy(void)
{
	Vector* vecResult;
	size_t resultOriginalSize;
	VectorResult resultStatus;
	printf("Tests for VectorDestroy() for NULL\n");
	VectorDestroy(NULL, NULL);
	printf("PASS ");
	printf("\nTests for VectorDestroy() for single free \n");
	vecResult = VectorCreate(5, 2);
	VectorDestroy(&vecResult, NULL);
	printf("PASS");
	printf("\nTests for VectorDestroy() for double free \n");
	vecResult = VectorCreate(5, 2);
	VectorDestroy(&vecResult, NULL);
	VectorDestroy(&vecResult, NULL);
	printf("PASS\n");
}

void TestVectorAppend(void) {
	Vector* vecResult;
	int item[3] = {1, 2, 3};
	size_t resultOriginalSize;	
	size_t resultSize;			
	size_t resultNItems;		
	size_t resultBlockSize;
	VectorResult resultStatus;
	printf("\nTests for VectorAppend() for correct inputs:\n");
	vecResult = VectorCreate(5, 2);
	VectorAppend(vecResult, item);
	resultOriginalSize = GetVecOrigSize(vecResult);
	resultOriginalSize == 5 ? printf("PASS ") : printf("FAIL ");
	resultSize = GetVecSize(vecResult);
	resultSize == 5 ? printf("PASS ") : printf("FAIL ");
	resultNItems = GetVecNItems(vecResult);
	resultNItems == 1 ? printf("PASS ") : printf("FAIL ");
	resultBlockSize = GetVecBlockSize(vecResult);
	resultBlockSize == 2 ? printf("PASS ") : printf("FAIL ");
	printf("\nTests for VectorAppend() for incorrect inputs:\n");
	resultStatus = VectorAppend(NULL, item);
	resultStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	vecResult = VectorCreate(2, 0);
	resultStatus = VectorAppend(vecResult, NULL);
	resultStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resultStatus = VectorAppend(vecResult, item);
	resultStatus = VectorAppend(vecResult, item);
	resultStatus = VectorAppend(vecResult, item);
	resultStatus == VECTOR_OVERFLOW_ERROR ? printf("PASS ") :
		printf("FAIL ");
	VectorDestroy(&vecResult, NULL);
	printf("\n");
}

void TestVectorRemove(void) {
	Vector* vecResult;
	int temp = 2;
	void* item;
	size_t resultOriginalSize;	
	size_t resultSize;			
	size_t resultNItems;		
	size_t resultBlockSize;
	VectorResult resultStatus;
	printf("\nTests for VectorRemove() for correct inputs:\n");
	vecResult = VectorCreate(5, 2);
	VectorAppend(vecResult, &temp);
	VectorRemove(vecResult, &item);
	resultNItems = GetVecNItems(vecResult);
	resultNItems == 0 ? printf("PASS ") : printf("FAIL ");
	*(int*)item == 2 ? printf("PASS ") : printf("FAIL ");
	printf("\nTests for VectorRemove() for incorrect inputs:\n");
	VectorAppend(vecResult, &temp);
	resultStatus = VectorRemove(NULL, &item);
	resultStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resultStatus = VectorRemove(vecResult, NULL);
	resultStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resultStatus = VectorRemove(vecResult, &item);
	resultStatus = VectorRemove(vecResult, &item);
	resultStatus = VectorRemove(vecResult, &item);
	resultStatus == VECTOR_UNDERFLOW_ERROR ? printf("PASS ") :
		printf("FAIL ");
	VectorDestroy(&vecResult, NULL);
	printf("\n");
}

void ChecksForVectorGet(void) {
	Vector* ptrvec;
	VectorResult resStatus;
	int val1 = 10, val2 = 11, val3 = 12, val4 = 13;
	void* item;
	printf("\nTests for VectorGet() for correct inputs:\n");
	ptrvec = VectorCreate(4, 1);
	VectorAppend(ptrvec, &val1);
	VectorAppend(ptrvec, &val2);
	VectorAppend(ptrvec, &val3);
	VectorAppend(ptrvec, &val4);
	resStatus = VectorGet(ptrvec, 3, &item);
	resStatus == VECTOR_OK ? printf("PASS ") : printf("FAIL ");
	*(int*)item == 13 ? printf("PASS ") : printf("FAIL ");
	VectorGet(ptrvec, 3, &item);
	
	printf("\nTests for VectorGet() for incorrect inputs:\n");
	resStatus = VectorGet(NULL, 3, &item);
	resStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resStatus = VectorGet(ptrvec, 3, NULL);
	resStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resStatus = VectorGet(NULL, 3, NULL);
	resStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resStatus = VectorGet(ptrvec, 5, &item);
	resStatus == VECTOR_WRONG_INDEX ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrvec, NULL);
	putchar('\n');
}

void ChecksForVectorSet(void) {
	Vector* ptrvec = NULL;
	VectorResult resStatus;
	int val1 = 10, val2 = 11, val3 = 12, val4 = 13, val10 = 20;
	void* item;
	printf("\nTests for VectorSet() for correct inputs:\n");
	ptrvec = VectorCreate(4, 1);
	VectorAppend(ptrvec, &val1);
	VectorAppend(ptrvec, &val2);
	VectorAppend(ptrvec, &val3);
	VectorAppend(ptrvec, &val4);
	VectorSet(ptrvec, 0, &val10);
	VectorSet(ptrvec, 1, &val10);
	VectorSet(ptrvec, 2, &val10);
	resStatus = VectorSet(ptrvec, 3, &val10);
	resStatus == VECTOR_OK ? printf("PASS ") : printf("FAIL ");
	VectorGet(ptrvec, 3, &item);
	*(int*)item == val10 ? printf("PASS ") : printf("FAIL ");
	printf("\nTests for VectorSet() for incorrect inputs:\n");
	resStatus = VectorSet(NULL, 0, &val2);
	resStatus == VECTOR_UNITIALIZED_ERROR ? printf("PASS ") :
		printf("FAIL ");
	resStatus = VectorSet(ptrvec, 6, &val2);
	resStatus == VECTOR_WRONG_INDEX ? printf("PASS ") : printf("FAIL ");
	VectorDestroy(&ptrvec, NULL);
	putchar('\n');
}

/*
void TestVectorForEach(void) {
	Vector* ptrvec = NULL;
	VectorResult resStatus;
	int val1 = 10, val2 = 11, val3 = 12, val4 = 13;
	void* item;
	printf("\nTests for VectorForEach() for invalid inputs:\n");
	VectorAppend(ptrvec, &val1);
	VectorAppend(ptrvec, &val2);
	VectorAppend(ptrvec, &val3);
	VectorAppend(ptrvec, &val4);
	resStatus = VectorForEach(ptrvec, NULL, NULL);
	resStatus = VectorForEach(NULL, NULL, NULL);
	printf("PASS ");
	printf("\nTests for VectorForEach() for valid inputs:\n");
	resStatus = VectorForEach(ptrvec, , item)
	putchar('\n');
	VectorDestroy(&ptrvec, NULL);
}
void TestAction(void* _element, size_t _index, void* _context) {
	printf("T\nE\nS\nT\n");
}
*/
/*
typedef int	(*VectorElementAction)(void* _element, size_t _index,
									void* _context);
*/

