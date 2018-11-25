#include "HuffTree.h"
#include "Heap.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

template<typename E>
class minTreeComp {
public:
	static bool prior(HuffTree<E>* a, HuffTree<E>* b)
	{
		return a->weight() > b->weight();//权重越大优先级越高
	}
};

template<typename E>
HuffTree<E>* buildHuff(HuffTree<E>** TreeArray, int count)
{
	heap<HuffTree<E>*, minTreeComp<E>>* forest = new
		heap<HuffTree<E>*, minTreeComp<E>>(TreeArray, count, count);

	HuffTree<E>* temp1, *temp2, *temp3;
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

int main()
{

	return 0;
}