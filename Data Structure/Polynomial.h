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

	Polynomial(const Polynomial& poly)//拷贝构造函数
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

	void operator=(const Polynomial& poly)//赋值函数
	{
		Item* temp = poly.getHeadpointer()->next;
		curr = head;
		while (temp->next!=nullptr)
		{
			curr = curr->next = new Item(temp->coef, temp->exp, curr,curr->next);
			temp = temp->next;
		}
	}

	void insert(int c, int b)//插入一个项
	{
		if (c == 0)//当项数的系数为0时直接跳过
			return;
		curr = head->next;
		while (true)
		{
			if (b > curr->exp)
			{
				if (curr == tail)//已经走到了链表的末尾,则在末尾进行插入
				{
					Item* ptr = new Item(c, b, curr->prev, curr);
					curr->prev->next = ptr;
					curr->prev = ptr;
					break;
				}
				curr = curr->next;
			}
			else if (b == curr->exp)//找到同位的项时进行合并
			{
				curr->coef += c;
				if (curr->coef == 0)//如果合并后的系数是0,将该项删除
				{
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
					delete curr;
				}
				break;
			}
			else//temp的exp比b高,在temp之前插入
			{
				Item* ptr = new Item(c, b, curr->prev, curr);
				curr->prev->next = ptr;
				curr->prev = ptr;
				break;
			}
		}
	}

	void Ascend_print()//按照次序升输出
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

	void Descend_print()//按位次降序输出
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



