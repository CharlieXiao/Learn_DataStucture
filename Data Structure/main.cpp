#include "ListGraph.h"
#include "Graph_traverse.h"
#include <iostream>
using namespace std;

int main()
{
	GraphL *m = new GraphL(7);
	m->setEdge(0, 1, 1);
	m->setEdge(0, 2, 1);
	m->setEdge(1, 3, 1);
	m->setEdge(1, 5, 1);
	m->setEdge(1, 4, 1);
	m->setEdge(2, 4, 1);
	m->setEdge(4, 5, 1);
	m->setEdge(5, 6, 1);
	//DFS_Traverse(m);
	//cout << endl;
	topsort_nonrecursive(m);
	cout << endl;
	topsort_recursive(m);
	delete m;
	return 0;
}