#pragma once
#include "List.h"
#include "DualNode.h"
#include <iostream>

using std::cout;
using std::endl;

template<typename E>
class CDList
	:public List<E>
{
private:
	DualNode<E>* head;
	DualNode<E>* tail;
	DualNode<E>* curr;
	int cnt;

	void init()
	{
		tail = head = curr = nullptr;
		cnt = 0;
	}

	void removeall()
	{
		tail->next = nullptr;
		while (head != nullptr)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}

public:
	CDList()
	{
		init();
	}

	~CDList()
	{
		removeall();
	}

	void clear()
	{
		removeall();
		init();
	}

	void insert(const E& item)
	{
		if (!cnt)
		{
			tail = curr = head = new DualNode<E>(item);
			head->next = tail;
			tail->prev = head;
		}
		else
		{	
			curr->next = curr->next->prev = new DualNode<E>(item, curr, curr->next);
			if (curr == tail)
			{
				tail = curr->next;
			}
		}
		cnt++;
	}

	void append(const E& item)
	{
		if (!cnt)
		{
			tail = curr = head = new DualNode<E>(item);
			head->next = tail;
			tail->prev = head;
		}
		else
		{
			tail = tail->next = tail->next->prev = new DualNode<E>(item, tail, tail->next);
		}
		cnt++;
	}

	E remove()
	{
		if (curr == nullptr)
		{
			cout << "No element!" << endl;
			system("pause");
			exit(-1);
		}
		E temp = curr->next->value;
		DualNode<E>* ptr = curr->next;
		curr->next = curr->next->next;
		curr->next->next->prev = curr;
		if (tail == curr->next)
		{
			tail = curr;
		}
		else if (head == curr->next)
		{
			head = curr;
		}
		delete ptr;
		cnt--;
		return temp;
	}

	void next()
	{
		curr = curr->next;
	}

	void prev()
	{
		curr = curr->prev;
	}

	int currPos()
	{
		DualNode<E>* temp = head;
		int i = 0;
		while (temp != curr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}

	void moveToStart()
	{
		curr = head;
	}

	void moveToEnd()
	{
		curr = tail;
	}

	void moveToPos(int pos)
	{
		curr = head;
		for (int i = 0; i < pos; i++)
		{
			curr = curr->next;
		}
	}

	const E& getValue()
	{
		if (curr == nullptr)
		{
			cout << "No element!" << endl;
			system("pause");
			exit(-1);
		}
		return curr->next->value;
	}

	int length()
	{
		return cnt;
	}
};