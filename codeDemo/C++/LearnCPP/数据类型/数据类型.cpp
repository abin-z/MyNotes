#include <iostream>
#include <string>
#define EXIT_SUCCESS 1
using namespace std;

int main() {
	cout << "Hello World!" << endl;
	// ����
	short ss = 10;
	cout << "short ռ�ÿռ�Ϊ: " << sizeof(ss) << "���ֽ�." << endl;
	int ii = 10;
	cout << "int ռ�ÿռ�Ϊ: " << sizeof(int) << "���ֽ�." << endl;
	long ll = 10L;				// long ���ͺ�����Ҫ��� L
	cout << "long ռ�ÿռ�Ϊ: " << sizeof(long) << "���ֽ�." << endl;
	long long llll = 10;
	cout << "long long ռ�ÿռ�Ϊ: " << sizeof(llll) << "���ֽ�." << endl;
	// ������
	float ff = 3.14F;			// float���͵����ݺ�����Ҫ��� f����F;
	cout << "float ռ�ÿռ�Ϊ: " << sizeof(ff) << "���ֽ�." << endl;
	double dd = 3.1415926;
	cout << "doubleռ�ÿռ�Ϊ: " << sizeof(dd) << "���ֽ�." << endl;

	// ��ѧ������
	float f2 = 2e5f;			// 2e5f = 2 * 10 ^ 5 = 200000
	cout << "��ѧ������: f2 = " << f2 << endl;

	float f3 = 2e-3f;			// 2e3f = 2 * 0.1 ^ 3 = 0.002
	cout << "��ѧ������: f3 = " << f3 << endl;
	// �ַ�����
	char cc = '\0';				// ֻ��ʹ�õ����� ת���ַ� \0 
	cout << "char ռ�ÿռ�Ϊ: " << sizeof(char) << "���ֽ�." << endl;
	cout << "char ����ת��Ϊint���͵�����: " << (int)cc << endl;		// 0
	cout << "char ����ת��Ϊint���͵�����: " << (int)'A' << endl;		// 65
	cout << "char ����ת��Ϊint���͵�����: " << (int)'a' << endl;		// 97
	cout << "char ����ת��Ϊint���͵�����: " << (int)'\n' << endl;		// 97

	// �ַ���
	char str1[] = "���, ����!";			// C�����ַ���, �ַ�����[]
	cout << str1 << endl;
	string str2 = "���, ����!";			// C++ �����ַ���
	cout << str2 << endl;				// ��Ҫ��� #include <string> ��ͷ�ļ�

	// ��������
	// true  -- - �棨������1�� ��0���ֶ�����true
	// false -- - �٣�������0��
	bool flag = true;
	cout << "true = " << flag << endl; // 1
	flag = false;
	cout << "false = " << flag << endl; // 0
	cout << "size of bool = " << sizeof(bool) << endl; //1

	// ��������
	string s1, s2;
	cout << "�������ַ���: " << endl;
	cin >> s1 >> s2;
	cout << s1 + s2 << endl;

	//�ַ�������
	char ch = 0;
	cout << "�������ַ��ͱ�����" << endl;
	cin >> ch;
	cout << ch << endl;

	//������������
	bool flag1;
	cout << "�����벼���ͱ�����" << endl;
	// ֻҪ�Ƿ�0���������ֶ�Ϊ��; ������(-1, 1)Ϊfalse 0, ���඼Ϊ1; ����Ϊ������Ϊfalse 0;
	cin >> flag1;						
	cout << flag1 << endl;

	system("pause");
	return EXIT_SUCCESS;
}