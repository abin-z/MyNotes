#include <iostream>
#include <string>
using namespace std;

class Base1 {
public:
	int m_a;
protected:
	int m_b;
private:
	int m_cc;
	static int s_cout;		// 静态的成员不在类对象模型中
	const int c_PI = 3;
};

int Base1::s_cout = 0;	//静态属性类外初始化


class Base2 {
private:
	int m_k;
	char m_cha;		// 注意内存对齐的问题
};

class Son : public Base1, protected Base2 {
private:
	int m_d;
};

int main()
{
	cout << "sizeof(Base) = " << sizeof(Base1) << endl;			// 16
	cout << "sizeof(Base) = " << sizeof(Base2) << endl;			// 8 内存对齐的原因
	cout << "sizeof(Son) = " << sizeof(Son) << endl;			// 28
	std::cout << "Hello World!\n";
}
