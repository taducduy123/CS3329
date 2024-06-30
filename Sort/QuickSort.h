#ifndef  QUICKSORT_H
#define  QUICKSORT_H
#include <iostream>
using namespace std;


//************************************************************************************************
//                                    Quick Sort (Version 1)									 *
//************************************************************************************************
void swap(int &value1, int &value2) 
{ 
 	int temp = value1; 
 	value1 = value2; 
 	value2 = temp; 
}

int Partition_Version1(int set[], int start, int end) 
{ 
	int pivotValue, pivotIndex, mid; 
	mid = (start + end) / 2; 
								
	swap(set[start], set[mid]); 						
	pivotIndex = start; 								
	pivotValue = set[start]; 							
	
	for (int scan = start + 1; scan <= end; scan++) 			// # Comparisons = (n-1)+1 = n
	{ 
 		if (set[scan] < pivotValue) 							// # Comparisons = n-1
 		{ 
 			pivotIndex++; 
 			swap(set[pivotIndex], set[scan]); 
 		} 
 	} 
 	swap(set[start], set[pivotIndex]); 
 	return pivotIndex; 
} 

void QuickSort_Version1(int set[], int start, int end) 
{ 
 	if (start < end) 											// # Comparisons = 1
 	{ 
 		// Get the pivot point. 
 		int pivotPoint = Partition_Version1(set, start, end);   // # Comparisons = 2n-1
 		// Sort the left sublist. 
 		QuickSort_Version1(set, start, pivotPoint - 1); 		// # Comparisons = T(a)
 		// Sort the right sublist. 
 		QuickSort_Version1(set, pivotPoint + 1, end); 			// # Comparisons = T(b), where a+b+1 = n
 	} 
} 


/*-------------------------------- Analysis of Complexity ----------------------------------------

Let T(n) be the number of comparisons required for sorting the list of size n. We get
	T(0) = T(1) = 1
	T(n) = T(a) + T(b) + 2n, where n=a+b+1 and n>1

+)  The worst case: the middle element of each sublist (after partition) is the largest value of the sublist

	  	Ex:      3  6  8   9   5  4  7 					
	  	   
		->   	 3  6  8  [9]  5  4  7 					//selected pivot value = 9
	  	->       9  6  8  {3}  5  4  7					//swap 9 <-> 3
	  	==>     {7} 6  8   3   5  4  9					//swap 9 <-> 7
	  	
	    ->       7  6 [8]  3   5  4						//selected pivot value = 8
	    ->       8  6 {7}  3   5  4						//swap 8 <-> 7
	    ==>     {4} 6  7   3   5  8						//swap 8 <-> 4
	     
	    ->       4  6 [7]  3   5                  		//selected pivot value = 7
	    ->       7  6 {4}  3   5                        //swap 7 <-> 4
	    ==>     {5} 6  4   3   7                        //swap 7 <-> 5
	     
	    ->       5 [6] 4   3							//selected pivot value = 6
	    ->      {6} 5  4   3							//swap 6 <-> 5
	    ==>     {3} 5  4   6							//swap 6 <-> 3
	    
	    ->       3  5  4								//selected pivot value = 5
	    ->      {5} 3  4								//swap 5 <-> 3
	    ==>     {4} 3  5								//swap 5 <-> 4
	     
	    
	    ->      [4] 3									//selected pivot value = 4
	    ->      {4} 3									//swap 4 <-> 4
	    ==>   	{3} 4									//swap 4 <-> 3
	    
	    ->      [3]           							//selected pivot value = 3
	    ==>      3
	    
	    []  : the selected pivot value
	    {}  : the value swaps with the pivot value
	    ==> : the list after Partition
	
	  
	For the worst case, T(a) = T(n-1) and T(b) = T(0) = 1. Therefore, we get
		T(n) = T(n-1) + 2n+1
	We deduce that
		T(n) = T(1) + (2*2+1)+(2*3+1)+...+(2*n+1)
		     = 1 + (5+7+9+...+2n+1)
		     = 1 + (n+3)(n-1)
		     = n^2+2n-2
	  	
	=> Big-Theta(n^2)
	

+)  The best case: the list is already sorted
	
	We deduce that T(a) = T(b) = T((n-1)/2). Therefore,
		T(n) = 2T((n-1)/2) + 2n
	We deduce that
		T(n) = (2^k)*T([(n-(2^k - 1)]/[2^k]) + 2n + 2(n-1) + 2(n-3) + 2(n-7) + 2(n-15) + ... + 2(n-(2^(k-1) - 1))
		     = (2^k)*T([(n-(2^k - 1)]/[2^k]) + 2nk - 2(0 + 1 + 3 + ... + 2^(k-1)-1)
		     = (2^k)*T([(n-(2^k - 1)]/[2^k]) + 2nk - 2[(2^0 - 1)+(2^1 - 1)+(2^2 - 1)+...+(2^(k-1) - 1)]
		     = (2^k)*T([(n-(2^k - 1)]/[2^k]) + 2nk - 2[(2^k - 1) - k]											(*)		     
	For simplicity, we assume that n = 2^(k+1) - 1, k>=0, then (*) is equivalent to
	    T(n) = (n+1)/2 * T(1) + 2n(log(n+1)-1) - 2[((n+1)/2 - 1) - (log(n+1)-1)]
	         = (2n+2)log(n+1) - (5n+1)/2
	         
	=> Big-Omega(nlog(n))
*/



//---------------------------------------------------------------------------------------------------------------------------------------------



//************************************************************************************************
//                                   Quick Sort (Version 2)									     *
//************************************************************************************************
int Partition_Version2(int set[], int start, int end)
{
	int pivotValue = set[end];
	int pivotIndex = start - 1;
	
	for(int i = start; i <= end - 1; i++)						// #Comparisons = (n-1)+1 = n
	{
		if(set[i] < pivotValue)									// #Comparisons = n-1
		{
			pivotIndex++;
			swap(set[i], set[pivotIndex]);
		}
	}
	swap(set[end], set[pivotIndex+1]);
	
	return pivotIndex + 1;
}

void QuickSort_Version2(int set[], int start, int end)
{
	if(start < end)												// #Comparisons = 1
	{
		int pivotPoint = Partition_Version2(set, start, end);	// #Comparisons = 2n-1
		QuickSort_Version2(set, start, pivotPoint - 1);			// #Comparisons = T(a)
		QuickSort_Version2(set, pivotPoint + 1, end);			// #Comparisons = T(b), where a+b+1 = n
	}	
}


/*-------------------------------- Analysis of Complexity ----------------------------------------

Let T(n) be the number of comparisons required for sorting the list of size n. We get
	T(0) = T(1) = 1
	T(n) = T(a) + T(b) + 2n, where n=a+b+1 and n>1

+)  The worst case: the list is already sorted.
		T(n) = T(n-1) + 2n+1
	With the similar argument as previous part, we deduce
		T(n) = n^2+2n-2
		
	=> Big-Theta(n^2)
	
	
+) 	The best case: the last element of each sublist is the middle value of the sublist
   	Ex: 2 1 4 5 3
   	
   	Then, T(a) = T(b) = T((n-1)/2). Therefore,
		T(n) = 2T((n-1)/2) + 2n
	With the similar argument as previous, we get
		T(n) = (2n+2)log(n+1) - (5n+1)/2, with the assumption that n = 2^(k+1) - 1, k>=0.
		
	=> Big-Omega(nlog(n))
*/

#endif
