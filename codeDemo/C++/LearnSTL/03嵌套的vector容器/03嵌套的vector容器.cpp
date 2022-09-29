#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
public:
	Person(string name, int age) :
		m_name(name), m_age(age)
	{}

public:
	string m_name;
	int m_age;
};


void test() {
	// 容器嵌套
	vector<vector<Person>> v;

	vector<Person> v1;
	vector<Person> v2;
	vector<Person> v3;
	vector<Person> v4;
	vector<Person> v5;

	for (int i = 0; i < 5; i++)
	{
		Person p1 = Person("xiaoming" + to_string(i), i + 10); // C++ 中不能将字符串和int类型直接相加, 需要用 to_string()函数
		Person p2 = Person("lihua" + to_string(i), i + 50);
		Person p3 = Person("tom" + to_string(i), i + 30);
		Person p4 = Person("tony" + to_string(i), i + 20);
		Person p5 = Person("jerry" + to_string(i), i + 100);
		v1.push_back(p1);
		v2.push_back(p2);
		v3.push_back(p3);
		v4.push_back(p4);
		v5.push_back(p5);
	}

	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);
	v.push_back(v5);

	// 遍历
	for (vector<vector<Person>>::iterator it = v.begin(); it != v.end(); ++it) {
		for (vector<Person>::iterator vit = (*it).begin(); vit != (*it).end(); ++vit) {
			cout << "{" << (*vit).m_name << "," << (*vit).m_age << "}";
		}
		cout << endl;
	}
}

int main()
{
	test();
	std::cout << "Hello World!" + to_string(20) + "\n";
}


