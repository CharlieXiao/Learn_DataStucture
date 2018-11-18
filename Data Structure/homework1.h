#pragma once
#include "List.h"
#include "AList.h"
#include "LList.h"
#include "DList.h"
#include "CList.h"
#include "CDList.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <algorithm>
using std::string;
//打印表
template<typename E>
void print_list(List<E>& a)
{
	cout << "< ";
	int temp = a.currPos();
	for (a.moveToStart(); a.currPos() < temp; a.next())
	{
		cout << a.getValue() << " ";
	}
	cout << "| ";
	for (; a.currPos() < a.length(); a.next())
	{
		cout << a.getValue() << " ";
	}
	cout << ">" << endl;
	a.moveToPos(temp);
}

//合并LList
template<typename E>
LList<E> Merge_LList(LList<E>&a, LList<E>&b)//a、b是由小到大排
{
	LList<E> ans;
	a.moveToStart();
	b.moveToStart();
	int l1 = a.length(), l2 = b.length(), i = 0, j = 0;
	while (i < l1 && j < l2)
	{
		E A = a.getValue(), B = b.getValue();
		if (A > B)
		{
			ans.append(B);
			b.next();
			j++;
		}
		else
		{
			ans.append(A);
			a.next();
			i++;
		}
	}
	for (; i < l1; i++)
	{
		ans.append(a.getValue());
		a.next();
	}
	for (; j < l2; j++)
	{
		ans.append(b.getValue());
		b.next();
	}
	print_list(ans);
	return ans;
}


//合并AList
template<typename E>
AList<E> Merge_AList(AList<E>& a, AList<E>& b)
{
	AList<E> ans;
	a.moveToStart();
	b.moveToStart();
	int l1 = a.length(), l2 = b.length(), i = 0, j = 0;
	while (i < l1 && j < l2)
	{
		E A = a.getValue(), B = b.getValue();
		if (A > B)
		{
			ans.append(B);
			b.next();
			j++;
		}
		else
		{
			ans.append(A);
			a.next();
			i++;
		}
	}
	for (; i < l1; i++)
	{
		ans.append(a.getValue());
		a.next();
	}
	for (; j < l2; j++)
	{
		ans.append(b.getValue());
		b.next();
	}
	print_list(ans);
	return ans;
}

//按另一个链表顺序输出当前链表
template<typename E>
void PrintLots(LList<E>& L, LList<int>& P)
{
	for (P.moveToStart(); P.currPos() < P.length(); P.next())
	{
		int i = P.getValue();
		L.moveToPos(i);
		cout << L.getValue() << endl;
	}
}

//求两个链表的交集
template<typename E>
LList<E> intersection_LList(LList<E>& a, LList<E>& b)
{
	LList<E> ans;
	for (a.moveToStart(); a.currPos() < a.length(); a.next())
	{
		E temp = a.getValue();
		for (b.moveToStart(); b.currPos() < b.length(); b.next())
		{
			if (temp == b.getValue())
			{
				ans.append(temp);
				break;
			}
		}
	}
	print_list(ans);
	return ans;
}

//求两个顺序表的交集
template<typename E>
AList<E> intersection_AList(AList<E>& a, AList<E>& b)
{
	AList<E> ans;
	for (a.moveToStart(); a.currPos() < a.length(); a.next())
	{
		E temp = a.getValue();
		for (b.moveToStart(); b.currPos() < b.length(); b.next())
		{
			if (temp == b.getValue())
			{
				ans.append(temp);
				break;
			}
		}
	}
	print_list(ans);
	return ans;
}

//打印普通模式的链表
template<typename E>
void printlist(Node<E>* head)
{
	Node<E>* curr = head;
	cout << "< ";
	while (curr != nullptr)
	{
		cout << curr->value << " ";
		curr = curr->next;
	}
	cout << ">" << endl;
}

//删除普通模式的链表
template<typename E>
void deletelist(Node<E>* head)
{
	Node<E>* curr;
	while (head != nullptr)
	{
		curr = head->next;
		delete head;
		head = curr;
	}
}

//以元素位置的奇偶划分链表
template<typename E>
void divide_list(Node<E>* head)
{
	Node<E>* odd, *even, *curr, *t1, *t2;
	int i = 0;
	curr = head;
	while (curr != nullptr)
	{
		if (i % 2 == 0)
		{
			if (i == 0)
			{
				even = t1 = curr;
			}
			else
			{
				t1->next = curr;
				t1 = t1->next;
			}
		}
		else
		{
			if (i == 1)
			{
				odd = t2 = curr;
			}
			else
			{
				t2->next = curr;
				t2 = t2->next;
			}
		}
		i++;
		curr = curr->next;
	}
	printlist(even);
	printlist(odd);
	deletelist(even);
	deletelist(odd);
}

//约瑟夫环循环链表实现
class P {
public:
	int password;
	int num;
	P(int p, int n)
	{
		password = p;
		num = n;
	}
	P() {}
};

void Josephus(int n, int m)
{
	CList<P> j;
	for (int i = 1; i <= n; i++)
	{
		int a;
		cout << "Enter the password of No." << i << " ." << endl;
		std::cin >> a;
		j.append(P(a, i));
	}
	while (j.length() != 0)
	{
		for (int i = 0; i < m; i++)
			j.next();
		P temp = j.remove();
		m = temp.password;
		cout << "No." << temp.num << " out" << endl;
	}
}

class Info {
public:
	std::string name;
	int x, y;
	Info(){}
	Info(string n,int X,int Y):name(n),x(X),y(Y){}
	Info(const Info & i)
	{
		name = i.name;
		x = i.x;
		y = i.y;
	}
	void operator=(const Info & i)
	{
		name = i.name;
		x = i.x;
		y = i.y;
	}
	bool operator==(const Info & i)
	{
		if (i.name == name && i.x == x && i.y == y)
			return true;
		return false;
	}
	~Info(){}

};

class CityData {
private:
	AList<Info> *c;
	CityData(const CityData & data){}
	void operator=(const CityData & data){}
	double dis(double x1, double y1, double x2, double y2)
	{
		return pow(x1 - x2, 2) + pow(y1 - y2, 2);
	}
public:
	CityData()
	{
		c = new AList<Info>;
	}

	~CityData()
	{
		delete c;
	}

	void insert(Info & i)
	{
		c->append(i);
	}

	void insert(string name, int X, int Y)
	{
		c->append(Info(name, X, Y));
	}

	bool find(string name)
	{
		for (c->moveToStart(); c->currPos() != c->length(); c->next())
		{
			if (c->getValue().name == name)
			{
				return true;
			}
		}
		return false;
	}

	bool find(int X, int Y)
	{
		bool flag = true;
		for (c->moveToStart(); c->currPos() != c->length(); c->next())
		{
			Info temp = c->getValue();
			if (temp.x == X && temp.y == Y)
			{
				return true;
			}
		}
		return false;
	}

	void remove(string name)
	{
		if (find(name))
		{
			c->remove();
			cout << "City removed" <<"."<< endl;
		}
		else
		{
			cout << "Cannot find city named " << name << "." << endl;
		}
	}

	void remove(int X, int Y)
	{
		if (find(X, Y))
		{
			c->remove();
			cout << "City removed" << "." << endl;
		}
		else
		{
			cout << "Cannot find city located in pos(" 
				 << X << "," << Y << ")." << endl;
		}
	}

	void PrintCity(int X, int Y, double D)
	{
		D = D * D;
		for (c->moveToStart(); c->currPos() != c->length(); c->next())
		{
			Info temp = c->getValue();
			if (dis(temp.x, temp.y, X, Y) < D)
			{
				cout << temp.name << " (" << temp.x << "," << temp.y << ")" << endl;
			}

		}
	}
};

//第一题
/*
（a）如果curr在链表的末尾话再插入需要修改tail指针，有类似的方法处理，但会十分复杂
void insert(E item)
{
	curr->next = new Node<E>(curr->value,curr->next);
	curr->value = item;
	if(tail->next == curr)
		tail = curr;
}
(b)不能在常数时间内完成删除操作，不可以连续删除多个节点，
   由于每次删除都要遍历链表查找到当前元素的前驱。
*/