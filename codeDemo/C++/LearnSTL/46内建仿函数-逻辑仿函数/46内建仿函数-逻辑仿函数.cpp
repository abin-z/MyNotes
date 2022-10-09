#include <iostream>
#include <functional>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

/*
* `template<class T> bool logical_and<T>`              //逻辑与
* `template<class T> bool logical_or<T>`                //逻辑或
* `template<class T> bool logical_not<T>`              //逻辑非
*/

// 打印vector
void printVector(vector<bool> v) {
	for (vector<bool>::const_iterator cit = v.cbegin(); cit != v.cend(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
}

void test() {
	vector<bool> v;
	
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	v.push_back(false);

	printVector(v);
	vector<bool> v2;
	// 一定要重新resize一下,否则运行会出错
	v2.resize(v.size());

	// 逻辑非 
	// 将v容器的元素搬运至v2中
	transform(v.begin(), v.end() ,v2.begin(),logical_not<bool>());

	printVector(v2);
}

int main()
{
	// 随机数种子
	srand((unsigned int)time(nullptr));
	test();
    std::cout << "Hello World!\n";
}
