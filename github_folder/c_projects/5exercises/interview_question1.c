#include <stdio.h>
#define ARR_SIZE 7
/*
question:
suppose you have an array of ints where except for one integer all the others occurs two times in the array.
how will you find the single value with complexity of O(n)?
answer:
below is the answer
each time you do xor for the same number than it becomes zero.
than only the single number remains.
*/
int main()
{
    int array[ARR_SIZE] = {1, 2, 3, 4, 1, 2, 4};
    int i;
    int number = array[0];	/* number = 1 */

    for (i = 1; i < ARR_SIZE; ++i)
    {
        number ^= array[i];
    }
    printf("%d\n", number);
    
    return 0;
}

/*
	1 ^= 2 = 3
	0000 0001
  ^	0000 0010
  	---------
  	0000 0011

	3 ^= 3 = 0
	0000 0011
  ^	0000 0011
  	---------
	0000 0000

	0 ^= 4 = 4
	0000 0000
  ^	0000 0100
	---------
	0000 0100
	
	4 ^= 1 = 5
	0000 0100
  ^	0000 0001
	---------
	0000 0101
	
	5 ^= 2 = 7
	0000 0101
  ^	0000 0010
	---------
	0000 0111
	
	7 ^= 4 = 3
	0000 0111
  ^	0000 0100
	---------
	0000 0011
	
*/







