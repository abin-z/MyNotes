#include <iostream>
#include <string>
using namespace std;

class Base {		// 基类
public:
	string m_public;
protected:
	string m_protected;
private:
	string m_private;
};

class Son1 :public Base {		// public 公共继承
	void func() {// 成员函数
		m_public = "123";		// 父类中 public 权限继承到子类,依然是 public 权限
		m_protected = "123";	// 父类中 protected 权限继承到子类,依然是 protected 权限
		//m_private = "";			// 子类中无法访问父类私有成员	
	}
};

class Son2 :protected Base {	// protected 保护继承
	void func() {// 成员函数
		m_public = "123";		// 父类中 public 权限继承到子类, 变为了 protected 权限
		m_protected = "123";	// 父类中 protected 权限继承到子类,依然是 protected 权限
		//m_private = "";			// 子类中无法访问父类私有成员	
	}
};

class Son3 :private Base {		// private 私有继承
	void func() {// 成员函数
		m_public = "123";		// 父类中 public 权限继承到子类, 变为了 private 权限
		m_protected = "123";	// 父类中 protected 权限继承到子类,依然是 private 权限
		//m_private = "";			// 子类中无法访问父类私有成员	
	}
};

class GrandSon2 : protected Son2 {	// 保护继承---可以一直继承下去, 派生类都可以访问
	void func() {// 成员函数
		m_public = "123";		// 基类中 protected 权限继承到子类, 变为了 protected 权限
		m_protected = "123";	// 基类中 protected 权限继承到子类, 依然是 protected 权限
		//m_private = "";			// 子类中无法访问父类私有成员	
	}
};

class GrandSon3 : private Son3 {	// 私有继承---只能继承一次
	void func() {// 成员函数
		//m_public = "123";		// 基类中 private 权限继承到子类, 子类无法访问
		//m_protected = "123";	// 基类中 private 权限继承到子类, 子类无法访问
		//m_private = "";			// 子类中无法访问父类私有成员	
	}
};


void test() {
	Son1 s1;	// 公共继承
	s1.m_public = "";			
	//s1.m_protected = "";	// 继承后仍然为保护权限, 类外无法访问

	Son2 s2;	// 保护继承
	//s2.m_public = "";		// 继承后成为保护权限, 类外无法访问
	//s2.m_protected = "";	// 继承后仍然为保护权限, 类外无法访问

	Son3 s3;	// 私有继承
	//s3.m_public = "";		// 继承后成为私有权限, 类外无法访问
	//s3.m_protected = "";	// 继承后成为私有权限, 类外无法访问
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}