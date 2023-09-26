#include <stdio.h>
#define SIZE_UNSIGNED_CHAR 8
#define SIZE_UNSIGNED_INT 8
#define BITS_IN_BYTE 8
#define BITS_IN_INT (BITS_IN_BYTE * sizeof(int))
#define ARR_LENGTH 256
#define INNER_SIZE 4
#define IS_NOT_EQUAL(num, i, size) \
( ( (num & (1 << i)) == 0 && (num & (1 << size - i - 1)) != 0 ) ||\
( (num & (1 << i)) != 0 && (num & (1 << size - i - 1)) == 0 ) )

static int CountOnBits(unsigned char _ch);
static void PrintUnsigneChar(unsigned char _ch);
static void PrintInts(unsigned int _num);
static void PrintInts2(unsigned int _num);

static int Calculate_Count_Bit_UInt(unsigned int _num);
static int Calculate_Count_Bit_UChar(unsigned char _ch);
static int CountBigNumbers(unsigned int _num, int* _countBitArr);
unsigned int ReverseNum(unsigned int _num);

static int CountBitUIntLUT(unsigned int _num);
static int CountBitUCharLUT(unsigned char _ch);
static int FlipBits(unsigned int _num);

static void BuildReversedArr(unsigned char *_reversedBitArr);
static char ReverseChar(unsigned char _ch);

static int SwapTwoSeq(unsigned int _num);

static int SerachThirdOnBit(unsigned int _num);
static void UppgradedCountBitCharLUT(char* _lut);

static void CalcCountIndexBits(unsigned char* _lut,
	unsigned int _numOfBitsToCheck);
	
static int IndexBitOn(unsigned char _num, unsigned char _numOfBitsOn);
static int LutFor3rdONBit(unsigned int _num);


int main()
{
	unsigned int num1 = 1500;	/* 0101 1101 1100 */
	int num2 = 2;
	printf("%d\n", CountOnBits('0'));
	PrintUnsigneChar('0');
	printf("CountBitUCharLUT: %d\n", CountBitUCharLUT('0'));
	printf("CountBitUIntLUT: %d\n", CountBitUIntLUT(1500));

	printf("ReverseNum ");
	PrintInts2(ReverseNum(num2));

	printf("FlipBits: %d\n", FlipBits(num2));
	
	printf("\nSerachThirdOnBit(%d) : %d\n", num1, SerachThirdOnBit(num1));

	printf("LutFor3rdONBit(%d) = %d\n", num2, LutFor3rdONBit(num2));
	return 0;
}


static int LutFor3rdONBit(unsigned int _num)
{
	static char CountBitArr[ARR_LENGTH];
	static unsigned char arrCountOnBits1[ARR_LENGTH];
	static unsigned char arrCountOnBits2[ARR_LENGTH];
	static unsigned char arrCountOnBits3[ARR_LENGTH];
	int count = 0, prevCount = 0, i, index, temp;
	static int flag;
	if (!flag)
	{
		UppgradedCountBitCharLUT(CountBitArr);
		CalcCountIndexBits(arrCountOnBits1, 1);
		CalcCountIndexBits(arrCountOnBits2, 2);
		CalcCountIndexBits(arrCountOnBits3, 3);
		flag = 1;
	}
	for (i = 0; i < BITS_IN_INT; i += BITS_IN_BYTE)
	{
		if(count >= 3)
		{
			break;
		}
		temp = _num & 0xff;
		prevCount = count;
		count += CountBitArr[temp];
		_num >>= BITS_IN_BYTE;
	}
	if (count < 3)
	{
		return 0;
	}
	switch (prevCount)
	{
		case 0: index = arrCountOnBits3[temp]; break;
		case 1: index = arrCountOnBits2[temp]; break;
		case 2: index = arrCountOnBits1[temp]; break;
		default: break;
	}
	return index + (i - BITS_IN_BYTE);
}

static void UppgradedCountBitCharLUT(char* _lut)
{
	int i, temp, count = 0;
	for (i = 0; i < ARR_LENGTH; ++i)
	{
		temp = i;
		while (temp != 0)
		{
			if (temp & 1)
			{
				++count;
			}
			temp >>= 1;
		}
		_lut[i] = count;
		count = 0;
	}
}

static void CalcCountIndexBits(unsigned char* _lut,
	unsigned int _numOfBitsToCheck)
{
	int i, count = 0;
	char temp;
	for (i = 0; i < ARR_LENGTH; ++i)
	{
		temp = i;
		_lut[i] = IndexBitOn(temp, _numOfBitsToCheck);
	}
}

static int IndexBitOn(unsigned char _num, unsigned char _numOfBitsOn)
{
	int i, count = 0;
	if (0 == _numOfBitsOn)
	{
		return 0;
	}
	for (i = 0; i < ARR_LENGTH && count < _numOfBitsOn; ++i)
	{
		if (_num & (1 << i))
		{
			++count;
			if (count == _numOfBitsOn)
			{
				return i;
			}
		}
	}
}

static int SerachThirdOnBit(unsigned int _num)
{
	int count = 0, index = 0, tempBit = 0;
	while (_num)
	{
		tempBit = _num >> 1;
		if (tempBit & 1)
		{
			++count;
			if (3 == count)
			{
				return index;
			}
		}
		++index;
		_num >>= 1;
	}
	return index + 1; /* case there is no three ON bits */
}

static int FlipBits(unsigned int _num)
{
	int i;
	static int flag;
	static int flipBitArr[ARR_LENGTH];
	if (!flag)
	{	
		for (i = 0; i < ARR_LENGTH; ++i)
		{
			flipBitArr[i] = SwapTwoSeq(i);
		}
		flag = 1;
	}
	return flipBitArr[_num];
}

unsigned int ReverseNum(unsigned int _num)
{
	unsigned int i;
	static int flag;
	static unsigned char ch;
	static unsigned char reversedBitArr[ARR_LENGTH];
	unsigned int res = 0;
	if (!flag)
	{
		BuildReversedArr(reversedBitArr);
		flag = 1;
	}
	for (i = 0; i < INNER_SIZE; ++i)
	{
		ch = _num & 0xff;
		res <<= SIZE_UNSIGNED_CHAR;
		res = res | reversedBitArr[ch];
		_num >>= SIZE_UNSIGNED_CHAR;
	}
	return res;
}

static int CountBitUIntLUT(unsigned int _num)
{
	int i;
	static int flag;
	static int countBitArr[ARR_LENGTH];
	if (!flag)
	{	
		for (i = 0; i < ARR_LENGTH; ++i)
		{
			countBitArr[i] = Calculate_Count_Bit_UInt(i);
		}
		flag = 1;
	}
	return CountBigNumbers(_num, countBitArr);
}

static int CountBitUCharLUT(unsigned char _ch)
{
	int i;
	static char flag;
	static char countBitArr[ARR_LENGTH];
	if (!flag)
	{
		for (i = 0; i < ARR_LENGTH; ++i)
		{
			countBitArr[i] = Calculate_Count_Bit_UChar(i);
		}
		flag = 1;
	}
	return countBitArr[_ch];
}

static int SwapTwoSeq(unsigned int _num)
{
	int i;
	for (i = 0; i < SIZE_UNSIGNED_INT -1; i += 2)
	{
		if 
		( 
			( (_num & (1 << i)) == 0) &&
			((_num & (1 << i + 1)) != 0 ) ||
			( (_num & (1 << i)) != 0) &&
			((_num & (1 << i + 1)) == 0 ) 
		)
		{
			_num = _num ^ (1 << i);
			_num = _num ^ (1 << (i + 1));
		}
	}
	return(_num);
}

static void BuildReversedArr(unsigned char *_reversedBitArr)
{
	int i;
	for (i = 0; i < ARR_LENGTH; ++i)
	{
		_reversedBitArr[i] = ReverseChar((unsigned char)i);
	}
}

static char ReverseChar(unsigned char _ch)
{
	char i;
	for (i = 0; i < SIZE_UNSIGNED_CHAR / 2; ++i)
	{	
		if (IS_NOT_EQUAL(_ch, i, SIZE_UNSIGNED_CHAR))
		{
			_ch = _ch ^ (1 << i);
			_ch = _ch ^ (1 << (SIZE_UNSIGNED_CHAR - i - 1));
		}
	}
	return _ch;
}

static int CountBigNumbers(unsigned int _num, int* _countBitArr)
{
	int slicedNum, count = 0;
	while (_num)
	{
		slicedNum = _num & 0xff; /* 0xff equal 255 same as 1111 1111 */
		count += _countBitArr[slicedNum];
		_num >>= 8;
	}
	return count;
}

static int Calculate_Count_Bit_UInt(unsigned int _num)
{
	int mask = 1;
	int count = 0;
	while (_num)
	{
		if (_num & mask)
		{
			count++;
		}
		_num >>= 1;
	}
	return count;
}

static int Calculate_Count_Bit_UChar(unsigned char _ch)
{
	int mask = 1;
	int count = 0;
	while (_ch)
	{
		if (_ch & mask)
		{
			count++;
		}
		_ch >>= 1;
	}
	return count;
}

static void PrintInts2(unsigned int _num)
{
	int i, size = SIZE_UNSIGNED_CHAR * INNER_SIZE;
	for (i = size; i > 0; i--)
	{
		_num & 1 << size - 1 ? printf("1") : printf("0");
		_num <<= 1;
	}
	putchar('\n');
}

static void PrintInts(unsigned int _num)
{
	int i;
	for (i = SIZE_UNSIGNED_INT; i >= 0; i--)
	{
		_num & 1 << SIZE_UNSIGNED_INT - 1 ? printf("1") : printf("0");
		_num <<= 1;
	}
	putchar('\n');
}

static void PrintUnsigneChar(unsigned char _ch)
{
	int i = 0;
	for (i = 0; i < SIZE_UNSIGNED_CHAR; ++i)
	{
		_ch & 1 << SIZE_UNSIGNED_CHAR  - 1 ? printf("1") : printf("0");
		_ch <<= 1;
	}
	putchar('\n');
}

static int CountOnBits(unsigned char _ch)
{
	int mask = 1;
	int count = 0;
	while (_ch)
	{
		if (_ch & mask)
		{
			count++;
		}
		_ch >>= 1;
	}
	return count;
}

