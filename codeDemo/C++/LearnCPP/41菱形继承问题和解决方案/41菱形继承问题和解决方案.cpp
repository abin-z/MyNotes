#include <iostream>
using namespace std;

//继承前加virtual关键字后，变为虚继承
//此时公共的父类Animal称为虚基类

// 动物类
class Animal {	// 此时为虚基类
public:
	int m_age; // 年龄
};

// 羊类
class Sheep :virtual public Animal {};		// virtual 虚继承
// 驼类
class Camel :virtual public Animal {};		// virtual 虚继承
// 羊驼类
class Alpaca : public Sheep, public Camel {};	// 菱形继承

void func() {
	Alpaca alpaca;
	//alpaca.m_age = 5;			// 在没有使用虚继承之前会出现二义性, 因为不知道m_age来自于那个父类;
	alpaca.m_age = 5;			// 使用虚继承后不会出现二义性
	// 可以通过添加类名作用域区分
	alpaca.Camel::m_age = 10;
	alpaca.Sheep::m_age = 88;
	
	cout << "alpaca.Camel::m_age = " << alpaca.Camel::m_age << endl; //88	// 添加作用域区分		
	cout << "alpaca.Sheep::m_age = " << alpaca.Sheep::m_age << endl; //88	// 添加作用域区分		
	cout << "alpaca.Sheep::m_age = " << alpaca.m_age << endl;		 //88  使用虚继承后不会出现二义性, 修改的也是同一份数据
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
