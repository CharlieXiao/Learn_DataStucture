#pragma once
#include "LStack.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;

//用stack来判断一个括号是不是匹配{}、[]、<>、()四种
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

int CalcPostfix(string & s)//存在局限,若为对字符串的读写,只能读取10以下的数字，无法计算含有10以上的
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
			int a = num.pop();//中缀表达式中后面那项
			int b = num.pop();//中缀表达式中前面那项
			switch (s[i])
			{
			case '*':
				num.push(a * b);
				break;
			case '/'://除法时被除数不可为零，即a不可为零
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
		return 0;//代表结尾
}

//支持运算符+、-、*、/、(、)
//暂不支持幂运算
string ToPostfix(string &s)//对优先级进行讨论
{
	LStack<char> o;
	string res = "";
	o.push('#');//确保栈中一定有值,避免判空
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

//计算n个字母的出栈顺序
