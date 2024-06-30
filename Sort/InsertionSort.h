#ifndef  INSERTIONSORT_H
#define  INSERTIONSORT_H
#include <iostream>
using namespace std;

//************************************************************************************************
//                                  Insertion Sort (Version 1) 									 *
//************************************************************************************************
void InsertionSort_Version1(int *A, const int size)
{
	for(int i = 1; i < size; i++)											// #Comparisons = (n-1)+1 = n
	{
		int j = 0;					//Insert position
		while(A[i] > A[j])												    // #Comparisons = (1+1)+(2+1)+(3+1)+...+(n-1+1) 
		{																	//				= (n^2+n-2)/2
			j++;
		}
		//Insert A[i] into correct position among a[0],a[1],...,a[i-1]
		//Notice the case the array only has 2 elements
		int temp = A[i];				
		for(int k = i; k > j; k--)											// #Comparisons = (1+1)+(2+1)+...+(n-1+1)
		{																	//				= (n^2+n-2)/2		   
			A[k] = A[k-1];
		}	
		A[j] = temp;				
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
The worst case: a[0] > a[1] > a[2] > ... > a[n-1]. In this case the insert position, j, is 0

#Comparisons = n + (n^2+n-2) = n^2+2n-2

=> Big-Theta(n^2)
*/


//---------------------------------------------------------------------------------------------------------------------------------------------


//************************************************************************************************
//                                  Insertion Sort (Version 2) 									 *
//************************************************************************************************
void InsertionSort_Version2(int *A, const int size)
{
	for(int i = 1; i < size; i++)											// #Comparisons = (n-1)+1 = n
	{
		int key = A[i];
		//Insert A[i] into the sorted sequence A0,A1,..,A_i-1
		int j = i - 1;						
		while(j >= 0 && A[j] > key)										    // #Comparisons = 2[1+2+...+(n-1)] = n(n-1)
		{
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = key;						
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
The worst case: a[0] > a[1] > a[2] > ... > a[n-1]

#Comparisons = n + n(n-1) = n^2

=> Big-Theta(n^2)
*/


//---------------------------------------------------------------------------------------------------------------------------------------------


//************************************************************************************************
//                                  Insertion Sort (Version 3) 									 *
//************************************************************************************************
void InsertionSort_Version3(int *A, int first, int last)
{
	if(first < last)										// #Comparisons = 1
	{
		InsertionSort_Version3(A, first, last-1);			// #Comparisons = T(n-1)
		
		//Insert a[n-1] into correct position among n-1 precede elements a[0], a[1], a[2],..., a[n-2] 
		//Notice that these n-1 elements are already sorted.
		int key = A[last];
		int j = last - 1;				//Insert position
		while(j >= first && A[j] > key)						// #Comparisons = 2(n-1)+1 = 2n-1 for the worst cast
		{
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = key;	
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------
The worst case: a[0] > a[1] > a[2] > ... > a[n-1].
Let T(n) be the number of comparisons required for sorting list of size n. Then, we get
			T(1) = 1
			T(n) = T(n-1)+2n,	for n > 1	
Therefore,
			T(n) = T(1) + 2(2+3+4+...+n)
			     = 1 + n^2+n-2
				 = n^2+n-1
			
=> Big-Theta(n^2)
*/
#endif
