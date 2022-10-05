#include <iostream>
#include <map>
using namespace std;

/*
* map中所有元素都是pair对组
* pair中第一个元素为key（键值），起到索引作用，第二个元素为value（实值）
* 所有元素都会根据元素的键值自动排序
*/

void printMap(const map<int, int>&m) {
	for (map<int, int>::const_iterator it = m.cbegin(); it != m.cend(); it++) {
		// 对组的第一个值为first, 第二个值为second
		cout << "{" << (*it).first << "," << it->second << "}" << endl;
	}
}

void test() {
	// 默认构造函数
	map<int, int> m;
	// map容器在插入的时候会根据Key值排序, map的key值不可以重复
	m.insert(make_pair(10, 10));		// 匿名对组
	m.insert(pair<int, int>(30, 2000));	// 匿名对组
	m.insert(make_pair(20, 100));		// 匿名对组
	m.insert(pair<int, int>(40, 200));	// 匿名对组
	printMap(m);
	cout << "===================" << endl;
	// 拷贝构造
	map<int, int> m2(m);
	printMap(m2);

	cout << "===================" << endl;
	map<int, int> m3;
	// 赋值运算符
	m3 = m2;
	printMap(m3);
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
