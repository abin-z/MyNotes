#include <iostream>
#include <string>
using namespace std;

//学习目标：
//
//* 类模板实例化出的对象，向函数传参的方式
// 
//一共有三种传入方式：
//
//1. 指定传入的类型-- - 直接显示对象的数据类型(常用)
//2. 参数模板化-- - 将对象中的参数变为模板进行传递
//3. 整个类模板化-- - 将这个对象类型 模板化进行传递

// 类模板
template<class T1, class T2>
class Person {
public:
	Person(T1 name, T2 age) {
		this->m_age = age;
		this->m_name = name;
	}

	void showPerson() {
		cout << "m_name = " << m_name << ", m_age = " << m_age << endl;
	}
private:
	T1 m_name;
	T2 m_age;
};

//1、指定传入的类型 常用
void func01(Person<string, int> &p) {
	p.showPerson();
}

//2、参数模板化
template<typename M, typename N>
void func02(Person<M, N> &p) {
	p.showPerson();
	cout << "M 的类型 = " << typeid(M).name() << endl;
	cout << "N 的类型 = " << typeid(N).name() << endl;
}

//3、整个类模板化
template<typename T>
void func03(T &p) {
	p.showPerson();
	cout << "T 的类型 = " << typeid(T).name() << endl;
}

void test01() {
	Person<string, int> p1("zhangsan", 18);
	func01(p1);

	Person<string, int> p2("白骨精", 18);
	func02(p2);

	char arr[] = "张三丰";
	Person<char *, long> p3(arr, 200);
	func03(p3);
}

int main()
{
	test01();
	return 0;
}
