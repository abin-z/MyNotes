#include <iostream>
#include <string>
using namespace std;
/*
* `string& operator=(const char* s); `             //char*类型字符串 赋值给当前的字符串
* `string& operator=(const string &s); `         //把字符串s赋给当前的字符串
* `string& operator=(char c); `                          //字符赋值给当前的字符串
* `string& assign(const char *s); `                  //把字符串s赋给当前的字符串
* `string& assign(const char *s, int n); `     //把字符串s的前n个字符赋给当前的字符串
* `string& assign(const string &s); `              //把字符串s赋给当前字符串
* `string& assign(int n, char c); `                  //用n个字符c赋给当前字符串
*/
void test() {
	string s1("baidu");
	
	string s2;
	s2 = "123456";
	
	string s3;
	s3 = s1;

	string s4;
	s4 = 'j';

	string s5;
	s5.assign("11111");
	cout << s5 << endl;

	string s6;
	s6.assign("hello world",5);
	cout << "s6 = " << s6 << endl;		// 把字符串s的前n个字符赋给当前的字符串

	string s7;
	s7.assign(s1);
	cout << s7 << endl;

	string s8;
	s8.assign(10,'m');					// 用n个字符c赋给当前字符串
	cout << s8 << endl;


}

int main()
{
	test();
	std::cout << "Hello World!\n";
}

