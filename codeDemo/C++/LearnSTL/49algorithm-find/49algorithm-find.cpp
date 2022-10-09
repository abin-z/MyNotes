#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

/*
`find(iterator beg, iterator end, value);  `

// ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��

// beg ��ʼ������

// end ����������

// value ���ҵ�Ԫ��
*/

// ����string����Ԫ��, string�Ѿ������� == �����
void test01() {
	vector<string> v;

	string s = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++)
	{
		v.push_back(string("Ա��") += s.at(i));
	}
	string tgt = "Ա��B";
	vector<string>::iterator pos = find(v.begin(), v.end(), tgt);
	if (pos == v.end()) {
		cout << "not find" << endl;
	}
	else {
		cout << "�ҵ���: " << *pos << endl;
	}
}

struct MyStruct
{
	// ��Ԫ����
	friend ostream& operator<<(ostream &out, const MyStruct &s);
	MyStruct() {
		m_name = string();
		m_age = 0;
	}

	MyStruct(string name, int age) {
		m_name = name;
		m_age = age;
	}

	// �Զ���������Ҫ�ṩ == �����������
	bool operator==(const MyStruct &s) {
		// �Լ��Ƚ�
		if (this == &s) {
			return true;
		}
		// �Ƚ�����
		if (this->m_name == s.m_name && this->m_age == this->m_age) {
			return true;
		}
		return  false;
	}

private:
	string m_name;
	int m_age;
};

// ����<<�����
ostream& operator<<(ostream &out, const MyStruct &s)
{
	out << "{" << s.m_name << "," << s.m_age << "}";
	return out;
}


// �����Զ�����������
void test02() {
	vector<MyStruct> vtr;

	MyStruct p1("xiaming", 12);
	MyStruct p2("lihua", 13);
	MyStruct p3("tom", 14);
	MyStruct p4("tony", 15);

	vtr.push_back(p1);
	vtr.push_back(p2);
	vtr.push_back(p3);
	vtr.push_back(p4);

	MyStruct p5("tony", 15);
	// �����Զ�����������ʱ����Ҫ����==�����
	vector<MyStruct>::iterator pos = find(vtr.begin(), vtr.end(), p5);
	if (pos == vtr.end()) {
		cout << "not find" << endl;
	}
	else {
		cout << "�ҵ���: " << *pos << endl;
	}
}

int main()
{
	test01();
	test02();
	std::cout << "Hello World!\n";
}