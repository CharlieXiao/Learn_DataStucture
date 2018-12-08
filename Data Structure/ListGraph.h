#pragma once
#include "Graph.h"
#include "List.h"
#include "LList.h"
#include <iostream>
using std::cout;
using std::endl;

class Edge {
private:
	int vert;//边所指向的顶点
	int wt;

public:
	Edge()
	{
		vert = -1;
		wt = -1;
	}

	Edge(int v, int w)
		:vert(v), wt(w){}

	int vertex() const
	{
		return vert;
	}

	int weight() const
	{
		return wt;
	}

	~Edge(){}
};

class GraphL
	:public Graph
{
private:
	List<Edge>** vertex;
	int numVertex;
	int numEdge;
	int *mark;

public:
	GraphL(int numVert)
	{
		Init(numVert);
	}

	~GraphL()
	{
		delete[] mark;
		for (int i = 0; i < numVertex; i++)
			delete[] vertex[i];
		delete[] vertex;
	}

	void Init(int n)
	{
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[numVertex];
		for (i = 0; i < numVertex; i++)
			mark[i] = 0;
		vertex = (List<Edge>**) new List<Edge>*[numVertex];
		for (i = 0; i < numVertex; i++)
		{
			vertex[i] = new LList<Edge>();
		}
	}

	int n()
	{
		return numVertex;
	}

	int e()
	{
		return numEdge;
	}

	int first(int v)
	{
		if (vertex[v]->length() == 0)
			return numVertex;
		vertex[v]->moveToStart();
		Edge it = vertex[v]->getValue();
		return it.vertex();
	}

	int next(int v, int w)
	{
		Edge it;
		if (isEdge(v, w))
		{
			if ((vertex[v]->currPos() + 1) < vertex[v]->length())
			{
				vertex[v]->next();
				it = vertex[v]->getValue();
				return it.vertex();
			}
		}
		return numVertex;
	}

	void setEdge(int i, int j, int weight)
	{
		if (weight <= 0)
		{
			cout << "May not set weight to 0" << endl;
			system("pause");
			exit(-1);
		}
		Edge currEdge(j, weight);
		if (isEdge(i, j))
		{
			vertex[i]->remove();
			vertex[i]->insert(currEdge);
		}
		else
		{
			numEdge++;
			for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next())
			{
				Edge temp = vertex[i]->getValue();
				if (temp.vertex() > j)
					break;
			}
			vertex[i]->insert(currEdge);
		}
	}

	void delEdge(int i, int j)
	{
		if (isEdge(i, j))
		{
			vertex[i]->remove();
			numEdge--;
		}
	}

	bool isEdge(int i, int j)
	{
		Edge it;
		for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next())
		{
			Edge temp = vertex[i]->getValue();
			if (temp.vertex() == j)
				return true;
		}
		return false;
	}

	int weight(int i, int j)
	{
		Edge currEdge;
		if (isEdge(i, j))
		{
			currEdge = vertex[i]->getValue();
			return currEdge.weight();
		}
		else
			return 0;
	}

	int getMark(int v)
	{
		return mark[v];
	}

	void setMark(int v, int val)
	{
		mark[v] = val;
	}

	void print()
	{
		for (int i = 0; i < numVertex; i++)
		{
			for (vertex[i]->moveToStart(); vertex[i]->currPos() < vertex[i]->length(); vertex[i]->next())
				cout << "from " << i << " to " << (vertex[i]->getValue()).vertex() << endl;
		}
	}
};