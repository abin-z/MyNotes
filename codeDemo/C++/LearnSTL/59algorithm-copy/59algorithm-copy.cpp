#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
`copy(iterator beg, iterator end, iterator dest);  `

// ��ֵ����Ԫ�أ��ҵ�����ָ��λ�õ��������Ҳ������ؽ���������λ��

// beg  ��ʼ������

// end  ����������

// dest Ŀ����ʼ������
*/

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

void test() {
	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i + 1);
	}

	vector<int> v2;
	v2.resize(v.size());		// ����Ҫ��ǰ���ٿռ�
	copy(v.cbegin(),v.cend(),v2.begin());
	for_each(v2.begin(), v2.end(), myPrint());
	cout << endl;
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}

