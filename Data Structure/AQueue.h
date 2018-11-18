#pragma once
#include "Queue.h"
#include <iostream>
using std::cout;
using std::endl;

const int defaultSize = 5;

template<typename E>
class AQueue
	:public Queue<E>
{
private:
	int maxSize;
	int front;
	int rear;
	E* listArray;

public:
	AQueue(int size = defaultSize)
	{
		maxSize = size + 1;//数组的大小为n+1,但只需存储n个元素,方便判断队列是空还是满
		rear = 0;
		front = 1;
		listArray = new E[maxSize];
	}

	~AQueue()
	{
		delete[] listArray;
	}

	void clear()
	{
		front = 1;
		rear = 0;
	}

	void enqueue(const E& it)
	{
		if ((rear + 2) % maxSize == front)
		{
			cout << "Queue is full" << endl;
			system("pause");
			exit(-1);
		}
		rear = (rear + 1) % maxSize;
		listArray[rear] = it;
	}

	E dequeue()
	{
		if (length() == 0)
		{
			cout << "Queue is empty" << endl;
			system("pause");
			exit(-1);
		}
		E it = listArray[front];
		front = (front + 1) % maxSize;
		return it;
	}

	const E& frontValue() const
	{
		if (length() == 0)
		{
			cout << "Queue is empty" << endl;
			system("pause");
			exit(-1);
		}
		return listArray[front];
	}

	virtual int length() const
	{
		return ((rear + maxSize) - front + 1) % maxSize;//确保rear-front
	}
};