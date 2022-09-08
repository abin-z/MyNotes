#include <iostream>
#include <string>
using namespace std;

class MyPrint {
public:
	void operator()(string s) {		// ()运算符重载, 仿函数
		cout << s << endl;
	}
};

class MyAdd
{
public:
	int operator()(int v1, int v2)	// 仿函数没有固定的写法, 根据需要编写
	{
		return v1 + v2;
	}
};

void func() {
	MyPrint p;
	p("你好, 我是仿函数!");		// 特别像函数调用, 因此称为仿函数

	MyAdd add;
	int sum = add(10, 20);		// 仿函数
	cout << "sum = " << sum << endl;

	//匿名对象调用  MyAdd()为匿名对象, 本语句运行完就立即释放;
	cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
