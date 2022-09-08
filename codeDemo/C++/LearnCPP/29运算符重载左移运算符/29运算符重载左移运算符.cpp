#include <string>
#include <iostream>
using namespace std;

// 重载左移运算符 << 无法通过成员函数实现, 只能通过全局函数实现
class Person {
	friend ostream& operator<<(ostream &out, const Person &p);	// 友元全局函数, 访问私有属性
public:
	Person() : m_name(""), m_value(0) {}
	Person(string name, double value) : m_name(name), m_value(value) {}

private:
	string m_name;
	double m_value;
};

// << 左移运算符号重载
ostream& operator<<(ostream &out, const Person &p) {		// 需要返回 ostream& 的引用才能链式调用
	out << "{m_name = " << p.m_name << ", m_value = " << p.m_value << "}";
	return out;
}

void func() {
	Person p("圆周率", 3.14159);
	Person p2;
	cout << "输出: " << p << endl << p2 << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
