#include <iostream>
#include <set>
#include <string>
using namespace std;

class Person {
public:
	Person() {}
	Person(string name, int age) {
		this->m_name = name;
		this->m_age = age;
	}

public:
	int m_age;
	string m_name;
};

class PersonCompare {
public:
	bool operator() (const Person &p1, const Person &p2) {
		return p1.m_age > p2.m_age;
	}
};

void test() {

	set<Person, PersonCompare> s; // 对于自定义类型的set集合, 必须要自定义排序规则
	Person p1("唐僧", 20);
	Person p2("孙悟空", 500);
	Person p3("猪八戒", 400);
	Person p4("沙师弟", 300);

	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);

	for (set<Person, PersonCompare>::const_iterator cit = s.cbegin(); cit != s.cend(); cit++) {
		cout << "{" << cit->m_name << "," << cit->m_age << "}" << endl;
	}
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}