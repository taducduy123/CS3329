#include "PriorityQueue.h"

//************************************************************************
//Overloading Operator <<												 *
//************************************************************************

ostream &operator << (ostream &out, const PriorityQueue &obj)
{
	for(int i = 0; i < obj.size; i++)
	{
		out << obj.A[i] << " ";
	}
	return out;
}

//************************************************************************
//                           Heapify								     *
//************************************************************************

void PriorityQueue::heapify(int size, int i)
{
	int lChild = Left(i);
	int rChild = Right(i);
	int largest = i;
	
	if(lChild < size && A[lChild].priority > A[largest].priority)
		largest = lChild;
	if(rChild < size && A[rChild].priority > A[largest].priority)
		largest = rChild;
	if(i != largest)
	{
		swap(A[i], A[largest]);
		heapify(size, largest);
	}
}


//************************************************************************
//                          Enqueue								     *
//************************************************************************

void PriorityQueue::enqueue(int priority, string data)
{
	if(size < CAP)
	{
		//1. Append the new element to the tail of the original array
		size++;
		Node newNode(priority, data);
		A[size-1] = newNode;
		
		//2. Modify the new array so that it satisfies the property of max heap
		int i = size - 1;
		int parent = Parent(i);
		while(parent != i && A[i].priority > A[parent].priority)
		{
			swap(A[i], A[parent]);
			i = parent;
			parent = Parent(i);
		} 
	}
	else
	{
		cout << "Cannot Enqueue!" << endl;
	}
}


//************************************************************************
//                            Dequeue								     *
//************************************************************************

void PriorityQueue::dequeue()
{
	if(size > 0)
	{
		//1. Swap the last node with the root node
		swap(A[size-1], A[0]);
		
		//2. Narrow down the array
		size--;
		
		//3. Modify the new array so that it satisfies the property of max heap
		heapify(size, 0);	
	}
	else
	{
		cout << "Cannot Dequeue!" << endl;
	}
}

/*
//************************************************************************
//                          Sort (Descending)							 *
//************************************************************************

void MaxHeap::sort()
{
	int tempSize = size;
	int temp[tempSize];
	for(int i = 0; i < tempSize; i++)
	{
		erase(temp[i]);
	}
	for(int i = 0; i < tempSize; i++)
	{
		insert(temp[i]);
	}
	
}
*/


