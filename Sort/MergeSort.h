#ifndef  MERGESORT_H
#define  MERGESORT_H
#include <iostream>
#include <limits>
using namespace std;


//************************************************************************************************
//                                        Merge Sort 									         *
//************************************************************************************************
void Merge(int *L, int first, int between, int last)
{
	int sizeL1 = between - first + 1;
	int sizeL2 = last - between;
	
	int L1[sizeL1+1];		//L1 = {L[0], L[1],..., L[between], inf} and assume that L1 is sorted
	L1[sizeL1] = numeric_limits<int>::max();
	for(int i = 0; i < sizeL1; i++)					// #Comparisons = sizeL1 + 1
	{
		L1[i] = L[i];
	}
	
	int L2[sizeL2+1];		//L2 = {L[between+1], L[between+1],..., L[last], inf} and assume that L2 is sorted
	L2[sizeL2] = numeric_limits<int>::max();
	for(int i = 0; i < sizeL2; i++)					// #Comparisons = sizeL2 + 1
	{
		L2[i] = L[i+sizeL1];
	}
	
	int i = 0;		// Index of the-smallest-value element of array L1
	int j = 0;		// Index of the-smallest-value element of array L2
	for(int k = 0; k < sizeL1+sizeL2; k++)		   // #Comparisons = sizeL1 + sizeL2 + 1 = n+1
	{
		if(L1[i] <= L2[j])						   // #Comparisons = sizeL1 + sizeL2 = n
		{
			L[k] = L1[i];
			i++;
		}
		else
		{
			L[k] = L2[j];
			j++;
		}
	}
}


void MergeSort(int *L, int first, int last)
{
	if(last > first)							// #Comparisons = 1
	{
		int middle = (last+first)/2;
		MergeSort(L, first, middle);			// #Comparisons = T(n/2)
		MergeSort(L, middle+1, last);			// #Comparisons = T(n/2)
		Merge(L, first, middle, last);			// #Comparisons = (sizeL1 + 1) + (sizeL2 + 1) + (n+1) + n = 3n+3
	}
}


/*-------------------------------- Analysis of Complexity ----------------------------------------
Assume that list has n = 2^k elements, where k >= 0. 
Let T(n) be the number of comparisons required for sorting the list of size n. We get
		T(1) = 1
		T(n) = 2T(n/2) + 3n+4, for n > 1
Therefore,
		T(n) = 2^k*T(n/(2^k)) + 3kn + 4(2^k - 1)
		     = nT(1) + 3nlog(n) + 4(n-1)
		     = n + 3nlog(n) + 4(n-1)
		     = 3nlog(n) + 5n - 4
		     
=> Big-Theta(nlog(n))
*/


#endif
