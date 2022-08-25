#include "MyTest.h"
using namespace std;

int add(int num1, int num2);
void swap(int num1, int num2);
int max(int, int);
int max(int, int);
int max(int, int);

int main()
{
	int a = 10;
	int b = 20;
	cout << "a = " << a << " b = " << b << endl;
	swap(a, b);
	cout << "a = " << a << " b = " << b << endl;
    //std::cout << add(10, 5);
	cout << max(a, b) << endl;
	myFunc();
	return 0;
}

//定义
int max(int a, int b)
{
	return a > b ? a : b;
}


// 值传递交换
void swap(int num1, int num2)
{
	cout << "交换前：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	int temp = num1;
	num1 = num2;
	num2 = temp;

	cout << "交换后：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	//return ; 当函数声明时候，不需要返回值，可以不写return
}


int add(int num1, int num2)
{
	int sum = num1 + num2;
	return sum;
}