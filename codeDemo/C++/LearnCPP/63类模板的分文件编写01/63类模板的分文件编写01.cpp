//#include "Person.h" // 包含类模板的.h文件时不够的. 原因: 类模板中成员函数创建时机是在**调用阶段**，**导致分文件编写时链接不到**
#include "Person.cpp"	//直接包含.cpp源文件, 但是实际开发中很少这么去做

void func() {
	Person<string, int> p("zhangsanfeng", 22);
	p.showPerson();
}

int main()
{
	func();
    std::cout << "Hello World!\n";
}
