#include <iostream>
#include <ctime>
#include <cstdlib>

void func1();
void func2();
void func3();
void func4();

int main()
{
	//func1();
	func2();
	//func3();
	//func4();
	std::cout << "Hello World!\n";

	// system()C 库函数 int system(const char *command) 
	// 把 command 指定的命令名称或程序名称传给要被命令处理器执行的主机环境，并在命令完成后返回。
	system("java -version");				
	return 0;
}

// 乘法表
void func4() {
	for (int i = 1; i < 10; ++i) {
		for (int j = 1; j <= i; ++j) {
			std::cout << j << "*" << i << "=" << i * j << "\t";
		}
		std::cout << std::endl;
	}
}


// 敲桌子==从1开始数到数字100， 如果数字个位含有7，或者数字十位含有7，或者该数字是7的倍数，我们打印敲桌子，其余数字直接打印输出。
void func3() {
	int a = 0;			// 个位
	int b = 0;			// 十位
	for (int i = 1; i <= 100; ++i)
	{
		a = i % 10;
		b = i / 10 % 10;
		if (a == 7 || b == 7 || i % 7 == 0) {
			std::cout << i << " 敲桌子" << std::endl;
		}
		else
		{
			std::cout << i << std::endl;
		}
	}
}

/// 水仙花数
void func2() {
	int num = 100;
	int a = 0;			// 个位
	int b = 0;			// 十位
	int c = 0;			// 百位
	while (num < 1000)
	{
		a = num % 10;		// 取出个位数
		b = num / 10 % 10;	// 取出十位数
		c = num / 100;		// 取出百位数
		if ((a * a*a + b * b*b + c * c*c) == num) {
			//std::cout << num << std::endl;
			printf("%d\n", num);
		}
		num++;
	}
}


/// 猜数字
void func1() {
	// 添加随机数
	srand((unsigned int)time(NULL));  // 产生随机种子  把0换成NULL也行
	int num_target = rand() % 100 + 1;			// 生成一个(0+1) ~ (99+1)的随机数 
	int num_user = -1;
	//std::cout << num_target << std::endl;
	do
	{
		std::cout << "请输入您猜测的数字:" << std::endl;
		std::cin >> num_user;
		if (num_user > num_target)
		{
			std::cout << "猜大了" << std::endl;
		}
		else if (num_user < num_target)
		{
			std::cout << "猜小了" << std::endl;
		}
		else
		{
			std::cout << "恭喜你! 猜对了" << std::endl;
			break;
		}
	} while (true);
	std::cout << num_target << std::endl;

}
