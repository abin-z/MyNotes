#include <iostream>
#include <string>
using namespace std;
namespace ZB {
	void test();
}

//只要创建一个类, 编译器会自动生成三个函数
//1.默认构造函数		当用户自定义了构造函数后, 编译器将不会再提供默认的构造函数,但是会提供默认的拷贝构造函数
//2.析构函数			
//3.拷贝构造函数		当用户自定义了拷贝构造函数后, 编译器将不会提供其他的构造函数,包括默认的构造函数也不会提供

class Student {
public:
	Student();		// 默认构造函数
	Student(string name, int age); // 有参构造函数
	Student(const Student &s);		// 自定义拷贝构造
	~Student();		// 析构函数
	int getAge();

private:
	string name;
	int *age;		// 指针类型的变量
};

// 无参构造
Student::Student() {
	cout << "无参构造函数调用" << endl;
}

// 有参构造
Student::Student(string name, int age) {
	this->name = name;
	this->age = new int(age);		//这是通过new关键字 在堆区中开辟的空间, 需要程序员自己管理释放操作
	cout << "有参构造函数调用" << endl;
}

// 自定义拷贝构造函数
Student::Student(const Student &s) {
	//编译器默认的拷贝构造函数提供的是浅拷贝,类似于以下代码
	//this->name = s.name;
	//this->age = s.age;			//浅拷贝, 仅仅是值的拷贝, 会导致指针类型的属性都指向同一块内存空间.会导致很多问题

	this->name = s.name;				// 正常值拷贝(浅拷贝)
	this->age = new int(*(s.age));		//深拷贝, 在堆区中重新开辟空间
	cout << "有参构造函数调用" << endl;
}

// 析构函数
Student::~Student() {
	if (this->age != nullptr) {
		delete age;					// 释放堆区的内存空间,防止内存泄漏
		age = nullptr;
		cout << "释放空间" << endl;
	}
	cout << "析构函数调用" << endl;
}

int Student::getAge() {
	return *(this->age);
}

void ZB::test() {
	//在创建对象时,如果调用的是默认无参构造器,不能写成: Student s1(); 不能写括号
	//Student s1(); 这样编译器不会创建Student对象,  编译器会认为这是一个函数的声明
	Student s1;
	Student s2("tom", 16);
	cout << "s2.age = " << s2.getAge() << endl;
	Student s3(s2);		//调用拷贝构造函数
	cout << "s3.age = " << s3.getAge() << endl;
}

int main()
{
	ZB::test();
	cout << endl << "如果在类属性有堆区开辟的(new),一定要自己提供 拷贝构造函数 ,并利用深拷贝(new)来解决浅拷贝带来的问题" << endl;
	return 0;
}