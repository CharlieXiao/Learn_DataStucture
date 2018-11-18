#pragma once
#include "BInNode.h"

//未区分叶节点和分支接待
//template <typename Key,typename E>
template<typename E>
class BSTNode
	:public BinNode<E>
{
private:
	//Key k;
	E it;
	BSTNode* lc;
	BSTNode* rc;

public:
	BSTNode()
	{
		lc = rc = nullptr;
	}

	BSTNode(E e,BSTNode* l = nullptr,BSTNode* r = nullptr)
		:it(e),lc(l),rc(r){}

	~BSTNode() {}

	E& element()
	{
		return it;
	}

	void setElement(const E& e)
	{
		it = e;
	}
	/*

	Key& key()
	{
		return k;
	}

	void setKey(const Key& K)
	{
		k = K;
	}

	*/
	
	inline BSTNode* left() const
	{
		return lc;
	}

	void setLeft(BinNode<E>* b)
	{
		lc = (BSTNode*)b;
	}

	inline BSTNode* right() const
	{
		return rc;
	}

	void setRight(BinNode<E>* b)
	{
		rc = (BSTNode*)b;
	}

	bool isLeaf()
	{
		return (lc == nullptr) && (rc == nullptr);
	}
};

/*
//采用简单的继承区分内节点和叶节点
template<typename E>
class VarBinNode {
public:
	virtual ~VarBinNode() {}
	virtual bool isLeaf() = 0;
	virtual void traverse() = 0;
};

template<typename Operand>
class LeafNode
	:public VarBinNode<Operand>
{
private:
	E var;

public:
	LeafNode(const Operand& val)
	{
		var = val;
	}

	bool isLeaf()
	{
		return true;
	}

	Operand value()
	{
		return var;
	}

	void traverse()
	{
		cout << "Leaf: " << value() << endl;
	}
};

template<typename Operator>
class IntlNode
	:public VarBinNode<Operator>
{
private:
	VarBinNode* left;
	VarBinNode* right;
	Operator opx;

public:
	IntlNode(const Operator& op,VarBinNode* l = nullptr,VarBinNode* r = nullptr)
		:opx(op),right(r),left(l){}

	bool isLeaf()
	{
		return false;
	}

	VarBinNode* leftchild()
	{
		return left;
	}

	VarBinNode* rightchild()
	{
		return right;
	}

	Operator value()
	{
		return opx;
	}

	void traverse()
	{
		cout << "Internal: " < value() << endl;
		if (left() != nullptr)
			left()->traverse();
		if (right() != nullptr)
			right()->traverse();
	}
};
*/
