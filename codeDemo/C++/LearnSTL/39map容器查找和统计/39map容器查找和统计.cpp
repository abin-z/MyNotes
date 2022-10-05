#include <iostream>
#include <map>
#include <string>
using namespace std;

void test() {
	map<int, string> m1;
	m1.insert(pair<int, string>(50,"xiaoming"));
	m1.insert(pair<int, string>(40,"lihua"));
	m1.insert(make_pair(45,"tom"));
	m1.insert(make_pair(60,"tony"));
	m1.insert(map<int,string>::value_type(80, "jerry"));
	m1.insert(map<int,string>::value_type(70, "merry"));

	map<int, string>::iterator it = m1.find(40);			// find函数返回的是一个迭代器
	if (it != m1.end()) {		// 如果没有找到, 返回的是结束迭代器. 注意: 我们不能直接访问结束迭代器
		cout << "找到了 " << it->first << "," << it->second << endl;
	}
	else {
		cout << "未找到!" << endl;	
	}
	cout << m1.count(50) << endl;			// 统计key
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
