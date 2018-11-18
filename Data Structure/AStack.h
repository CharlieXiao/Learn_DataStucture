#pragma once
#include "Stack.h"
#include <iostream>
using std::cout;
using std::endl;

const int defaultSize = 10;
template<typename E>
class AStack
	:public Stack<E>
{
private:
	int maxSize;
	int top;//top代表第一个空闲的位置,因此top的值同时也可以代表栈的长度
	E *listArray;

public:
	AStack(int size = defaultSize)
	{
		maxSize = size;
		top = 0;
		listArray = new E[size];
	}
	
	~AStack()
	{
		delete[] listArray;
	}

	void clear()
	{
		top = 0;
	}

	void push(const E& it)
	{
		if (top == maxSize)
		{
			cout << "Stack is full" << endl;
			system("pause");
			exit(-1);
		}
		listArray[top++] = it;
	}

	E pop()
	{
		if (top == 0)
		{
			cout << "Stack is empty" << endl;
			system("pause");
			exit(-1);
		}
		return listArray[--top];
	}

	const E& topValue() const
	{
		if (top == 0)
		{
			cout << "Stack is empty" << endl;
			system("pause");
			exit(-1);
		}
		return listArray[top - 1];
	}

	int length() const
	{
		return top;
	}
};