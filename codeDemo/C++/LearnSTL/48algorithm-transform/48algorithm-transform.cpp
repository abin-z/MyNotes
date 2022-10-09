#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void showInt(int val) {
	cout << val << " ";
}

int getInt(int a) {
	return a + 100;
}


void test() {
	vector<int> v;

	for (int i = 0; i < 20; ++i) {
		v.push_back(rand()%10);
	}
	for_each(v.cbegin(), v.cend(), showInt);
	
	cout << endl;
	// 使用transform
	vector<int> vTarget;
	vTarget.resize(v.size());		// 注意： 必须要先开辟空间
	// 可以使用仿函数也可以使用函数地址
	transform(v.cbegin(), v.cend(), vTarget.begin(),getInt);	
	for_each(vTarget.cbegin(), vTarget.cend(), showInt);

	cout << endl;
	
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
