#pragma once
#include <string>
#include <iostream>
using namespace std;

//解决方式2：将声明和实现写到同一个文件中，并更改后缀名为.hpp，hpp是约定的名称，并不是强制

// 类模板
template<class T1, class T2>
class Person {
public:
	Person(T1 name, T2 age);
	void showPerson();

private:
	T1 m_name;
	T2 m_age;
};

// 类成员函数类外实现,
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_age = age;
	this->m_name = name;
}

// 类成员函数类外实现
template<class T1, class T2>
void Person<T1, T2>::showPerson() {
	cout << "m_name = " << m_name << endl;
	cout << "m_age = " << m_age << endl;
}

