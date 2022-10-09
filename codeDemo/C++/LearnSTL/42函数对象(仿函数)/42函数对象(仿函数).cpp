#include <string>
#include <iostream>
using namespace std;

/*
* 函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
* 函数对象超出普通函数的概念，函数对象可以有自己的状态
* 函数对象可以作为参数传递
*/

// 1.函数对象在使用时，可以像普通函数那样调用, 可以有参数，可以有返回值
class MyAdd {
public:
	int operator()(const int &v1, const int &v2) {	// 重写()运算符
		return v1 + v2;
	}
};


// 2.函数对象超出普通函数的概念，函数对象可以有自己的状态
class MyPrint {
public:
	MyPrint() :count(0) {}
	void operator()(const string &str) {
		cout << str << endl;
		count++;
	}
	int getCount() { return count; }
private:
	int count;	// 可以有自己的属性
};

// 3.函数对象可以作为参数传递
class MySmile {
public:
	void operator()(string &str) const {
		str += " 哈哈哈!";
		cout << str << endl;
	}
};

void doSomething(const string &str, const MySmile &simle) {
	string& s = const_cast<string&>(str);	// 将const的转为非const, 能不用尽量不用
	simle(s);		// 函数对象, 仿函数
}

void test() {
	MyAdd add;
	cout << add(10,20) << endl;

	MyPrint myPrint;
	myPrint("你好,世界!");
	myPrint("你好,世界!");
	myPrint("你好,世界!");
	myPrint("你好,世界!");
	cout << myPrint.getCount() << endl;

	string st = "今晚加班";
	doSomething(st, MySmile());
	cout << st << endl;
}


int main()
{
	test();
    std::cout << "Hello World!\n";
}