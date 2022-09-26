#pragma once
#include <string>
#include <iostream>
using namespace std;

//�����ʽ2����������ʵ��д��ͬһ���ļ��У������ĺ�׺��Ϊ.hpp��hpp��Լ�������ƣ�������ǿ��

// ��ģ��
template<class T1, class T2>
class Person {
public:
	Person(T1 name, T2 age);
	void showPerson();

private:
	T1 m_name;
	T2 m_age;
};

// ���Ա��������ʵ��,
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_age = age;
	this->m_name = name;
}

// ���Ա��������ʵ��
template<class T1, class T2>
void Person<T1, T2>::showPerson() {
	cout << "m_name = " << m_name << endl;
	cout << "m_age = " << m_age << endl;
}

