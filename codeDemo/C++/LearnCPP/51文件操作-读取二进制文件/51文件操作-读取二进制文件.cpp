#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Birthday {
public:
	Birthday(int y, int m, int d) :year(y), mouth(m), day(d) {}
	int year;
	int mouth;
	int day;
};

class Person {
	friend ostream& operator<<(ostream &out, const Person &person);
public:
	char m_name[64];
	//string m_name;		// 二进制读写不能使用string, 会读取文件时导致程序崩溃
	int m_age;
	Birthday *birthday;
};

ostream& operator<<(ostream &out, const Person &person) {
	out << "{" << person.m_name << ","
		<< person.m_age << ",{"
		<< person.birthday->year
		<< "," << person.birthday->mouth
		<< "," << person.birthday->day << "}}";
	return out;
}

void writeFile() {
	ofstream ofs;
	ofs.open("Person.dat", ios::out | ios::binary);
	Person person = {
		"张三丰【】",
		50,
		nullptr
	};
	person.birthday = new Birthday(1999, 10, 23);
	// 注意: 需要将对应的地址强转换为 const char *
	ofs.write((const char *)&person, sizeof(Person));	// 二进制的方式写文件
	ofs.close();
}

void test() {
	ifstream ifs;
	ifs.open("Person.dat", ios::in | ios::binary);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	// 读取数据
	Person person;
	// 注意: 需要将对应的地址强转换为 char *
	ifs.read((char *)&person, sizeof(Person));
	cout << person.m_name << endl;
	cout << person.m_age << endl;
	cout << person.birthday->year << endl;
	cout << person.birthday->mouth << endl;
	cout << person.birthday->day << endl;
	cout << person << endl;
}

int main()
{
	writeFile();
	test();
	std::cout << "Hello World!\n";
}
