#include <iostream>
#include <set>
using namespace std;

// 自定义类, 使用仿函数
class MyCompare {
public:
	bool operator()(int v1, int v2) {
		return v1 > v2;
	}
};

void printSet(const set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test() {
	set<int> s;
	s.insert(60);
	s.insert(20);
	s.insert(30);
	s.insert(40);
	s.insert(10);

	printSet(s);

	// 指定排序规则, 需要在构造set容器的时候就指定排序规则
	set<int, MyCompare> s2;
	s2.insert(30);
	s2.insert(100);
	s2.insert(20);
	s2.insert(50);
	s2.insert(60);


	for (set<int, MyCompare>::const_iterator it = s2.cbegin(); it != s2.cend(); it++)
	{
		cout << *it << " ";
	}
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
