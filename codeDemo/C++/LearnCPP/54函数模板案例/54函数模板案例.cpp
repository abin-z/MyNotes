#include <iostream>
#include <string>
using namespace std;
//
//案例描述：
//
//* 利用函数模板封装一个排序的函数，可以对**不同数据类型数组**进行排序
//* 排序规则从大到小，排序算法为**选择排序**
//* 分别利用**char数组**和**int数组**进行测试

// 交换模板
template<typename T>
void mySwap(T &n, T &m) {
	T temp = n;
	n = m;
	m = temp;
}

// 排序模板
template<typename T>
void sort(T * arr, int len) {
	// 选择排序
	for (int i = 0; i < len; i++)
	{
		int minIndex = i;	// 最小数字下标
		for (int j = i + 1; j < len; j++) // 找最小下标
		{
			if (arr[minIndex] > arr[j]) {
				minIndex = j;
			}
		}
		if (minIndex != i) {	 // 如果最小数的下标不是i，交换两者
			mySwap(arr[minIndex], arr[i]);
		}
	}
}

// 打印函数
template<typename T>
void print(T * arr, int len) {
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
}

void test01() {
	char charArray[] = "deagcebf";
	int length = sizeof(charArray) / sizeof(char);
	sort<char>(charArray, length);	// 显示说明类型
	print<>(charArray, length);		// <>中可以不写,自动推导类型
}

void test02() {
	int intArray[] = { 7, 5, 8, 1, 3, 9, 2, 4, 6 };
	int length = sizeof(intArray) / sizeof(int);
	sort<int>(intArray, length);
	print(intArray, length);		// 自动推导类型
}

int main()
{
	test01();
	cout << endl;
	test02();
}
