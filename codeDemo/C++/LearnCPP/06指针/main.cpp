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

	cout << *p << endl; //* ������
	cout << sizeof(p) << endl;
	cout << sizeof(char *) << endl;
	cout << sizeof(float *) << endl;
	cout << sizeof(double *) << endl;

	// ��ָ��   ע��: ����ֱ�ӷ��ʿ�ָ��
	int *p0 = 0;
	int *p1 = NULL;
	int *p2 = nullptr;		// �Ƽ�ʹ�����ֿ�ָ��

	// Ұָ��	һ��Ҫ��������Ұָ��
	int *p5 = (int *)0x11110000;
	//*p5 = 10000;		// ����д��

	// ָ�������
	func();
	// ʹ��ָ�뽻��ֵ
	int m = 100, n = 200;
	cout << endl << "m = " << m << endl << "n = " << n << endl;
	swap01(&m,&n);
	cout << endl << "m = " << m << endl << "n = " << n << endl;
	return 0;
}

// ָ�������
void func() {
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	cout << "ͨ�������±���з���: " << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
		cout << arr[i] << " ";
	}

	cout << endl << "ͨ��ָ����н��з���: " << endl;
	int *p = arr;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
		cout << *p << " ";
		++p;				// ָ������ƶ�
	}
}

// ʹ��ָ����н���
void swap01(int *p1, int *p2) {
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}