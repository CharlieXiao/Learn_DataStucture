#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

const int INF = 0x7f7f7f7f;

struct DijkElem {
	int vertax;
	int distance;

	bool operator>(const DijkElem & b) const
	{
		return distance > b.distance;
	}

	bool operator<(const DijkElem & b) const
	{
		return distance < b.distance;
	}
};

class Graph {
private:
	int numVertax, numEdge;
	int **matrix;
	int *mark;

	void bfs_help(int start)
	{
		int v, w;
		queue<int> q;
		q.push(start);
		setMark(start, 1);
		while (!q.empty())
		{
			v = q.front();
			q.pop();
			cout << v << " ";
			for (w = first(v); w < numVertax; w = next(v, w))
			{
				if (getMark(w) == 0)
				{
					setMark(w, 1);
					q.push(w);
				}
			}
		}
	}

	void dfs_help(int start)
	{
		setMark(start, 1);
		cout << start << " ";
		for (int w = first(start); w < numVertax; w = next(start, w))
		{
			if (getMark(w) == 0)
			{
				dfs_help(w);
			}
		}
	}

	bool isCyclicGraph_help(int v, int pre)
	{
		setMark(v, 1);
		for (int w = first(v); w < numVertax; w = next(v, w))
		{
			if (w == pre)
				continue;
			else if (w != pre && getMark(w) == 1)
			{				
				return true;
			}
			else
			{
				return isCyclicGraph_help(w,v);
			}
		}
		return false;
	}

public:
	Graph(int numVert)
	{
		Init(numVert);
	}

	~Graph()
	{
		delete[] mark;
		for (int i = 0; i < numVertax; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	void Init(int n)
	{
		int i;
		numVertax = n;
		numEdge = 0;
		mark = new int[n];
		for (i = 0; i < n; i++)
			mark[i] = 0;
		matrix = (int**) new int*[n];
		for (i = 0; i < n; i++)
			matrix[i] = new int[n];
		for (i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = 0;
	}

	int n()
	{
		return numVertax;
	}

	int e()
	{
		return numEdge;
	}

	int first(int v)
	{
		for (int i = 0; i < numVertax; i++)
			if (matrix[v][i] != 0)
				return i;
		return numVertax;
	}

	int next(int v, int w)
	{
		for (int i = w + 1; i < numVertax; i++)
			if (matrix[v][i] != 0)
				return i;
		return numVertax;
	}

	void setEdge(int v1, int v2, int wt)
	{
		if (wt <= 0)
		{
			cout << "Illegal weight value" << endl;
			system("pause");
			exit(-1);
		}
		if (matrix[v1][v2] == 0)
			numEdge++;
		matrix[v1][v2] = wt;
	}

	void delEdge(int v1, int v2)
	{
		if (matrix[v1][v2] != 0)
			numEdge--;
		matrix[v1][v2] = 0;
	}

	bool isEdge(int v1, int v2)
	{
		return matrix[v1][v2] != 0;
	}

	int weight(int v1, int v2)
	{
		return matrix[v1][v2];
	}

	int getMark(int v)
	{
		return mark[v];
	}

	void setMark(int v, int val)
	{
		mark[v] = val;
	}

	bool isCyclicGraph()//判断图是否有环
	{
		bool flag;
		for (int i = 0; i < numVertax; i++)
		{
			setMark(i, 0);
		}
		for (int i = 0; i < numVertax; i++)
		{
			if (getMark(i) == 0)
			{
				flag = isCyclicGraph_help(i, i);
				if (flag)
					return flag;
			}
		}
		return flag;
	}

	void dfs(int start)
	{
		int v;

		for (v = 0; v < numVertax; v++)
		{
			setMark(v, 0);
		}

		for (v = 0; v < numVertax; v++)
		{
			if (getMark(v) == 0)
			{
				dfs_help(v);
			}
		}
		cout << endl;
	}

	void bfs(int start)
	{
		int v;

		for (v = 0; v < numVertax; v++)
		{
			setMark(v, 0);
		}

		for (v = 0; v < numVertax; v++)
		{
			if (getMark(v) == 0)
			{
				bfs_help(v);
			}
		}
		cout << endl;
	}

	void Dijkstra(int *D)
	{
		const int n = numVertax;
		int i, j, v, Min;

		for (i = 0; i < n; i++)//将D初始化为无穷
		{
			D[i] = INF;
			setMark(i, 0);//将所有节点设置为未访问
		}
		D[0] = 0;

		for (i = 0; i < n; i++)
		{
			//找到第一个未被访问的节点
			Min = INF, v = -1;

			for (j = 0; j < n; j++)
			{
				if (getMark(j) == 0 && Min > D[j])
				{
					v = j;
					Min = D[j];
				}
			}

			if (Min == INF)//代表所有的节点都被访问过了
				return;

			setMark(v, 1);

			for (j = first(v); j < n; j = next(v, j))
			{
				if (D[j] > (D[v] + weight(v, j)))
				{
					D[j] = D[v] + weight(v, j);
				}
			}
		}
	}

	void Dijkstra()
	{
		int *D = new int[numVertax];
		for (int i = 0; i < numVertax; i++)
		{
			D[i] = INF;
			setMark(i, 0);
		}
		D[0] = 0;

		int i, j, v, m;
		DijkElem temp;
		temp.distance = 0;
		temp.vertax = 0;
		priority_queue<DijkElem,vector<DijkElem>,greater<DijkElem>> q;
		q.push(temp);
		for (i = 0; i < numVertax; i++)
		{
			do
			{
				if (q.empty())
				{
					goto Label;
				}
				temp = q.top();
				q.pop();
				v = temp.vertax;
			} while (getMark(v) == 1);
			setMark(v, 1);
			for (j = first(v); j < numVertax; j = next(v, j))
			{
				if (D[j] > D[v] + weight(v, j))
				{
					D[j] = D[v] + weight(v, j);
					temp.distance = D[j];
					temp.vertax = j;
					q.push(temp);
				}
			}
		}

	Label:
		for (m = 1; m < numVertax; m++)
		{
			if (D[m] != INF)
			{
				cout << "0 " << m << " " << D[m] << endl;
			}
			else
			{
				cout << "0 " << m << " 0" << endl;
			}
		}
		delete[] D;
		return;
	}
};

int main()
{
	/*
	priority_queue<DijkElem,vector<DijkElem>,greater<DijkElem>> q;
	DijkElem a, b, c, d;
	a.vertax = 0;
	b.vertax = 0;
	c.vertax = 0;
	d.vertax = 0;
	a.distance = 1;
	b.distance = 1;
	c.distance = 2;
	d.distance = 7;
	q.push(a);
	q.push(b);
	q.push(c);
	q.push(d);
	while (!q.empty())
	{
		cout << q.top().distance << endl;
		q.pop();
	}
	*/
	
	int n, m,i,a,b,w;
	cin >> n >> m;
	Graph g(n);
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> w;
		g.setEdge(a, b, w);
		g.setEdge(b, a, w);
	}
	g.bfs(0);
	g.dfs(0);
	int *D = new int[g.n()];
	g.Dijkstra(D);
	for (int m = 1; m < g.n(); m++)
	{
		if (D[m] != INF)
		{
			cout << "0 " << m << " " << D[m] << endl;
		}
		else
		{
			cout << "0 " << m << " 0" << endl;
		}
	}
	//g.Dijkstra();
	if (g.isCyclicGraph())
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}