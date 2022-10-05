#include <iostream>
#include <string>
using namespace std;


void test() {
	// 构造方式一
	pair<int, string> s(10, "baidu");
	cout << s.first << " " << s.second << endl;



	// 构造方式二
	pair<string, string> p = make_pair("name", "xiaoming");
	cout << p.first << " " << p.second << endl;

}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
