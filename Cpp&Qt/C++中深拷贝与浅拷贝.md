# C++中深拷贝与浅拷贝的问题



### C++ 中类的拷贝构造函数 如果是编译器自动生成的,采用的是浅拷贝 



#### 浅拷贝: 仅仅是值的拷贝

#### 深拷贝: 重新开辟新的内存空间, 然后把值复制到新的内存空间上



```C++
#include "iostream"
#include "string"
using namespace std;

class Student
{
public:
	//只要创建一个类, 编译器会自动生成三个函数
	//1.默认构造函数		当用户自定义了构造函数后, 编译器将不会再提供默认的构造函数,但是会提供默认的拷贝构造函数
	//2.析构函数			
	//3.拷贝构造函数		当用户自定义了拷贝构造函数后, 编译器将不会提供其他的构造函数,包括默认的构造函数也不会提供
	Student();
	Student(string name, int age);
	~Student();
	Student(const Student& s);

	int getAge();

private:
	string name;
	int * age;//是一个int指针变量
};

//构造函数
Student::Student()
{
	cout << "调用Student()默认构造函数" << endl;
}

//有参构造函数
Student::Student(string name, int age)
{
	cout << "调用Student(string name, int age)有参构造函数" << endl;
	this->name = name;
	this->age = new int(age);//这是通过new关键字 在堆区中开辟的空间, 需要程序员自己管理释放操作
}

//析构函数
Student::~Student()
{
	//一般释放操作放在析构函数里面, 但是需要注意浅拷贝的问题
	if (age != NULL) {
		delete age;
		age = NULL;//将指针置为NULL, 防止成为野指针
	}

	cout << "调用~Student()析构函数" << endl;
}

//自定义的拷贝构造函数, 需要使用深拷贝
Student::Student(const Student& s) {
	cout << "调用Student(const Student& s)拷贝构造函数" << endl;

	//编译器默认的拷贝构造函数提供的是浅拷贝,类似于以下代码
	//this->name = s.name;
	//this->age = s.age;			//浅拷贝, 仅仅是值的拷贝, 会导致指针类型的属性都指向同一块内存空间.会导致很多问题

	this->name = s.name;
	this->age = new int(*s.age);	//深拷贝, 在堆区中重新开辟空间
}

int Student::getAge() {
	return *(this->age);
}

void test() {
	//在创建对象时,如果调用的是默认无参构造器,不能写成: Student s1(); 不能写括号
	//Student s1(); 这样编译器不会创建Student对象,  编译器会认为这是一个函数的声明
	Student s1;
	Student s2("tom", 16);
	cout << "s2.age = " << s2.getAge() << endl;
	Student s3(s2);
	cout << "s3.age = " << s3.getAge() << endl;
}

int main() {
	test();
	cout << endl << "如果在类属性有堆区开辟的(new),一定要自己提供 拷贝构造函数 ,并利用深拷贝(new)来解决浅拷贝带来的问题" << endl;
	return 0;
}
```



### 总结: 如果在类属性有堆区开辟的(new),一定要自己提供拷贝构造函数 ,并利用深拷贝(new)来解决浅拷贝带来的问题.



**网址链接:**    [C++细节 深拷贝和浅拷贝(位拷贝）详解](https://blog.csdn.net/weixin_41143631/article/details/81486817)

