#ifndef COUNTINGSORT_H
#define	COUNTINGSORT_H
#include <iostream>
using namespace std;


//************************************************************************************************
//                                   Counting Sort (Version 1)									 *
//************************************************************************************************
int findMaxValue(int set[], int size)
{
	int max = set[0];
	for(int i = 1; i < size; i++)
	{
		if(set[i] > max)
		{
			max = set[i];
		}
	}
	return max;
}

int findMinValue(int set[], int size)
{
	int min = set[0];
	for(int i = 1; i < size; i++)
	{
		if(set[i] < min)
		{
			min = set[i];
		}
	}
	return min;
}

void CountingSort_Version1(int set[], int size)
{
	int maxValue = findMaxValue(set, size);					 // # Comparisons = (n-1)+1 = n
	int minValue = findMinValue(set, size);					 // # Comparisons = (n-1)+1 = n
	
	//Initialize counter array
	int sizeCounter = maxValue - minValue + 1;
	int counter[sizeCounter];
	for(int i = 0; i < sizeCounter; i++)					// # Comparisons = (max-min+1)+1 = k+1
	{
		counter[i] = 0;
	}
	
	//Count occurence of each element in the set
	for(int i = 0; i < size; i++)						    // # Comparisons = n+1
	{
		counter[set[i] - minValue]++;		//Notice elements in the set can be negative	
	}
	
	//Place indexes of counter array to correct positions in the set
	int j = 0;							
	for(int i = 0; i < sizeCounter; i++)					// # Comparisons = (max-min+1)+1 = k+1
	{
		while(counter[i] > 0)								// # Comparisons = (n1 + 1)+(n2 + 1)+(n3 + 1)+...+(n_k + 1) = n+k 
		{													// where n1,n2,n3,...,n_k are the number of occurences of consecutive
			set[j] = i + minValue;							// values from a1 to a_k (a1, a_k are min and max value in the set), respectively 
			j++;											// (notice a1 < a2 < ... < a_k)
			counter[i]--;
		}
	}	
}


/*-------------------------------- Analysis of Complexity ----------------------------------------
Let n be the size of the list and k be the number of integers from the smallest value to the largest value of the list.
Let T(n) be the number of comparisons required for sorting the list, then
	T(n) = 2n+ (k+1) + (n+1) + (k+1) + (n+k)
	     = 4n + 3k + 3
	     
	=> Big-Theta(n+k), which is Big-Theta(n) only if k = O(n)
	     
	Therefore, the counting sort is feasible only if k = O(n)
*/	  


//---------------------------------------------------------------------------------------------------------------------------------------------


//************************************************************************************************
//                                   Counting Sort (Version 2)									 *
//************************************************************************************************  
void CountingSort_Version2(int set[], int size)
{
	int maxValue = findMaxValue(set, size);					 // # Comparisons = (n-1)+1 = n
	int minValue = findMinValue(set, size);					 // # Comparisons = (n-1)+1 = n
	
	int sizeCounter = maxValue - minValue + 1;
	int counter[sizeCounter];
	
	//1. Initialize the array to count the occurence of elements in the list
	for(int i = 0; i < sizeCounter; i++)
	{
		counter[i] = 0;
	}
	//2. Count the occurrence
	for(int i = 0; i < size; i++)
	{
		counter[set[i] - minValue]++;
	}
	//3. Determine the correct position of each element in the list 
	//(this position is going to be over 1 unit compared to the actual correct position)
	for(int i = 1; i < sizeCounter; i++)
	{
		counter[i] += counter[i-1];
	}
	//4. Place the elements in the list to the correct positions
	int temp[size];
	for(int i = size - 1; i >= 0; i--)		//Notice we must scan from the last to remain the stability
	{
		counter[set[i] - minValue]--;
		temp[counter[set[i] - minValue]] = set[i];
	}
	//Copy temp array to original list
	for(int i = 0; i < size; i++)
	{
		set[i] = temp[i];
	}
} 
#endif
