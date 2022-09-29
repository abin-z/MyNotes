#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Person {
public:
	Person(string name, int age) :
		m_name(name),
		m_age(age)
	{}
public:
	string m_name;
	int m_age;
};

void test() {
	queue<Person> q;		// 创建队列

	Person p1("唐僧", 1000);
	Person p2("孙悟空", 1000);
	Person p3("猪八戒", 1000);
	Person p4("沙师弟", 1000);

	// 入列
	q.push(p1);
	q.push(p2);
	q.push(p3);
	q.push(p4);

	cout << " size = " << q.size() << endl;

	while (!q.empty())
	{
		cout << "对头 = {" << q.front().m_name << "," << q.front().m_age << "}" << endl;
		cout << "对尾 = {" << q.back().m_name << "," << q.back().m_age << "}" << endl;

		// 出队列
		q.pop();
	}
	cout << " size = " << q.size() << endl;
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
