#include <map>
#include <iostream>
using namespace std;

// 使用函数对象实现排序
class MyCompare {
public:
	bool operator()(const int &v1, const int &v2) const	// 这里需要添加const,变成常函数, 才能编译通过
	{
		return v1 > v2;
	}
};

void test() {
	multimap<int, int, MyCompare> m;

	m.insert(make_pair(1,10));
	m.insert(make_pair(5,50));
	m.insert(make_pair(5,50));
	m.insert(make_pair(5,50));
	m.insert(make_pair(3,30));
	m.insert(make_pair(6,60));
	m.insert(make_pair(6,60));
	m.insert(make_pair(2,20));
	m.insert(make_pair(2,20));
	m.insert(make_pair(4,40));
	m.insert(make_pair(4,40));

	for (multimap<int, int, MyCompare>::const_iterator it = m.cbegin(); it != m.cend(); it++) {
		cout << it->first << "," << it->second << endl;
	}

	cout << "count = " <<  m.count(5) << endl;
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
