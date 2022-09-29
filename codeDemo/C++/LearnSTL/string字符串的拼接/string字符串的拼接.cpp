#include <iostream>
#include <string>
using namespace std;

/*
* `string& operator+=(const char* str);`                   //重载+=操作符
* `string& operator+=(const char c);`                      //重载+=操作符
* `string& operator+=(const string& str);`                 //重载+=操作符
* `string& append(const char *s); `                        //把字符串s连接到当前字符串结尾
* `string& append(const char *s, int n);`                  //把字符串s的前n个字符连接到当前字符串结尾
* `string& append(const string &s);`                       //同operator+=(const string& str)
* `string& append(const string &s, int pos, int n);`	   //字符串s中从pos开始的n个字符连接到字符串结尾
*/

void test() {
	string s1 = "你好";
	string s2 = "世界";
	s1.append(s2, 0, 2);			// 注意: 汉字是两个长度
	cout << s1 << endl;


	s1 += "123";
	cout << s1 << endl;

	s1 += '0';
	cout << s1 << endl;

	s1 += s2;
	cout << s1 << endl;

	s1.append("test");
	cout << s1 << endl;
	//s1.append("百度", 1);			// 注意: 汉字是两个长度, 会乱码
	s1.append("百度", 2);			// 注意: 汉字是两个长度
	cout << s1 << endl;
	s1.append(s2);
	cout << s1 << endl;
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
