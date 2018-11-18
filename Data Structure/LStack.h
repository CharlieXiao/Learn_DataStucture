#pragma once
#include "Stack.h"
#include "Node.h"
#include <iostream>
using std::cout;
using std::endl;
const int defaultSize = 10;

template<typename E>
class LStack
	:public Stack<E>
{
private:
	Node<E>* top;
	int size;

public:
	LStack(int s = defaultSize)
	{
		top = nullptr;
		size = 0;
	}

	~LStack()
	{
		clear();
	}

	void clear()
	{
		while (top != nullptr)
		{
			Node<E>* temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	void push(const E& it)
	{
		top = new Node<E>(it, top);
		size++;
	}

	E pop()
	{
		if (top == nullptr)
		{
			cout << "Stack is empty" << endl;
			system("pause");
			exit(-1);
		}
		E it = top->value;
		Node<E>* temp = top->next;
		delete top;
		top = temp;
		size--;
		return it;
	}

	const E& topValue()
	{
		if (top == nullptr)
		{
			cout << "Stack is empty" << endl;
			system("pause");
			exit(-1);
		}
		return top->value;
	}

	int length()
	{
		return size;
	}
};