#include <iostream>
using namespace std;

int* func()
{
	int* a = new int(10);	// 在堆去开辟int类型得内存空间
	return a;				// 返回指针	
}

int main()
{
	int* p_int = nullptr;
	p_int = func();
	cout << *p_int << endl;
	cout << *p_int << endl;
	cout << *p_int << endl;

	// 一定要记得释放堆区的内存空间， 否则会出现内存泄露
	delete p_int;		// 释放内存空间
	cout << "=======================" << endl;

	int* arr = new int[10];		// 返回该类型数组的首地址的一个指针

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	//释放数组 delete 后加 []
	delete[] arr;

	system("pause");
	return 0;
}
