#include <iostream>
#include <vector>
using namespace std;

// 实现两个容器内元素的互换
// 函数原型 swap(vec);	将vec和this元素互换

void printVector(vector<int> v) {
	for (auto i : v)
	{
		std::cout << i << " ";
	}
	cout << endl;
}


// 基本使用
void test01() {
	vector<int> v;
	for (int i = 1; i <= 10; i++)
	{
		v.push_back(i);
	}
	cout << "交换前" << endl;

	vector<int> vec;
	for (int i = 100; i <= 110; i++)
	{
		vec.push_back(i);
	}
	cout << "v = ";
	printVector(v);
	cout << "vec = ";
	printVector(vec);

	v.swap(vec);
	cout << "交换后" << endl;
	cout << "v = ";
	printVector(v);
	cout << "vec = ";
	printVector(vec);
}

// 实际用途
void test02() {
	vector<int> vec;
	//vector<int> *p = nullptr;
	//int count = 0;
	for (int i = 0; i < 100000; i++)
	{
		vec.push_back(i);
		//if (p != &vec) {
		//	p = &vec;
		//	++count;
		//	cout << "第" << count
		//		<< "次: 容量 = " << vec.capacity()
		//		<< " 大小 = " << vec.size()
		//		<< endl;
		//}
	}

	cout << "vec.capacity() = " << vec.capacity()
		<< "  vec.size() = " << vec.size() << endl;

	// 重置大小
	vec.resize(10);		// 重置大小后容量并没有变小, 但是只存储10个数.空间浪费

	cout << "vec.capacity() = " << vec.capacity()
		<< "  vec.size() = " << vec.size() << endl;
	cout << "// 重置大小后容量并没有变小, 但是只存储10个数.空间浪费" << endl;;

	// 互换容器
	vector<int>(vec).swap(vec);	// 前面是匿名对象, 本行结束后释放资源

	cout << "vec.capacity() = " << vec.capacity()
		<< "  vec.size() = " << vec.size() << endl;

}


int main()
{
	//test01();
	test02();
	std::cout << "Hello World!\n";
}
