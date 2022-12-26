#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/*
`set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  `

// ���������ϵĽ���

// **ע��:�������ϱ�������������**

// beg1 ����1��ʼ������
// end1 ����1����������
// beg2 ����2��ʼ������
// end2 ����2����������
// dest Ŀ��������ʼ������
*/

class MyPrint {
public:
	void operator()(int val) {
		cout << val << "  ";
	}
};


void test() {
	vector<int> v1;
	vector<int> v2;

	// �󽻼��ļ��ϱ����������
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 5);
	}

	vector<int> vTarget;
	// ���뿪���㹻�Ŀռ�
	vTarget.resize(min(v1.size(), v2.size()));

	// �󽻼�,���ص��ǽ������һ��Ԫ�صĵ�����
	vector<int>::iterator pos = set_intersection(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), vTarget.begin());
	
	for_each(vTarget.cbegin(), vTarget.cend(), MyPrint());
	cout << endl;
	// Ӧ��ʹ�÷��ػ����ĵ���������
	for_each(vTarget.begin(), pos, MyPrint());
}

/*
* �󽻼����������ϱ������������
* Ŀ���������ٿռ���Ҫ��**����������ȡСֵ**
* set_intersection����ֵ���ǽ��������һ��Ԫ�ص�λ��
*/

int main()
{
	test();
	std::cout << "Hello World!\n";
}