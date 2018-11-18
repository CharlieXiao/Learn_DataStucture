#pragma once
/*
ϡ��������ת��
*/
#include <iostream>
#include <string>
using namespace std;

struct Node {
	int row, col;
	int value;
};

/*
ϡ�����������Ԫ��
(v,x,y)
v����Ԫ�ص�ֵ
x����Ԫ�ص��к�
y����Ԫ�ص��к�
Ĭ���к��ж��Ǵ��㿪ʼ
����˳���洢ϡ�����
arr[0]�ֱ𴢴�(����Ԫ����,����,����)
����Ҫ����n+1���ռ�
*/

void trans(Node* arr)
{
	int row = arr[0].row, col = arr[0].col , j;
	const int n = arr[0].value;
	int * row_num = new int[n];
	int * row_pos = new int[n];
	Node* b = new Node[n + 1];
	for (int i = 0; i < n; i++)
		row_num[i] = 0;
	for (int i = 1; i <= n; i++)
		row_num[arr[i].row]++;
	row_pos[0] = 1;
	for (int i = 1; i < n; i++)
		row_pos[i] = row_pos[i - 1] + row_num[i - 1];
	b[0].col = arr[0].row;
	b[0].row = arr[0].col;
	b[0].value = arr[0].value;
	for(int i=1;i<=n;i++)
	{
		j = row_pos[arr[i].col]++;
		b[j].col = arr[i].row;
		b[j].row = arr[i].col;
		b[j].value = arr[i].value;
	}
	for (int i = 0; i <= n; i++)
		cout << b[i].row << " " << b[i].col << " " << b[i].value << endl;
	delete[] row_num;
	delete[] row_pos;
	delete[] b;
}

int main()
{
	const int n = 8;
	Node* arr = new Node[n + 1];
	arr[0] = { 6,6,8 };
	arr[1] = { 0,0,15 };
	arr[2] = { 0,3,22 };
	arr[3] = { 0,5,-15 };
	arr[4] = { 1,1,11 };
	arr[5] = { 1,2,3 };
	arr[6] = { 2,3,-6 };
	arr[7] = { 4,0,91 };
	arr[8] = { 5,2,28 };
	trans(arr);
	delete[] arr;
	return 0;
}