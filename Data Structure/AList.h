#pragma once
#include "List.h"
#include <iostream>

using std::cout;
using std::endl;

const int defaultSize = 1024;

template<typename E>
class AList 
	:public List<E>
{
private:
	int ListSize;
	int MaxSize;
	int curr;
	E* ListArray;
public:
	AList(int size = defaultSize) 
	{
		MaxSize = size;
		curr = ListSize = 0;
		ListArray = new E[size];
	}

	~AList()
	{
		delete[] ListArray;
	}

	void clear()
	{
		delete[] ListArray;
		ListSize = curr = 0;
		ListArray = new E[MaxSize];
	}

	void insert(const E& item)
	{
		//首先判断是不是超出表的最大长度
		if (ListSize > MaxSize)
		{
			cout << "List capacity exceeded!" << endl;
			system("pause");
			exit(-1);
		}
		//然后再执行插入操作
		for (int i = ListSize; i > curr; i--)
		{
			ListArray[i] = ListArray[i - 1];//为当前要插入的元素移出空间
		}
		ListArray[curr] = item;
		ListSize++;
	}

	void append(const E& item)
	{
		//同样需要判断是否超出表的最大长度
		if (ListSize >= MaxSize)
		{
			cout << "List capacity exceeded!" << endl;
			system("pause");
			exit(-1);
		}
		//再执行插入操作
		ListArray[ListSize++] = item;
	}

	E remove()
	{
		//判断当前位置是否有元素
		if (curr < 0 || curr >= ListSize)
		{
			cout << "No element!" << endl;
			system("pause");
			exit(-1);
		}
		//再执行删除操作
		E temp = ListArray[curr];
		for (int i = curr; i < ListSize - 1; i++)
		{
			ListArray[i] = ListArray[i + 1];
		}
		ListSize--;
		return temp;
	}

	void next()
	{
		if (curr < ListSize)
		{
			curr++;
		}
	}

	void prev()
	{
		if (curr != 0)
			curr--;
	}

	void moveToStart()
	{
		curr = 0;
	}

	void moveToEnd()
	{
		curr = ListSize;//指到表的最后一个元素
	}

	void moveToPos(int pos)
	{
		//判断pos是否超出表的范围
		if (pos<0 || pos>ListSize)
		{
			cout << "Pos out of range!" << endl;
			system("pause");
			exit(-1);
		}
		curr = pos;
	}

	int currPos()
	{
		return curr;
	}

	int length()
	{
		return ListSize;
	}

	const E& getValue()
	{
		if (curr < 0 || curr >= ListSize)
		{
			cout << "No current element!" << endl;
			system("pause");
			exit(-1);
		}
		return ListArray[curr];
	}

	void reverse()
	{
		E temp;
		for (int i = 0; i < ListSize / 2; i++)
		{
			temp = ListArray[i];
			ListArray[i] = ListArray[ListSize-1 - i];
			ListArray[ListSize-1- i] = temp;
		}
	}
};