#ifndef  SELECTIONSORT_H
#define  SELECTIONSORT_H
#include <iostream>
using namespace std;

//************************************************************************************************
//                                       Selection Sort 									     *
//************************************************************************************************
void SelectionSort(int *A, const int size)
{
	int minIndex;
	int minValue;
	
	for(int i = 0; i < size - 1; i++)					// #Comparisons = (n-1)+1 = n
	{
		minIndex = i;
		minValue = A[i];		
		for(int j = i + 1; j < size; j++)				// #Comparisons = (n-1+1)+(n-2+1)+(n-3+1)+...+(1+1) = (n^2+n-2)/2 
		{
			if(minValue > A[j])							// #Comparisons = (n-1)+(n-2)+...+1 = n(n-1)/2
			{
				minIndex = j;
				minValue = A[j];	
			}	
		}		
		A[minIndex] = A[i];
		A[i] = minValue;
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
The worst case: a[0] > a[1] > a[2] > ... > a[n-1], where n is the size of array.

#Comparisons = n + (n^2+n-2)/2 + n(n-1)/2 = n^2+n-1

#Swaps = n-1

=> Big-Theta(n^2)
*/
#endif
