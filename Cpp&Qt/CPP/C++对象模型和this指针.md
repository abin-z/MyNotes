# C++对象模型和this指针



### 成员变量和成员函数是分开存储的

只有**非静态成员变量**才属于类对象上, 能在类外初始化或者定义的都不在类对象上

```C++
#include <iostream>
using namespace std;

//成员变量和成员函数是分开存储的,
//只有非静态成员变量才属于类对象上

//每一个非静态成员函数只会诞生一份函数实例，
//也就是说多个同类型的对象会共用一块代码


//C++通过提供特殊的对象指针，this指针:
//this指针指向被调用的成员函数所属的对象

//1.this指针是隐含每一个非静态成员函数内的一种指针
//2.this指针不需要定义，直接使用即可
//3.this是一个指针 调用的时候用 this->成员

class Person
{
public:
	Person();
	~Person();

	int a;	//非静态成员变量 属于类的对象上

	static int m_b;	//静态成员变量   不属于类对象上

	void func() {}	//非静态成员函数  不属于类对象上

	static void func2() {} //静态成员函数 不属于类对象上


private:

};

//静态成员变量需要在类外初始化
int Person::m_b = 20;

Person::Person()
{
}

Person::~Person()
{
}

int main() {
	//空对象,里面什么都没有, 但是编译器也会分配1个字节空间(用于区分空对象)
	Person p;
	//但是如果类中有非静态成员变量的话,则对象的大小就是非静态成员变量的字节大小
	cout << "sizeof p = " << sizeof(p) << endl;
	return 0;
}
```





### 空指针访问成员函数的坑

成员函数没有使用this指针,并不会出异常, 如果**使用this指针就会触发异常**, 可以添加相应代码提升鲁棒性

```C++
#include <iostream>
using namespace std;

class Person
{
public:
	Person();
	~Person();
	void doit();//非静态成员函数
	void func();//非静态成员函数
private:
	int age = 18;
};

Person::Person()
{
}

Person::~Person()
{
}

void Person::doit() {
	cout << "调用了Person类的doit()" << endl;
	//由于本成员函数没有使用this指针,所以空指针调用的时候没有异常
}

void Person::func() {
	//防止空指针调用成员函数
	if (this == nullptr)//空指针尽量使用nullptr 少使用NULL
	{
		return;
	}

	cout << "age = " << age << endl;//age 默认是 this->age
}

int main() {
	Person p;

	p.doit();
	p.func();

	//使用空指针调用成员函数
	Person* p1 = nullptr;
	p1->doit();
	p1->func();//这里会直接return

	return 0;
}
```



### 空指针

[C++空指针究竟怎么用: NULL, 0, nullptr](https://www.cnblogs.com/porter/p/3611718.html)



### this指针

this指针的本质就是 指针常量(ClassName *const **this**), 指针的指向是不可以修改的

- this 是 const 指针，它的值是不能被修改的，一切企图修改该指针的操作，如赋值、递增、递减等都是不允许的。
- this 只能在成员函数内部使用，用在其他地方没有意义，也是非法的。
- 只有当对象被创建后 this 才有意义，因此不能在 static 成员函数中使用（后续会讲到 static 成员）。

[C++ this指针详解](http://c.biancheng.net/view/2226.html)

