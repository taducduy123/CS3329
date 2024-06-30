#ifndef	 RADIXSORT_H
#define	 RADIXSORT_H
#include <iostream>
#include <cmath>
using namespace std;


//************************************************************************************************
//                                    Radix Sort (Version 1)									 *
//************************************************************************************************

int findMaxValue(int set[], int size)
{
	int max = set[0];
	for(int i = 1; i < size; i++)											//# Comparisons = (n-1)+1 = n
	{
		if(set[i] > max)													//# Comparisons = n-1
		{
			max = set[i];
		}
	}
	return max;
}

int findMinValue(int set[], int size)
{
	int min = set[0];
	for(int i = 1; i < size; i++)											//# Comparisons = (n-1)+1 = n
	{
		if(set[i] < min)													//# Comparisons = n-1
		{
			min = set[i];
		}
	}
	return min;
}

int findNumberOfDigits(int number)
{
	int numDigits = 1;
	while(abs(number) >= pow(10, numDigits))								//# Comparisons = m
	{
		numDigits++;
	}
	return numDigits;
}

int findMaxNumDigits(int set[], int size)
{
	int maxValue = findMaxValue(set, size);									//# Comparisons = 2n-1
	return findNumberOfDigits(maxValue);									//# Comparisons = m
}

void CountingSort_Version1(int set[], int size, int d)
{
	int maxNumDigits = findMaxNumDigits(set, size);							//# Comparisons = (2n+m-1)
	int digits[size];
	if(d <= maxNumDigits)													//# Comparisons = 1
	{
		//Collect the digit at d-th position of each number
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			digits[i] = (set[i] % ((int)pow(10, d))) / ((int)pow(10, d-1));
		}
	}
	else
	{
		//Collect the sign of each number									
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			if(set[i] >= 0)													//# Comparisons = n
				digits[i] = 1;		//positive
			else
				digits[i] = 0;		//negative
		}
	}
	
	//1. Initialize counter array
	int maxValue = findMaxValue(digits, size);								//# Comparisons = 2n-1
	int minValue = findMinValue(digits, size);								//# Comparisons = 2n-1
	int countSize = maxValue - minValue + 1;								
	int count[countSize];
	for(int i = 0; i < countSize; i++)										//# Comparisons = k+1
	{
		count[i] = 0;
	}
	//2. Count the occurence of each element in the digits array
	for(int i = 0; i < size; i++)											//# Comparisons = n+1
	{
		count[digits[i] - minValue]++;
	}
	//3. Determine the correct position (over 1 unit)
	for(int i = 1; i < countSize; i++)										//# Comparisons = (k-1)+1 = k
	{
		count[i] += count[i-1];
	}
	//4. Place the elements to the correct positions
	int temp[size];
	//Notice we must scan from the last to maintain the stability
	for(int i = size - 1; i >= 0; i--)										//# Comparisons = n+1
	{
		count[digits[i] - minValue]--;
		temp[count[digits[i] - minValue]] = set[i];
	}
	for(int i = 0; i < size; i++)											//# Comparisons = n+1
	{
		set[i] = temp[i];
	}		
}

void RadixSort_Version1(int set[], int size)
{
	//Find max number of digits in the set
	int maxNumDigits = findMaxNumDigits(set, size);							//# Comparisons = 2n+m-1
	//Apply stable sort (counting sort) for each radix 
	//(notice sign can be considered as a radix)
	for(int i = 1; i <= maxNumDigits + 1; i++)								//# Comparisons = (m+1)+1 = m+2
	{
		CountingSort_Version1(set, size, i);								//# Comparisons = m(10n+m+2k+3) + (11n+m+2k+3)
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
Let n be the number of input numbers
    m be the max amount of digits using for each input number
    k = max value - min value + 1
Let T(n) be the number of comparisons required for sorting list of size n, then
	T(n) = (2n+m-1) + (m+2) + (m(10n+m+2k+3) + (11n+m+2k+3))
	     = 2n+2m+1 + (10mn + m^2 + 2km + 3m + 11n + m + 2k + 3)
	     = (13+10m)n + [m^2 + (6+2k)m + 2k+4] 
Notice that in the worst case, k = 9-0+1 = 10

=> O(mn + m^2), which is O(n^2) only if m = O(n)
*/


//---------------------------------------------------------------------------------------------------------------------------------------------


//************************************************************************************************
//                                    Radix Sort (Version 2)									 *
//************************************************************************************************
const int maxLength = 101;

void CountingSort_Version2(char name[][maxLength], int size, int d)
{
	if(d <= maxLength-1)													//# Comparisons = 1
	{
		//Collect position-at-d character of each name
		char ch[size];
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			ch[i] = name[i][d];
		}
		
		//Find the character whose ACSII value is largest
		int max = ch[0];
		for(int i = 1; i < size; i++)										//# Comparisons = (n-1)+1 = n
		{
			if(ch[i] > max)													//# Comparisons = n-1
			{
				max = ch[i];
			}
		}
		//Find the character whose ACSII value is smallest
		int min = ch[0];
		for(int i = 1; i < size; i++)										//# Comparisons = (n-1)+1 = n
		{
			if(ch[i] < min)													//# Comparisons = n-1
			{
				min = ch[i];
			}
		}
		
		//Initialize an array to count the occurence of each element in ch array
		int countSize = max-min+1;
		int count[countSize];
		for(int i = 0; i < countSize; i++)									//# Comparisons = k+1
		{
			count[i] = 0;
		}
		//Count the occurence of each element in ch array					
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			count[ch[i] - min]++;
		}
		//Determine the correct position of each element in ch array (over 1 unit)
		for(int i = 1; i < countSize; i++)									//# Comparisons = (k-1)+1 = k
		{
			count[i] += count[i-1];
		}
		//Place the element to correct position. Notice we scan from the end of the list
		char temp[size][maxLength];
		for(int i = size-1; i >= 0; i--)									//# Comparisons = n+1
		{
			count[ch[i] - min]--;
			for(int j = 0; j < maxLength; j++)								//# Comparisons = (m+1)n
			{
				temp[count[ch[i] - min]][j] = name[i][j]; 
			}
		}
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			for(int j = 0; j < maxLength; j++)								//# Comparisons = (m+1)n
			{
				name[i][j] = temp[i][j];
			}
		}	
	}	
}

void RadixSort_Version2(char name[][maxLength], int size)
{	
	for(int i = maxLength - 1; i >= 0; i--)									//# Comparisons = m+1
	{
		CountingSort_Version2(name, size, i);								//# Comparisons = m(2mn+10n+2k+4)
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
Let n be the number of input names
    m be the max amount of characters using for each input name
    k = (max ASCII value - min ASCII value) + 1
Let T(n) be the number of comparisons required for sorting list of size n, then
	T(n) = (m+1) + m(2mn+10n+2k+4)
	     = 2(m^2)n + 10mn + (2k+5)m + 1
Notice that k can be considered as a constant

=> O((m^2)n), which is O(n^3) only if m = O(n)
*/


//---------------------------------------------------------------------------------------------------------------------------------------------


//************************************************************************************************
//                                    Radix Sort (Version 3)									 *
//************************************************************************************************

int findMaxLength(string names[], int size)
{
	int max = names[0].length();
	for(int i = 1; i < size; i++)											//# Comparisons = (n-1)+1 = n
	{
		if(names[i].length() > max)											//# Comparisons = n-1
		{
			max = names[i].length();
		}
	}
	return max;
}

int findLargestASCII(char ch[], int size)
{
	int largestValue = ch[0];
	for(int i = 1; i < size; i++)											//# Comparisons = (n-1)+1 = n
	{
		if(largestValue < ch[i])											//# Comparisons = n-1
		{
			largestValue = ch[i];
		}
	}
	return largestValue;
}

int findSmallestASCII(char ch[], int size)
{
	int smallestValue = ch[0];
	for(int i = 1; i < size; i++)											//# Comparisons = (n-1)+1 = n
	{
		if(smallestValue > ch[i])											//# Comparisons = n-1
		{
			smallestValue = ch[i];
		}
	}
	return smallestValue;
}

void CountingSort_Version3(string names[], int size, int d)
{
	if(d >= 0)																//# Comparisons = 1
	{
		//Collect character at d-position of each name
		char character[size];
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			character[i] = names[i][d];
		}
		
		//Initialize an array to count the occurence of each character
		int largestASCII = findLargestASCII(character, size);				//# Comparisons = 2n-1
		int smallestASCII = findSmallestASCII(character, size);				//# Comparisons = 2n-1
		int countSize = largestASCII - smallestASCII + 1;
		int count[countSize];
		for(int i = 0; i < countSize; i++)									//# Comparisons = k+1
		{
			count[i] = 0;
		}
		//Count the occurence of each character
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			count[character[i] - smallestASCII]++;
		}
		//Determine the correct position of each character (over 1 unit)
		for(int i = 1; i < countSize; i++)									//# Comparisons = (k-1)+1 = k
		{
			count[i] += count[i-1];
		}
		//Place names correspoding to the above characters to the correct positions
		//Notice we scan from the end of the list
		string temp[size];
		for(int i = size - 1; i >= 0; i--)									//# Comparisons = n+1
		{
			count[character[i] - smallestASCII]--;
			temp[count[character[i] - smallestASCII]] = names[i];		
		}
		for(int i = 0; i < size; i++)										//# Comparisons = n+1
		{
			names[i] = temp[i];
		}
	}
}   

void RadixSort_Version3(string names[], int size)
{
	int maxLength = findMaxLength(names, size);								//# Comparisons = 2n-1
	for(int i = maxLength - 1; i >= 0; i--)									//# Comparisons = m+1
	{
		CountingSort_Version3(names, size, i);								//# Comparisons = m(8n+2k+4)
	}
}


/*-------------------------------- Analysis of Complexity ----------------------------------------
Let n be the number of input names
	m be the max amount of characters using for each input name
    k = (max ASCII value - min ASCII value) + 1
Let T(n) be the number of comparisons required for sorting list of size n, then
	T(n) = (2n-1) + (m+1) + m(8n+2k+4)
	     = (2+8m)n + (5+2k)m 
Notice that k can be considered as a constant

=> Big-Theta(mn)
*/
#endif
