#include <iostream>
#include <string>
using namespace std;

// 函数模板: 建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一个虚拟的类型来代表。
//template<typename T>			// 可以使用 typename 关键字
template<class T>				// 也可以使用 class	关键字
void mySwap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

void func() {
	int a = 100;
	int b = 200;
	cout << "a = " << a << endl << "b = " << b << endl;
	mySwap<int>(a, b);	// 显示的说明T的类型;
	cout << "a = " << a << endl << "b = " << b << endl;
	mySwap(a, b); // 编译器自动推导类型
	cout << "a = " << a << endl << "b = " << b << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}