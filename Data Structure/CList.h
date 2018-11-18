#pragma once
#include "List.h"
#include "Node.h"
#include <iostream>

using std::cout;
using std::endl;

template<typename E>
class CList
	:public List<E>
{
private:
	Node<E>* head;
	Node<E>* tail;
	Node<E>* curr;
	int cnt;

	void init()
	{
		head = curr = tail = nullptr;
		cnt = 0;
	}

	void removeall()
	{
		tail->next = nullptr;//将循环链表断开然后再按链表删除方式析构
		while (head!=nullptr)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}

public:
	CList()
	{
		init();
	}

	~CList()
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
			curr = head = tail = new Node<E>(item);
			tail->next = head;
		}
		else
		{
			curr->next = new Node<E>(item, curr->next);
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
			curr = head = tail = new Node<E>(item);
			tail->next = head;
		}
		else
		{
			tail = tail->next = new Node<E>(item, tail->next);
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
		Node<E>* ptr = curr->next;
		if (curr->next == tail)
		{
			tail = curr;
		}
		else if (curr->next == head)//还有可能是头指针指向的元素被删除
		{
			head = curr;
		}
		curr->next = curr->next->next;
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
		if (!cnt)
		{
			return;
		}
		Node<E>* temp = head;
		while (temp->next != curr)
		{
			temp = temp->next;
		}
		curr = temp;
	}

	int currPos()
	{
		Node<E>* temp = head;
		int i = 0;
		while (temp != curr)
		{
			temp = temp->next;
			i++;
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
		/*if (pos < 0 || pos >= cnt)
		{
			cout << "Pos out of range" << endl;
			system("pause");
			exit(-1);
		}*/
		curr = head;
		for (int i = 0; i < pos; i++)
		{
			curr = curr->next;
		}
	}

	const E& getValue()
	{
		if (curr == nullptr || curr->next == nullptr)
		{
			cout << "No element" << endl;
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
