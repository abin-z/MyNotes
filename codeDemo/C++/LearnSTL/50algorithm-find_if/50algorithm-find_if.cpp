#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

/*
- `find_if(iterator beg, iterator end, _Pred);  `
  // ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��
  // beg ��ʼ������
  // end ����������
  // _Pred ��������ν�ʣ�����bool���͵ķº�����
*/

// ǰ������
class Person;

class GreaterFive {
public:
	bool operator()(const Person &p);   //���ﲻ��ֱ��дʵ��
};

class Person {
	// ��Ԫ����
	friend ostream& operator<<(ostream &out, const Person &p);
	friend bool GreaterFive::operator()(const Person &p);
public:
	Person(string name, int age) :
		m_name(name),
		m_age(age)
	{	}

private:
	string m_name;
	int m_age;
};

// ��Ա��������ʵ��
bool GreaterFive::operator()(const Person &p) {
	return p.m_age > 5;
}

// ȫ�ֺ��� << ���������
ostream& operator<<(ostream &out, const Person &p) {
	out << "{" << p.m_name << "," << p.m_age << "}";
	return out;
}

// ȫ�ֺ���
void showPerson(const Person &p) {
	cout << p << endl;
}

void test() {
	vector<Person> vtr;
	vtr.push_back(Person("AAA", 1));
	vtr.push_back(Person("BBB", 3));
	vtr.push_back(Person("CCC", 5));
	vtr.push_back(Person("DDD", 8));

	for_each(vtr.cbegin(), vtr.cend(), showPerson);
	vector<Person>::const_iterator pos =
		find_if(vtr.cbegin(), vtr.cend(), GreaterFive());
	if (pos == vtr.cend())
	{
		cout << "δ�ҵ�!" << endl;
	}
	else
	{
		cout << "�ҵ���: " << *pos << endl;
	}
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}