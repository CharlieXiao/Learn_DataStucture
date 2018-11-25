#pragma once
#include "HuffNode.h"

template<typename E>
class HuffTree {
private:
	HuffNode<E>* Root;

public:
	HuffTree(E& val, int freq)
	{
		root = new LeafNode<E>(val, freq);
	}

	HuffTree(HuffTree<E>* l, HuffTree<E>*r)
	{
		root = new IntlNode<E>(l->root(), r->root());
	}

	~HuffTree(){}

	HuffNode<E>* root()
	{
		return Root;
	}

	int weight()
	{
		return Root->weight();
	}
};