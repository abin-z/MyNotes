#include <iostream>
using namespace std;
//函数重载注意事项
//1、引用作为重载条件

void func(int &a)				// 没有const的引用, 常规引用
{
	cout << "func (int &a) 调用 " << endl;
}

void func(const int &a)			// 添加const的引用, 常量引用
{
	cout << "func (const int &a) 调用 " << endl;
}


//2、函数重载碰到函数默认参数,  当下面两个函数 func2(10); 会产生二义性,报错

void func2(int a, int b = 10)
{
	cout << "func2(int a, int b = 10) 调用" << endl;
}

void func2(int a)
{
	cout << "func2(int a) 调用" << endl;
}

int main() {

	int a = 10;
	func(a); //调用无const
	func(10);//调用有const

	//func2(10); //碰到默认参数产生歧义，需要避免

	system("pause");

	return 0;
}