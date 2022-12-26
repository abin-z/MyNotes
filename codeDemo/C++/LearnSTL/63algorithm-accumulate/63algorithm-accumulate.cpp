#include <iostream>
#include <numeric>	// 包含头文件
#include <vector>
using namespace std;

/*
`accumulate(iterator beg, iterator end, value);  `
// 计算容器元素累计总和
// beg 开始迭代器
// end 结束迭代器
// value 起始值
*/

void test() {
	vector<int> v;
	for (int i = 1; i <= 100; i++)
	{
		v.push_back(i);
	}

	int sum = accumulate(v.begin(), v.end(), 0);

	cout << "sum = " << sum << endl;

}

int main()
{
	test();
    std::cout << "Hello World!\n";
}