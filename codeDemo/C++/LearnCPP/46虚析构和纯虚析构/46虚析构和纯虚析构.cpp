#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
	Animal()
	{
		cout << "Animal 父类构造函数调用" << endl;
	}

	//virtual ~Animal() {	// 虚析构函数
	//	cout << "Animal 父类析构函数调用" << endl;
	//}

	virtual ~Animal() = 0; // 纯虚函数, 当有纯虚函数时, 该类为抽象类, 无法实例化对象

	// 纯虚函数
	virtual void speak() = 0;
};

Animal::~Animal() {
	cout << "Animal 父类析构函数调用" << endl;
}


class Cat :public Animal {
public:
	Cat(string name) : m_name(new string(name))	// 初始化列表
	{
		cout << "Cat 子类构造函数调用" << endl;
	}

	~Cat() {	// 析构函数中释放资源, 此时需要注意 拷贝构造函数 和 赋值运算符重载 问题
		if (m_name != nullptr) {
			delete m_name;	//释放资源
			m_name = nullptr;
		}
		cout << "Cat 子类析构函数调用" << endl;
	}

	// 重写拷贝构造函数
	Cat(const Cat &cat) {
		this->m_name = new string(*(cat.m_name));	// 深拷贝;
	}

	// 重写赋值运算符重载
	Cat& operator=(const Cat &cat) {		// 必须返回引用
		if (this->m_name != nullptr) {
			delete this->m_name;
		}
		this->m_name = new string(*(cat.m_name));	// 使用深拷贝
		return *this;	// 返回自身的引用
	}

	virtual void speak() override
	{
		cout << *m_name << "猫在说话!" << endl;
	}

private:
	string *m_name;
};

void doWork(Animal * animal) {
	animal->speak();
	delete animal;
}

void func() {
	doWork(new Cat("TOM"));	// 父类指针指向子类对象
}

int main()
{
	func();
}
