#pragma once
#include "Queue.h"
#include "Node.h"
#include <iostream>
using std::cout;
using std::endl;

const int defaultSize = 5;

template<typename E> 
class LQueue
	:public Queue<E>
{
private:
	//由于队列的操作只能在头尾两端进行,不能在中间进行操作,因此只有两个指针
	Node<E>* front;
	Node<E>* rear;
	int size;

public:
	LQueue(int sz = defaultSize)
	{
		front = rear = new Node<E>();
		size = 0;
	}

	~LQueue()
	{
		clear();
		delete front;
	}

	void clear()
	{
		while (front->next != nullptr)
		{
			rear = front;
			delete rear;
		}
		rear = front;
		size = 0;
	}

	void enqueue(const E& it)
	{
		rear = rear->next = new Node<E>(it, nullptr);
		size++;
	}

	E dequeue()
	{
		if (size == 0)
		{
			cout << "Queue is empty" << endl;
			system("pause");
			exit(-1);
		}
		E it = front->next->value;
		Node<E>* temp = front->next;
		front->next = temp->next;
		if (rear == temp)
			rear = front;
		delete temp;
		size--;
		return it;
	}

	const E& frontValue() const
	{
		if (size == 0)
		{
			cout << "Queue is empty" << endl;
			system("pause");
			exit(-1);
		}
		return front->next->value;
	}

	virtual int length() const
	{
		return size;
	}
};