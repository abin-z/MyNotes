#include "Person.h"

// ���캯��
template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age) {
	this->m_name = name;
	this->m_age = age;
}

// ��Ա����
template<class T1, class T2>
void Person<T1, T2>::showPerson() {
	cout << "name = " << this->m_name << " age = " << this->m_age << endl;
}
