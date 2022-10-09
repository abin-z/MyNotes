#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <functional>
using namespace std;

struct MyPrint
{
	void operator()(int val) {
		cout << val << " ";
	}
};

void showInt(int val) {
	cout << val << " ";
}

void printVector(vector<int> &v) {
	// 使用迭代器打印
	for (vector<int>::const_iterator it = v.cbegin(); it != v.cend(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;

	//sort(v.begin(),v.end(),greater<int>());
	// 也可以使用for_each = 使用仿函数
	for_each(v.cbegin(), v.cend(), MyPrint());
	cout << endl;

	// for_each使用函数地址
	for_each(v.cbegin(), v.cend(), showInt);
	cout << endl;


}

void test() {
	vector<int> vtr;

	for (int i = 0; i < 10; i++)
	{
		vtr.push_back(rand()%100);
	}

	printVector(vtr);
}

int main()
{
	srand((unsigned int)time(nullptr));
	test();
    std::cout << "Hello World!\n";
}
