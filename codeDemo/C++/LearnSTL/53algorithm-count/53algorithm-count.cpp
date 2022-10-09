#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
`count_if(iterator beg, iterator end, _Pred);  `
// ������ͳ��Ԫ�س��ִ���
// beg ��ʼ������
// end ����������
// _Pred ν��
*/

// ͳ��������������
void test01() {
	vector<int> vtr;
	vtr.push_back(0);
	vtr.push_back(20);
	vtr.push_back(20);
	vtr.push_back(30);
	vtr.push_back(15);
	vtr.push_back(20);
	vtr.push_back(23);

	int num = count(vtr.cbegin(), vtr.cend(), 20);
	cout << "Ϊ20������" << num << "��" << endl;
}

class Person {
public:
	Person(string name, int age) :
		m_name(name),
		m_age(age)
	{}

	bool operator==(const Person &p)
	{
		if (this == &p) {
			return true;
		}
		// ������������ж�
		if (this->m_age == p.m_age) {
			return true;
		}
		return false;
	}

private:
	string m_name;
	int m_age;
};

// ͳ���Զ�����������
void test02() {
	vector<Person> vtr;
	vtr.push_back(Person("�ŷ�", 50));
	vtr.push_back(Person("����", 25));
	vtr.push_back(Person("����", 26));
	vtr.push_back(Person("���߹�", 90));
	vtr.push_back(Person("�ֱ���", 25));

	Person p("�����", 25);

	int num = count(vtr.begin(), vtr.end(), p);
	cout << "�������һ��25�����: " << num << "��" << endl;
}


int main()
{
	test01();
	test02();
	std::cout << "Hello World!\n";
}