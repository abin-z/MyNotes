#include "GeneralArray.hpp"
#include <string>

void printArray(GeneralArray<long> &array) {
	for (int i = 0; i < array.getSize(); i++)
	{
		cout << array[i] << endl;
	}
}

void test01() {
	GeneralArray<long> array(5);
	array.push_back(101);
	array.push_back(102);
	array.push_back(103);
	array.push_back(104);
	array.push_back(105);
	printArray(array);

	cout << "==================" << endl;
	GeneralArray<long> arr2(array);	// 调用拷贝构造函数
	cout << "容量 = " << arr2.getCapacity() << endl;
	cout << "元素个数 = " << arr2.getSize() << endl;
	arr2.push_back(999);
	printArray(arr2);
	cout << "==================" << endl;

	GeneralArray<long> arr3(100);
	arr3 = array;
	arr3.pop_back();
	arr3.pop_back();
	printArray(arr2);
	cout << "容量 = " << arr3.getCapacity() << endl;
	cout << "元素个数 = " << arr3.getSize() << endl;
}

class Student {
public:
	Student() {}
	Student(string name, int age) {
		this->m_name = name;
		this->m_age = age;
	}
	string m_name;
	int m_age;
};

void printArray(GeneralArray<Student> &array) {
	for (int i = 0; i < array.getSize(); i++)
	{
		cout << "{" << array[i].m_name << "," << array[i].m_age << "}" << endl;
	}
}

void test02() {
	GeneralArray<Student> array(7);
	Student s1("zhangsan", 18);
	Student s2("李四", 20);
	Student s3("孔乙己", 28);
	Student s4("安其拉", 19);
	Student s5("tom", 20);
	array.push_back(s1);
	array.push_back(s2);
	array.push_back(s3);
	array.push_back(s4);
	array.push_back(s5);
	printArray(array);
	array = array;				// 调用赋值运算符号
	cout << "=========自定义=========" << endl;
	GeneralArray<Student> array01(array);
	array01.pop_back();
	printArray(array01);
	cout << "==================" << endl;
	GeneralArray<Student> array02(10000000);	// 观察内存状态,当申请内存过多将无法运行
	array02 = array01;
	printArray(array02);
}

int main()
{
	test01();
	cout << "+++++++++++++++++++++++ test02 +++++++++++++++++++++++" << endl;
	test02();
	std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
