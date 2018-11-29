#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
�����ʽ��
��1�У���1������m����ʾ������Ҫ�����m����¼��
��2�е���1+m�У�ÿ�б�ʾһ�������¼������һ���ַ���cityName����������x��y���ֱ��ʾ�������ƺ����ꡣ
������n�У�Ϊ���������Ĳ����ɾ��������������Ϊ0����ɾ����������Ϊ1������룬������Ϊ2����������롢ɾ��������
������1�У�1���ַ�����ʾҪ���м�����ָ����ĸ��
���1�У�3��������x��y��d��x��y��ʾָ��������꣬d��ʾ���롣
�����ʽ��
��ɲ����ɾ������֮���������BST����ӡ��ÿ����¼����һ�У���������������
����ָ����ĸ��ͷ�����г��м�¼��ÿ����¼����һ�У��������������֣�x��y����
��ӡ��ָ����ľ����ڸ���ֵ֮�ڵ����г��м�¼��ÿ����¼����һ�У��������������֣�x��y����

*/

class CityInfo {
public:
	string name;
	int x;
	int y;
	CityInfo* lc;
	CityInfo* rc;

	CityInfo(string n,int X,int Y,CityInfo* l = nullptr,CityInfo* r = nullptr)
		:name(n),x(X),y(Y),lc(l),rc(r){}

	CityInfo(const CityInfo & a)
	{
		name = a.name;
		x = a.x;
		y = a.y;
		lc = a.lc;
		rc = a.rc;
	}

	void operator=(const CityInfo& a)
	{
		name = a.name;
		x = a.x;
		y = a.y;
		lc = a.lc;
		rc = a.rc;
	}

	~CityInfo(){}
};

//�������������ͬ,���ֲ�������ͬ
class CityDB {
private:
	CityInfo* root;
	int cnt;

	CityDB(const CityDB & a){}

	void operator=(const CityDB & a){}

	//һϵ�и����ݹ麯��

	int CalcDis(int x1, int y1, int x2, int y2)
	{
		return (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);
	}

	bool Comp(string a, string b)
	{
		int l1 = a.length();
		int l2 = b.length();
		int i = 0;
		while (i != l1 && i != l2)//��λ�Ƚ��ַ�����ASCII��
		{
			//���ԱȽ�ʱֱ�ӷ��رȽϵ�ֵ
			if (a[i] < b[i])
				return true;
			else if (a[i] > b[i])
				return false;
			i++;//����λ�õ���ĸ��ͬ��ʱ������Ƚ�
		}
		if (l1 < l2)//�����������ַ����е�һ�����жϳ���,���ȳ����ַ����ϴ�
			return true;
		return false;
	}
	
	//����������С�ڵ��ָ��
	CityInfo* getMin(CityInfo* root)
	{
		if (root->lc != nullptr)
			return getMin(root->lc);
		else
			return root;
	}

	CityInfo* deleteMin(CityInfo* root)
	{
		if (root->lc == nullptr)
			return root->rc;
		else
		{
			root->lc = deleteMin(root->lc);
			return root;
		}
	}

	void clear(CityInfo* root)
	{
		if (root != nullptr)
		{
			clear(root->lc);
			clear(root->rc);
			delete root;
		}
	}

	void print(CityInfo* root)
	{
		if (root != nullptr)
		{
			print(root->lc);
			cout << root->name << endl;
			print(root->rc);
		}
	}

	CityInfo* insert(CityInfo* root, string N, int X, int Y)
	{
		if (root == nullptr)
			return new CityInfo(N,X,Y);
		if (Comp(N, root->name))
			root->lc = insert(root->lc, N, X, Y);
		else
			root->rc = insert(root->rc, N, X, Y);
		return root;
	}

	CityInfo* remove(CityInfo* root, string n)
	{
		if (root == nullptr)
			return nullptr;
		else if (Comp(n, root->name))
			root->lc = remove(root->lc, n);
		else if (n == root->name)
		{
			CityInfo* temp = root;
			if (temp->lc == nullptr)
			{
				root = root -> rc;
				delete temp;
			}
			else if (temp->rc == nullptr)
			{
				root = root->lc;
				delete temp;
			}
			else
			{
				temp = getMin(root->rc);
				root->name = temp->name;
				root->x = temp->x;
				root->y = temp->y;
				root->rc = deleteMin(root->rc);
				delete temp;
			}
		}
		else
			root->rc = remove(root->rc, n);
		return root;
	}

	void find_in_distance(CityInfo* root,int X,int Y, int dis)//�˴�disʵ��Ϊdis��ƽ�������ڼ���
	{
		//�������
		if (root != nullptr)
		{
			find_in_distance(root->lc, X, Y, dis);
			if (CalcDis(root->x, root->y, X, Y) < dis)
				cout << root->name << " " << root->x << " " << root->y << endl;
			find_in_distance(root->rc, X, Y, dis);
		}
	}

	void find_with_initial(CityInfo* root, char ch)
	{
		if (root == nullptr)
			return;
		if (ch > root->name[0])
			find_with_initial(root->rc, ch);
		else if (ch < root->name[0])
			find_with_initial(root->lc, ch);
		else
		{
			find_with_initial(root->lc, ch);
			cout << root->name << " " << root->x << " " << root->y << endl;
			find_with_initial(root->rc, ch);
		}
	}

public:
	CityDB()
		:root(nullptr),cnt(0){}

	~CityDB()
	{
		clear(root);
	}

	void clear()
	{
		clear(root);
		cnt = 0;
	}

	void insert(string N,int X,int Y)
	{
		root = insert(root, N, X, Y);
		cnt++;
	}

	void remove(string N)
	{
		root = remove(root, N);
		cnt--;
	}

	void print()
	{
		print(root);
	}

	/*
	CityInfo find(string n)//�ҵ�֮��ֱ�ӷ���CityInfo
	{

	}
	*/

	void find_in_distance(int X,int Y, int dis)
	{
		find_in_distance(root, X, Y, dis*dis);
	}

	void find_with_initial(char ch)
	{
		find_with_initial(root, ch);
	}
};

int main()
{

	/*
	����������
	���룺
	4
	chongqing 1 1
	chengdu 1 2
	shenyang 2 2
	changchun 2 3
	1 shanghai 2 3
	0 changchun
	0 shenyang
	1 beijing 2 2
	2
	c
	0 0 3
	*/
	CityDB cdb;
	int n, x, y, d;
	char ch;
	string a;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> x >> y;
		cdb.insert(a, x, y);
	}
	while (true)
	{
		cin >> n;
		if (n == 0)
		{
			cin >> a;
			cdb.remove(a);
		}
		else if (n == 1)
		{
			cin >> a >> x >> y;
			cdb.insert(a, x, y);
		}
		else
			break;
	}
	cdb.print();
	cin >> ch;
	cdb.find_with_initial(ch);
	cin >> x >> y >> d;
	cdb.find_in_distance(x, y, d);
	return 0;
}

/*
�����
	beijing
	chengdu
	chongqing
	shanghai
	chengdu 1 2
	chongqing 1 1
	beijing 2 2
	chengdu 1 2
	chongqing 1 1

*/