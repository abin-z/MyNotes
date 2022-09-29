#include <iostream>
#include <string>
using namespace std;

void test() {
	string s = "hello world";
	s.insert(1, "222");			// 插入字符串
	cout << "s = " << s << endl;

	// 删除字符串 erase()
	s.erase(1, 3);
	cout << "s = " << s << endl;
}

int main()
{
	test();
}


