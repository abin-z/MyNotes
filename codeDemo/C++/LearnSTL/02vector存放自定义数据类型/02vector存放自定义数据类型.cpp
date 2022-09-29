#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
public:
	Person(string name, int age) :
		m_name(name),
		m_age(age)
	{
	}

public:
	int m_age;
	string m_name;
};


void test() {
	Person p1("xiaoming", 20);
	Person p2("lihua", 23);
	Person p3("baidu", 24);
	Person p4("ceshi", 25);
	Person p5("tom", 22);

	vector<Person> v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	for (vector<Person>::iterator i = v.begin(); i != v.end(); ++i)
	{
		//cout << "姓名: " << (*i).m_name << ",年龄: " << (*i).m_age << endl;
		cout << "姓名: " << i->m_name << ",年龄: " << i->m_age << endl;
	}

}

void test02() {
	Person p1("xiaoming", 20);
	Person p2("lihua", 23);
	Person p3("baidu", 24);
	Person p4("ceshi", 25);
	Person p5("tom", 22);

	vector<Person *> v;
	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	v.push_back(&p4);
	v.push_back(&p5);

	Person * p = nullptr;
	for (vector<Person *>::iterator i = v.begin(); i != v.end(); ++i)
	{
		//cout << "姓名: " << (*i)->m_name << ",年龄: " << (*i)->m_age << endl;
		p = *i;
		cout << "姓名: " << p->m_name << ",年龄: " << p->m_age << endl;
	}
}

int main()
{
	test();
	cout << "====================" << endl;
	test02();
	std::cout << "Hello World!\n";
}

