#include <iostream>
using namespace std;

class Animal {	// 抽象类: 只要类中有纯虚函数, 该类就是一个抽象类
public:
	virtual void speak() = 0;		// 纯虚函数, 子类必须实现该纯虚函数, 否则子类依然是抽象类
};

class Cat :public Animal {
	virtual void speak() override // 重写父类的函数最好加上 override 关键字
	{		
		cout << "猫在说话!!!" << endl;
	}
};

class Dog :public Animal {
	//virtual void speak() override {		// 重写父类的函数最好加上 override 关键字
	//	cout << "狗在说话!!!" << endl;
	//}
};


void func() {
	//Animal animal;  //		抽象类无法实例化对象
	//Dog dog;	// Dog类没有重写 speak() 纯虚函数, 所以也是抽象类, 无法实例化对象
	Animal * animal = new Cat();
	animal->speak();
	delete animal;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}

