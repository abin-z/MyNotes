#include <iostream>
#include <list>
#include <algorithm>
#include <deque>
using namespace std;

class PrintList{
public:
	void operator()(const int num) const
	{
		cout << num << " ";
	}
};

struct MyCompare
{
	bool operator()(int val1, int val2) {
		return val1 > val2;
	}
};

void test() {
	//list<int> ls;		// list 不支持随机访问
	deque<int> ls;

	ls.push_back(10);
	ls.push_back(50);
	ls.push_back(20);
	ls.push_back(60);
	ls.push_back(30);
	ls.push_back(20);
	cout << "====排序前====" << endl;
	for_each(ls.cbegin(),ls.cend(), PrintList());
	cout << "====排序后====" << endl;
	sort(ls.begin(),ls.end());		// 容器需要支持随机迭代器访问才行
	for_each(ls.cbegin(), ls.cend(), PrintList());
	cout << "====降序====" << endl;
	sort(ls.begin(), ls.end(),MyCompare());
	for_each(ls.cbegin(),ls.cend(),PrintList());
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}