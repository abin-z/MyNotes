// 49文件操作-读文本文件.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void writeFile() {
	ofstream ofs;
	ofs.open("file.txt", ios::out);
	string data = "123456789\n你好,世界!";
	ofs << data << endl << "[计算机科学与技术]" << endl;
	ofs.close();
}

void fileTest() {
	ifstream ifs;	// 创建输入流对象

	ifs.open("file.txt", ios::in);	// 读的方式打开文件

	// 判断是否打开成功
	if (!ifs.is_open()) {
		cout << "文件打开失败!!!" << endl;
		return;
	}

	// 读取数据
	// 读取方式1
	//char buff[1024] = { 0 };
	//while (ifs >> buff)
	//{
	//	cout << buff << endl;
	//}

	// 读取方式2
	//char buff2[1024] = { 0 };
	//while (ifs.getline(buff2, sizeof(buff2)))
	//{
	//	cout << buff2 << endl;
	//}

	// 读取方式3
	//string buff3;
	//while (getline(ifs, buff3))	// 此时的getline是全局函数
	//{
	//	cout << buff3 << endl;
	//}

	// 读取方式4: 一个字符一个字符的读
	char c;
	while ((c = ifs.get()) != EOF)	// EOF : end of file 文件结尾
	{
		cout << c;
	}

	ifs.close();
}

int main()
{
	//writeFile();
	fileTest();
}
