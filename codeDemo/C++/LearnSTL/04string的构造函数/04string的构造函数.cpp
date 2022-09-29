// 04string的构造函数.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

/*
* `string();`          				//创建一个空的字符串 例如: string str;
* `string(const char* s);`	        //使用字符串s初始化
* `string(const string& str);`    //使用一个string对象初始化另一个string对象
* `string(int n, char c);`           //使用n个字符c初始化
*/

void test() {
	string s1;	// 无参构造函数`string();` 
	string s2("hello world!");		// `string(const char* s);`	
	cout << "s2 = " << s2 << endl;	

	string s3(s2);	// 
	cout << "s3 = " << s3 << endl;	//`string(const string& str);`

	string s4(100, 'm');
	cout << "s4 = " << s4 << endl;	// `string(int n, char c);` 
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}

