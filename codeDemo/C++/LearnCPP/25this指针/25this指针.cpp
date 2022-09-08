#include <iostream>
#include <string>
using namespace std;

// this指针的本质是一个指针常量    

class Person {
public:
	Person(int age) {
		this->age = age;	// this指针等价于 Person * const this;
	}

	int getAge() {
		return this->age;
	}

	// 链式编程
	Person& addAge(int a);
private:
	int age;
};

Person& Person::addAge(int a) {		// 返回类型一定要是引用, 否则会调用拷贝构造返回的不是同一个对象
	this->age += a;
	return *this;   // 返回当前调用的对象
}

void func() {
	Person p(20);

	// 链式编程
	p.addAge(1)
		.addAge(2)
		.addAge(2)
		.addAge(5);

	cout << p.getAge() << endl;
}

int main()
{
	func();
    std::cout << "Hello World!\n";
}

