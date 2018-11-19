#pragma once
#include <iostream>
using std::cout;
using std::endl;
//Heap class

template <typename E,typename Comp>
class heap {
private:
	E* Heap;
	int maxSize;
	int n;

	void swap(E* Heap, int pos1, int pos2)
	{
		int temp = Heap[pos1];
		Heap[pos1] = Heap[pos2];
		Heap[pos2] = temp;
	}

	void siftup(int pos)
	{
		while (pos != 0)
		{
			int par = parent(pos);
			//����ȸ��ڵ����ȼ��͵Ļ�ֱ�ӷ���
			if (Comp::prior(Heap[par], Heap[pos]))
				return;
			//����ȸ��ڵ����ȼ��ߵĻ�,���佻��,������һ��
			swap(Heap,par,pos);
			pos = par;
		}
	}

	void siftdown(int pos)
	{
		while (!isLeaf(pos))
		{
			int MAX = leftchild(pos);
			int rc = rightchild(pos);
			//�������Һ����нϴ��Ǹ�
			if ((rc < n) && Comp::prior(Heap[rc], Heap[MAX]))
				MAX = rc;
			//�Ƚ����ȼ�
			//������ڵ����ȼ����ӽڵ����ȼ�����ֱ�ӷ���
			if (Comp::prior(Heap[pos], Heap[MAX]))
				return;
			//������ڵ����ȼ����ӽڵ����ȼ����򽻻�
			swap(Heap, pos, MAX);
			pos = MAX;
		}
	}

public:
	heap(E* h, int num, int max)
		:Heap(h),n(num),maxSize(max)
	{
		buildHeap();
	}

	int size() const
	{
		return n;
	}

	bool isLeaf(int pos) const
	{
		//��ȫ��������һ��ڵ㶼��Ҷ�ڵ�
		return (pos >= n / 2) && (pos < n);
	}

	int leftchild(int pos) const
	{
		return 2 * pos + 1;
	}

	int rightchild(int pos) const
	{
		return 2 * pos + 2;
	}

	int parent(int pos) const
	{
		return (pos - 1) / 2;
	}

	void buildHeap()
	{
		for (int i = n / 2 - 1; i >= 0; i--)
			siftdown(i);
	}

	void insert(const E& it)
	{
		if (n >= maxSize)
		{
			cout << "Heap is full" << endl;
			system("pause");
			exit(-1);
		}
		int curr = n++;
		Heap[curr] = it;
		siftup(curr);
	}

	E removefirst()
	{
		if (n == 0)
		{
			cout << "Heap is empty" << endl;
			system("pause");
			exit(-1);
		}
		swap(Heap, 0, --n);
		if (n != 0)
			siftdown(0);
		return Heap[n];
	}

	E remove(int pos)
	{
		if (pos < 0 && pos >= n)
		{
			cout << "Bad position" << endl;
			if (pos == (n - 1))
				n--;
			else
			{
				swap(Heap, pos, --n);
				siftup(pos);
			}
			if (n != 0)
				siftdown(pos);
		}
		return Heap[n];
	}
};