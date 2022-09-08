#include <iostream>
using namespace std;

//1. 值传递
void mySwap01(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

//2. 地址传递
void mySwap02(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//3. 引用传递
void mySwap03(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
    cout << "Hello World!\n";

	int a = 10;
	int b = 20;
	////int &c; //错误，引用必须初始化
	//int &c = a; //一旦初始化后，就不可以更改, c为a的别名
	//c = b; //这是赋值操作，不是更改引用

	//cout << "a = " << a << endl;
	//cout << "b = " << b << endl;
	//cout << "c = " << c << endl;


	//mySwap01(a, b);			// 值传递, 并不能交换
	//cout << "a:" << a << " b:" << b << endl;

	//mySwap02(&a, &b);			// 地址传递, 可以实现交换
	//cout << "a:" << a << " b:" << b << endl;

	mySwap03(a, b);				// 引用传递, 可以实现交换
	cout << "a:" << a << " b:" << b << endl;


	system("pause");
	return 0;
}
