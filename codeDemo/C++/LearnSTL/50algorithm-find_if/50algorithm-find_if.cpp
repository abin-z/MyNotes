#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

/*
- `find_if(iterator beg, iterator end, _Pred);  `
  // 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
  // beg 开始迭代器
  // end 结束迭代器
  // _Pred 函数或者谓词（返回bool类型的仿函数）
*/

// 前置声明
class Person;

class GreaterFive {
public:
	bool operator()(const Person &p);   //这里不能直接写实现
};

class Person {
	// 友元函数
	friend ostream& operator<<(ostream &out, const Person &p);
	friend bool GreaterFive::operator()(const Person &p);
public:
	Person(string name, int age) :
		m_name(name),
		m_age(age)
	{	}

private:
	string m_name;
	int m_age;
};

// 成员函数类外实现
bool GreaterFive::operator()(const Person &p) {
	return p.m_age > 5;
}

// 全局函数 << 运算符重载
ostream& operator<<(ostream &out, const Person &p) {
	out << "{" << p.m_name << "," << p.m_age << "}";
	return out;
}

// 全局函数
void showPerson(const Person &p) {
	cout << p << endl;
}

void test() {
	vector<Person> vtr;
	vtr.push_back(Person("AAA", 1));
	vtr.push_back(Person("BBB", 3));
	vtr.push_back(Person("CCC", 5));
	vtr.push_back(Person("DDD", 8));

	for_each(vtr.cbegin(), vtr.cend(), showPerson);
	vector<Person>::const_iterator pos =
		find_if(vtr.cbegin(), vtr.cend(), GreaterFive());
	if (pos == vtr.cend())
	{
		cout << "未找到!" << endl;
	}
	else
	{
		cout << "找到了: " << *pos << endl;
	}
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}