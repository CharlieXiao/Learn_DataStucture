#pragma once
#include "Dictionary.h"
#include "BSTNode.h"
#include <iostream>
using std::cout;
using std::endl;

//const int NULL = 0x7f7f7f7f7f;

template <typename Key,typename E>
class BST
	:Dictionary<Key, E>
{
private:
	BSTNode<Key, E>* root;
	int NodeCount;
	
	//一系列递归辅助程序

	//采用后序遍历清除二叉树
	void ClearHelp(BSTNode<Key, E>* r)
	{
		if (r == nullptr)
			return;
		ClearHelp(r->left());
		ClearHelp(r->right());
		delete r;
	}

	BSTNode<Key, E>* InsertHelp(BSTNode<Key, E>* r, const Key& k, const E& e)
	{
		if (r == nullptr)
			return new BSTNode<Key, E>(k, e);
		//重新赋值比判断运算所需的时间要少
		else if (k < r->key())
			r->setLeft(InsertHelp(r->left(), k, e));
		else
			r->setRight(InsertHelp(r->right(), k, e));
		return r;
	}

	BSTNode<Key, E>* DeleteMin(BSTNode<Key, E>* r)
	{
		//找到一棵树中最左端的节点(最小的节点)然后将其父节点直接指向其右节点
		if (r->left() == nullptr)
			return r->right();
		else
		{
			r->setLeft(DeleteMin(r->left()));
			return r;
		}
	}

	BSTNode<Key, E>* GetMin(BSTNode<Key, E>* r)
	{
		if (r->left() == nullptr)
			return r;
		else
			return GetMin(r->left());
	}

	BSTNode<Key, E>* RemoveHelp(BSTNode<Key, E>* r, const Key& k)
	{
		//先查找k是否在树中出现
		if (r == nullptr)
			return nullptr;
		else if (k < r->key())
			r->setLeft(RemoveHelp(r->left(), k));
		else if (k > r->key())
			r->setRight(RemoveHelp(r->right(), k));
		//根据k所在节点判断其左孩子右孩子是否存在并进行删除
		else
		{
			BSTNode<Key, E>* temp = r;
			//左孩子为空，直接将r指向其右孩子并删除即可
			if (r->left() == nullptr)
			{
				r = r->right();
				delete temp;
			}
			//右孩子为空，直接将r指向其左孩子并删除
			else if (r->right() == nullptr)
			{
				r = r->left();
				delete temp;
			}
			//左右孩子都不为空，在右子树中查找最小的节点并于r的值进行替换，再将其删除即可
			else
			{
				BSTNode<Key, E>* temp = GetMin(r->right());
				r->setElement(temp->element());
				r->setRight(DeleteMin(r->right()));
				delete temp;
			}
		}
		return r;
	}

	E FindHelp(BSTNode<Key, E>* r, const Key& k) const
	{
		if (r == nullptr)
			return E();

		if (k < r->key())
			return FindHelp(r->left(), k);

		else if (k > r->key())
			return FindHelp(r->right(), k);

		else
			return r->element();
	}

	void PrintHelp(BSTNode<Key, E>* r, int l) const
	{
		if (r == nullptr)
			return;
		PrintHelp(r->left(), l + 1);
		for (int i = 0; i < l; i++)
			cout << " ";
		cout << r->element() << endl;
		PrintHelp(r->right(), l + 1);
	}

public:
	BST()
	{
		root = nullptr;
		NodeCount = 0;
	}

	~BST()
	{
		ClearHelp(root);
	}

	void clear()
	{
		ClearHelp(root);
		root = nullptr;
		NodeCount = 0;
	}

	void insert(const Key& k, const E& e)
	{
		root = InsertHelp(root, k, e);
		NodeCount++;
	}

	E remove(const Key& k)
	{
		E temp = FindHelp(root, k);
		if (temp != E())
		{
			root = RemoveHelp(root, k);
			NodeCount--;
		}
		return temp;
	}

	E removeAny()
	{
		if (root != nullptr)
		{
			E temp = root->element();
			root = RemoveHelp(root, root->key());
			NodeCount--;
			return temp;
		}
		else
			return E();
	}

	E find(const Key& k) const
	{
		return FindHelp(root, k);
	}

	int size()
	{
		return NodeCount;
	}

	void print() const
	{
		if (root == nullptr)
		{
			cout << "The BST is empty" << endl;
		}
		else
		{
			PrintHelp(root, 0);
		}
	}
};