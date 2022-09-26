#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	Person(string name, int age) {
		this->m_age = age;
		this->m_name = name;
	}

	int m_age;
	string m_name;

	//// 方式1: 重写 == 运算符重载
	//bool operator==(const Person &p) {
	//	if (this->m_age == p.m_age && this->m_name == p.m_name) {
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}
	//}
};

// 比较模板
template<typename T>
bool myCompare(T &a, T &b) {
	if (a == b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 具体化，显示具体化的原型和定意思以template<>开头，并通过名称来指出类型
// 具体化优先于常规模板
template<> bool myCompare(Person &p1, Person &p2) {	// 参数列表需要给出具体类型, 前面需要添加 temolate<>
	if (p1.m_age == p2.m_age && p1.m_name == p2.m_name)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void test() {
	int a = 10;
	int b = 20;
	cout << "myCompare(a, b) = " << myCompare(a, b) << endl;
}

void test02() {
	Person p1("tom", 18);
	Person p2("tom", 18);
	cout << "myCompare(p1, p2) = " << myCompare(p1, p2) << endl;
}

int main()
{
	test();
	test02();
	std::cout << "Hello World!\n";
}
