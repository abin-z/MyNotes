#include <iostream>
using namespace std;

//ȫ�ֱ���
int g_a = 10;
int g_b = 10;

//ȫ�ֳ���
const int c_g_a = 10;
const int c_g_b = 10;

void main() {
	//�ֲ�����
	int a = 10;
	int b = 10;

	//��ӡ��ַ
	cout << "�ֲ�����a��ַΪ�� " << (int)&a << endl;
	cout << "�ֲ�����b��ַΪ�� " << (int)&b << endl;

	cout << "ȫ�ֱ���g_a��ַΪ�� " << (int)&g_a << endl;
	cout << "ȫ�ֱ���g_b��ַΪ�� " << (int)&g_b << endl;

	//��̬����
	static int s_a = 10;
	static int s_b = 10;

	cout << "��̬����s_a��ַΪ�� " << (int)&s_a << endl;
	cout << "��̬����s_b��ַΪ�� " << (int)&s_b << endl;

	cout << "�ַ���������ַΪ�� " << (int)&"hello world" << endl;
	cout << "�ַ���������ַΪ�� " << (int)&"hello world1" << endl;

	cout << "ȫ�ֳ���c_g_a��ַΪ�� " << (int)&c_g_a << endl;
	cout << "ȫ�ֳ���c_g_b��ַΪ�� " << (int)&c_g_b << endl;

	const int c_l_a = 10;
	const int c_l_b = 10;
	cout << "�ֲ�����c_l_a��ַΪ�� " << (int)&c_l_a << endl;
	cout << "�ֲ�����c_l_b��ַΪ�� " << (int)&c_l_b << endl;

	system("pause");
	return;
}