#include <iostream>
#include <set>
#include <string>
using namespace std;

/*
* `find(key);`                  //查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回set.end() 迭代器;
* `count(key);`                //统计key的元素个数
*/

void printSet(const set<string> &s) {
	for (set<string>::const_iterator it = s.cbegin(); it != s.cend(); it++)
	{
		cout << *it << endl;
	}
}

void test() {
	set<string> s;

	s.insert("xiaoming");
	s.insert("lihua");
	s.insert("tom");
	s.insert("tony");
	s.insert("jerry");

	printSet(s);

	set<string>::iterator it = s.find("tom");				// 找到了直接返回迭代器, 没找到返回结束迭代器

	if (it != s.end()) {
		cout << " = " << *it << endl;
	}
	else {
		cout << "未找到" << endl;
	}

	int count = s.count("tony");
	cout << "count = " << count << endl;
	

}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
