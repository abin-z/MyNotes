#include <iostream>
using namespace std;

//C++中拷贝构造函数调用时机通常有三种情况
//
//* 使用一个已经创建完毕的对象来初始化一个新对象
//* 值传递的方式给函数参数传值
//* 以值方式返回局部对象

class Person {
public:
	// 无参构造函数
	Person() {
		cout << "无参构造函数被调用" << endl;
		m_age = 0;
	}
	// 有参构造函数(重载)
	Person(int age) {
		cout << "有参构造函数被调用" << endl;
		m_age = age;
	}
	// 拷贝构造函数
	Person(const Person &p ) {			// 若不提供,编译器会提供一个值拷贝的默认的拷贝构造.
		cout << "拷贝构造函数被调用" << endl;
		m_age = p.m_age;
	}
	// 析构函数
	~Person() {
		cout << "~析构构造函数被调用" << endl;
	}

private:
	int m_age;		// 私有属性
};

void doSometing(Person p) {		// 值传递方式的参数, 会创建一个临时副本
	// doSometing.....
	// 函数执行完后会执行p对象的析构函数
}

Person doTest() {				// 值传递方式的返回局部对象
	Person p;	// 调用构造函数
	cout << "函数中局部变量的p对象地址: " << (int)&p << endl;
	return p;	
}

void func() {
	Person p1;				// 调用构造函数
	//Person p2();	// 错误: 当调用无参构造的时候不能添加(), 编译器会认为是函数的声明

	Person p2(p1);			// 调用拷贝构造函数: 使用一个已经创建完毕的对象来初始化一个新对象

	// 参数为值传递才会调用拷贝构造, 非地址传递和非引用传递
	doSometing(p1);			// 调用拷贝构造函数: 值传递的方式给函数参数传值

	Person p = doTest();	// 调用拷贝构造函数: 以值方式返回局部对象
	cout << "main函数中的p对象地址: " << (int)&p << endl;
}

int main()
{	
	func();
    cout << "Hello World!\n";
	return 0;
}


