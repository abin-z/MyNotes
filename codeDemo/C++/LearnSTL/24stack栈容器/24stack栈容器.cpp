// 24stack栈容器.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

void test() {
	// 符合先进后出的数据结构, 不存在遍历行为
	stack<string> s;

	s.push("xiaoming");
	s.push("baidu");
	s.push("tom");
	s.push("jerry");
	s.push("tony");

	stack<string> s2(s);	// 拷贝构造

	stack<string> s3;
	s3 = s2;				// 赋值运算符

	cout << "s.empty() = " << s.empty() << endl;
	cout << "s.size() = " << s.size() << endl;
	cout << "s.size() = " << s.top() << endl;

	// 只要栈不为空
	while (!s3.empty())
	{
		// 查看栈顶元素
		cout << "栈顶元素: " << s3.top() << endl;	// 查看元素需要使用top()函数		
		s3.pop();			// pop() 函数返回的是void
	}
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}

