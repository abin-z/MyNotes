#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;

/*
`set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);  `

// ���������ϵĲ���

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
	vTarget.resize(v1.size() + v2.size());
	// �󲢼�,���ص��ǵ�����
	vector<int>::iterator pos = set_union(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), vTarget.begin());

	for_each(vTarget.begin(), pos, MyPrint());
}

/*
- �󲢼����������ϱ������������
- Ŀ���������ٿռ���Ҫ**�����������**
- set_union����ֵ���ǲ��������һ��Ԫ�ص�λ��
*/

int main()
{
	test();
	std::cout << "Hello World!\n";
}
