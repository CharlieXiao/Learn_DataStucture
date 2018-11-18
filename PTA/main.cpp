#include <iostream>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

//3+12/(2-4)

int priority(char s)
{
	if (s == '(')
		return 4;
	else if (s == '*' || s == '/')
		return 3;
	else if (s == '+' || s == '-')
		return 2;
	else if (s == '#')
		return 0;//代表结尾
}

string toPostfix(string &s)
{
	//s = s + '#';
	stack<char> o;
	o.push('#');
	string res;
	stringstream ss;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= '0'&&s[i] <= '9')
		{
			string temp;
			while (i < s.length() && s[i] >= '0'&&s[i] <= '9')
			{
				temp += s[i];
				i++;
			}
			res = res + temp + ' ';
		}
		if (i == s.length())
			break;
		else if (s[i] == '(')
		{
			o.push(s[i]);
		}
		else if (s[i] == ')')
		{
			while (o.top() != '(')
			{
				res = res + o.top() + ' ';
				o.pop();
			}
			o.pop();
		}
		else
		{
			int a = priority(o.top());
			int b = priority(s[i]);
			while (priority(o.top()) >= priority(s[i]))
			{
				if (o.top() == '(')
					break;
				res = res + o.top() + ' ';
				o.pop();
			}
			o.push(s[i]);
		}
	}
	while (o.top() != '#')
	{
		res = res + o.top() + ' ';
		o.pop();
	}
	return res;
}

int CalcPostfix(string &s)
{
	stack<int> num;
	stringstream ss;
	int n;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= '0'&&s[i] <= '9')
		{
			string temp;
			while (i != s.length() && s[i] >= '0'&&s[i] <= '9')
			{
				temp += s[i];
				i++;
			}
			ss.str(temp);
			ss.clear();
			ss >> n;
			num.push(n);
		}
		else
		{
			int a = num.top();//中缀表达式中后面那项
			num.pop();
			int b = num.top();//中缀表达式中前面那项
			num.pop();
			switch (s[i])
			{
			case '*':
				num.push(a * b);
				break;
			case '/':
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
	return num.top();
}

int main()
{
	//string a = "3+12/(2-4)";
	string a;
	cin >> a;
	cout << a << endl;
	a = toPostfix(a);
	cout << a.substr(0, a.length() - 1) << endl;
	cout << CalcPostfix(a) << endl;


	/*
	string s = "12345";
	string res;
	for (int i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]))
			res += s[i];
	}
	stringstream ss(res);
	int x;
	ss >> x;
	cout << x << endl;
	*/
	return 0;
}