#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
* `vector<T> v; `               			//采用模板实现类实现，默认构造函数
* `vector(v.begin(), v.end());   `			//将v[begin(), end())区间中的元素拷贝给本身。
* `vector(n, elem);`                        //构造函数将n个elem拷贝给本身。
* `vector(const vector &vec);`				//拷贝构造函数。
*/

void printVector(vector<int> v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void printVector(vector<double> v) {
	for (vector<double>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test() {
	vector<int> v1;	// 无参构造
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}
	printVector(v1);

	vector<int> v2(v1.begin(), v1.end());	// 将v[begin(), end())区间中的元素拷贝给本身。
	printVector(v2);

	vector<double> v3(10, 99.99);			// 构造函数将n个elem拷贝给本身。
	printVector(v3);

	vector<double> v4(v3);					// 拷贝构造函数。
	printVector(v4);
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}
