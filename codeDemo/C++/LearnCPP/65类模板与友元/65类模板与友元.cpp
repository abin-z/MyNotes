#include <iostream>
#include <string>
using namespace std;

// 类模板的前置声明: 仅仅是为了全局友元函数
template<class T1, class T2>
class Person;

// 友元函数类外实现(比较麻烦), 只能在类模板的前面写
template<class T1, class T2>
void printPerson02(const Person<T1, T2> &p) {
	cout << "name = " << p.m_name << " age = " << p.m_age << endl;
}

// 类模板
template<class T1, class T2>
class Person {
	// 类外实现全局友元函数
	friend void printPerson02<>(const Person<T1, T2> &p);

	// 类内实现全局友元函数
	friend void printPerson(const Person &p)		// 这是一个全局的友元函数, 只不过是在类内实现的
	{
		cout << "name = " << p.m_name << " age = " << p.m_age << endl;
	}

public:
	Person(T1 name, T2 age);

private:
	T1 m_name;
	T2 m_age;
};

// 类成员函数类外实现
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_age = age;
	this->m_name = name;
}

void test() {
	Person<string, long> person("李华", 255);
	printPerson(person);	// 调用类内实现的全局友元函数
	printPerson02(person);	// 调用类外实现的全局友元函数
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}

