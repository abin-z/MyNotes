#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

/*
`count_if(iterator beg, iterator end, _Pred);  `
// 按条件统计元素出现次数
// beg 开始迭代器
// end 结束迭代器
// _Pred 谓词
*/

// 统计内置数据类型
void test01() {
	vector<int> vtr;
	vtr.push_back(0);
	vtr.push_back(20);
	vtr.push_back(20);
	vtr.push_back(30);
	vtr.push_back(15);
	vtr.push_back(20);
	vtr.push_back(23);

	int num = count(vtr.cbegin(), vtr.cend(), 20);
	cout << "为20的数有" << num << "个" << endl;
}

class Person {
public:
	Person(string name, int age) :
		m_name(name),
		m_age(age)
	{}

	bool operator==(const Person &p)
	{
		if (this == &p) {
			return true;
		}
		// 根据年龄进行判断
		if (this->m_age == p.m_age) {
			return true;
		}
		return false;
	}

private:
	string m_name;
	int m_age;
};

// 统计自定义数据类型
void test02() {
	vector<Person> vtr;
	vtr.push_back(Person("张飞", 50));
	vtr.push_back(Person("赵云", 25));
	vtr.push_back(Person("关羽", 26));
	vtr.push_back(Person("洪七公", 90));
	vtr.push_back(Person("贾宝玉", 25));

	Person p("诸葛亮", 25);

	int num = count(vtr.begin(), vtr.end(), p);
	cout << "和诸葛亮一样25岁的有: " << num << "个" << endl;
}


int main()
{
	test01();
	test02();
	std::cout << "Hello World!\n";
}