#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

/*
`swap(container c1, container c2);  `
// 互换两个容器的元素
// c1容器1
// c2容器2
*/

class myPrint
{
public:
	void operator()(string val)
	{
		cout << val << " ";
	}
};

void test() {
	deque<string> d1;
	d1.push_back("123456789");
	d1.push_back("xiaoming");
	d1.push_back("baidu");

	deque<string> d2;
	d2.push_back("898989");
	d2.push_back("asdfjakl");
	d2.push_back("mmmmasdfa");

	cout << "交换前： " << endl;
	for_each(d1.begin(), d1.end(), myPrint());
	cout << endl;
	for_each(d2.begin(), d2.end(), myPrint());
	cout << endl;

	swap(d1,d2);

	cout << "交换后： " << endl;
	for_each(d1.begin(), d1.end(), myPrint());
	cout << endl;
	for_each(d2.begin(), d2.end(), myPrint());
	cout << endl;
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}