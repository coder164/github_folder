#include <stdio.h>
#include <stdlib.h>
#include "gensort.h"
#define OK 0
#define SIZE 5

int SmallToBig(const void* _first, const void* _second);
void PrintArrInt(int* _arr, int _size);
void TestGenSort(void);
int SmallToBigArrs(const void* _first, const void* _second);
void PrintIntPtrs(int** _arrPtrs, int _size);
typedef struct Person Person;
struct Person {
	int id;
	char name[30];
	int age;
};
int IncreasePerson(const void* _first, const void* _second);
void PrintPersons(Person* _studetns, int _size);

int main() {
	TestGenSort();
	return OK;
}

void TestGenSort(void) {
	Person arrStudents[SIZE] = {{4, "lev4", 34}, {0, "lev0", 30}, 
		{2, "lev2", 32}, {1, "lev1", 31}, {3, "lev3", 33}};
	int i;
	int arr[] = {10, 6, 8, 35, 7};
	int* arrPtrs[SIZE];
	for (i = 0; i < SIZE; ++i) {
		arrPtrs[i] = &arr[i];
	}
	
	PrintArrInt(arr, SIZE);
	GenSort(arr, sizeof(int), SIZE, SmallToBig);
	PrintArrInt(arr, SIZE);
	printf("Test for integers sort: 	PASS\n");
	GenSort(NULL, sizeof(int), SIZE, SmallToBig);
	printf("Test for input NULL: 		PASS\n");
	
	GenSort(arrPtrs, sizeof(int*), SIZE, SmallToBigArrs);
	PrintIntPtrs(arrPtrs, SIZE);
	printf("Test for array of pointers:	PASS\n");
	PrintPersons(arrStudents, SIZE);
	GenSort(arrStudents, sizeof(Person), SIZE, IncreasePerson);
	PrintPersons(arrStudents, SIZE);
	printf("Test for struct person: 	PASS\n");

}
int SmallToBig(const void* _first, const void* _second)
{
	return (*(int*)_first) > (*(int*)_second);
}

int SmallToBigArrs(const void* _first, const void* _second)
{
	return (**(int**)_first) > (**(int**)_second);
}

int IncreasePerson(const void* _first, const void* _second)
{
	return (*(Person*)_first).id > (*(Person*)_second).id;
}

void PrintArrInt(int* _arr, int _size)
{
	int i;
	for (i = 0; i < _size; i++)
	{
		printf("%d ", _arr[i]);
	}
	putchar ('\n');
}

void PrintIntPtrs(int** _arrPtrs, int _size)
{
	int i;
	for (i = 0; i < _size; i++)
	{
		printf("%d ", *_arrPtrs[i]);
	}
	putchar ('\n');
}

void PrintPersons(Person* _studetns, int _size)
{
	int i;
	for (i = 0; i < _size; i++)
	{
		printf("%d ", (_studetns[i]).id);
	}
	putchar ('\n');
}
