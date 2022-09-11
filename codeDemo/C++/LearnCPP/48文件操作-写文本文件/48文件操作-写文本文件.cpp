#include <iostream>
#include <string>
#include <fstream> // 包含头文件
using namespace std;

//写文件步骤如下：
//1. 包含头文件
//\#include <fstream\>
//2. 创建流对象
//ofstream ofs;
//3. 打开文件
//ofs.open("文件路径", 打开方式);
//4. 写数据
//ofs << "写入的数据";
//5. 关闭文件
//ofs.close();

void fileTest() {
	ofstream ofs;	// 创建输出流对象
	ofs.open("file.txt",ios::out);	// 打开文件
	// 写内容
	string str = "hello world\n你好, 世界\n你好, C++";
	ofs << "123456789" << endl;
	ofs << "【计算机科学与技术】" << endl;
	ofs << str << endl;
	// 关闭流
	ofs.close();
}

int main()
{
	fileTest();
    std::cout << "Hello World!\n";
}