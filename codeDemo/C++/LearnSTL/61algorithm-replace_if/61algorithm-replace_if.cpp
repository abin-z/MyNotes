#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
- `replace_if(iterator beg, iterator end, _pred, newvalue);  `

  // �������滻Ԫ�أ������������滻��ָ��Ԫ��

  // beg ��ʼ������

  // end ����������

  // _pred ν��

  // newvalue �滻����Ԫ��
*/

class myPrint
{
public:
	void operator()(int val)
	{
		cout << val << " ";
	}
};

struct Greate20
{
	bool operator()(int val) {
		return val > 20;
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

	replace_if(v.begin(), v.end(), Greate20(), 888);

	cout << "�滻��" << endl;
	for_each(v.begin(), v.end(), myPrint());
	cout << endl;



}

int main()
{
	test01();
	std::cout << "Hello World!\n";
}