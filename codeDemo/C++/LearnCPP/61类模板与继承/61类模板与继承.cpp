#include <iostream>
#include <string>
using namespace std;

// 模板类
template<class T>
class Base {
public:
	T m;
};


//class Son:public Base  //错误，c++编译需要给子类分配内存，必须知道父类中T的类型才可以向下继承
// 继承模板类但本身不是类模板需要明确父类的类型
class Son1 : public Base<string> {	// 必须指定一个类型
private:
	int m_age;
};

// 继承类模板本类依然是一个类模板, //类模板继承类模板 ,可以用T2指定父类中的T类型
template<class T1, class T2>
class Son2 :public Base<T2> 
{
public:
	Son2(T1 gender, T2 m) {
		this->m_gender = gender;
		this->m = m;
		cout << "T1 = " << typeid(T1).name() << endl;
		cout << "T2 = " << typeid(T2).name() << endl;
	}

	T1 m_gender;
};

void func() {
	Son1 son1;
	Son2<string, int> son2("男", 22);
	cout << son2.m_gender << son2.m << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
