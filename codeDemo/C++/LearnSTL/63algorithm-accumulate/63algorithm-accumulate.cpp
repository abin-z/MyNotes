#include <iostream>
#include <numeric>	// ����ͷ�ļ�
#include <vector>
using namespace std;

/*
`accumulate(iterator beg, iterator end, value);  `
// ��������Ԫ���ۼ��ܺ�
// beg ��ʼ������
// end ����������
// value ��ʼֵ
*/

void test() {
	vector<int> v;
	for (int i = 1; i <= 100; i++)
	{
		v.push_back(i);
	}

	int sum = accumulate(v.begin(), v.end(), 0);

	cout << "sum = " << sum << endl;

}

int main()
{
	test();
    std::cout << "Hello World!\n";
}