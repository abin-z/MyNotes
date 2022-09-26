#include <iostream>
#include <string>
using namespace std;

// 类模板
template<class NameType, class AgeType>
class Person {			// 类
public:
	Person(NameType name, AgeType age) :
		m_name(name),
		m_age(age)
	{

	}

	void setName(NameType name) {
		this->m_name = name;
	}

	void setName(AgeType age) {
		this->m_age = age;
	}

	NameType getName() {
		return m_name;
	}
	AgeType getAge() {
		return m_age;
	}

private:
	NameType m_name;
	AgeType m_age;
};

void test() {
	Person<string, int> p("zhangsan", 18);	// 必须显示的给出模板的具体类型
	cout << "{m_name = " << p.getName() << ", m_age = " << p.getAge() << "}" << endl;
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}
