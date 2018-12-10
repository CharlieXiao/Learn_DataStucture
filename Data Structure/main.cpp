#include "ListGraph.h"
#include "Graph_traverse.h"
#include <iostream>
using namespace std;

int main()
{
	GraphL *m = new GraphL(5);
	int *Pre = new int[m->n()];
	int *D = new int[m->n()];
	m->setEdge(0, 1, 10);
	m->setEdge(0, 3, 30);
	m->setEdge(0, 4, 100);
	m->setEdge(1, 2, 50);
	m->setEdge(2, 4, 10);
	m->setEdge(3, 2, 20);
	m->setEdge(3, 4, 60);
	
	Dijkstra(m, D,Pre,0);
	PrintPath(Pre, 4, 0);

	delete m;
	delete[] Pre;
	delete[] D;
	return 0;
}