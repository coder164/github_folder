#include <stdio.h>
#include <math.h>   /* for pow() */
#define ARRAY_SIZE (7)
#define INT_SIZE_IN_BITS (32)
#define BIGGEST_POWER (INT_SIZE_IN_BITS - 1)

/*
question:
suppose you have an array of ints where except for one integer all the
others occurs triple times in the array.
how will you find the single value with complexity of O(n)?

first method:
declare array of 32 inegers and initialize all values to zeroes.
then loop over the given array 32 times and in each iteration if
the most left bit is 1 then raise the current place in the
assistant array that you created by one. else remain it the same.
in each iteration also shift left by one the current number in the
given array. when it finishes then your assistant array will have
something like 
[3, 3, 3, 0, 0, 3, 1, 0, 3, 0, 1, 0, 3, 3, 1, 0, 3 ..., 0]
than you can extract from where there is only '1' that its bit
is of the single number and the '3' is of all the other numbers.
the '0' representing only shift of the number by one bit.
then if you do on each value in that array %3 then only the
single integer will be represented. so next thing is to extract that
number from that array.

the second method is very similar:
declare array of 32 inegers and initialize all values to zeroes.
then uprise by one the index of what bit is on in each number.
when it finishes then your bits array will have
something like 
[3, 3, 3, 0, 0, 3, 1, 0, 3, 0, 1, 0, 3, 3, 1, 0, 3 ..., 0]
if you do %3 on each valu in the bits array then all of the triplets
will be zero and you will left with only the bits that representing
the single number. then you can extract that and you will get your
number. 
*/

unsigned int FirstMethod( int _givenArray[], int _arraySize);
unsigned int SecondMethod(const int _givenArray[], int _arraySize);
void PrintArrayInBits(unsigned int _arr[], unsigned int _size);
unsigned int EvaluateNumber(unsigned int _arr[], unsigned int _size);

int main()
{
    int givenArray[ARRAY_SIZE] = {1, 1, 1, 2147483646, 3, 3, 3};
    int desiredNumber = 0;

    desiredNumber = SecondMethod(givenArray, ARRAY_SIZE);
    printf("Desired number = %d from SecondMethod()\n", desiredNumber);

    desiredNumber = 0;
    desiredNumber = FirstMethod(givenArray, ARRAY_SIZE);
    printf("Desired number = %d from FirstMethod()\n", desiredNumber);

    return 0;
}

unsigned int SecondMethod(const int _givenArray[], int _arraySize)
{
    unsigned int bitsArray[INT_SIZE_IN_BITS] = {0};
    unsigned int i, j;
    for (i = 0; i < _arraySize; ++i)
    {
        for (j = 0; j < INT_SIZE_IN_BITS; ++j)
        {
            if (_givenArray[i] &
                (unsigned int)pow(2, (BIGGEST_POWER - j)) )
            {
                bitsArray[j] += 1;
            }
        }
    }
    return EvaluateNumber(bitsArray, INT_SIZE_IN_BITS);
}

unsigned int FirstMethod(int _givenArray[], int _arraySize)
{
    unsigned int bitsArray[INT_SIZE_IN_BITS] = {0};
    unsigned int i, j;
    for (i = INT_SIZE_IN_BITS; i != 0; --i)
    {
        for (j = 0; j < _arraySize; ++j)
        {
            if (_givenArray[j] & 1)
            {
                bitsArray[i - 1] += 1;
            }
            _givenArray[j] >>= 1;
        }
    }
    return EvaluateNumber(bitsArray, INT_SIZE_IN_BITS);
}

void PrintArrayInBits(unsigned int _arr[], unsigned int _size)
{
    unsigned int i;
    unsigned int countForSpace = 4;
    for (i = 0; i < _size; ++i, --countForSpace)
    {
        if (0 == countForSpace)
        {
            putchar(' ');
            countForSpace = 4;
        }
        printf("%d ", _arr[i]);
    }
    printf("\n\n");
}

unsigned int EvaluateNumber(unsigned int _arr[], unsigned int _size)
{
    long int i;
    unsigned int number = 0;
    for (i = 0; i < _size; ++i)
    {
        _arr[i] %= 3;
    }
    for (i = _size - 1; i >= 0; --i)
    {
        if (_arr[i] != 0)
        {
            number += pow(2, (_size - i - 1));
        }
    }
    return number;
}
