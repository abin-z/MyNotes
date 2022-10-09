#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

/*
`find(iterator beg, iterator end, value);  `

// 按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置

// beg 开始迭代器

// end 结束迭代器

// value 查找的元素
*/

// 查找string类型元素, string已经重载了 == 运算符
void test01() {
	vector<string> v;

	string s = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++)
	{
		v.push_back(string("员工") += s.at(i));
	}
	string tgt = "员工B";
	vector<string>::iterator pos = find(v.begin(), v.end(), tgt);
	if (pos == v.end()) {
		cout << "not find" << endl;
	}
	else {
		cout << "找到了: " << *pos << endl;
	}
}

struct MyStruct
{
	// 友元函数
	friend ostream& operator<<(ostream &out, const MyStruct &s);
	MyStruct() {
		m_name = string();
		m_age = 0;
	}

	MyStruct(string name, int age) {
		m_name = name;
		m_age = age;
	}

	// 自定义数据需要提供 == 运算符号重载
	bool operator==(const MyStruct &s) {
		// 自己比较
		if (this == &s) {
			return true;
		}
		// 比较内容
		if (this->m_name == s.m_name && this->m_age == this->m_age) {
			return true;
		}
		return  false;
	}

private:
	string m_name;
	int m_age;
};

// 重载<<运算符
ostream& operator<<(ostream &out, const MyStruct &s)
{
	out << "{" << s.m_name << "," << s.m_age << "}";
	return out;
}


// 查找自定义数据类型
void test02() {
	vector<MyStruct> vtr;

	MyStruct p1("xiaming", 12);
	MyStruct p2("lihua", 13);
	MyStruct p3("tom", 14);
	MyStruct p4("tony", 15);

	vtr.push_back(p1);
	vtr.push_back(p2);
	vtr.push_back(p3);
	vtr.push_back(p4);

	MyStruct p5("tony", 15);
	// 查找自定义数据类型时，需要重载==运算符
	vector<MyStruct>::iterator pos = find(vtr.begin(), vtr.end(), p5);
	if (pos == vtr.end()) {
		cout << "not find" << endl;
	}
	else {
		cout << "找到了: " << *pos << endl;
	}
}

int main()
{
	test01();
	test02();
	std::cout << "Hello World!\n";
}