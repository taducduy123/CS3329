#include "Graph.h"

int main()
{
	Graph g(1);
	//cin >> g;
	//cout << g;
	
	g.openGraph("GraphFile.txt");
	cout << g;
	return 0;
	
	
}
