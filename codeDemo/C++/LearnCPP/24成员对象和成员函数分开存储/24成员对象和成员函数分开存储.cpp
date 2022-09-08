#include <iostream>
using namespace std;

class Student {

};

class Data {	// 存在内存对齐的状况
	int m_a;
	char m_c;
};

class Person {
public:
	Person() {
		mA = 0;
	}
	//非静态成员变量占对象空间
	int mA;
	//静态成员变量不占对象空间
	static int mB;
	//函数也不占对象空间，所有函数共享一个函数实例
	void func() {
		cout << "mA:" << this->mA << endl;
	}
	//静态成员函数也不占对象空间
	static void sfunc() {
	}
};

int main() {
	cout << sizeof(Student) << endl;		// 空对象也会占用一个字节
	cout << sizeof(Person) << endl;			// 占用4个字节
	cout << sizeof(Data) << endl;			// 占用8个字节, 存在内存对齐的情况

	system("pause");
	return 0;
}
