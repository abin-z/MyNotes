#include <iostream>
#include <functional>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

/*
* `template<class T> bool equal_to<T>`                    //等于
* `template<class T> bool not_equal_to<T>`            //不等于
* `template<class T> bool greater<T>`                      //大于
* `template<class T> bool greater_equal<T>`          //大于等于
* `template<class T> bool less<T>`                           //小于
* `template<class T> bool less_equal<T>`               //小于等于
*/


// 仿函数也可以使用结构体
struct MyCompare
{
	bool operator()(int v1, int v2) {
		return v1 > v2;
	}
};


 // 打印vector
void printVector(vector<int> v) {
	for (vector<int>::const_iterator cit = v.cbegin(); cit != v.cend(); ++cit){
		cout << *cit << " ";
	}
	cout << endl;
}

void test() {
	vector<int> vtr;
	
	for (int i = 0; i < 20; ++i) {
		vtr.push_back(rand()%1000);
	}
	printVector(vtr);

	// 默认是升序排序
	sort(vtr.begin(),vtr.end());
	printVector(vtr);

	// 使用自定义的仿函数
	//sort(vtr.begin(), vtr.end(), MyCompare());
	//printVector(vtr);

	// 可以使用内建的仿函数
	sort(vtr.begin(), vtr.end(), greater<int>());
	printVector(vtr);
}

int main()
{
	// 随机数种子
	srand((unsigned int)time(nullptr));
	test();
    std::cout << "Hello World!\n";
}