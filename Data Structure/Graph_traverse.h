#pragma once
#include "Graph.h"
#include <iostream>
#include <queue>
using namespace std;

void DFS(Graph* G, int v)
{
	//PreVisit
	cout << v << endl;
	G->setMark(v, 1);
	for (int w = G->first(v); w < G->n(); w = G->next(v, w))
		if (G->getMark(w) == 0)
			DFS(G, w);
	//PostVisit
}


void DFS_Traverse(Graph* G)
{
	int v;
	for (v = 0; v < G->n(); v++)
	{
		G->setMark(v, false);
	}
	for (v = 0; v < G->n(); v++)
		if (G->getMark(v) == 0)
			DFS(G, v);
}

void BFS(Graph* G, int start)
{
	queue<int> q;
	int v, w;
	q.push(start);
	G->setMark(start, 1);
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		//PreVisit
		cout <<v << endl;
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
		{
			if (G->getMark(w) == 0)
			{
				q.push(w);
				G->setMark(w, 1);
			}
		}
	}
}

void BFS_Traverse(Graph* G)
{
	int v;
	for (v = 0; v < G->n(); v++)
	{
		G->setMark(v, 0);
	}
	for (v = 0; v < G->n(); v++)
		if (G->getMark(v) == 0)
			BFS(G, v);
}