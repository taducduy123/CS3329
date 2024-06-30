#ifndef  BUBBLESORT_H
#define BuBBLESORT_H
#include <iostream>
using namespace std;

//************************************************************************************************
//                                   Bubble Sort (Version 1) 									 *
//************************************************************************************************

void BubbleSort_Version1(int *A, const int size)
{
	bool swap = true;											
	int temp;												
	while(swap)													// #Comparisons = n+1 
	{
		swap = false;											
		for(int i = 0; i < size - 1; i++)						// #Comparisons = [(n-1)+1]n = n^2
		{
			if(A[i] > A[i+1])									// #Comparisons = (n-1)n
			{
				swap = true;									
				temp = A[i+1];									
				A[i+1] = A[i]; 									
				A[i] = temp;									
			}
		}
	}
}

/*-------------------------------- Analysis of Complexity -----------------------------------------
The worst case: a0 > a1 > a2 > .... > a_n-1, where n is the size of array.

#Comparisons = n+1 + n^2 + (n-1)n = 2n^2 + 1

#Swaps = (n-1)+(n-2)+(n-3)+...+1 = n(n-1)/2

=> Big-Theta(n^2)
*/


//---------------------------------------------------------------------------------------------------------------------------------------------


//************************************************************************************************
//                                   Bubble Sort (Version 2) 									 *
//************************************************************************************************
void BubbleSort_Version2(int *A, const int size)
{
	int temp;
	for(int i = 0; i < size - 1; i++)							// #Comparisons = (n-1)+1 = n
	{
		for(int j = 0; j < (size - 1) - i; j++)					// #Comparisons = (n-1+1)+(n-2+1)+(n-3+1)+...+(1+1) = (n^2+n-2)/2
		{
			if(A[j] > A[j+1])									// #Comparisons = (n-1)+(n-2)+(n-3)+...+1 = n(n-1)/2
			{								
				temp = A[j+1];									
				A[j+1] = A[j]; 									
				A[j] = temp;									
			}
		}
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
The worst case: a0 > a1 > a2 > .... > a_n-1, where n is the size of array.

#Comparisons = n + (n^2+n-2)/2 + n(n-1)/2 = n^2+n-1

#Swaps = (n-1)+(n-2)+(n-3)+...+1 = n(n-1)/2

=> Big-Theta(n^2)
*/
#endif
