#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

/*
`bool binary_search(iterator beg, iterator end, value);  `
// ����ָ����Ԫ�أ��鵽 ����true  ����false
// ע��: ��**���������в�����**
// beg ��ʼ������
// end ����������
// value ���ҵ�Ԫ��
*/

void test() {
	vector<int> vtr;

	for (int i = 0; i < 10; ++i) {
		vtr.push_back(i);
	}
	vtr.push_back(2);
	
	//sort(vtr.begin(), vtr.end(), greater<int>());// ����Ϊ��������
	sort(vtr.begin(), vtr.end());

	// ���ֲ���һ��Ҫ����������(ֻ������������)������������ȷ
	// ������ʹ��binary_search֮ǰҪ��������sort
	bool res = binary_search(vtr.begin(), vtr.end(), 9);
	if (res) {
		cout << "�ҵ���" << endl;
	}
	else {
		cout << "δ�ҵ�" << endl;
	}

}

int main()
{
	test();
	std::cout << "Hello World!\n";
}