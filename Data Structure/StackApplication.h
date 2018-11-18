#pragma once
#include "LStack.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;

//��stack���ж�һ�������ǲ���ƥ��{}��[]��<>��()����
bool isBalance(string & s)
{
	LStack<char> b;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(' || s[i] == '<' || s[i] == '{' || s[i] == '[')
		{
			b.push(s[i]);
		}
		if (s[i] == ')' || s[i] == '>' || s[i] == '}' || s[i] == ']')
		{
			if (b.length() == 0)
			{
				return false;
			}
			switch (s[i])
			{
			case ')':
				if (b.pop() != '(')
					return false;
				break;
			case '>':
				if (b.pop() != '<')
					return false;
				break;
			case '}':
				if (b.pop() != '{')
					return false;
				break;
			case ']':
				if (b.pop() != '[')
					return false;
				break;
			}
		}
	}
	return true;
}

int CalcPostfix(string & s)//���ھ���,��Ϊ���ַ����Ķ�д,ֻ�ܶ�ȡ10���µ����֣��޷����㺬��10���ϵ�
{
	LStack<int> num;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')
			num.push(s[i] - '0');
		else
		{
			if (num.length() < 2)
			{
				cout << "Wrong expression" << endl;
				system("pause");
				exit(-1);
			}
			int a = num.pop();//��׺���ʽ�к�������
			int b = num.pop();//��׺���ʽ��ǰ������
			switch (s[i])
			{
			case '*':
				num.push(a * b);
				break;
			case '/'://����ʱ����������Ϊ�㣬��a����Ϊ��
				if (a == 0)
				{
					cout << "Divisor is zero" << endl;
					system("pause");
					exit(-1);
				}
				num.push(b / a);
				break;
			case '+':
				num.push(a + b);
				break;
			case '-':
				num.push(b - a);
				break;
			}
		}
	}
	return num.pop();
}

int priority(char s)
{
	if (s == '(')
		return 5;
	//else if (s == '^')
		//return 4;
	else if (s == '*' || s == '/')
		return 3;
	else if (s == '+' || s == '-')
		return 2;
	else if (s == '#')
		return 0;//�����β
}

//֧�������+��-��*��/��(��)
//�ݲ�֧��������
string ToPostfix(string &s)//�����ȼ���������
{
	LStack<char> o;
	string res = "";
	o.push('#');//ȷ��ջ��һ����ֵ,�����п�
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')
			res += s[i];
		else if (s[i] == '(')
			o.push(s[i]);
		else if(s[i] == ')')
		{
			while (o.topValue() != '(')
				res += o.pop();
			o.pop();
		}
		else
		{
			while (priority(o.topValue()) >= priority(s[i]))
			{
				if (o.topValue() == '(')
					break;
				res += o.pop();
			}
			o.push(s[i]);
		}
	}
	while (o.length() != 1)
		res += o.pop();
	return res;
}

//����n����ĸ�ĳ�ջ˳��
