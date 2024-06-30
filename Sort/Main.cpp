//#include "BubbleSort.h"
//#include "SelectionSort.h"
//#include "InsertionSort.h"
//#include "MergeSort.h"
//#include "QuickSort.h"
//#include "CountingSort.h"
//#include "RadixSort.h"
//#include "BucketSort.h"
//#include "HeapSort.h"
//#include "PriorityQueue.h"
#include "KMP.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
//Function Prototype
void displayArray(const int *A, const int size);
void displayArray1(const string *A, const int size);
void change(int *ptr);
bool checkAS(int array[], int size);

int main()
{
	srand(time(0));
	
	
	
	const int size = 1000;
	int A[size];
	for(int i = 0; i < size; i++)
	{
		A[i] = (rand() % size);
		if(A[i] % 2 == 0)
			A[i] = -A[i];
		
	}
	
	
	int tSize = 49;
	char T[tSize] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	
	int pSize = 4;
	char P[pSize] = "aab";
	
	KMP_Matcher(T,tSize-1, P,pSize-1);
	
	
	
}


void displayArray(const int *A, const int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << A[i] << " ";
	}
}

void displayArray1(const string *A, const int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << A[i] << endl;
	}
}

void change(int *ptr)
{
	int a = 10;
	cout << "address of local variable = " << &a << endl;
	ptr = &a;
}

bool checkAS(int array[], int size)
{
	for(int i = 0; i < size - 1; i++)
	{
		if(array[i] > array[i+1])
			return false;
	}
	return true;
}
