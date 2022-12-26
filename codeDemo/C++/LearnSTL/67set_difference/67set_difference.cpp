#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;

/*
`set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  `

// 求两个集合的差集

// **注意:两个集合必须是有序序列**

// beg1 容器1开始迭代器
// end1 容器1结束迭代器
// beg2 容器2开始迭代器
// end2 容器2结束迭代器
// dest 目标容器开始迭代器
*/

class MyPrint {
public:
	void operator()(int val) {
		cout << val << "  ";
	}
};

void test() {
	vector<int> v1;
	vector<int> v2;

	// 求交集的集合必须是有序的
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int> vTarget;
	// 必须开辟足够的空间
	vTarget.resize(max(v1.size(), v2.size()));
	// 求并集,返回的是迭代器
	cout << "v1与v2的差集为:" << endl;
	vector<int>::iterator pos = set_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), vTarget.begin());
	for_each(vTarget.begin(), pos, MyPrint());
	cout << endl << "=================" << endl;

	// 求并集,返回的是迭代器
	cout << "v2与v1的差集为:" << endl;
	pos = set_difference(v2.cbegin(), v2.cend(), v1.cbegin(), v1.cend(), vTarget.begin());
	for_each(vTarget.begin(), pos, MyPrint());
}

/*
- 求差集的两个集合必须的有序序列
- 目标容器开辟空间需要从**两个容器取较大值**
- set_difference返回值既是差集中最后一个元素的位置
*/

int main()
{
	test();
}