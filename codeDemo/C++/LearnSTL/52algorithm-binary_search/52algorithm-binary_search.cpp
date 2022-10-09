#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

/*
`bool binary_search(iterator beg, iterator end, value);  `
// 查找指定的元素，查到 返回true  否则false
// 注意: 在**无序序列中不可用**
// beg 开始迭代器
// end 结束迭代器
// value 查找的元素
*/

void test() {
	vector<int> vtr;

	for (int i = 0; i < 10; ++i) {
		vtr.push_back(i);
	}
	vtr.push_back(2);
	
	//sort(vtr.begin(), vtr.end(), greater<int>());// 不能为降序序列
	sort(vtr.begin(), vtr.end());

	// 二分查找一定要是有序序列(只能是升序序列)，否则结果不正确
	// 建议在使用binary_search之前要进行排序sort
	bool res = binary_search(vtr.begin(), vtr.end(), 9);
	if (res) {
		cout << "找到了" << endl;
	}
	else {
		cout << "未找到" << endl;
	}

}

int main()
{
	test();
	std::cout << "Hello World!\n";
}