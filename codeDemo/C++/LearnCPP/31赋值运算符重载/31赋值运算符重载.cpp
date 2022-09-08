#include <iostream>
#include <string>

using namespace std;

//c++编译器至少给一个类添加4个函数
//
//1. **默认构造函数(无参，函数体为空)**
//2. **默认析构函数(无参，函数体为空)**
//3. **默认拷贝构造函数，对属性进行值拷贝**
//4. **赋值运算符 operator=, 对属性进行值拷贝**

class Person
{
public:
	Person() : m_Age(nullptr) {}
	Person(int age)
	{
		//将年龄数据开辟到堆区
		m_Age = new int(age);
	}

	Person(const Person &p)
	{
		//将年龄数据开辟到堆区
		this->m_Age = new int(p.getM_Age());
		cout << "Person(const Person &p) is called." << endl;
	}

	// 赋值运算符重载 需要返回自身引用
	Person& operator=(const Person &p) {
		if (this->m_Age != nullptr){
			delete this->m_Age;
		}
		this->m_Age = new int(p.getM_Age());	// 深拷贝
		cout << "Person& operator=(const Person &p) is called." << endl;
		return *this;
	}

	// 析构函数释放内存
	~Person() {
		if (this->m_Age != nullptr) {
			delete m_Age;						// 注意深浅拷贝问题, 重写拷贝构造和赋值运算重载
			m_Age = nullptr;
		}
	}

	// getter 
	int getM_Age() const { return *m_Age; }

private:
	int *m_Age;
};

void func() {
	Person p1(20);
	Person p2(30);
	Person p5;
	p5 = p2 = p1;		// 这是赋值操作, 调用的是赋值运算符重载函数
	cout << "p1 = " << p1.getM_Age() << endl;
	cout << "p2 = " << p2.getM_Age() << endl;

	Person p3 = p1;		// 这是初始化p3, 调用的是拷贝构造函数;
	Person p4(p2);		// 这也是初始化p4, 调用的是拷贝构造函数;
	cout << "p3 = " << p3.getM_Age() << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
