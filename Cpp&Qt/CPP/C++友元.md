# C++友元



友元: 可以访问私有成员

```C++
#include <iostream>
using namespace std;
#include <string>


class Home;//前置声明
class MyFriend
{
public:
	//这里不能写具体实现,因为编译器认为Home类还没有具体实现
	void visit(Home *h);
};

class Person {
public:
	void access(Home *h);
	void access1(Home *h);
};

class Home
{
	friend void func(Home *h);//全局函数做友元
	friend class MyFriend;//友元类
	friend void Person::access(Home *h);//成员函数做友元
public:
	Home();
	string livingRoom;//客厅 public

private:
	string bedRoom;//卧室 private
};

Home::Home()
{
	livingRoom = "客厅";
	bedRoom = "卧室";
}

//友元类的成员函数
void MyFriend::visit(Home *h) {
	cout << "友元类visit() 访问 " << h->livingRoom << endl;
	//访问私有成员
	cout << "友元类visit() 访问 " << h->bedRoom << endl;
}

//成员函数友元
void Person::access(Home *h) {
	cout << "成员函数access() 访问 " << h->livingRoom << endl;
	//访问私有成员
	cout << "成员函数access() 访问 " << h->bedRoom << endl;
}

//普通成员函数
void Person::access1(Home *h) {
	cout << "成员函数access1() 访问 " << h->livingRoom << endl;
	//并没有声明为友元成员函数,则不能访问私有成员
	//cout << "成员函数access1() 访问 " << h->bedRoom << endl;
}



//全局函数
void func(Home *h) {
	cout << "全局函数友元func() 访问 " << h->livingRoom << endl;
	//访问私有成员
	cout << "全局函数友元func() 访问 " << h->bedRoom << endl;
}

void test() {
	Home myHome;
	func(&myHome);

	MyFriend f;
	f.visit(&myHome);

	Person p;
	p.access(&myHome);
	p.access1(&myHome);
}

//main函数
int main() {
	cout << "hello" << endl;
	test();
	return 0;
}
```

