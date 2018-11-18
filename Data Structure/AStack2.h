#pragma once
#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;

const int defaultSize = 5;

template<typename E>
class AStack2
{
private:
	int top1;
	int top2;
	int maxSize;
	E* listArray;
public:
	AStack(int sz = defaultSize)
	{
		maxSize = sz;
		top1 = 0;
		top2 = maxSize - 1;
		listArray = new E[maxSize];
	}

	~AStack2()
	{
		delete[] listArray;
	}

	void clear(int st)//stµÈÓÚ1»ò2
	{
		if (st == 1)
			top1 = 0;
		else
			top2 = maxSize - 1;
	}

	void push(int st,const E& it)
	{
		if (top1 + 1 == top2)
		{
			cout << "Stack is full" << endl;
			system("pause");
			exit(-1);
		}
		if (st == 1)
		{
			listArray[top1++] = it;
		}
		else
		{
			listArray[top2--] = it;
		}
	}

	E pop(int st)
	{
		if (top1 == 0 || top2 == maxSize - 1)
		{
			cout << "Stack is empty" << endl;
			system("pause");
			exit(-1);
		}
		if (st == 1)
		{
			return listArray[--top1];
		}
		else
		{
			return listArray[++top2];
		}
	}

	const E& topValue(int st)
	{
		if (top1 == 0 || top2 == maxSize - 1)
		{
			cout << "Stack is empty" << endl;
			system("pause");
			exit(-1);
		}
		if (st == 1)
		{
			return listArray[top1 - 1];
		}
		else
		{
			return listArray[top2 + 1];
		}
	}

	int length(int st)
	{
		if (st == 1)
		{
			return top1;
		}
		else
		{
			return maxSize - top2 - 1;
		}
	}
};