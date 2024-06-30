#ifndef  HEAPSORT_H
#define	 HEAPSORT_H
#include <iostream>
using namespace std;

int Parent(int i)
{return (i-1)/2;}

int Left(int i)
{return 2*i+1;}

int Right(int i)
{return 2*i+2;
}

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//************************************************************************************************
//                                    Heap Sort (Version 1) 									 *
//This version uses Max Heap to sort the list in ASCENDING order								 *
//************************************************************************************************

void MaxHeapify_Version1(int arr[], int size, int i)
{
	int lChild = Left(i);
	int rChild = Right(i);
	int largest = i;
	
	if(lChild < size && arr[lChild] > arr[largest])						//# Comparisons = 2
		largest = lChild;
	if(rChild < size && arr[rChild] > arr[largest])						//# Comparisons = 2
		largest = rChild;
	if(largest != i)													//# Comparisons = 1
	{
		swap(arr[i], arr[largest]);
		MaxHeapify_Version1(arr, size, largest);						//# Comparisons = T((n-1)/2)
	}
}

void BuildMaxHeap_Version1(int arr[], int size)
{
	for(int i = (size/2)-1; i >= 0; i--)								//# Comparisons = n/2+1
	{
		MaxHeapify_Version1(arr, size, i);								//# Comparisons = 2^{h-2}G(3) + 2^{h-3}G(7) + 2^{h-4}G(15) + 2^{0}G(n)
	}
}

void MaxHeapSort_Version1(int arr[], int size)
{
	BuildMaxHeap_Version1(arr, size);									//# Comparisons = 8n + 8
	for(int i = size-1; i >= 1; i--)									//# Comparisons = (n-1)+1 = n
	{
		swap(arr[0], arr[i]);
		MaxHeapify_Version1(arr, i, 0);									//# Comparisons = 5[log(n-1+1)+log(n-2+1)+...+log(2+1)] 
	}
}

/*-------------------------------- Analysis of Complexity ----------------------------------------

+) 	First, we count the number of comparisons in function MaxHeapify_Version1
	Let n, h be the number of nodes and the height of the complete tree, respectively. We get
			2^(h) - 1 = n
		=>  h = log(n+1)															      (*)
   	Let G(n) be the number of comparisons required to heapify from the root of the tree having n nodes, then
   			G(1) = 5
   			G(n) = T((n-1)/2) + 5
   	Therefore,
   			G(n) = T([n-(2^k - 1)]/2^k] + 5k, where k is any integer >= 1
   				 = T([n-(2^{h-1} - 1)]/2^{h-1}) + 5(h-1)
   				 = T(1) + 5(log(n+1)-1)											  (since (*))
   				 = 5 + 5(log(n+1)-1)
   				 = 5log(n+1)
   				 
+) 	Next, we count the number of comparisons in function BuildMaxHeap_Version1
	Let K(n) be the number of comparisons required for the function BuildMaxHeap_Version1 with input of size n, then
			K(n) = (n-1)/2 + 1 + [2^{h-2}G(3) + 2^{h-3}G(7) + 2^{h-4}G(15) + ... + 2^{0}G(n)
			     = (n-1)/2 + 1 + [2^{h-2}G(2^{2}-1) + 2^{h-3}G(2^{3}-1) + ... + 2^{h-h}G(2^{h}-1)]
			     = (n-1)/2 + 1 + [2^{h-2}*5log(2^2) + 2^{h-3}*5log(2^3) + ... + 2^{0}*5log(2^{h})]
			     = (n-1)/2 + 1 + 5[2*2^{h-2} + 3*2^{h-3} + 4*2^{h-4} + ... + h*2^{0}]
			     = (n-1)/2 + 1 + 5[2^{h-1} + 2*2^{h-2} + 3*2^{h-3} + 4*2^{h-4} + ... + h*2^{0}] - 5*2^{h-1}
			     = (n-1)/2 + 1 + 5*2^{h}[x + 2x^2 + 3x^3 + 4x^4 + 5x^5 + ... + hx^h] - 5*2^{h-1}, where x = 1/2  
				    
    =>  lim K(n) when n -> inf
	             = (n-1)/2 + 1 + 5*2^{h}[x/(1-x)^2] - 5*2^{h-1}
	             = (n-1)/2 + 1 + 5*2^{h}*2 - 5*2^{h-1}							  (since x = 1/2)
	             = (n-1)/2 + 1 + 15*2^{h-1}
	             = (n-1)/2 + 1 + 15*(n+1)/2
	             = 8n + 8
			
+)  Finally, we count the number of comparisons in function MaxHeapSort_Version1
	Let T(n) be the number of comparisons required for the function MaxHeapSort_Version1 with input of size n, then
			T(n) = [8n+8] + n + 5[log(n-1+1)+log(n-2+1)+...+log(2+1)] 
			     = 9n+8 + 5[log(n!) - 1]
			     = 9n+3 + 5log(n!)
			    <= 9n+3 + 5log(n^n)
			     = 9n+3 + 5nlog(n)
			     
	=> O(nlog(n))
*/


//--------------------------------------------------------------------------------------------------------------------------------------------

//************************************************************************************************
//                                    Heap Sort (Version 2) 									 *
//This version uses Max Heap to sort the list in DESCENDING order								 *
//************************************************************************************************
void MaxHeapify_Version2(int arr[], int begin, int end, int i)
{
	if(begin <= i && i <= end)											//# Comparisons = 2
	{
		int lChild = Left(i-begin) + begin;
		int rChild = Right(i-begin) + begin;
		int largest = i;
		
		if(lChild <= end && arr[lChild] > arr[largest])					//# Comparisons = 2
			largest = lChild;
		if(rChild <= end && arr[rChild] > arr[largest])					//# Comparisons = 2
			largest = rChild;
		if(largest != i)												//# Comparisons = 1
		{
			swap(arr[i], arr[largest]);
			MaxHeapify_Version2(arr, begin, end, largest);				//# Comparisons = T((n-1)/2)
		}
	}
	else
	{
		cout << "Invalid i" << endl;
	}
}

void BuildMaxHeap_Version2(int arr[], int begin, int end)
{
	int actualSize = end - begin + 1;
	for(int i = (actualSize/2)-1 + begin; i >= begin; i--)				//# Comparisons = (n-1)/2 + 1 for the worst case that every node has exactly 2 children
	{
		MaxHeapify_Version2(arr, begin, end, i);						//# Comparisons = 2^{h-2}G(3) + 2^{h-3}G(7) + 2^{h-4}G(15) + 2^{0}G(n)
	}
}

void MaxHeapSort_Version2(int arr[], int size)		
{
	for(int i = 0; i < size-1; i++)										//# Comparisons = (n-1)+1 = n	
	{
		BuildMaxHeap_Version2(arr, i, size-1);							//# Comparisons = K(n)+K(n-1)+...+K(2)
	}																	//where K(i) be the number of comparisons required for
}																		//function BuildMaxHeap_Version2 with size i

/*-------------------------------- Analysis of Complexity ----------------------------------------

+) 	First, we count the number of comparisons in function MaxHeapify_Version2
	Let n, h be the number of nodes and the height of the complete tree, respectively. We get
			2^(h) - 1 = n
		=>  h = log(n+1)															      (*)
   	Let G(n) be the number of comparisons required to heapify from the root of the tree having n nodes, then
   			G(1) = 7
   			G(n) = T((n-1)/2) + 7
   	Therefore,
   			G(n) = T([n-(2^k - 1)]/2^k] + 7k, where k is any integer >= 1
   				 = T([n-(2^{h-1} - 1)]/2^{h-1}) + 7(h-1)
   				 = T(1) + 7(log(n+1)-1)											  (since (*))
   				 = 7 + 7(log(n+1)-1)
   				 = 7log(n+1)
   				 
+) 	Next, we count the number of comparisons in function BuildMaxHeap_Version2
	Let K(n) be the number of comparisons required for the function BuildMaxHeap_Version2 with input of size n, then
			K(n) = (n-1)/2 + 1 + [2^{h-2}G(3) + 2^{h-3}G(7) + 2^{h-4}G(15) + ... + 2^{0}G(n)
			     = (n-1)/2 + 1 + [2^{h-2}G(2^{2}-1) + 2^{h-3}G(2^{3}-1) + ... + 2^{h-h}G(2^{h}-1)]
			     = (n-1)/2 + 1 +  [2^{h-2}*7log(2^2) + 2^{h-3}*7log(2^3) + ... + 2^{0}*7log(2^{h})]
			     = (n-1)/2 + 1 + 7[2^h + 2^h + 2^h + ... + 2^h]
			     = (n-1)/2 + 1 + 7(h-1)2^h
			     = (n-1)/2 + 1 + 7(log(n+1)-1)(n+1)
			     = 7(n+1)log(n+1) - (13n+15)/2 + 1
			
+)  Finally, we count the number of comparisons in function MaxHeapSort_Version2
	Let T(n) be the number of comparisons required for the function MaxHeapSort_Version2 with input of size n, then
			T(n) = n + K(n)+K(n-1)+...+K(2)
				<= n + [nlog(n) + (n-1)log(n-1)+...+2log(2)]
				<= n + c[nlog(n) + nlog(n) + ....+ nlog(n)]
				 = n + c(n-1)nlog(n)
	=> O(n^2log(n))
*/










#endif
