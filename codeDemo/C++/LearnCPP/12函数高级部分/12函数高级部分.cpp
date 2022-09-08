#include <iostream>
using namespace std;

int defaultFunc(int a, int b = 20, int c = 100);	// 函数声明
int defaultFunc1(int a1, int b1, int c1);			// 函数声明

void func() {
	int a = defaultFunc(100);
	cout << a << endl;
}

// 当函数声明有参数默认值时, 函数实现则不能有参数默认值
int defaultFunc(int a, int b, int c) {				// 函数实现
	int res = a + b + c;
	return res;
}

// 当函数实现的参数有默认值, 则函数声明不能有参数默认值
int defaultFunc1(int a1, int b1 = 200, int c1 = 300) {			// 函数实现
	int res = a1 + b1 + c1;
	return res;
}			

int main()
{
	cout << "Hello World!\n";
	func();
	return 0;
}

// 函数默认参数注意:
// 1. 如果某个位置参数有默认值，那么从这个位置往后，从左向右，必须都要有默认值 (有默认参数的必须放在最后)
// 2. 如果函数声明有默认值，函数实现的时候就不能有默认参数
//    如果函数实现有默认值, 则函数声明就不能有默认值
//	  函数默认值在声明和实现中只能有一个, 不能两个都存在