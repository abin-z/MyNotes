#include <iostream>
#include <string>
#define EXIT_SUCCESS 1
using namespace std;

int main() {
	cout << "Hello World!" << endl;
	// 整型
	short ss = 10;
	cout << "short 占用空间为: " << sizeof(ss) << "个字节." << endl;
	int ii = 10;
	cout << "int 占用空间为: " << sizeof(int) << "个字节." << endl;
	long ll = 10L;				// long 类型后面需要添加 L
	cout << "long 占用空间为: " << sizeof(long) << "个字节." << endl;
	long long llll = 10;
	cout << "long long 占用空间为: " << sizeof(llll) << "个字节." << endl;
	// 浮点型
	float ff = 3.14F;			// float类型的数据后面需要添加 f或者F;
	cout << "float 占用空间为: " << sizeof(ff) << "个字节." << endl;
	double dd = 3.1415926;
	cout << "double占用空间为: " << sizeof(dd) << "个字节." << endl;

	// 科学计数法
	float f2 = 2e5f;			// 2e5f = 2 * 10 ^ 5 = 200000
	cout << "科学计数法: f2 = " << f2 << endl;

	float f3 = 2e-3f;			// 2e3f = 2 * 0.1 ^ 3 = 0.002
	cout << "科学计数法: f3 = " << f3 << endl;
	// 字符类型
	char cc = '\0';				// 只能使用单引号 转移字符 \0 
	cout << "char 占用空间为: " << sizeof(char) << "个字节." << endl;
	cout << "char 可以转换为int类型的数字: " << (int)cc << endl;		// 0
	cout << "char 可以转换为int类型的数字: " << (int)'A' << endl;		// 65
	cout << "char 可以转换为int类型的数字: " << (int)'a' << endl;		// 97
	cout << "char 可以转换为int类型的数字: " << (int)'\n' << endl;		// 97

	// 字符串
	char str1[] = "你好, 世界!";			// C风格的字符串, 字符数组[]
	cout << str1 << endl;
	string str2 = "你好, 世界!";			// C++ 风格的字符串
	cout << str2 << endl;				// 需要添加 #include <string> 的头文件

	// 布尔类型
	// true  -- - 真（本质是1） 非0数字都代表true
	// false -- - 假（本质是0）
	bool flag = true;
	cout << "true = " << flag << endl; // 1
	flag = false;
	cout << "false = " << flag << endl; // 0
	cout << "size of bool = " << sizeof(bool) << endl; //1

	// 数据输入
	string s1, s2;
	cout << "请输入字符串: " << endl;
	cin >> s1 >> s2;
	cout << s1 + s2 << endl;

	//字符型输入
	char ch = 0;
	cout << "请输入字符型变量：" << endl;
	cin >> ch;
	cout << ch << endl;

	//布尔类型输入
	bool flag1;
	cout << "请输入布尔型变量：" << endl;
	// 只要是非0的整型数字都为真; 浮点数(-1, 1)为false 0, 其余都为1; 若不为数字则都为false 0;
	cin >> flag1;						
	cout << flag1 << endl;

	system("pause");
	return EXIT_SUCCESS;
}