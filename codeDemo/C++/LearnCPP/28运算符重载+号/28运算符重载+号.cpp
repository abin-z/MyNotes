#include <iostream>
using namespace std;

class Person {
public:
	// constuctor
	Person() {};
	Person(int a, int b) :m_A(a), m_B(b) {};

	// + 号运算符重载(成员函数)
	//Person operator+(const Person &p);	

	// + 号运算符重载的函数重载版本(成员函数)
	Person operator+(int num);

	// getter
	int getM_A() const { return m_A; }	// 常函数
	int getM_B() const { return m_B; }	// 常函数
	// setter
	void setM_A(int a) { m_A = a; }
	void setM_B(int b) { m_B = b; }

private:
	int m_A;
	int m_B;
};

// + 号运算符重载(成员函数重载)
//Person Person::operator+(const Person &p) {
//	Person temp;
//	temp.m_A = p.m_A + this->m_A;
//	temp.m_B = p.m_B + this->m_B;
//	cout << "成员运算符函数重载" << endl;
//	return temp;
//}

Person Person::operator+(int num) {
	Person temp;
	temp.m_A = this->m_A + num;
	temp.m_B = this->m_B + num;
	return temp;
}

// + 号全局函数运算符重载
Person operator+(const Person &p1, const Person &p2) {
	Person temp;
	temp.setM_A(p1.getM_A() + p2.getM_A());
	temp.setM_B(p1.getM_B() + p2.getM_B());
	cout << "全局运算符函数重载" << endl;
	return temp;
}

void func() {
	Person p1(10, 10);
	Person p2(20, 20);

	Person p3 = p1 + p2;	// 等价于调用运算符重载函数
	//Person p3 = operator+(p1, p2);	//---全局函数
	cout << "p3.m_A = " << p3.getM_A() << endl;
	cout << "p3.m_B = " << p3.getM_B() << endl;

	Person p4 = p1 + 50;	// 等价于调用运算符重载
	//Person p4 = p1.operator+(50);		//---成员函数
	cout << "p4.m_A = " << p4.getM_A() << endl;
	cout << "p4.m_B = " << p4.getM_B() << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
