#include <string>
#include <iostream>
using namespace std;

void test() {
	string str = "hello world!";
	//cout << "str = " << str << endl;
	for (int i = 0; i < str.size(); i++)
	{
		// str[i] 访问单个字符
		cout << str[i];		// string 类重载了 [] 运算符
	}
	cout << endl;
	str.at(0) = '5';
	for (int i = 0; i < str.length(); i++)
	{
		// str.at(i) 访问单个字符
		cout << str.at(i);
	}
}

int main()
{
	test();
}
