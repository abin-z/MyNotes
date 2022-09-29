#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void myPrint(int val) {
	cout << val << endl;
}

void test() {
	// 创建vector 容器: STL中最常用的容器为Vector，可以理解为数组
	vector<int> vtr;
	vtr.push_back(100);
	vtr.push_back(200);
	vtr.push_back(300);
	vtr.push_back(400);
	vtr.push_back(500);

	//每一个容器都有自己的迭代器，迭代器是用来遍历容器中的元素
	//v.begin()返回迭代器，这个迭代器指向容器中第一个数据
	//v.end()返回迭代器，这个迭代器指向容器元素的最后一个元素的下一个位置
	//vector<int>::iterator 拿到vector<int>这种容器的迭代器类型

	// 遍历容器需要使用迭代器, 遍历方式1
	vector<int>::iterator itBegin = vtr.begin();	// v.begin()返回迭代器，这个迭代器指向容器中第一个数据
	vector<int>::iterator itEnd = vtr.end();		// v.end()返回迭代器，这个迭代器指向容器元素的最后一个元素的下一个位置

	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		++itBegin;		// 移动到下一个位置
	}

	cout << "=============================" << endl;

	// 遍历方式二
	for (vector<int>::iterator i = vtr.begin(); i < vtr.end(); ++i)
	{
		cout << *i << endl;
	}

	cout << "=============================" << endl;
	vtr.pop_back();
	// 遍历方式三 使用for_each算法
	for_each(vtr.begin(), vtr.end(), myPrint);	// myPrint为函数地址.
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
