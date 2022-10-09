/*
* 返回bool类型的仿函数称为**谓词**
* 如果operator()接受一个参数，那么叫做一元谓词
* 如果operator()接受两个参数，那么叫做二元谓词
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 一元谓词
class GreaterFive {
public:
	bool operator()(int &val) {
		return val > 5;
	}
};

// 二元谓词
class MyCompare {
public:
	bool operator()(int &v1, int &v2) {
		return v1 > v2;
	}
};

// 遍历vector
void printVector(const vector<int> &vtr) {
	for (vector<int>::const_iterator it = vtr.cbegin(); it != vtr.cend(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	vector<int> vtr;
	
	for (int i = 0; i < 10; i++)
	{
		vtr.push_back(i);
	}

	printVector(vtr);
	// 使用自定义的一元谓词范围查找
	vector<int>::iterator pos = find_if(vtr.begin(),vtr.end(),GreaterFive());	
	if (pos != vtr.end()) {
		cout << "找到了: " << *pos << endl;
	}
	else {
		cout << "未找到" << endl;
	}
}

void test02() {
	vector<int> vtr;
	vtr.push_back(50);
	vtr.push_back(100);
	vtr.push_back(60);
	vtr.push_back(70);
	vtr.push_back(10);

	cout << "===================================" << endl;
	printVector(vtr);

	sort(vtr.begin(), vtr.end());
	printVector(vtr);

	sort(vtr.begin(),vtr.end(),MyCompare());		// 使用自定义的二元谓词排序
	printVector(vtr);
}

int main()
{
	test01();
	test02();
    std::cout << "Hello World!\n";
}

