#pragma once
#include "BSTNode.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
using namespace std;


//���ú�������ķ�ʽ�Զ���������ɾ��
template<typename E>
void Remove(BSTNode<E>* root)
{
	if (root != nullptr)
	{
		Remove(root->left());
		Remove(root->right());
		cout << root->element() << " deleted" << endl;
		delete root;
	}
	return;
}

//��������ķǵݹ�ʵ�֣�ջʵ�֣�
template<typename E>
void NoRecursive(BSTNode<E>* root)
{
	stack <BSTNode<E>*> s;
	BSTNode<E>* temp = root;
	while (temp != NULL || !s.empty())
	{
		//�ҵ���������������Ǹ�
		while (temp != nullptr)
		{
			s.push(temp);
			temp = temp->left();
		}//��
		if (!s.empty())
		{
			temp = s.top();//��
			s.pop();
			cout << temp->element() << endl;
			temp = temp->right();//��
		}
	}
}

//ǰ�����ջʵ��
template<typename E>
void NoRecursive_PreOrder(BSTNode<E>* root)
{
	stack<BSTNode<E>*> s;
	BSTNode<E>* temp = root;
	while (temp != nullptr || !s.empty())
	{
		while (temp != nullptr)
		{
			cout << temp->element() << endl;
			if (temp->right() != nullptr)
				s.push(temp->right());
			temp = temp->left();
		}
		if (!s.empty())
		{
			temp = s.top();
			s.pop();
		}
	}
}

//��������ջʵ��
//ʵ���Ѷ�������ζ�ȡ��һ��һ���ڵ���ҽڵ��ص���ǰ�ڵ�
template<typename E>
void Norecursive_PostOrder(BSTNode<E>* root)
{
	stack<BSTNode<E>*> s;
	BSTNode<E>* temp = root;
	//����ÿһ���ڵ㶼��ջ�д�����Σ���һ�ζ�ȡ���ӽڵ㣬�ڶ��βŶ������ݽ������
	s.push(temp);
	s.push(temp);
	while (!s.empty())
	{
		temp = s.top();
		s.pop();
		if (!s.empty() && temp == s.top())
		{
			if (temp->right() != nullptr)
			{
				s.push(temp->right());
				s.push(temp->right());
			}
			if (temp->left() != nullptr)
			{
				s.push(temp->left());
				s.push(temp->left());
			}
		}
		else
			cout << temp->element() << endl;
	}
}

//����ʵ�ֶ������Ĳ������
template<typename E>
void level_print(BSTNode<E>* root)
{
	queue<BSTNode<E>*> q;
	BSTNode<E>* temp = root;
	q.push(temp);
	while (!q.empty())
	{
		temp = q.front();
		q.pop();
		if (temp->left() != nullptr)
			q.push(temp->left());
		if (temp->right() != nullptr)
			q.push(temp->right());
		cout << temp->element() << endl;

	}
}

//����ǰ������Զ��������д�ӡ���
template<typename E>
void Print(BSTNode<E>* root)
{
	if (root != nullptr)
	{
		cout << root->element() << endl;
		Print(root->left());
		Print(root->right());
	}
	return;
}

//�����������
template<typename E>
void inOrder(BSTNode<E>* root)
{
	if (root != nullptr)
	{
		inOrder(root->left());
		cout << root->element() << endl;
		inOrder(root->right());
	}
	return;
}

//�ݹ����ڵ�ĸ���
template<typename E>
int Count_Node(BSTNode<E>* root)
{
	if (root != nullptr)
		return 1 + Count_Node(root->left()) + Count_Node(root->right());
	return 0;
}

//�ݹ�������ĸ߶�
template<typename E>
int Height(BSTNode<E>* root)
{
	if (root != nullptr)
		return 1 + max(Height(root->left()), Height(root->right()));
	return 0;
}

//�ݹ����Ҷ�ڵ�ĸ���
template<typename E>
int Count_Leaf(BSTNode<E>* root)
{
	if (root == nullptr)
		return 0;
	else if (root->isLeaf())
		return 1;
	return Count_Leaf(root->left()) + Count_Leaf(root->right());
}