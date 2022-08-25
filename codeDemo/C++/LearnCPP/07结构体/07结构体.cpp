#include <iostream>
#include <string>
using namespace std;

struct Student			// 定义结构体
{
	string name;
	int age;
	string gender;
}stu;

//教师结构体定义
struct teacher
{
	//成员列表
	int id; //职工编号
	string name;  //教师姓名
	int age;   //教师年龄
	struct Student stu; //子结构体 学生
};

// 嵌套的结构体
void func3() {
	struct teacher t1;
	t1.id = 10000;
	t1.name = "老王";
	t1.age = 40;

	t1.stu.name = "张三";
	t1.stu.age = 18;
	t1.stu.gender = "男";

	cout << "教师 职工编号： " << t1.id << " 姓名： " << t1.name << " 年龄： " << t1.age << endl;

	cout << "辅导学员 姓名： " << t1.stu.name << " 年龄：" << t1.stu.age << " 考试分数： " << t1.stu.gender << endl;
}


// 结构体数组
void func() {
	// 定义结构体数组
	struct Student stuArray[3] = {
		{"zhangsan", 12, "男"},
		{"李四", 36, "男"},
		{"tom"}
	};

	for (int i = 0; i < 3; ++i)
	{
		cout << "姓名: " << stuArray[i].name << " 年龄: " << stuArray[i].age << " 性别: " << stuArray[i].gender << endl;
	}

	// 修改数组中的结构体值:
	stuArray[2].age = 50;
	stuArray[2].gender = "xiaoming";
	cout << "修改后的值\n";


	for (int i = 0; i < 3; ++i)
	{
		cout << "姓名: " << stuArray[i].name << " 年龄: " << stuArray[i].age << " 性别: " << stuArray[i].gender << endl;
	}
}

// 结构体指针
void func1() {
	struct Student s;
	struct Student *p = &s;
	p->name = "lihua";
	p->age = 16;
	p->gender = "gay";
	cout << "姓名: " << p->name << " 年龄: " << p->age << " 性别: " << p->gender << endl;
}


int main()
{
	std::cout << "Hello World!\n";
	struct Student s1;
	s1.age = 18;
	s1.name = "zhangsan";
	s1.gender = "男";
	cout << "姓名: " << s1.name << " 年龄: " << s1.age << " 性别: " << s1.gender << endl;

	Student s2 = { "lisi", 20, "女" };
	cout << "姓名: " << s2.name << " 年龄: " << s2.age << " 性别: " << s2.gender << endl;

	stu.age = 22;
	stu.name = "wangwu";
	stu.gender = "保密";
	cout << "姓名: " << stu.name << " 年龄: " << stu.age << " 性别: " << stu.gender << endl;
	cout << "========================================" << endl;
	func();
	cout << "========================================" << endl;
	func1();
	cout << "========================================" << endl;
	func3();
}

