#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*
`replace(iterator beg, iterator end, oldvalue, newvalue);  `

// �������ھ�Ԫ�� �滻�� ��Ԫ��

// beg ��ʼ������

// end ����������

// oldvalue ��Ԫ��

// newvalue ��Ԫ��
*/

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test01()
{
	vector<int> v;
	v.push_back(20);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);
	v.push_back(50);
	v.push_back(10);
	v.push_back(20);

	cout << "�滻ǰ��" << endl;
	for_each(v.begin(), v.end(), myPrint());
	cout << endl;

	replace(v.begin(),v.end(),20,111);
	cout << "�滻��" << endl;
	for_each(v.begin(), v.end(), myPrint());
	cout << endl;
}

int main()
{
	test01();
    std::cout << "Hello World!\n";
}
