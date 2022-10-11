#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
`replace(iterator beg, iterator end, oldvalue, newvalue);  `

// 将区间内旧元素 替换成 新元素

// beg 开始迭代器

// end 结束迭代器

// oldvalue 旧元素

// newvalue 新元素
*/

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int> v;
	v.push_back(20);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);
	v.push_back(50);
	v.push_back(10);
	v.push_back(20);

	cout << "替换前：" << endl;
	for_each(v.begin(), v.end(), myPrint());
	cout << endl;

	replace(v.begin(),v.end(),20,111);
	cout << "替换后：" << endl;
	for_each(v.begin(), v.end(), myPrint());
	cout << endl;
}

int main()
{
	test01();
    std::cout << "Hello World!\n";
}
