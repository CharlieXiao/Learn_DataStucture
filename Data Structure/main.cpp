#include "HuffTree.h"
#include "HuffNode.h"
#include "Heap.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

/*
	A	77	N	67
	B	17	O	67
	C	32	P	20
	D	42	Q	5
	E	120	R	59
	F	24	S	67
	G	17	T	85
	H	50	U	37
	I	76	V	12
	J	4	W	22
	K	7	X	4
	L	42	Y	22
	M	24	Z	2
*/

//自定义优先级比较类
template<typename E>
class minTreeComp {
public:
	static bool prior(HuffTree<E>* a, HuffTree<E>* b)
	{
		return a->weight() < b->weight();//权重越小优先级越高
	}
};

//采用优先队列构建霍夫曼树
template<typename E>
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count)
{
	heap<HuffTree<E>*, minTreeComp<E>>* forest = new
		heap<HuffTree<E>*, minTreeComp<E>>(TreeArray, count, count);

	HuffTree<E>* temp1, *temp2, *temp3 = nullptr;
	while (forest->size() > 1)
	{
		temp1 = forest->removefirst();
		temp2 = forest->removefirst();
		temp3 = new HuffTree<E>(temp1, temp2);
		forest->insert(temp3);
		delete temp1;
		delete temp2;
	}
	return temp3;
}

map<char, string> CodeTable;

void MakeCodeTable(HuffNode<char>* tree, string code)
{
	if (tree->isLeaf())
	{
		CodeTable.insert(pair<char, string>(((LeafNode<char>*)tree)->val(), code));
		return;
	}
	MakeCodeTable(((IntlNode<char>*)tree)->left(), code + '0');
	MakeCodeTable(((IntlNode<char>*)tree)->right(), code + '1');
}

string Encode(string sec)
{
	string Code = "";
	for (int i = 0; i < sec.length(); i++)
	{
		map<char,string>::iterator it = CodeTable.find(sec[i]);
		//在map中查找一个元素，如果没找到则返回map.end()
		if (it == CodeTable.end())
		{
			return "";
		}
		Code += it->second;
	}
	return Code;
}

string Decode(HuffTree<char>* tree,string code)
{
	string sec = "";
	HuffNode<char>* temp = tree->root();
	int i = 0, l = code.length();
	while (i < l)
	{
		//当到达叶子节点时i不加一
		while (!temp->isLeaf())
		{
			if (code[i] == '0')
				temp = ((IntlNode<char>*)temp)->left();
			else if (code[i] == '1')
				temp = ((IntlNode<char>*)temp)->right();
			i++;
		}
		sec += ((LeafNode<char>*)temp)->val();
		temp = tree->root();
	}
	return sec;
}

int main()
{
	HuffTree<char>** Array = new HuffTree<char>*[10];
	//HuffTree<char>* temp = new HuffTree<char>('A',10);
	Array[0] = new HuffTree<char>('A', 77);
	Array[1] = new HuffTree<char>('B', 17);
	Array[2] = new HuffTree<char>('C', 32);
	Array[3] = new HuffTree<char>('D', 42);
	Array[4] = new HuffTree<char>('E', 120);
	Array[5] = new HuffTree<char>('F', 24);
	Array[6] = new HuffTree<char>('G', 17);
	Array[7] = new HuffTree<char>('H', 50);
	Array[8] = new HuffTree<char>('I', 76);
	Array[9] = new HuffTree<char>('J', 4);
	HuffTree<char>* tree = buildHuff(Array, 10);
	cout << tree->weight() << endl;
	MakeCodeTable(tree->root(), "");
	
	string code = Encode("BAD");
	cout << Decode(tree, code) << endl;

	return 0;
}
