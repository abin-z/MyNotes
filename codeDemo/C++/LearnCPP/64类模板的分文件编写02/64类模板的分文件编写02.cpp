#include "person.hpp"		// 直接包含.hpp文件
void test() {
	Person<int, double> p(20, 3.14159);
	p.showPerson();
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
