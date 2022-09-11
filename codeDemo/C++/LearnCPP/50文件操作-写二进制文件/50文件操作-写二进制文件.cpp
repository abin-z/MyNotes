#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Person {
public:
	char m_name[64];	// 建议不要使用string类, 读取的时候会出现问题
	int m_age;
	double m_tatal;	
};

void test() {
	ofstream ofs;	// 创建输出流对象
	ofs.open("Person.dat", ios::out | ios::binary); // 以二进制的方式打开文件
	// 写入数据
	Person person = {
		"xiaoming",
		22,
		99.8
	};
	ofs.write( (const char *)&person, sizeof(Person));
	ofs.close();
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
