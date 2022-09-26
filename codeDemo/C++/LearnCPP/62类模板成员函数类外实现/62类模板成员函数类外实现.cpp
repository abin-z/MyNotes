#include <string>
#include <iostream>
using namespace std;
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

// 类成员函数类外实现
template<class T1, class T2>
Person<T1,T2>::Person(T1 name, T2 age) {
	this->m_age = age;
	this->m_name = name;
}

// 类成员函数类外实现
template<class T1, class T2>
void Person<T1,T2>::showPerson() {
	cout << "m_name = " << m_name << endl;
	cout << "m_age = " << m_age << endl;
}

void test() {
	Person<string, int> p("猪八戒", 999);
	p.showPerson();
}


int main()
{
	test();
    std::cout << "Hello World!\n";
}