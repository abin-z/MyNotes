#include <iostream>
#include <string>
using namespace std;

class MyInteger {
	// 友元全局函数--运算符重载
	friend ostream& operator<<(ostream& cout, const MyInteger &integer);
public:
	MyInteger() : m_value(0) {}
	MyInteger(int value) : m_value(value) {}

	// 前置递减运算符重载
	MyInteger& operator--() {
		this->m_value++;	// 先++ 然后再返回
		return *this;
	}

	// 后置递减运算符重载
	MyInteger operator--(int) {
		MyInteger temp = *this;		//记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
		this->m_value++;
		return temp;
	}

private:
	int m_value;
};

// << 输出运算符重载
ostream& operator<<(ostream& cout, const MyInteger &integer) {
	cout << integer.m_value;
	return cout;
}

void func() {
	MyInteger num(20);
	cout << --num << endl;
	cout << num << endl;

	MyInteger num1(30);
	cout << num1-- << endl;
	cout << num1 << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
