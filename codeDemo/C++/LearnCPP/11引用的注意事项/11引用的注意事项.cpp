#include <iostream>
using namespace std;

// 不要返回局部变量的引用，因为局部变量在函数运行结束后会被释放
// 引用可以作为左值

void func();
void showValue(const int &value);
void showValue2(int &value);


int& test01() {
	int a = 10;
	return a;		// 错误： 返回局部变量的引用
}

int& test02() {
	static int a = 100;
	return a;		// 正确： 可以返回静态变量的引用，变量存放在全局区中
}

int main()
{
	int& ref = test01();				// 错误使用引用
	cout << "ref = " << ref << endl;	// 错误使用引用，访问会出现问题
	cout << "ref = " << ref << endl;	// 错误使用引用，访问会出现问题
	cout << "ref = " << ref << endl;	// 错误使用引用，访问会出现问题


	int& ref2 = test02();
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;
	test02() = 500;						// 引用可以作为左值, 修改的都是全局唯一的静态变量
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	cout << "===================" << endl;
	func();
	return 0;
}

void func() {
	//int& ref = 10;  错误,引用本身需要一个合法的内存空间，因此这行错误
	//加入const就可以了，编译器优化代码，int temp = 10; const int& ref = temp;
	const int& ref = 10;		// 编译器优化代码，int temp = 10; const int& ref = temp;
	const int aa = 10;

	//ref = 100;  //加入const后不可以修改变量
	cout << ref << endl;

	//函数中利用常量引用防止误操作修改实参
	int a = 30;
	showValue(a);
	showValue2(a);			// 使用可以修改的a变量没有问题
	//showValue2(aa);			// 参数类型不对应,参数是否有const
	//showValue2(ref);		// 参数类型不对应,参数是否有const

}

void  showValue(const int &value) {
	// 函数重载可以根据参数类型是否添加有const区分
	//value = 200;	错误写法,const不可以修改, 当我们不希望修改传入的参数时建议都加上const
	cout << "value = " << value << endl;
}

void  showValue2(int &value) {
	value += 10;
	cout << "value = " << value << endl;
}
