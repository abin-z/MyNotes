#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Greater4 {
public:
	bool operator()(int val) {
		return val > 4;
	}
};

/*
`count_if(iterator beg, iterator end, _Pred);  `
// 按条件统计元素出现次数
// beg 开始迭代器
// end 结束迭代器
// _Pred 谓词
*/

//内置数据类型
void test01()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(4);
	v.push_back(5);
	v.push_back(3);
	v.push_back(4);
	v.push_back(4);

	int num = count_if(v.begin(), v.end(), Greater4()); // 按条件统计(仿函数)

	cout << "大于4的个数为： " << num << endl;
}

//自定义数据类型
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

struct AgeLess35
{
	bool operator()(const Person &p) {
		return p.m_Age < 35;
	}
};

void test02()
{
	vector<Person> v;

	Person p1("刘备", 35);
	Person p2("关羽", 35);
	Person p3("张飞", 35);
	Person p4("赵云", 30);
	Person p5("曹操", 25);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	int num = count_if(v.begin(), v.end(), AgeLess35());  // 按条件统计(仿函数)
	cout << "小于35岁的个数：" << num << endl;
}


int main()
{
	test01();
	test02();
	std::cout << "Hello World!\n";
}