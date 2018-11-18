#pragma once
#include "List.h"
#include "DualNode.h"
#include <iostream>

using std::cout;
using std::endl;

template<typename E>
class DList
	:public List<E>
{
private:
	DualNode<E>* head;
	DualNode<E>* tail;
	DualNode<E>* curr;
	int cnt;

	void init()
	{
		head = curr = new DualNode<E>;
		tail = new DualNode<E>(head);
		head->next = tail;
		cnt = 0;
	}

	void removeall()
	{
		while (head != nullptr)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}

public:
	DList()
	{
		init();
	}

	~DList()
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
		curr->next = curr->next->prev = new DualNode<E>(item, curr,curr->next);
		cnt++;
	}

	void append(const E& item)
	{
		tail->prev = tail->prev->next = new DualNode<E>(item, tail->prev, tail);
		cnt++;
	}

	E remove()
	{
		if (curr->next == tail)
		{
			cout << "No element!" << endl;
			system("pause");
			exit(-1);
		}
		E temp = curr->next->value;
		DualNode<E>* ptr = curr->next;
		curr->next->next->prev = curr;
		curr->next = curr->next->next;
		delete ptr;
		cnt--;
		return temp;
	}

	void next()
	{
		if (tail->prev != curr)
		{
			curr = curr->next;
		}
	}

	void prev()
	{
		if (head != curr)
		{
			curr = curr->prev;
		}
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
		if (pos < 0 || pos >= cnt)
		{
			cout << "Pos out of range!" << endl;
			system("pause");
			exit(-1);
		}
		curr = head;
		for (int i = 0; i < pos; i++)
		{
			curr = curr->next;
		}
	}

	const E& getValue()
	{
		if (curr->next == tail)
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

	void swap()
	{
		DualNode<E>* temp = curr->next->next;
		curr->next->next->next->prev = curr->next;
		curr->next->next = curr->next->next->next;
		curr->next->prev = temp;
		temp->next = curr->next;
		temp->prev = curr;
		curr->next = temp;
	}
};