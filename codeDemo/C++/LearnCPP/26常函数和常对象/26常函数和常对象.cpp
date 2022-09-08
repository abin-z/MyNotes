#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	Person(string name, int age):  m_name(name), m_age(age){}

	// 常函数
	void constFunc() const;
	void funct();
	static void staticFunc() {}

private:
	static int s_cout;
	string m_name;
	int m_age;

public:
	mutable int m_height;	// 使用 mutable 关键字使得当前属性在常函数中允许修改
};

int Person::s_cout = 0;

// 常函数中不能修改本类对象的成员和属性
void Person::constFunc() const
{
	//this->m_name = "aa";	//	常函数中不能修改对象属性
	//this->m_age = 0;		//	常函数中不能修改对象属性
	this->m_height = 100;	// 常函数中可以修改mutable 关键字修饰的属性	
	s_cout = 500;			// 常函数中可以修改静态成员, 因为静态成员不属于任何一个对象
	cout << "this->m_height = " << this->m_height << endl;
	cout << "Person::s_cout = " << Person::s_cout << endl;
}

// 正常函数中可以修改本类对象数据
void Person::funct() {
	this->m_age = 10;
	this->m_height = 200;
	this->m_name = "null";
}

void func() {
	Person p("zhangsan", 16);
	// 常对象只能调用常函数不能调用非常函数
	const Person p1("xiaoming", 20);  // 常对象: 不允许修改对象属性,除非是mutable 关键字修饰的属性
	p1.m_height = 150;	// mutable 关键字修饰的非静态属性可以修改

	p.constFunc();		
	p.funct();

	//p1.funct();		// 错误: 常对象不能调用非常函数
	p1.constFunc();		// 正确: 常对象只能调用常函数
	p1.staticFunc();	// 正确: 常对象可以调用静态函数, 因为静态函数中只有静态成员
}

int main()
{
	func();
    std::cout << "Hello World!\n";
}