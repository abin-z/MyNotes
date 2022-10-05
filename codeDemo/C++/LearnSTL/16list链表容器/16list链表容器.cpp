#include <iostream>
#include <string>
#include <list>
using namespace std;

// 打印
void printList(const list<int> &lst) {
	// 记得传入引用
	for (list<int>::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}


void test() {
	// 构造list
	list<int> l1;

	l1.push_back(10);
	l1.push_back(40);
	l1.push_back(50);
	l1.push_back(30);
	l1.push_back(20);

	printList(l1);

	// 区间的方式构造
	list<int> l2(l1.begin(), l1.end());
	printList(l2);

	// 拷贝构造
	list<int> l3(l1);
	printList(l3);

	// n个ele
	list<int> l4(100, 1);
	printList(l4);

	/// 赋值
	list<int> l5;
	l5 = l3;
	printList(l5);

	list<int> l6;
	l6.assign(l5.begin(), l5.end());
	printList(l6);

	list<int> l7;
	l6.assign(5,666);
	printList(l7);
}

//交换
void test02()
{

	list<int>L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);

	list<int>L2;
	L2.assign(10, 100);

	cout << "交换前： " << endl;
	printList(L1);
	printList(L2);

	cout << endl;

	L1.swap(L2);

	cout << "交换后： " << endl;
	printList(L1);
	printList(L2);

}

int main()
{
	test();
	test02();
	std::cout << "Hello World!\n";
}
