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
	
	//һϵ�еݹ鸨������

	//���ú���������������
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
		//���¸�ֵ���ж����������ʱ��Ҫ��
		else if (k < r->key())
			r->setLeft(InsertHelp(r->left(), k, e));
		else
			r->setRight(InsertHelp(r->right(), k, e));
		return r;
	}

	BSTNode<Key, E>* DeleteMin(BSTNode<Key, E>* r)
	{
		//�ҵ�һ����������˵Ľڵ�(��С�Ľڵ�)Ȼ���丸�ڵ�ֱ��ָ�����ҽڵ�
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
		//�Ȳ���k�Ƿ������г���
		if (r == nullptr)
			return nullptr;
		else if (k < r->key())
			r->setLeft(RemoveHelp(r->left(), k));
		else if (k > r->key())
			r->setRight(RemoveHelp(r->right(), k));
		//����k���ڽڵ��ж��������Һ����Ƿ���ڲ�����ɾ��
		else
		{
			BSTNode<Key, E>* temp = r;
			//����Ϊ�գ�ֱ�ӽ�rָ�����Һ��Ӳ�ɾ������
			if (r->left() == nullptr)
			{
				r = r->right();
				delete temp;
			}
			//�Һ���Ϊ�գ�ֱ�ӽ�rָ�������Ӳ�ɾ��
			else if (r->right() == nullptr)
			{
				r = r->left();
				delete temp;
			}
			//���Һ��Ӷ���Ϊ�գ����������в�����С�Ľڵ㲢��r��ֵ�����滻���ٽ���ɾ������
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