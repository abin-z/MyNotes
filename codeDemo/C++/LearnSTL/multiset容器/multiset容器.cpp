#include <iostream>
#include <set>
using namespace std;

/*
* set不可以插入重复数据，而multiset可以
* set插入数据的同时会返回插入结果，表示插入是否成功
* multiset不会检测数据，因此可以插入重复数据
*/

void printSet(const set<int> &s) {
	for (set<int>::const_iterator it = s.begin(); it != s.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test() {
	set<int> s;
	pair<set<int>::iterator, bool> ret = s.insert(10);
	s.insert(60);
	s.insert(30);
	// set容器insert返回的是一个对组pair<iterator, bool>, 第一个是迭代器, 第二个是是否插入成功
	pair<set<int>::iterator, bool> res = s.insert(10);
	s.insert(20);
	// 第一次插入
	if (ret.second) {			// second是一个属性，并不是方法
		cout << "插入成功" << endl;
	}
	else {
		cout << "插入失败" << endl;
	}

	// 第二次插入
	if (res.second) {			// second是一个属性，并不是方法
		cout << "插入成功" << endl;
	}
	else {
		cout << "插入失败" << endl;
	}

	printSet(s);
}

void test02() {
	multiset<int> ms;
	multiset<int>::iterator res = ms.insert(100);	// multiset的insert方法返回的是一个迭代器
	ms.insert(100);
	ms.insert(100);
	ms.insert(100);

	cout << *res << endl;

	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++)
	{
		cout << *res << " ";
	}

	cout << endl;
}

int main()
{
	test();
	test02();
	std::cout << "Hello World!\n";
}
