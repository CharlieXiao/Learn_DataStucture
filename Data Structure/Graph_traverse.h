#pragma once
#include "Graph.h"
#include "Heap.h"
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

//�����޻�ͼ����������

void topsort_nonrecursive(Graph* G) // ���ö���ʵ��
{
	queue<int> q;
	const int n = G->n();
	int i, j;
	int* count = new int[n];
	for (i = 0; i < n; i++)
		count[i] = 0;
	//����ÿһ���ڵ�����
	for (i = 0; i < n; i++)
	{
		for (j = G->first(i); j < n; j = G->next(i, j))
		{
			count[j]++;
		}
	}
	//�����Ϊ��Ľڵ���������
	for (i = 0; i < n; i++)
	{
		if (count[i] == 0)
		{
			q.push(i);
		}
	}

	//������������
	while (!q.empty())
	{
		i = q.front();
		q.pop();
		cout << i << endl;
		for (j = G->first(i); j < n; j = G->next(i, j))
		{
			count[j]--;
			//�ڵ������������Ϊ��Ľڵ�Ҳ���������
			if (count[j] == 0)
			{
				q.push(j);
			}
		}
	}
	delete[] count;
}

void tophelp(Graph* G, int v)
{
	G->setMark(v, 1);//����״̬��Ϊ�ѷ���
	for (int w = G->first(v); w < G->n(); w = G->next(v, w))
	{
		if (G->getMark(w) == 0)
		{
			tophelp(G, w);
		}
	}
	//���ᵹ�������������
	cout << v << endl;
}

void topsort_recursive(Graph* G)
{
	int i;
	for (i = 0; i < G->n(); i++)
	{
		G->setMark(i, 0);
	}
	for (i = 0; i < G->n(); i++)
	{
		if (G->getMark(i) == 0)//���i��δ���ʵĻ���������ӽڵ�
		{
			tophelp(G, i);
		}
	}
}

void PrintPath(int *P, int i,int a)
{
	if (i == a)
	{
		cout << a;
		return;
	}
	PrintPath(P,P[i],a);
	cout <<" -> "<< i;
}

//��Դ���·����Dijkstra��
void Dijkstra(Graph* G, int *D,int *Pre,int a)//���a�㵽�����������·��
{
	const int n = G->n();
	int i,j,v,Min;

	for (i = 0; i < n; i++)//��D��ʼ��Ϊ����
	{
		D[i] = INF;
		G->setMark(i, 0);//�����нڵ�����Ϊδ����
	}
	D[a] = 0;

	for (i = 0; i < n; i++)
	{
		//�ҵ���һ��δ�����ʵĽڵ�
		Min = INF, v = -1;

		for (j = 0; j < n; j++)
		{
			if (G->getMark(j) == 0 && Min > D[j])
			{
				v = j;
				Min = D[j];
			}
		}
		
		if (Min == INF)//�������еĽڵ㶼�����ʹ���
			return;

		G->setMark(v, 1);

		for (j = G->first(v); j < n; j = G->next(v, j))
		{
			if (D[j] > (D[v] + G->weight(v, j)))
			{
				D[j] = D[v] + G->weight(v, j);
				Pre[j] = v;
			}
		}
	}
}

class DijkElem {
public:
	int vertex;
	int distance;
	DijkElem()
	{
		vertex = -1;
		distance = -1;
	}

	DijkElem(int v, int d)
	{
		vertex = v;
		distance = d;
	}
};

class Comp {
public:
	static bool prior(DijkElem a, DijkElem b)//����ԽС���ȼ�Խ��
	{
		return a.distance < b.distance;
	}
};

void Dijkstra_PriorityQueue(Graph* G, int *D,int *Pre, int a)
{
	int i, v, w;
	DijkElem* E = new DijkElem[G->e()], temp(0,a);
	E[0] = temp;
	heap<DijkElem, Comp> h(E,1,G->e());

	for (i = 0; i < G->n(); i++)
	{
		D[i] = INF;
		G->setMark(i,0);
	}

	D[a] = 0;

	for (i = 0; i < G->n(); i++)
	{
		do
		{
			if (h.size() == 0)
				return;
			temp = h.removefirst();
			v = temp.vertex;
		} while (G->getMark(v) == 1);
		G->setMark(v, 1);
		if (D[v] == INF)
			return;
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
		{
			if (D[w] > D[v] + G->weight(v, w))
			{
				D[w] = D[v] + G->weight(v, w);
				temp.distance = D[w];
				temp.vertex = w;
				Pre[w] = v;
				h.insert(temp);
			}
		}
	}

}