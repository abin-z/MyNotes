#include <iostream>
#include <string>
using namespace std;

//类模板中成员函数和普通类中成员函数创建时机是有区别的：
//
//* 普通类中的成员函数一开始就可以创建
//* 类模板中的成员函数在调用时才创建

class Person1 {
public:
	void showPerson1() {
		cout << "showPerson1() 调用" << endl;
	}
};
class Person2 {
public:
	void showPerson2() {
		cout << "showPerson2() 调用" << endl;
	}
};

template<class T>
class Clazz {
public:
	T obj;


	//类模板中的成员函数，并不是一开始就创建的，而是在模板调用时再生成
	void func01() {
		obj.showPerson1();
	}

	void func02() {
		obj.showPerson2();
	}
};

void test() {
	Clazz<Person1> clazz;
	clazz.func01();
	//clazz.func02();  //编译会出错，说明函数调用才会去创建成员函数
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}

//总结：类模板中的成员函数并不是一开始就创建的，在调用时才去创建