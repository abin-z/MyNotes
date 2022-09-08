#include <iostream>
#include <string>
using namespace std;

//当类中成员是其他类对象时，我们称该成员为 对象成员
//构造的顺序是 ：先调用对象成员的构造，再调用本类构造
//析构顺序与构造相反

class Phone {
public:
	Phone() {
		cout << "Phone() 构造函数" << endl;
	}

	Phone(const Phone &p) {
		this->m_name = p.m_name;
		cout << "Phone(const Phone &p) 拷贝构造函数" << endl;
	}

	Phone(string name) :m_name(name) {
		cout << "Phone(string name) 构造函数" << endl;
	}
	string m_name;
};

class Person {
public:
	Person() {
		cout << "Person() 构造函数" << endl;
	}
	Person(string name, int age) :m_name(name), m_age(age) {}
	Person(string name, int age, Phone phone);
	Person(string name, int age, string phoneName);
	Person(const Person &person);	// 拷贝构造

	string m_name;
	int m_age;
	Phone m_phone;
};

// 使用初始化列表, 直接调用拷贝构造函数进行构造, 只需要执行一步操作
Person::Person(string name, int age, Phone phone) :m_phone(phone) {
	m_age = age;
	m_name = name;
	cout << "Person(string name, int age, Phone phone) 构造函数" << endl;
}

// 在构造函数中赋值, 这样会先调用默认构造函数构造了类成员，然后再调用赋值运算符对之前默认构造的类成员进行赋值，这实际上进行了两步操作
//Person::Person(string name, int age, Phone phone) {
//	m_age = age;
//	m_name = name;
//	m_phone = phone;
//	cout << "Person(string name, int age, Phone phone) 构造函数" << endl;
//}

Person::Person(const Person &person) {
	this->m_age = person.m_age;
	this->m_name = person.m_name;
	this->m_phone = Phone(person.m_phone);
	cout << "Person(const Person &person) 拷贝构造函数" << endl;
}

// 使用初始化列表 编译器会自动转化: Phone m_phone = Phone(phoneName);
Person::Person(string name, int age, string phoneName) : m_age(age), m_name(name), m_phone(phoneName) {
	cout << "Person(string name, int age, string phoneName) 构造函数" << endl;
}

void func() {
	//Person p;	// 调用无参构造函数, 会先构造Phone对象再构造Person对象
	//Person p("tom", 18, "xiaomi");	// 调用有参构造, 也会先调用Phone的有参构造

	Phone phone("apple");
	Person p("tony", 28, phone);
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}