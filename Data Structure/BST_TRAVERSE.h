#pragma once
#include "BSTNode.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
using namespace std;


//采用后序遍历的方式对二叉树进行删除
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

//中序遍历的非递归实现（栈实现）
template<typename E>
void NoRecursive(BSTNode<E>* root)
{
	stack <BSTNode<E>*> s;
	BSTNode<E>* temp = root;
	while (temp != NULL || !s.empty())
	{
		//找到左子树的最左端那个
		while (temp != nullptr)
		{
			s.push(temp);
			temp = temp->left();
		}//左
		if (!s.empty())
		{
			temp = s.top();//中
			s.pop();
			cout << temp->element() << endl;
			temp = temp->right();//右
		}
	}
}

//前序遍历栈实现
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

//后续遍历栈实现
//实现难度在于如何读取完一个一个节点的右节点后回到当前节点
template<typename E>
void Norecursive_PostOrder(BSTNode<E>* root)
{
	stack<BSTNode<E>*> s;
	BSTNode<E>* temp = root;
	//对于每一个节点都在栈中存放两次，第一次读取其子节点，第二次才对其内容进行输出
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

//队列实现二叉树的层序遍历
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

//采用前序遍历对二叉树进行打印输出
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

//采用中序遍历
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

//递归计算节点的个数
template<typename E>
int Count_Node(BSTNode<E>* root)
{
	if (root != nullptr)
		return 1 + Count_Node(root->left()) + Count_Node(root->right());
	return 0;
}

//递归计算树的高度
template<typename E>
int Height(BSTNode<E>* root)
{
	if (root != nullptr)
		return 1 + max(Height(root->left()), Height(root->right()));
	return 0;
}

//递归计算叶节点的个数
template<typename E>
int Count_Leaf(BSTNode<E>* root)
{
	if (root == nullptr)
		return 0;
	else if (root->isLeaf())
		return 1;
	return Count_Leaf(root->left()) + Count_Leaf(root->right());
}