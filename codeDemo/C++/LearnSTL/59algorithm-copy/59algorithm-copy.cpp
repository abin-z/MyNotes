#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
`copy(iterator beg, iterator end, iterator dest);  `

// 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置

// beg  开始迭代器

// end  结束迭代器

// dest 目标起始迭代器
*/

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test() {
	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}

	vector<int> v2;
	v2.resize(v.size());		// 必须要提前开辟空间
	copy(v.cbegin(),v.cend(),v2.begin());
	for_each(v2.begin(), v2.end(), myPrint());
	cout << endl;
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}

