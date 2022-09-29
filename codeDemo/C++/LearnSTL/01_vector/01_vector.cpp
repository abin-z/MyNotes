#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void myPrint(int val) {
	cout << val << endl;
}

void test() {
	// ����vector ����: STL����õ�����ΪVector���������Ϊ����
	vector<int> vtr;
	vtr.push_back(100);
	vtr.push_back(200);
	vtr.push_back(300);
	vtr.push_back(400);
	vtr.push_back(500);

	//ÿһ�����������Լ��ĵ����������������������������е�Ԫ��
	//v.begin()���ص����������������ָ�������е�һ������
	//v.end()���ص����������������ָ������Ԫ�ص����һ��Ԫ�ص���һ��λ��
	//vector<int>::iterator �õ�vector<int>���������ĵ���������

	// ����������Ҫʹ�õ�����, ������ʽ1
	vector<int>::iterator itBegin = vtr.begin();	// v.begin()���ص����������������ָ�������е�һ������
	vector<int>::iterator itEnd = vtr.end();		// v.end()���ص����������������ָ������Ԫ�ص����һ��Ԫ�ص���һ��λ��

	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		++itBegin;		// �ƶ�����һ��λ��
	}

	cout << "=============================" << endl;

	// ������ʽ��
	for (vector<int>::iterator i = vtr.begin(); i < vtr.end(); ++i)
	{
		cout << *i << endl;
	}

	cout << "=============================" << endl;
	vtr.pop_back();
	// ������ʽ�� ʹ��for_each�㷨
	for_each(vtr.begin(), vtr.end(), myPrint);	// myPrintΪ������ַ.
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
