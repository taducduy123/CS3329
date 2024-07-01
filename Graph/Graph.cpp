#include "Graph.h"


//**********************************************************************
//				         Depth First Search							   *
//**********************************************************************

void Graph::DFS(int v, bool iniFlag)
{
	if(iniFlag == true)
	{
		for(int i = 0; i < numVertice; i++)
		{
			visited[i] = false;
		}
	}
	else
	{
		visited[v] = true;
		int adj;
		for(int i = 0; i < adjList[v].size(); i++)
		{
			adj = adjList[v][i];
			if(!visited[adj])
			{
				DFS(adj, false);
			}
		}
	}
}









//**********************************************************************
//				       Read Graph From File						       *
//**********************************************************************

void Graph::openGraph(const string fileName)
{
	string str;
	vector<string> numbers;
	fstream file;
	
	//Open input file
	file.open(fileName, ios::in);
	
	//Check if file is successfully opened
	if(file.fail())
	{
		cout << "Unable to open file " + fileName << endl;
		exit(0);
	}
	
	//Working with input file	
	//Read number of vertice?
	int numberOfVertice;
	getline(file, str, '\n');
	numberOfVertice = stoi(str);
	
	this->~Graph();
	this->numVertice = numberOfVertice;
	this->adjList = new vector<int>[numberOfVertice];
	this->visited = new bool[numberOfVertice];	
	//Read adjacent lists
	int i = 0;
	while(file && i < numberOfVertice)
	{
		//Reading each line
		getline(file, str, '\n');
		
		//Tokenlize each line
		numbers.clear();
		tokenlizer(str, numbers);
		
		//Store data
		for(int j = 0; j < numbers.size(); j++)
		{
			this->adjList[i].push_back(stoi(numbers[j]));
		}
		i++;
	}
	
	//Close the file
	file.close();
}



//**********************************************************************
//				       Overloading Operator >>						   *
//**********************************************************************

istream &operator>> (istream &in, Graph &obj)
{
	int adj;
	string str;
	vector<string> numbers;
	for(int i = 0; i < obj.numVertice; i++)
	{
		numbers.clear();
		
		cout << "Enter adjacents of vertex #" << i << " (each separated by at least one space): ";
		getline(cin, str);
		obj.tokenlizer(str, numbers);
		
		for(int j = 0; j < numbers.size(); j++)
		{
			obj.adjList[i].push_back(stoi(numbers[j]));
		}
					
	}
	return in;
}


//**********************************************************************
//				       Overloading Operator <<						   *
//**********************************************************************

ostream &operator<< (ostream &out, Graph &obj)
{
	for(int i = 0; i < obj.numVertice; i++)
	{
		cout << i << " ---> ";
		for(int j = 0; j < obj.adjList[i].size(); j++)
		{
			cout << obj.adjList[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}


//**********************************************************************
//				           tokenlizer								   *
//**********************************************************************

void Graph::tokenlizer(string str, vector<string> &token)
{
	//Trimming input string
	while(str.length() > 0 && isspace(str.at(0)))
	{
		str.erase(0, 1);
	}
	while(str.length() > 0 && isspace(str.at(str.length()-1)))
	{
		str.erase(str.length()-1,1);
	}
	//Append a white-space character to the end of str
	str.append(1, ' ');
	
	//Tokenlize the standard string
	int i = 0;
	int wordLength = 0;
	bool spaceFlag = false;
	
	while(i < str.length())
	{
		if(!isspace(str.at(i)))
		{
			wordLength++;
			if(spaceFlag == true)
			{
				spaceFlag = false;
			}
		}
		else
		{
			if(spaceFlag == false)
			{
				spaceFlag = true;
				token.push_back(str.substr(i-wordLength, wordLength));
				wordLength = 0;
			}	
		}
		i++;
	}
}

