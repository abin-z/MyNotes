#include <iostream>
#include <string>
using namespace std;


class CExample {
public:
	//构造函数初始化列表
	CExample() : a(0), b(8.8)
	{}
	//构造函数内部赋值
	//CExample()
	//{
	//	a = 0;
	//	b = 8.8;
	//}

private:
	int a;
	float b;
};


class Person {
public:
	Person();
	Person(int age, string name);
private:
	int m_age;
	string m_name;
};

// 无参构造函数
Person::Person() {

}

// 使用初始化列表: 先声明的先初始化
Person::Person(int age, string name) :m_age(age), m_name(name) {
	//初始化列表的成员初始化顺序: C++ 初始化类成员时，是按照声明的顺序初始化的，而不是按照出现在初始化列表中的顺序。
}

int main()
{
	Person p(18, "xaioming");
	cout << "Hello World!\n";
}