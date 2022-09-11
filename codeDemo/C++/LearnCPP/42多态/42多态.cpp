#include <iostream>				// 多态
using namespace std;

class Animal {
public:
	virtual void speak() {		// 虚函数 仅仅添加一个 virtual 关键字
		cout << "动物在说话!" << endl;
	}
};

class Dog : public Animal {
public:
	void speak() override {		// 重写父类中的虚函数建议添加 override 关键字
		cout << "小狗在说话" << endl;
	}
};

class Cat : public Animal {
public:
	virtual void speak() override{		// 子类中重写的函数 virtual 关键字可加可不加
		cout << "小猫在说话" << endl;
	}
};

void doSpeak(Animal &animal) {
	animal.speak();			// 在没有使用动态多态的时候, 函数地址早绑定
}

void func() {
	Dog dog;
	doSpeak(dog);		// 输出: 小狗在说话

	Cat cat;
	doSpeak(cat);		// 输出: 小猫在说话

	Animal animal;
	doSpeak(animal);	// 输出: 动物在说话
}

int main()
{
	func();
	cout << "sizeof(Animal) = " << sizeof(Animal) << endl;	// sizeof(Animal) = 4
	cout << "sizeof(Dog) = " << sizeof(Dog) << endl;		// sizeof(Dog) = 4
	cout << "sizeof(Cat) = " << sizeof(Cat) << endl;		// sizeof(Cat) = 4

	std::cout << "Hello World!\n";
}