#include "BST.h"
#include <string>
using std::string;

int main()
{
	BST<int, string> name;
	name.insert(89, "Charlie");
	name.insert(88, "Marcus");
	name.insert(90, "Galrot");
	//cout << name.find(20174288) << endl;
	cout << endl;
	name.print();
	return 0;
}