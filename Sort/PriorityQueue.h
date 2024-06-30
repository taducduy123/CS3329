#ifndef	 PRIORITYQUEUE_H
#define	 PRIORITYQUEUE_H
#include <iostream>
using namespace std;

class PriorityQueue
{
	private:
		class Node
		{
			public:
				int priority;
				string data;
			
				//Default Constructor (If you don't have default constructor, memory allocation of type Node doesn't work
				Node()
				{}
				//Constructor with arguments
				Node(int priority, string data)
				{
					this->priority = priority;
					this->data = data;	
				}	
				//Overloading operator =
				const Node operator= (const Node &obj)
				{
					this->priority = obj.priority;
					this->data = obj.data;
					return *this;
				}
				//Overloading operator <<
				friend ostream &operator << (ostream &out, const Node &obj)
				{
					out << "(" << obj.data << ", " << obj.priority << ")";
					return out;
				}
		};
		Node *A;
		int CAP;
		int size;
		
		//Parent, Left, Right
		int Parent(int i)
		{return (i-1)/2;}
		int Left(int i)
		{return 2*i+1;}
		int Right(int i)
		{return 2*i+2;}
		//Heapify
		void heapify(int size, int i);
		//swap
		void swap(Node &a, Node &b)
		{
			Node temp = a;
			a = b;
			b = temp;
		}
		
	public:
		//Constructor
		PriorityQueue(int CAP)
		{
			this->CAP = CAP;
			this->size = 0;
			this->A = new Node[CAP];		
		}
		
		//Destructor
		~PriorityQueue()
		{delete [] A;}
		
		//enqueue
		void enqueue(int priority, string data);
		
		//dequeue
		void dequeue();
		
		//front
		string front();
		
		//back
		string back();

		//size
		int getSize()
		{return this->size;}
		
		//Overloading operator
		friend ostream &operator << (ostream &out, const PriorityQueue &obj);	
};


#endif
