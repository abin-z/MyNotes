#include <iostream>
using namespace std;

void func();
void swap01(int *, int *);

int main() {
	cout << "hello\n";
	int a = 100;
	int *p;
	p = &a;
	cout << "p = " << p << endl;
	cout << "(int)p = " << (int)p << endl;
	cout << "*p = " << *p << endl;
	*p = 500;
	cout << "a = " << a << endl;
	cout << "*p = " << *p << endl;

	cout << *p << endl; //* 解引用
	cout << sizeof(p) << endl;
	cout << sizeof(char *) << endl;
	cout << sizeof(float *) << endl;
	cout << sizeof(double *) << endl;

	// 空指针   注意: 不能直接访问空指针
	int *p0 = 0;
	int *p1 = NULL;
	int *p2 = nullptr;		// 推荐使用这种空指针

	// 野指针	一定要避免这种野指针
	int *p5 = (int *)0x11110000;
	//*p5 = 10000;		// 错误写法

	// 指针和数组
	func();
	// 使用指针交换值
	int m = 100, n = 200;
	cout << endl << "m = " << m << endl << "n = " << n << endl;
	swap01(&m,&n);
	cout << endl << "m = " << m << endl << "n = " << n << endl;
	return 0;
}

// 指针和数组
void func() {
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	cout << "通过数组下标进行访问: " << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
		cout << arr[i] << " ";
	}

	cout << endl << "通过指针进行进行访问: " << endl;
	int *p = arr;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
		cout << *p << " ";
		++p;				// 指针向后移动
	}
}

// 使用指针进行交换
void swap01(int *p1, int *p2) {
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}