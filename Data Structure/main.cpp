#include "ListGraph.h"
#include "Graph_traverse.h"
#include <iostream>
using namespace std;

int main()
{
	GraphL *m = new GraphL(6);
	m->setEdge(0, 2, 1);
	m->setEdge(2, 0, 1);
	m->setEdge(0, 4, 1);
	m->setEdge(4, 0, 1);
	m->setEdge(1, 2, 1);
	m->setEdge(2, 1, 1);
	m->setEdge(1, 5, 1);
	m->setEdge(5, 1, 1);
	m->setEdge(2, 5, 1);
	m->setEdge(5, 2, 1);
	m->setEdge(3, 5, 1);
	m->setEdge(5, 3, 1);
	m->setEdge(4, 5, 1);
	m->setEdge(5, 4, 1);
	m->setEdge(2, 3, 1);
	m->setEdge(3, 2, 1);
	//DFS_Traverse(m);
	//cout << endl;
	DFS_Traverse(m);
	delete m;
	return 0;
}