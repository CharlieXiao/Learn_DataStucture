#include "Heap.h"

class Comp
{
public:
	static bool prior(int a, int b)
	{
		return a > b;
	}
};

int main()
{
	int *h = new int[15];
	h[0] = 30;
	h[1] = 20;
	h[2] = 18;
	h[3] = 5;
	h[4] = 17;
	h[5] = 26;
	h[6] = 24;
	h[7] = 28;
	h[8] = 35;
	h[9] = 32;
	h[10] = 40;
	heap<int, Comp> heap(h, 11, 15);
	heap.insert(89);
	heap.insert(3);
	while (heap.size() != 0)
		cout << heap.removefirst() << endl;
	return 0;
}