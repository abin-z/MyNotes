#include <iostream>
using namespace std;

//函数占位参数 ，占位参数也可以有默认参数
void func(int a, int) {
	cout << "this is func" << endl;
}

//函数占位参数 ，占位参数也可以有默认参数
void func0(int a, int = 10) {
	cout << "this is func0" << endl;
}


// 在现阶段函数的占位参数存在意义不大，但是运算符重载会用到该技术
int main() {

	func(10, 10);	//占位参数必须填补
	func0(20);		//当函数占位参数有默认值的时候可以不传
	system("pause");

	return 0;
}
