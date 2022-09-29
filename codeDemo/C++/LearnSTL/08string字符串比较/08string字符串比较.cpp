#include <iostream>
#include <string>
using namespace std;

/*
* 字符串比较是按字符的ASCII码(字典顺序)进行对比

= 返回   0

\> 返回   1

< 返回  -1
*/


//字符串比较
void test01()
{

	string s1 = "hello";
	string s2 = "aello";

	int ret = s1.compare(s2);

	if (ret == 0) {
		cout << "s1 等于 s2" << endl;
	}
	else if (ret > 0)
	{
		cout << "s1 大于 s2" << endl;
	}
	else
	{
		cout << "s1 小于 s2" << endl;
	}

}

int main()
{
	test01();
    std::cout << "Hello World!\n";
}
