#ifndef	 GRAPH_H
#define	 GRAPH_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Graph
{
	private:
		int numVertice;
		vector<int> *adjList;
		bool *visited;
		

		//Helpfull Functions
		void tokenlizer(string str, vector<string> &token);
		
	public:
		//Default Constructor
		Graph()
		{}
		
		//Constructor with argument
		Graph(int numVertice)
		{
			this->numVertice = numVertice;
			this->adjList = new vector<int>[numVertice];
			this->visited = new bool[numVertice];	
		}	
		
		//Destructor
		~Graph()
		{
			delete [] adjList;
			delete [] visited;
		}
		
		//Basic Operations
		void openGraph(const string fileName);
		void DFS(int v, bool iniFlag);
		void BFS(int v, bool iniFlag);
		
		//Overloading Operator >>
		friend istream &operator>> (istream &in, Graph &obj);
		//Overloading Operator <<
		friend ostream &operator<< (ostream &out, Graph &obj);
		
		
		
};




#endif
