#include <iostream>
#include <vector>
using namespace std;

void test() {
	vector<int> v;
	cout << &v << endl;
	int *p = nullptr;		// 每次开辟内存都会移动全部原有的数据
	int count = 0;
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
		if (p != &v[0]) {			// 不能判断 &v 的地址, v的地址不会变
			p = &v[0];
			count++;
			cout << v.capacity() << " ," << v.size() << endl;
		}
	}
	cout << &v << endl;
	cout << "capacity = " << v.capacity() << ", size = " << v.size() << endl;
	cout << "增长空间次数 = " << count << endl;		// 分配了30次内存
}

void test01() {
	vector<int> v;
	int *p = nullptr;
	int count = 0;
	v.reserve(100000);		// 一次性就把100000的容量开辟好
	for (int i = 0; i < 100000; i++)
	{
		v.push_back(i);
		if (p != &v.front()) {			// v.front() == v[0]
			p = &v[0];
			count++;
			cout << v.capacity() << " ," << v.size() << endl;
		}
	}
	cout << "capacity = " << v.capacity() << ", size = " << v.size() << endl;
	cout << "增长空间次数 = " << count << endl;
}

int main()
{
	test();
	cout << "===================================================" << endl;
	test01();
	std::cout << "Hello World!\n";
}
