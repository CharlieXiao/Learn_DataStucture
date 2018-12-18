#include "ListGraph.h"
#include "Graph_traverse.h"
#include <iostream>
using namespace std;

int main()
{
	GraphL *m = new GraphL(6);
	int *Pre = new int[m->n()];
	int *D = new int[m->n()];
	m->setEdge(0, 2, 7);
	m->setEdge(2, 0, 7);
	m->setEdge(0, 4, 9);
	m->setEdge(4, 0, 9);
	m->setEdge(1, 2, 5);
	m->setEdge(2, 1, 5);
	m->setEdge(1, 5, 6);
	m->setEdge(5, 1, 6);
	m->setEdge(2, 3, 1);
	m->setEdge(3, 2, 1);
	m->setEdge(2, 5, 2);
	m->setEdge(5, 2, 2);
	m->setEdge(3, 5, 2);
	m->setEdge(5, 3, 2);
	m->setEdge(4, 5, 1);
	m->setEdge(5, 4, 1);
	
	Prim_PriorityQueue(m, D,0);
	//PrintPath(Pre, 4, 0);

	delete m;
	delete[] Pre;
	delete[] D;
	return 0;
}