#include <iostream>
using namespace std;

void fun();			// 一维数组
void fun2();		// 数组名用途
void fun3();		// 找最大值
void fun4();		// 数组元素逆置		
void bubbleSort();	// 冒泡排序	
void fun5();		// 二维数组
void fun6();		// 二维数组数组名

int main()
{
	//fun();
	//fun2();
	//fun3();
	//fun4();
	//bubbleSort();
	//fun5();
	fun6();
	std::cout << "\nHello World!\n";
	system("pause");
	return EXIT_SUCCESS;
}

// 冒泡排序
void bubbleSort() {
	int array[] = { 4,2,8,0,5,7,1,3,9 };
	int array_size = sizeof(array) / sizeof(array[0]);
	cout << "原始数组如下:" << endl;
	for (int i = 0; i < array_size; ++i) {
		cout << array[i] << " ";
	}

	// 开始排序
	for (int m = 0; m < array_size - 1; ++m) {					// 外层循环表示第m轮排序:	m = array_size - 1
		for (int n = 0; n < array_size - 1 - m; ++n) {			// 内层循环表示排序n次		n = array_size - 1 - m;
			if (array[n] > array[n + 1]) {						// 如果前一个数字大于后一个数字则交换
				int temp = array[n];
				array[n] = array[n + 1];
				array[n + 1] = temp;
			}
		}
	}

	cout << "冒泡排序后结果如下:" << endl;
	for (int i = 0; i < array_size; ++i) {
		cout << array[i] << " ";
	}
}

// 二维数组
void fun5()
{	
	//方式1  
	//数组类型 数组名 [行数][列数]
	int arr[2][3];
	arr[0][0] = 1;
	arr[0][1] = 2;
	arr[0][2] = 3;
	arr[1][0] = 4;
	arr[1][1] = 5;
	arr[1][2] = 6;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	//方式2  推荐使用
	//数据类型 数组名[行数][列数] = { {数据1，数据2 } ，{数据3，数据4 } };
	int arr2[2][3] =
	{
		{1,2,3},
		{4,5,6}
	};

	//方式3
	//数据类型 数组名[行数][列数] = { 数据1，数据2 ,数据3，数据4  };
	int arr3[2][3] = { 1,2,3,4,5,6 };

	//方式4 
	//数据类型 数组名[][列数] = { 数据1，数据2 ,数据3，数据4  };
	int arr4[][3] = { 1,2,3,4,5,6 };
}

// 二维数组的数组名
void fun6() {
	//数据类型 数组名[行数][列数] = { {数据1，数据2 } ，{数据3，数据4 } };
	int arr[3][4] =
	{
		{1,2,3,10},
		{4,5,6,20},
		{7,8,}
	};

	cout << "二维数组大小： " << sizeof(arr) << endl;
	cout << "二维数组一行大小： " << sizeof(arr[0]) << endl;
	cout << "二维数组元素大小： " << sizeof(arr[0][0]) << endl;

	cout << "二维数组行数： " << sizeof(arr) / sizeof(arr[0]) << endl;
	cout << "二维数组列数： " << sizeof(arr[0]) / sizeof(arr[0][0]) << endl;

	int arr_size = sizeof(arr);					// 二维数组总共的占用的内存空间
	int arr_line_size = sizeof(arr[0]);			// 二维数组每一行的占用的内存空间
	int arr_item_size = sizeof(arr[0][0]);		// 二维数组每个元素的占用的内存空间
	cout << endl;
	for (int i = 0; i < arr_size / arr_line_size; ++i) {			// 二维数组行数
		for (int j = 0; j < arr_line_size / arr_item_size; ++j) {	// 二维数组列数
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << "二维数组的地址:" << endl;							// 二维数组名就是这个数组的首地址
	cout << "二维数组首地址：" << (int)arr << endl;					// 可以不用加 & 取地址符
	cout << "二维数组首地址：" << (int)&arr << endl;					// 也可以加上 & 取地址符
	cout << "二维数组第一行地址：" << (int)arr[0] << endl;
	cout << "二维数组第一行地址：" << (int)&arr[0] << endl;
	cout << "二维数组第二行地址：" << (int)arr[1] << endl;
	cout << "二维数组第二行地址：" << (int)&arr[1] << endl;

	cout << "二维数组第一个元素地址：" << (int)&arr[0][0] << endl;		// 二维数组取元素地址必须加上 & 取地址符
	cout << "二维数组第二个元素地址：" << (int)&arr[0][1] << endl;

}



// 数组元素逆置
void fun4() {
	int array[5] = { 1, 3, 2, 5, 4 };
	int arr_size = sizeof(array) / sizeof(array[0]);			// 数组大小
	cout << "原始数组: ";
	for (int i = 0; i < arr_size; ++i) {
		cout << array[i] << " ";
	}

	int temp = 0;
	// 方法1
	for (int i = 0; i < arr_size / 2; ++i) {
		temp = array[i];
		array[i] = array[arr_size - 1 - i];
		array[arr_size - 1 - i] = temp;
	}
	// 方法2
	for (int left = 0, right = arr_size - 1; left < right; ++left, --right) {
		temp = array[left];
		array[left] = array[right];
		array[right] = temp;
	}

	cout << endl << "交换后数组: ";
	for (int i = 0; i < arr_size; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
}

// 找最大值
void fun3() {
	int array[5] = { 300, 350, 200, 400, 250 };
	int max = array[0];
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i) {
		if (array[i] > max) {
			max = array[i];
		}
	}
	cout << "最大值为: " << max << endl;
}



void fun2() {
	//数组名用途
		//1、可以获取整个数组占用内存空间大小
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "整个数组所占内存空间为： " << sizeof(arr) << endl;
	cout << "每个元素所占内存空间为： " << sizeof(arr[0]) << endl;
	cout << "数组的元素个数为： " << sizeof(arr) / sizeof(arr[0]) << endl;

	//2、可以通过数组名获取到数组首地址
	cout << "数组首地址为： " << (int)arr << endl;
	cout << "数组中第一个元素地址为： " << (int)&arr[0] << endl;
	cout << "数组中第二个元素地址为： " << (int)&arr[1] << endl;

	//arr = 100; 错误，数组名是常量，因此不可以赋值
}

void fun() {
	//定义方式1
	//数据类型 数组名[元素个数];
	int score[10];

	//利用下标赋值
	score[0] = 100;
	score[1] = 99;
	score[2] = 85;

	//利用下标输出
	cout << score[0] << endl;
	cout << score[1] << endl;
	cout << score[2] << endl;


	//第二种定义方式
	//数据类型 数组名[元素个数] =  {值1，值2 ，值3 ...};
	//如果{}内不足10个数据，剩余数据用0补全
	int score2[10] = { 100, 90,80,70,60,50,40,30,20,10 };

	//逐个输出
	//cout << score2[0] << endl;
	//cout << score2[1] << endl;

	//一个一个输出太麻烦，因此可以利用循环进行输出
	for (int i = 0; i < 10; i++)
	{
		cout << score2[i] << endl;
	}

	//定义方式3
	//数据类型 数组名[] =  {值1，值2 ，值3 ...};
	int score3[] = { 100,90,80,70,60,50,40,30,20,10 };

	for (int i = 0; i < 10; i++)
	{
		cout << score3[i] << endl;
	}
}

