#include <iostream>
#include <functional>		// 使用内建仿函数
using namespace std;


/*
* 算术仿函数
* 关系仿函数
* 逻辑仿函数

* 这些仿函数所产生的对象，用法和一般函数完全相同
* 使用内建函数对象，需要引入头文件 `#include<functional>`

* `template<class T> T plus<T>`                //加法仿函数
* `template<class T> T minus<T>`              //减法仿函数
* `template<class T> T multiplies<T>`    //乘法仿函数
* `template<class T> T divides<T>`         //除法仿函数
* `template<class T> T modulus<T>`         //取模仿函数
* `template<class T> T negate<T>`           //取反仿函数

*/

void test() {
	// negate 取反仿函数
	negate<int> n;
	cout << n(100) << endl;

	// plus 加法仿函数
	plus<int> p;
	cout << p(10,20) << endl;

	// multiplies	乘法仿函数
	multiplies<double> mul;
	cout << mul(3.14, 5.20) << endl;

	// minus 减法仿函数
	minus<int> min;
	cout << min(10, 20) << endl;
	
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}