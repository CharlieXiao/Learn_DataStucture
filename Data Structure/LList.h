#pragma once
#include "List.h"
#include "Node.h"
#include <iostream>

using std::cout;
using std::endl;

template<typename E>
class LList
	:public List<E>
{
private:
	Node<E>* head;
	Node<E>* tail;
	Node<E>* curr;
	int cnt;

	void init()
	{
		head = curr = tail = new Node<E>;
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
	LList()
	{
		init();
	}

	~LList()
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
		curr->next = new Node<E>(item, curr->next);
		if (tail == curr)
			tail = curr->next;
		cnt++;
	}

	void append(const E& item)
	{
		tail = tail->next = new Node<E>(item, nullptr);
		cnt++;
	}

	E remove()
	{
		if (curr == tail)
		{
			cout << "No element!" << endl;
			system("pause");
			exit(-1);
		}
		E temp = curr->next->value;
		Node<E>* ptr = curr->next;
		if (tail == curr->next)
		{
			tail = curr;
		}
		curr->next = curr->next->next;
		delete ptr;
		cnt--;
		return temp;
	}

	void next()
	{
		if (tail != curr)
		{
			curr = curr->next;
		}
	}

	void prev() 
	{
		if (curr != head)
		{
			Node<E>* temp = head;
			while (temp->next != curr)
			{
				temp = temp->next;
			}
			curr = temp;
		}
	}

	int currPos()
	{
		Node<E>* temp = head;
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
		if (curr->next == nullptr)
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

	void reverse()
	{
		curr = head->next;
		Node<E>* prev = nullptr;//head的前驱为nullptr
		Node<E>* temp = nullptr;
		while (curr != nullptr)
		{
			temp = curr->next;//保留要修改节点的后继
			curr->next = prev;//将当前节点的后记变为前驱
			prev = curr;//更新前驱
			curr = temp;//更新后继
		}
		temp = head->next;
		head->next = tail;//交换首尾指针
		tail = temp;
		curr = head;//重置curr的位置
	}

	void swap()
	{
		Node<E>* temp = curr->next->next;
		curr->next->next = temp->next;
		temp->next = curr->next;
		curr->next = temp;
	}
};
