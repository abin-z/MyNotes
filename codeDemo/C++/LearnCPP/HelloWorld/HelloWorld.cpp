#include <iostream>											// 包含头文件

using namespace std;										// 引用命名空间
#define DAY 7												// 宏定义常量

int main() {
	cout << "hello world" << endl;							// 打印输出
	cout << "一周总共有" << DAY << "天" << endl;

	const int month = 12;									// const修饰的变量也是常量
	cout << "一年总共有" << month << "个月" << endl;

	system("pause");										// 暂停
	return 0;
}