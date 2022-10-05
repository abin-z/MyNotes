﻿#include <iostream>
#include <string>
#include <list>
using namespace std;

void printList(const list<int>& L) {

	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

//大小操作
void test01()
{
	list<int>L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	if (L1.empty())
	{
		cout << "L1为空" << endl;
	}
	else
	{
		cout << "L1不为空" << endl;
		cout << "L1的大小为： " << L1.size() << endl;
	}
	// list 没有容量的概念
	printList(L1);

	//重新指定大小
	//L1.resize(10);
	L1.resize(10, 555);
	printList(L1);

	L1.resize(2);
	printList(L1);
}


int main()
{
	test01();
    std::cout << "Hello World!\n";
}
