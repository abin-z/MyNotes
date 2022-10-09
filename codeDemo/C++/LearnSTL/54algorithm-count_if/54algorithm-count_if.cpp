#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Greater4 {
public:
	bool operator()(int val) {
		return val > 4;
	}
};

/*
`count_if(iterator beg, iterator end, _Pred);  `
// ������ͳ��Ԫ�س��ִ���
// beg ��ʼ������
// end ����������
// _Pred ν��
*/

//������������
void test01()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(4);
	v.push_back(4);

	int num = count_if(v.begin(), v.end(), Greater4()); // ������ͳ��(�º���)

	cout << "����4�ĸ���Ϊ�� " << num << endl;
}

//�Զ�����������
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

struct AgeLess35
{
	bool operator()(const Person &p) {
		return p.m_Age < 35;
	}
};

void test02()
{
	vector<Person> v;

	Person p1("����", 35);
	Person p2("����", 35);
	Person p3("�ŷ�", 35);
	Person p4("����", 30);
	Person p5("�ܲ�", 25);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	int num = count_if(v.begin(), v.end(), AgeLess35());  // ������ͳ��(�º���)
	cout << "С��35��ĸ�����" << num << endl;
}


int main()
{
	test01();
	test02();
	std::cout << "Hello World!\n";
}