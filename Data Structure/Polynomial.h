#pragma once
#include <iostream>
using namespace std;

class Item {
private:
	static Item* freelist;
public:
	int coef;
	int exp;
	Item* next;
	Item* prev;

	Item(int c, int b, Item* p = nullptr, Item* n = nullptr)
		:coef(c), exp(b), next(n), prev(p) {}

	Item(Item* p = nullptr,Item* n = nullptr)
		:next(n),prev(p){}

	void* operator new(size_t)
	{
		if (freelist == nullptr)
			return ::new Item;
		Item* temp = freelist;
		freelist = freelist->next;
		return temp;
	}

	void operator delete(void* ptr)
	{
		((Item*)ptr)->next = freelist;
		freelist = (Item*)ptr;
	}
};

Item* Item::freelist = nullptr;

class Polynomial {
private:
	Item* head;
	Item* curr;
	Item* tail;
	int cnt;
	Item* getHeadpointer() const
	{
		return head;
	}

public:
	Polynomial()
	{
		curr = head = new Item;
		tail = new Item(head);
		head->next = tail;
	}

	~Polynomial()
	{
		while (head != nullptr)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}

	Polynomial(const Polynomial& poly)//�������캯��
	{
		Item* temp = poly.getHeadpointer()->next;
		curr = head = new Item;
		while (temp != nullptr)
		{
			curr = curr->next = new Item(temp->coef,temp->exp,curr);
			temp = temp->next;
		}
		tail = curr;
	}

	void operator=(const Polynomial& poly)//��ֵ����
	{
		Item* temp = poly.getHeadpointer()->next;
		curr = head;
		while (temp->next!=nullptr)
		{
			curr = curr->next = new Item(temp->coef, temp->exp, curr,curr->next);
			temp = temp->next;
		}
	}

	void insert(int c, int b)//����һ����
	{
		if (c == 0)//��������ϵ��Ϊ0ʱֱ������
			return;
		curr = head->next;
		while (true)
		{
			if (b > curr->exp)
			{
				if (curr == tail)//�Ѿ��ߵ��������ĩβ,����ĩβ���в���
				{
					Item* ptr = new Item(c, b, curr->prev, curr);
					curr->prev->next = ptr;
					curr->prev = ptr;
					break;
				}
				curr = curr->next;
			}
			else if (b == curr->exp)//�ҵ�ͬλ����ʱ���кϲ�
			{
				curr->coef += c;
				if (curr->coef == 0)//����ϲ����ϵ����0,������ɾ��
				{
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
					delete curr;
				}
				break;
			}
			else//temp��exp��b��,��temp֮ǰ����
			{
				Item* ptr = new Item(c, b, curr->prev, curr);
				curr->prev->next = ptr;
				curr->prev = ptr;
				break;
			}
		}
	}

	void Ascend_print()//���մ��������
	{
		curr = head->next;
		cout << curr->coef << "x^" << curr->exp;
		curr = curr->next;
		while (curr != tail)
		{
			cout << "+" << curr->coef << "x^" << curr->exp;
			curr = curr->next;
		}
		cout << endl;
	}

	void Descend_print()//��λ�ν������
	{
		curr = tail->prev;
		cout << curr->coef << "x^" << curr->exp;
		curr = curr->prev;
		while (curr != head)
		{
			cout << "+" << curr->coef << "x^" << curr->exp;
			curr = curr->prev;
		}
		cout << endl;
	}

	Polynomial operator+(const Polynomial& poly)
	{
		Polynomial res = poly;
		curr = head->next;
		while (curr != tail)
		{
			res.insert(curr->coef, curr->exp);
			curr = curr->next;
		}
		return res;
	}

	Polynomial operator*(const Polynomial& poly)
	{
		Polynomial res;
		Item * temp = poly.getHeadpointer()->next;
		while (temp->next != nullptr)
		{
			curr = head->next;
			while (curr != tail)
			{
				res.insert(temp->coef*curr->coef, temp->exp + curr->exp);
				curr = curr->next;
			}
			temp = temp->next;
		}
		return res;
	}
};



