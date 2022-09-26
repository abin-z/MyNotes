#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age);
	void showPerson();
private:
	T1 m_name;
	T2 m_age;
};

