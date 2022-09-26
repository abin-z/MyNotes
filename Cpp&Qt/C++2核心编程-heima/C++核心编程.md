# C++核心编程

本阶段主要针对C++==面向对象==编程技术做详细讲解，探讨C++中的核心和精髓。



## 1 内存分区模型

C++程序在执行时，将内存大方向划分为**4个区域**

- 代码区：存放函数体的二进制代码，由操作系统进行管理的
- 全局区：存放全局变量和静态变量以及常量
- 栈区：**由编译器自动分配释放**, 存放函数的参数值,局部变量等
- 堆区：**由程序员分配和释放**,若程序员不释放,程序结束时由操作系统回收



**内存四区意义：**

不同区域存放的数据，赋予不同的生命周期, 给我们更大的灵活编程



### 1.1 程序运行前

​	在程序编译后，生成了exe可执行程序，**未执行该程序前**分为两个区域

​	**代码区：**

​		存放 CPU 执行的机器指令

​		代码区是**共享**的，共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可

​		代码区是**只读**的，使其只读的原因是防止程序意外地修改了它的指令

​	**全局区：**

​		全局变量和静态变量存放在此.

​		全局区还包含了常量区, 字符串常量和其他常量也存放在此.

​		==该区域的数据在程序结束后由操作系统释放==.**（很重要）**



**示例：**

```c++
//全局变量
int g_a = 10;
int g_b = 10;

//全局常量
const int c_g_a = 10;
const int c_g_b = 10;

int main() {

	//局部变量
	int a = 10;
	int b = 10;

	//打印地址
	cout << "局部变量a地址为： " << (int)&a << endl;
	cout << "局部变量b地址为： " << (int)&b << endl;

	cout << "全局变量g_a地址为： " <<  (int)&g_a << endl;
	cout << "全局变量g_b地址为： " <<  (int)&g_b << endl;

	//静态变量
	static int s_a = 10;
	static int s_b = 10;

	cout << "静态变量s_a地址为： " << (int)&s_a << endl;
	cout << "静态变量s_b地址为： " << (int)&s_b << endl;

	cout << "字符串常量地址为： " << (int)&"hello world" << endl;
	cout << "字符串常量地址为： " << (int)&"hello world1" << endl;

	cout << "全局常量c_g_a地址为： " << (int)&c_g_a << endl;
	cout << "全局常量c_g_b地址为： " << (int)&c_g_b << endl;

	const int c_l_a = 10;
	const int c_l_b = 10;
	cout << "局部常量c_l_a地址为： " << (int)&c_l_a << endl;
	cout << "局部常量c_l_b地址为： " << (int)&c_l_b << endl;

	system("pause");

	return 0;
}
```

打印结果：

![1545017602518](assets/1545017602518.png)



总结：

* C++中在程序运行前分为全局区和代码区
* 代码区特点是共享和只读
* 全局区中存放全局变量、静态变量、常量
* 常量区中存放 const修饰的全局常量  和 字符串常量
* 局部变量和局部常量在运行时存放在栈区




### 1.2 程序运行后



​	**栈区：**

​		由编译器自动分配释放, 存放函数的参数值,局部变量等

​		注意事项：**==不要返回局部变量的地址==，栈区开辟的数据由编译器自动释放**



**示例：**

```c++
int * func()
{
	int a = 10;
	return &a;
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;	// 会出现非法数据

	system("pause");

	return 0;
}
```



​	**堆区：**

​		==由程序员分配释放==,若程序员不释放,程序结束时由操作系统回收

​		在C++中主要利用new在堆区开辟内存

**示例：**

```c++
int* func()
{
	int* a = new int(10);		// 在堆区开辟int类型得内存空间
	return a;					// 返回指针
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;
    
	system("pause");

	return 0;
}
```



**总结：**

**堆区数据由程序员管理开辟和释放**

堆区数据利用new关键字进行开辟内存



### 1.3 new操作符



​	C++中利用==new==操作符在堆区开辟数据

​	堆区开辟的数据，由程序员手动开辟，手动释放，释放利用操作符 ==delete==

​	语法：` new 数据类型`

​	利用new创建的数据，会返回该数据对应的类型的指针 



**示例1： 基本语法**

```c++
int* func()
{
	int* a = new int(10);		// 在堆区开辟数据, 需要手动释放
	return a;
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;

	//利用delete释放堆区数据,一定要记得释放堆区的数据,否则会产生内存泄漏
	delete p;

	//cout << *p << endl; //报错，释放的空间不可访问

	system("pause");

	return 0;
}
```



**示例2：开辟数组**

```c++
//堆区开辟数组
int main() {

	int* arr = new int[10];

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	//释放数组 delete 后加 []
	delete[] arr;			// 一定要记得释放堆区的内存空间， 否则会出现内存泄露

	system("pause");

	return 0;
}

```



## 2 引用

### 2.1 引用的基本使用

**作用： **给变量起别名

**语法：** `数据类型 &别名 = 原名`



**示例：**

```C++
int main() {

	int a = 10;
	int &b = a;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	b = 100;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	system("pause");

	return 0;
}
```



### 2.2 引用注意事项

* 引用必须初始化
* 引用在初始化后，不可以改变

示例：

```C++
int main() {

	int a = 10;
	int b = 20;
	//int &c; //错误，引用必须初始化
	int &c = a; //一旦初始化后，就不可以更改
	c = b; //这是赋值操作，不是更改引用

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;

	system("pause");
	return 0;
}
```



### 2.3 引用做函数参数

**作用：**函数传参时，可以利用引用的技术让形参修饰实参

**优点：**可以简化指针修改实参



**示例：**

```C++
//1. 值传递
void mySwap01(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

//2. 地址传递
void mySwap02(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//3. 引用传递
void mySwap03(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {

	int a = 10;
	int b = 20;

	mySwap01(a, b);
	cout << "a:" << a << " b:" << b << endl;

	mySwap02(&a, &b);
	cout << "a:" << a << " b:" << b << endl;

	mySwap03(a, b);
	cout << "a:" << a << " b:" << b << endl;

	system("pause");
	return 0;
}

```

> 总结：通过引用参数产生的效果同按地址传递是一样的。引用的语法更清楚简单



### 2.4 引用做函数返回值

作用：引用是可以作为函数的返回值存在的



注意：==**不要返回局部变量引用**==, 因为局部变量在函数执行完后会被释放

用法：函数调用作为左值



**示例：**

```C++
//返回局部变量引用, 会引发不必要的错误
int& test01() {
	int a = 10; //局部变量
	return a;
}

//返回静态变量引用
int& test02() {
	static int a = 20;
	return a;
}

int main() {

	//不能返回局部变量的引用
	int& ref = test01();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;

	//如果函数做左值，那么必须返回引用
	int& ref2 = test02();
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	test02() = 1000;	// 引用可以作为左值, 修改的都是全局唯一的静态变量

	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	system("pause");

	return 0;
}
```





### 2.5 引用的本质

本质：**引用的本质在c++内部实现是一个指针常量.** 必须要初始化且不能改变指向(==引用和指针的实现原理不一样, 引用不是一个对象==)

编译器在编译阶段会自动将引用转换为`int* const ref = &a;`

讲解示例：

```C++
//发现是引用，转换为 int* const ref = &a;
void func(int& ref){
	ref = 100; // ref是引用，转换为*ref = 100
}
int main(){
	int a = 10;
    
    //自动转换为 int* const ref = &a; 指针常量是指针指向不可改，也说明为什么引用不可更改
	int& ref = a; 
	ref = 20; //内部发现ref是引用，自动帮我们转换为: *ref = 20;
    
	cout << "a:" << a << endl;
	cout << "ref:" << ref << endl;
    
	func(a);
	return 0;
}
```

结论：C++推荐用引用技术，因为语法方便，引用本质是指针常量，但是所有的指针操作编译器都帮我们做了



### 2.6 常量引用

**作用：**常量引用主要用来修饰形参，防止误操作

在函数形参列表中，可以加==const修饰形参==，防止形参改变实参

**示例：**

```C++
//引用使用的场景，通常用来修饰形参
void showValue(const int& v) {
	//v += 10;
	cout << v << endl;
}
// 可以根据函数参数是否添加const来区分重载

int main() {

	//int& ref = 10;  错误,引用本身需要一个合法的内存空间，因此这行错误
	//加入const就可以了，编译器优化代码，int temp = 10; const int& ref = temp;
	const int& ref = 10;

	//ref = 100;  //加入const后不可以修改变量
	cout << ref << endl;

	//函数中利用常量引用防止误操作修改实参
	int a = 10;
	showValue(a);

	system("pause");

	return 0;
}
```



## 3 函数提高

### 3.1 函数默认参数

在C++中，函数的形参列表中的形参是可以有默认值的。

语法：` 返回值类型  函数名 （参数= 默认值）{}`



**示例：**

```C++
int func(int a, int b = 10, int c = 10) {
	return a + b + c;
}

//1. 如果某个位置参数有默认值，那么从这个位置往后，从左向右，必须都要有默认值
//2. 如果函数声明有默认值，函数实现的时候就不能有默认参数
//   如果函数实现有默认值, 则函数声明就不能有默认值
int func2(int a = 10, int b = 10);
int func2(int a, int b) {
	return a + b;
}

int main() {

	cout << "ret = " << func(20, 20) << endl;
	cout << "ret = " << func(100) << endl;

	system("pause");

	return 0;
}
```



### 3.2 函数占位参数

C++中函数的形参列表里可以有占位参数，用来做占位，调用函数时必须填补该位置

**语法：** `返回值类型 函数名 (数据类型){}`



在现阶段函数的占位参数存在意义不大，但是后面的课程中会用到该技术

**示例：**

```C++
//函数占位参数 ，占位参数也可以有默认参数
void func(int a, int) {
	cout << "this is func" << endl;
}

int main() {

	func(10,10); //占位参数必须填补, 虽然没有什么用

	system("pause");

	return 0;
}
```



### 3.3 函数重载

#### 3.3.1 函数重载概述

**作用：**函数名可以相同，提高复用性

**函数重载满足条件：**

* 同一个作用域下
* 函数名称相同
* 函数参数**类型不同**  或者 **个数不同** 或者 **顺序不同**
* **函数的&引用参数是否添加 const**



**注意:**  函数的返回值不可以作为函数重载的条件



**示例：**

```C++
//函数重载需要函数都在同一个作用域下
void func()
{
	cout << "func 的调用！" << endl;
}
void func(int a)
{
	cout << "func (int a) 的调用！" << endl;
}
void func(double a)
{
	cout << "func (double a)的调用！" << endl;
}
void func(int a ,double b)
{
	cout << "func (int a ,double b) 的调用！" << endl;
}
void func(double a ,int b)
{
	cout << "func (double a ,int b)的调用！" << endl;
}

//函数返回值不可以作为函数重载条件
//int func(double a, int b)
//{
//	cout << "func (double a ,int b)的调用！" << endl;
//}

int main() {

	func();
	func(10);
	func(3.14);
	func(10,3.14);
	func(3.14 , 10);
	
	system("pause");

	return 0;
}
```



#### 3.3.2 函数重载注意事项

* 引用作为重载条件

* 函数重载碰到函数默认参数

  

**示例：**

```C++
//函数重载注意事项
//1、引用作为重载条件

void func(int &a)
{
	cout << "func (int &a) 调用 " << endl;
}

void func(const int &a)
{
	cout << "func (const int &a) 调用 " << endl;
}


//2、函数重载碰到函数默认参数

void func2(int a, int b = 10)
{
	cout << "func2(int a, int b = 10) 调用" << endl;
}

void func2(int a)
{
	cout << "func2(int a) 调用" << endl;
}

int main() {
	
	int a = 10;
	func(a); //调用无const
	func(10);//调用有const


	//func2(10); //碰到默认参数产生歧义，需要避免

	system("pause");

	return 0;
}
```





## **4** 类和对象

C++面向对象的三大特性为：==封装、继承、多态==

C++认为==万事万物都皆为对象==，对象上有其属性和行为



**例如：**

​	人可以作为对象，属性有姓名、年龄、身高、体重...，行为有走、跑、跳、吃饭、唱歌...

​	车也可以作为对象，属性有轮胎、方向盘、车灯...,行为有载人、放音乐、放空调...

​	具有相同性质的==对象==，我们可以抽象称为==类==，人属于人类，车属于车类

### 4.1 封装

#### 4.1.1  封装的意义

封装是C++面向对象三大特性之一

封装的意义：

* 将属性和行为作为一个整体，表现生活中的事物
* 将属性和行为加以权限控制



**封装意义一：**

​	在设计类的时候，属性和行为写在一起，表现事物

**语法：** `class 类名{   访问权限： 属性  / 行为  };`



**示例1：**设计一个圆类，求圆的周长

**示例代码：**

```C++
//圆周率
const double PI = 3.14;

//1、封装的意义
//将属性和行为作为一个整体，用来表现生活中的事物

//封装一个圆类，求圆的周长
//class代表设计一个类，后面跟着的是类名
class Circle
{
public:  //访问权限  公共的权限

	//属性
	int m_r;//半径

	//行为
	//获取到圆的周长
	double calculateZC()
	{
		//2 * pi  * r
		//获取圆的周长
		return  2 * PI * m_r;
	}
};

int main() {

	//通过圆类，创建圆的对象
	// c1就是一个具体的圆
	Circle c1;
	c1.m_r = 10; //给圆对象的半径 进行赋值操作

	//2 * pi * 10 = = 62.8
	cout << "圆的周长为： " << c1.calculateZC() << endl;

	system("pause");

	return 0;
}
```



**示例2：**设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号

**示例2代码：**

```C++
//学生类
class Student {
public:
	void setName(string name) {
		m_name = name;
	}
	void setID(int id) {
		m_id = id;
	}

	void showStudent() {
		cout << "name:" << m_name << " ID:" << m_id << endl;
	}
public:
	string m_name;
	int m_id;
};

int main() {

	Student stu;
	stu.setName("德玛西亚");
	stu.setID(250);
	stu.showStudent();

	system("pause");

	return 0;
}

```



**封装意义二：**

类在设计时，可以把属性和行为放在不同的权限下，加以控制

访问权限有三种：



1. **public**        公共权限  
2. **protected** 保护权限
3. **private**      私有权限



**示例：**

```C++
//三种权限
//公共权限  public     类内可以访问  类外可以访问	 子类可以访问
//保护权限  protected  类内可以访问  类外不可以访问  子类可以访问
//私有权限  private    类内可以访问  类外不可以访问  子类不可以访问

class Person
{
	//姓名  公共权限
public:
	string m_Name;

	//汽车  保护权限
protected:
	string m_Car;

	//银行卡密码  私有权限
private:
	int m_Password;

public:
	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_Password = 123456;
	}
};

int main() {

	Person p;
	p.m_Name = "李四";
	//p.m_Car = "奔驰";  //保护权限类外访问不到
	//p.m_Password = 123; //私有权限类外访问不到

	system("pause");

	return 0;
}
```



#### 4.1.2 struct和class区别

在C++中 struct和class唯一的**区别**就在于 **==默认的访问权限不同==**

区别：

* struct  默认权限为公共
* class    默认权限为私有

[struct和class和union的异同](https://zhuanlan.zhihu.com/p/148833639)

```C++
class C1
{
	int  m_A; //默认是私有权限
};

struct C2
{
	int m_A;  //默认是公共权限
};

int main() {

	C1 c1;
	c1.m_A = 10; //错误，访问权限是私有

	C2 c2;
	c2.m_A = 10; //正确，访问权限是公共

	system("pause");

	return 0;
}
```



#### 4.1.3 成员属性设置为私有

**优点1：**将所有成员属性设置为私有，可以自己控制读写权限

**优点2：**对于写权限，我们可以检测数据的有效性



**示例：**

```C++
class Person {
public:

	//姓名设置可读可写
	void setName(string name) {
		m_Name = name;
	}
	string getName()
	{
		return m_Name;
	}


	//获取年龄 
	int getAge() {
		return m_Age;
	}
	//设置年龄
	void setAge(int age) {
		if (age < 0 || age > 150) {
			cout << "你个老妖精!" << endl;
			return;
		}
		m_Age = age;
	}

	//情人设置为只写
	void setLover(string lover) {
		m_Lover = lover;
	}

private:
	string m_Name; //可读可写  姓名
	
	int m_Age; //只读  年龄

	string m_Lover; //只写  情人
};


int main() {

	Person p;
	//姓名设置
	p.setName("张三");
	cout << "姓名： " << p.getName() << endl;

	//年龄设置
	p.setAge(50);
	cout << "年龄： " << p.getAge() << endl;

	//情人设置
	p.setLover("苍井");
	//cout << "情人： " << p.m_Lover << endl;  //只写属性，不可以读取

	system("pause");

	return 0;
}
```



**练习案例1：设计立方体类**

设计立方体类(Cube)

求出立方体的面积和体积

分别用全局函数和成员函数判断两个立方体是否相等。

![1545533548532](assets/1545533548532.png)



**练习案例2：点和圆的关系**

设计一个圆形类（Circle），和一个点类（Point），计算点和圆的关系。

![1545533829184](assets/1545533829184.png)



### 4.2 对象的初始化和清理



*  生活中我们买的电子产品都基本会有出厂设置，在某一天我们不用时候也会删除一些自己信息数据保证安全
*  C++中的面向对象来源于生活，每个对象也都会有初始设置以及 对象销毁前的清理数据的设置。





#### 4.2.1 构造函数和析构函数

对象的**初始化和清理**也是两个非常重要的安全问题

​	一个对象或者变量没有初始状态，对其使用后果是未知

​	同样的使用完一个对象或变量，没有及时清理，也会造成一定的安全问题



c++利用了**构造函数**和**析构函数**解决上述问题，这两个函数将会被编译器自动调用，完成对象初始化和清理工作。

对象的初始化和清理工作是编译器强制要我们做的事情，因此如果**我们不提供构造和析构，编译器会提供**

**编译器提供的构造函数和析构函数是空实现。**



* 构造函数：主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。
* 析构函数：主要作用在于对象**销毁前**系统自动调用，执行一些清理工作。



**构造函数语法：**`类名(){}`

1. 构造函数，没有返回值也不写void
2. 函数名称与类名相同
3. 构造函数可以有参数，因此可以发生重载
4. 程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次



**析构函数语法：** `~类名(){}`

1. 析构函数，没有返回值也不写void
2. 函数名称与类名相同,在名称前加上符号  ~
3. 析构函数不可以有参数，因此不可以发生重载
4. 程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次

```C++
class Person
{
public:
	//构造函数
	Person()
	{
		cout << "Person的构造函数调用" << endl;
	}
	//析构函数
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

};

void test01()
{
	Person p;
}

int main() {
	
	test01();

	system("pause");

	return 0;
}
```



#### 4.2.2 构造函数的分类及调用

两种分类方式：

​	按参数分为： 有参构造和无参构造

​	按类型分为： 普通构造和拷贝构造      拷贝构造函数: `Person(const Person &p){ this.age = p.age; }`

三种调用方式：

​	括号法

​	显示法

​	隐式转换法



**示例：**

```C++
//1、构造函数分类
// 按照参数分类分为 有参和无参构造   无参又称为默认构造函数
// 按照类型分类分为 普通构造和拷贝构造

class Person {
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数!" << endl;
	}
	//有参构造函数
	Person(int a) {
		age = a;
		cout << "有参构造函数!" << endl;
	}
	//拷贝构造函数
	Person(const Person& p) {
		//age = p.age;		
		this->age = p.age;
		cout << "拷贝构造函数!" << endl;
	}
	//析构函数
	~Person() {
		cout << "析构函数!" << endl;
	}
public:
	int age;
};

//2、构造函数的调用
//调用无参构造函数
void test01() {
	Person p; //调用无参构造函数
}

//调用有参的构造函数
void test02() {

	//2.1  括号法，常用
	Person p1(10);
	//注意1：调用无参构造函数不能加括号，如果加了编译器认为这是一个函数声明
	//Person p2();		// 错误 无参构造后面不能加括号

	//2.2 显式法
	Person p2 = Person(10); 
	Person p3 = Person(p2);
	//Person(10)单独写就是匿名对象  当前行结束之后，马上析构释放

	//2.3 隐式转换法
	Person p4 = 10; // Person p4 = Person(10); 
	Person p5 = p4; // Person p5 = Person(p4); 

	//注意2：不能利用 拷贝构造函数 初始化匿名对象 编译器认为是对象声明
	//Person p5(p4);
}

int main() {

	test01();
	//test02();

	system("pause");

	return 0;
}
```

- 注意1：**调用无参构造函数不能加括号**，如果加了编译器认为这是一个函数声明
- 注意2：**不能利用 拷贝构造函数 初始化匿名对象** 编译器认为是对象声明



#### 4.2.3 拷贝构造函数调用时机

C++中拷贝构造函数调用时机通常有三种情况

* 使用一个已经创建完毕的对象来**初始化**一个新对象 (是初始化不是赋值)
* 值传递的方式给函数参数传值
* 以值方式返回局部对象



注意: 对于第一种情况是初始化操作, 并不是赋值操作

**示例：**

```C++
#include <iostream>
using namespace std;

//C++中拷贝构造函数调用时机通常有三种情况
//
//* 使用一个已经创建完毕的对象来初始化一个新对象
//* 值传递的方式给函数参数传值
//* 以值方式返回局部对象

class Person {
public:
	// 无参构造函数
	Person() {
		cout << "无参构造函数被调用" << endl;
		m_age = 0;
	}
	// 有参构造函数(重载)
	Person(int age) {
		cout << "有参构造函数被调用" << endl;
		m_age = age;
	}
	// 拷贝构造函数
	Person(const Person &p ) {			// 若不提供,编译器会提供一个值拷贝的默认的拷贝构造.
		cout << "拷贝构造函数被调用" << endl;
		m_age = p.m_age;
	}
	// 析构函数
	~Person() {
		cout << "~析构构造函数被调用" << endl;
	}

private:
	int m_age;		// 私有属性
};

void doSometing(Person p) {		// 值传递方式的参数, 会创建一个临时副本
	// doSometing.....
	// 函数执行完后会执行p对象的析构函数
}

Person doTest() {				// 值传递方式的返回局部对象
	Person p;	// 调用构造函数
	cout << "函数中局部变量的p对象地址: " << (int)&p << endl;
	return p;	
}

void func() {
	Person p1;				// 调用构造函数
	//Person p2();	// 错误: 当调用无参构造的时候不能添加(), 编译器会认为是函数的声明

	Person p2(p1);			// 调用拷贝构造函数: 使用一个已经创建完毕的对象来初始化一个新对象

	// 参数为值传递才会调用拷贝构造, 非地址传递和非引用传递
	doSometing(p1);			// 调用拷贝构造函数: 值传递的方式给函数参数传值

	Person p = doTest();	// 调用拷贝构造函数: 以值方式返回局部对象
	cout << "main函数中的p对象地址: " << (int)&p << endl;
}

int main()
{	
	func();
    cout << "Hello World!\n";
	return 0;
}
```



```C++
class Person {
public:
	Person() {
		cout << "无参构造函数!" << endl;
		mAge = 0;
	}
	Person(int age) {
		cout << "有参构造函数!" << endl;
		mAge = age;
	}
	Person(const Person& p) {
		cout << "拷贝构造函数!" << endl;
		mAge = p.mAge;
	}
	//析构函数在释放内存之前调用
	~Person() {
		cout << "析构函数!" << endl;
	}
public:
	int mAge;
};

//1. 使用一个已经创建完毕的对象来初始化一个新对象
void test01() {

	Person man(100); //p对象已经创建完毕
	Person newman(man); //调用拷贝构造函数
	Person newman2 = man; //拷贝构造

	//Person newman3;
	//newman3 = man; //不是调用拷贝构造函数，赋值操作
}

//2. 值传递的方式给函数参数传值
//相当于Person p1 = p;
void doWork(Person p1) {}
void test02() {
	Person p; //无参构造函数
	doWork(p);
}

//3. 以值方式返回局部对象
Person doWork2()
{
	Person p1;
	cout << (int *)&p1 << endl;
	return p1;
}

void test03()
{
	Person p = doWork2();
	cout << (int *)&p << endl;
}


int main() {

	//test01();
	//test02();
	test03();

	system("pause");

	return 0;
}
```



#### 4.2.4 构造函数调用规则

默认情况下，c++编译器至少给一个类添加3个函数

1．**默认构造函数**(无参，函数体为空)

2．**默认析构函数**(无参，函数体为空)

3．**默认拷贝构造函数**，对属性进行==**值拷贝**==(浅拷贝)



构造函数调用规则如下：

* ==如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造==


* ==如果用户定义拷贝构造函数，c++不会再提供其他构造函数==



示例：

```C++
class Person {
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数!" << endl;
	}
	//有参构造函数
	Person(int a) {
		age = a;
		cout << "有参构造函数!" << endl;
	}
	//拷贝构造函数
	Person(const Person& p) {
		age = p.age;
		cout << "拷贝构造函数!" << endl;
	}
	//析构函数
	~Person() {
		cout << "析构函数!" << endl;
	}
public:
	int age;
};

void test01()
{
	Person p1(18);
	//如果不写拷贝构造，编译器会自动添加拷贝构造，并且做浅拷贝操作
	Person p2(p1);

	cout << "p2的年龄为： " << p2.age << endl;
}

void test02()
{
	//如果用户提供有参构造，编译器不会提供默认构造，会提供拷贝构造
	Person p1; //此时如果用户自己没有提供默认构造，会出错
	Person p2(10); //用户提供的有参
	Person p3(p2); //此时如果用户没有提供拷贝构造，编译器会提供

	//如果用户提供拷贝构造，编译器不会提供其他构造函数
	Person p4; //此时如果用户自己没有提供默认构造，会出错
	Person p5(10); //此时如果用户自己没有提供有参，会出错
	Person p6(p5); //用户自己提供拷贝构造
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



#### 4.2.5 深拷贝与浅拷贝

深浅拷贝是面试经典问题，也是常见的一个坑

浅拷贝：简单的赋值拷贝操作

深拷贝：**在堆区重新申请空间**，进行拷贝操作



**示例：**

```C++
#include <iostream>
#include <string>
using namespace std;
namespace ZB {
	void test();
}

//只要创建一个类, 编译器会自动生成三个函数
//1.默认构造函数		当用户自定义了构造函数后, 编译器将不会再提供默认的构造函数,但是会提供默认的拷贝构造函数
//2.析构函数			
//3.拷贝构造函数		当用户自定义了拷贝构造函数后, 编译器将不会提供其他的构造函数,包括默认的构造函数也不会提供

class Student {
public:
	Student();		// 默认构造函数
	Student(string name, int age); // 有参构造函数
	Student(const Student &s);		// 自定义拷贝构造
	~Student();		// 析构函数
	int getAge();

private:
	string name;
	int *age;		// 指针类型的变量
};

// 无参构造
Student::Student() {
	cout << "无参构造函数调用" << endl;
}

// 有参构造
Student::Student(string name, int age) {
	this->name = name;
	this->age = new int(age);		//这是通过new关键字 在堆区中开辟的空间, 需要程序员自己管理释放操作
	cout << "有参构造函数调用" << endl;
}

// 自定义拷贝构造函数
Student::Student(const Student &s) {
	//编译器默认的拷贝构造函数提供的是浅拷贝,类似于以下代码
	//this->name = s.name;
	//this->age = s.age;			//浅拷贝, 仅仅是值的拷贝, 会导致指针类型的属性都指向同一块内存空间.会导致很多问题

	this->name = s.name;				// 正常值拷贝(浅拷贝)
	this->age = new int(*(s.age));		//深拷贝, 在堆区中重新开辟空间
	cout << "有参构造函数调用" << endl;
}

// 析构函数
Student::~Student() {
	if (this->age != nullptr) {
		delete age;					// 释放堆区的内存空间,防止内存泄漏
		age = nullptr;
		cout << "释放空间" << endl;
	}
	cout << "析构函数调用" << endl;
}

int Student::getAge() {
	return *(this->age);
}

void ZB::test() {
	//在创建对象时,如果调用的是默认无参构造器,不能写成: Student s1(); 不能写括号
	//Student s1(); 这样编译器不会创建Student对象,  编译器会认为这是一个函数的声明
	Student s1;
	Student s2("tom", 16);
	cout << "s2.age = " << s2.getAge() << endl;
	Student s3(s2);		//调用拷贝构造函数
	cout << "s3.age = " << s3.getAge() << endl;
}

int main()
{
	ZB::test();
	cout << endl << "如果在类属性有堆区开辟的(new),一定要自己提供 拷贝构造函数 ,并利用深拷贝(new)来解决浅拷贝带来的问题" << endl;
	return 0;
}
```

![image-20220906121405050](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220906121405050.png)

```C++
class Person {
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数!" << endl;
	}
	//有参构造函数
	Person(int age ,int height) {
		
		cout << "有参构造函数!" << endl;

		m_age = age;
		m_height = new int(height);
		
	}
	//拷贝构造函数  
	Person(const Person& p) {
		cout << "拷贝构造函数!" << endl;
		//如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
		m_age = p.m_age;
		m_height = new int(*p.m_height);
		
	}

	//析构函数
	~Person() {
		cout << "析构函数!" << endl;
		if (m_height != NULL)
		{
			delete m_height;
		}
	}
public:
	int m_age;
	int* m_height;
};

void test01()
{
	Person p1(18, 180);

	Person p2(p1);

	cout << "p1的年龄： " << p1.m_age << " 身高： " << *p1.m_height << endl;

	cout << "p2的年龄： " << p2.m_age << " 身高： " << *p2.m_height << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

> 总结：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题



#### 4.2.6 初始化列表

**作用：**

C++提供了初始化列表语法，用来初始化属性

构造函数初始化列表以一个冒号开始，接着是以逗号分隔的数据成员列表，每个数据成员后面跟一个放在括号中的初始化式。

**语法：**`构造函数()：属性1(值1),属性2（值2）... {}`

C++ 初始化类成员时，**是按照声明的顺序初始化的**，而不是按照出现在初始化列表中的顺序。

[C＋＋初始化与赋值](https://www.cnblogs.com/chio/archive/2008/10/06/1305145.html)

**示例：**

```C++
class Person {
public:

	////传统方式初始化
	//Person(int a, int b, int c) {
	//	m_A = a;
	//	m_B = b;
	//	m_C = c;
	//}

	//初始化列表方式初始化
	Person(int a, int b, int c) :m_A(a), m_B(b), m_C(c) {}
	void PrintPerson() {
		cout << "mA:" << m_A << endl;
		cout << "mB:" << m_B << endl;
		cout << "mC:" << m_C << endl;
	}
private:
	int m_A;
	int m_B;
	int m_C;
};

int main() {

	Person p(1, 2, 3);
	p.PrintPerson();


	system("pause");

	return 0;
}
```

初始化列表注意事项:

```C++
class CExample {
public:
    int a;
    float b;
    //构造函数初始化列表
    CExample(): a(0),b(8.8)
    {}
    //构造函数内部赋值
    CExample()
    {
        a=0;
        b=8.8;
    }
};
```

上面的例子中两个构造函数的结果是一样的。上面的构造函数（使用初始化列表的构造函数）显式的初始化类的成员；而没使用初始化列表的构造函数是对类的成员赋值，并没有进行显式的初始化。

初始化和赋值对内置类型的成员没有什么大的区别，像上面的任一个构造函数都可以。对非内置类型成员变量，为了避免两次构造，推荐使用类构造函数初始化列表。但有的时候必须用带有初始化列表的构造函数：

- 1.成员类型是**没有默认构造函数的类**。若没有提供显示初始化式，则编译器隐式使用成员类型的默认构造函数，若类没有默认构造函数，则编译器尝试使用默认构造函数将会失败。
- 2.**const 成员**或**引用类型**的成员。因为 const 对象或引用类型只能初始化，不能对他们赋值。

**初始化数据成员与对数据成员赋值的含义是什么？有什么区别？**

首先把数据成员按类型分类并分情况说明:

- 1.**内置数据类型，复合类型（指针，引用）**- 在成员初始化列表和构造函数体内进行，在性能和结果上都是一样的
- 2.**用户定义类型（类类型）**- 结果上相同，但是性能上存在很大的差别。因为类类型的数据成员对象在进入函数体前已经构造完成，也就是说在成员初始化列表处进行构造对象的工作，调用构造函数，在进入函数体之后，进行的是对已经构造好的类对象的赋值，又调用个拷贝赋值操作符才能完成（如果并未提供，则使用编译器提供的默认按成员赋值行为）

**注意点：**

初始化列表的成员初始化顺序:

C++ 初始化类成员时，是按照声明的顺序初始化的，而不是按照出现在初始化列表中的顺序。

```C++
class CMyClass {
    CMyClass(int x, int y);
    int m_x;
    int m_y;
};

CMyClass::CMyClass(int x, int y) : m_y(y), m_x(m_y)
{
};
```

你可能以为上面的代码将会首先做 m_y=I，然后做 m_x=m_y，最后它们有相同的值。但是编译器先初始化 m_x，然后是 m_y,，因为它们是按这样的顺序声明的。结果是 m_x 将有一个不可预测的值。有两种方法避免它，一个是总是按照你希望它们被初始化的顺序声明成员，第二个是，如果你决定使用初始化列表，总是按照它们声明的顺序罗列这些成员。这将有助于消除混淆。



#### 4.2.7 类对象作为类成员

C++类中的成员可以是另一个类的对象，我们称该成员为 对象成员



例如：

```C++
class A {}
class B
{
    A a；
}
```

B类中有对象A作为成员，A为对象成员

那么当创建B对象时，A与B的构造和析构的顺序是谁先谁后？



**示例：**

```C++
class Phone
{
public:
	Phone(string name)
	{
		m_PhoneName = name;
		cout << "Phone构造" << endl;
	}

	~Phone()
	{
		cout << "Phone析构" << endl;
	}

	string m_PhoneName;

};


class Person
{
public:

	//初始化列表可以告诉编译器调用哪一个构造函数
	Person(string name, string pName) :m_Name(name), m_Phone(pName)
	{
		cout << "Person构造" << endl;
	}

	~Person()
	{
		cout << "Person析构" << endl;
	}

	void playGame()
	{
		cout << m_Name << " 使用" << m_Phone.m_PhoneName << " 牌手机! " << endl;
	}

	string m_Name;
	Phone m_Phone;

};
void test01()
{
	//当类中成员是其他类对象时，我们称该成员为 对象成员
	//构造的顺序是 ：先调用对象成员的构造，再调用本类构造
	//析构顺序与构造相反
	Person p("张三" , "苹果X");
	p.playGame();

}


int main() {

	test01();

	system("pause");

	return 0;
}
```











#### 4.2.8 静态成员

静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员,

静态成员不属于任何一个对象,属于整个类共有的

静态成员分为：

*  静态成员变量
   *  ==所有对象共享同一份数据==
   *  在编译阶段分配内存
   *  ==类内声明，类外初始化==
   *  访问方式有两种: 1. 通过类名直接访问`类名::静态成员变量`, 2.通过对象访问`对象名.静态成员变量`
*  静态成员函数
   *  所有对象共享同一个函数
   *  ==静态成员函数只能访问静态成员变量==



**示例1 ：**静态成员变量

```C++
class Person
{
	
public:

	static int m_A; //静态成员变量

	//静态成员变量特点：
	//1 在编译阶段分配内存
	//2 类内声明，类外初始化
	//3 所有对象共享同一份数据

private:
	static int m_B; //静态成员变量也是有访问权限的
};
int Person::m_A = 10;
int Person::m_B = 10;

void test01()
{
	//静态成员变量两种访问方式

	//1、通过对象
	Person p1;
	p1.m_A = 100;
	cout << "p1.m_A = " << p1.m_A << endl;

	Person p2;
	p2.m_A = 200;
	cout << "p1.m_A = " << p1.m_A << endl; //共享同一份数据
	cout << "p2.m_A = " << p2.m_A << endl;

	//2、通过类名
	cout << "m_A = " << Person::m_A << endl;


	//cout << "m_B = " << Person::m_B << endl; //私有权限访问不到
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



**示例2：**静态成员函数

```C++
class Person
{

public:

	//静态成员函数特点：
	//1 程序共享一个函数
	//2 静态成员函数只能访问静态成员变量
	
	static void func()
	{
		cout << "func调用" << endl;
		m_A = 100;
		//m_B = 100; //错误，不可以访问非静态成员变量
	}

	static int m_A; //静态成员变量
	int m_B; // 普通成员变量
private:

	//静态成员函数也是有访问权限的
	static void func2()
	{
		cout << "func2调用" << endl;
	}
};
int Person::m_A = 10;		// 类外初始化静态成员

void test01()
{
	//静态成员变量两种访问方式

	//1、通过对象
	Person p1;
	p1.func();

	//2、通过类名
	Person::func();

	//Person::func2(); //私有权限访问不到
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



### 4.3 C++对象模型和this指针

#### 4.3.1 成员变量和成员函数分开存储

在C++中，类内的成员变量和成员函数分开存储

只有**非静态成员变量**才属于类的对象上

```C++
class Student {

};

class Data {	// 存在内存对齐的状况
	int m_a;
	char m_c;
};

class Person {
public:
	Person() {
		mA = 0;
	}
	//非静态成员变量占对象空间
	int mA;
	//静态成员变量不占对象空间
	static int mB;
	//函数也不占对象空间，所有函数共享一个函数实例
	void func() {
		cout << "mA:" << this->mA << endl;
	}
	//静态成员函数也不占对象空间
	static void sfunc() {
	}
};

int main() {
	cout << sizeof(Student) << endl;		// 空对象也会占用一个字节
	cout << sizeof(Person) << endl;			// 占用4个字节
	cout << sizeof(Data) << endl;			// 占用8个字节, 存在内存对齐的情况

	system("pause");
	return 0;
}
```

理论上，32位系统下，int占4byte，char占一个byte，那么将它们放到一个结构体中应该占4+1=5byte；但是实际上，通过运行程序得到的结果是8 byte，这就是内存对齐所导致的。

[C/C++内存对齐详解](https://zhuanlan.zhihu.com/p/30007037)



#### 4.3.2 this指针概念

通过4.3.1我们知道在C++中成员变量和成员函数是分开存储的

每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码

那么问题是：这一块代码是如何区分那个对象调用自己的呢？



c++通过提供特殊的对象指针，this指针，解决上述问题。**this指针指向被调用的成员函数所属的对象**



this指针是隐含每一个非静态成员函数内的一种指针

this指针不需要定义，直接使用即可



this指针的用途：

*  当形参和成员变量同名时，可用this指针来区分
*  在类的非静态成员函数中返回对象本身，可使用return *this

```C++
class Person
{
public:

	Person(int age)
	{
		//1、当形参和成员变量同名时，可用this指针来区分
		this->age = age;
	}

	Person& PersonAddPerson(Person p)
	{
		this->age += p.age;
		//返回对象本身
		return *this;
	}
	int age;
};

void test01()
{
	Person p1(10);
	cout << "p1.age = " << p1.age << endl;

	Person p2(10);
	p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
	cout << "p2.age = " << p2.age << endl;
}

int main() {
	test01();
	system("pause");
	return 0;
}
```

```C++
#include <iostream>
#include <string>
using namespace std;

// this指针的本质是一个指针常量    Person * const this; 

class Person {
public:
	Person(int age) {
		this->age = age;	// this指针等价于 Person * const this;
	}

	int getAge() {
		return this->age;
	}

	// 链式编程
	Person& addAge(int a);
private:
	int age;
};

Person& Person::addAge(int a) {		// 返回类型一定要是引用, 否则会调用拷贝构造返回的不是同一个对象
	this->age += a;
	return *this;   // 返回当前调用的对象
}

void func() {
	Person p(20);

	// 链式编程
	p.addAge(1)
		.addAge(2)
		.addAge(2)
		.addAge(5);

	cout << p.getAge() << endl;
}

int main()
{
	func();
    std::cout << "Hello World!\n";
}
```



#### 4.3.3 空指针访问成员函数

==C++中空指针也是可以调用成员函数的，但是也要注意有没有用到this指针==

如果用到this指针，需要==加以判断==保证代码的健壮性



**示例：**

```C++
//空指针访问成员函数
class Person {
public:

	void ShowClassName() {
		cout << "我是Person类!" << endl;
	}

	void ShowPerson() {
		if (this == nullptr) {		// 防止空指针
			return;
		}
		cout << this->mAge << endl;
	}

public:
	int mAge;
};

void test01()
{
	Person * p = NULL;
	p->ShowClassName(); //空指针，可以调用成员函数
	p->ShowPerson();  //但是如果成员函数中用到了this指针，就不可以了
}

int main() {
	test01();
	system("pause");
	return 0;
}
```



#### 4.3.4 const修饰成员函数(常函数)

**常函数：**

* 成员函数后加const后我们称为这个函数为**常函数**
* ==常函数内不可以修改非静态成员属性== (与this指针有关联)
* 非静态成员属性声明时加关键字==**mutable**==后，在常函数中依然可以修改



**常对象：**

* 声明对象前加const称该对象为常对象
* ==常对象只能调用常函数和静态函数==



**注意:**

- **类的普通成员函数才有常函数。**
- C++中构造函数，静态成员函数，析构函数，全局成员函数都不能是常成员函数。
- 构造成员函数的用途是对对象初始化，成员函数主要是用来被对象调用的，如果构造函数被设置成const，就不能更改成员变量，失去了其作为构造函数的意义。同理析构函数。全局成员函数和静态成员函数static其函数体内部没有this指针，所以也不能是常成员函数



**示例：**

```C++
class Person {
public:
	Person() {
		m_A = 0;
		m_B = 0;
	}

	//this指针的本质是一个指针常量，指针的指向不可修改
	//如果想让指针指向的值也不可以修改，需要声明常函数
	void ShowPerson() const {
		//const Type* const pointer;
		//this = NULL; //不能修改指针的指向 Person* const this;
		//this->mA = 100; //但是this指针指向的对象的数据是可以修改的

		//const修饰成员函数，表示指针指向的内存空间的数据不能修改，除了mutable修饰的变量
		this->m_B = 100;
	}

	void MyFunc() const {
		//mA = 10000;
	}

public:
	int m_A;
	mutable int m_B; //可修改 可变的
};


//const修饰对象  常对象
void test01() {

	const Person person; //常量对象  
	cout << person.m_A << endl;
	//person.mA = 100; //常对象不能修改成员变量的值,但是可以访问
	person.m_B = 100; //但是常对象可以修改mutable修饰成员变量

	//常对象访问成员函数
	person.MyFunc(); //常对象不能调用const的函数

}

int main() {

	test01();

	system("pause");

	return 0;
}
```

```C++
#include <iostream>
#include <string>
using namespace std;

class Person {
public:
	Person(string name, int age):  m_name(name), m_age(age){}

	// 常函数
	void constFunc() const;
	void funct();
	static void staticFunc() {}

private:
	static int s_cout;
	string m_name;
	int m_age;

public:
	mutable int m_height;	// 使用 mutable 关键字使得当前属性在常函数中允许修改
};

int Person::s_cout = 0;

// 常函数中不能修改本类对象的成员和属性
void Person::constFunc() const
{
	//this->m_name = "aa";	//	常函数中不能修改对象属性
	//this->m_age = 0;		//	常函数中不能修改对象属性
	this->m_height = 100;	// 常函数中可以修改mutable 关键字修饰的属性	
	s_cout = 500;			// 常函数中可以修改静态成员, 因为静态成员不属于任何一个对象
	cout << "this->m_height = " << this->m_height << endl;
	cout << "Person::s_cout = " << Person::s_cout << endl;
}

// 正常函数中可以修改本类对象数据
void Person::funct() {
	this->m_age = 10;
	this->m_height = 200;
	this->m_name = "null";
}

void func() {
	Person p("zhangsan", 16);
	// 常对象只能调用常函数不能调用非常函数
	const Person p1("xiaoming", 20);  // 常对象: 不允许修改对象属性,除非是mutable 关键字修饰的属性
	p1.m_height = 150;	// mutable 关键字修饰的非静态属性可以修改

	p.constFunc();		
	p.funct();

	//p1.funct();		// 错误: 常对象不能调用非常函数
	p1.constFunc();		// 正确: 常对象只能调用常函数
	p1.staticFunc();	// 正确: 常对象可以调用静态函数, 因为静态函数中只有静态成员
}

int main()
{
	func();
    std::cout << "Hello World!\n";
}
```




### 4.4 友元



生活中你的家有客厅(Public)，有你的卧室(Private)

客厅所有来的客人都可以进去，但是你的卧室是私有的，也就是说只有你能进去

但是呢，你也可以允许你的好闺蜜好基友进去。

在程序里，有些私有属性 也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术



**友元的目的就是让一个函数或者类 访问另一个类中私有成员**



友元的关键字为  ==friend==



友元的三种实现

* 全局函数做友元 	`friend void func(Home *h); //全局函数做友元, 全局函数可以访问本类私有成员`
* 类做友元         `friend class MyFriend;//友元类, 友元类可以访问本类私有成员`
* 成员函数做友元      `friend void Person::access(Home *h);//成员函数做友元, 指定的友元成员函数可以访问私有成员`



#### 4.4.1 全局函数做友元

```C++
class Building
{
	//告诉编译器 goodGay全局函数 是 Building类的好朋友，可以访问类中的私有内容
	friend void goodGay(Building * building);

public:

	Building()
	{
		this->m_SittingRoom = "客厅";
		this->m_BedRoom = "卧室";
	}


public:
	string m_SittingRoom; //客厅

private:
	string m_BedRoom; //卧室
};


void goodGay(Building * building)
{
	cout << "好基友正在访问： " << building->m_SittingRoom << endl;
	cout << "好基友正在访问： " << building->m_BedRoom << endl;
}


void test01()
{
	Building b;
	goodGay(&b);
}

int main(){

	test01();

	system("pause");
	return 0;
}
```



#### 4.4.2 类做友元

```C++
class Building;
class goodGay
{
public:

	goodGay();
	void visit();

private:
	Building *building;
};


class Building
{
	//告诉编译器 goodGay类是Building类的好朋友，可以访问到Building类中私有内容
	friend class goodGay;

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay gg;
	gg.visit();

}

int main(){

	test01();

	system("pause");
	return 0;
}
```



#### 4.4.3 成员函数做友元

```C++

class Building;
class goodGay
{
public:

	goodGay();
	void visit(); //只让visit函数作为Building的好朋友，可以发访问Building中私有内容
	void visit2(); 

private:
	Building *building;
};


class Building
{
	//告诉编译器  goodGay类中的visit成员函数 是Building好朋友，可以访问私有内容
	friend void goodGay::visit();

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	//cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay  gg;
	gg.visit();

}

int main(){
    
	test01();

	system("pause");
	return 0;
}
```

案例2 :

```C++
#include <iostream>
using namespace std;
#include <string>


class Home;//前置声明
class MyFriend
{
public:
	//这里不能写具体实现,因为编译器认为Home类还没有具体实现
	void visit(Home *h);
};

class Person {
public:
	void access(Home *h);
	void access1(Home *h);
};

class Home
{
	friend void func(Home *h);//全局函数做友元, 全局函数可以访问本类私有成员
	friend class MyFriend;//友元类, 友元类可以访问本类私有成员
	friend void Person::access(Home *h);//成员函数做友元, 指定的友元成员函数可以访问私有成员
public:
	Home();
	string livingRoom;	//客厅 public

private:
	string bedRoom;		//卧室 private
};

Home::Home()
{
	livingRoom = "客厅";
	bedRoom = "卧室";
}

//友元类的成员函数
void MyFriend::visit(Home *h) {
	cout << "友元类visit() 访问 " << h->livingRoom << endl;
	//访问私有成员
	cout << "友元类visit() 访问 " << h->bedRoom << endl;
}

//成员函数友元
void Person::access(Home *h) {
	cout << "成员函数access() 访问 " << h->livingRoom << endl;
	//访问私有成员
	cout << "成员函数access() 访问 " << h->bedRoom << endl;
}

//普通成员函数
void Person::access1(Home *h) {
	cout << "成员函数access1() 访问 " << h->livingRoom << endl;
	//并没有声明为友元成员函数,则不能访问私有成员
	//cout << "成员函数access1() 访问 " << h->bedRoom << endl;
}

//全局函数
void func(Home *h) {
	cout << "全局函数友元func() 访问 " << h->livingRoom << endl;
	//访问私有成员
	cout << "全局函数友元func() 访问 " << h->bedRoom << endl;
}

void test() {
	Home myHome;
	func(&myHome);

	MyFriend f;
	f.visit(&myHome);

	Person p;
	p.access(&myHome);
	p.access1(&myHome);
}

//main函数
int main() {
	cout << "hello" << endl;
	test();
	return 0;
}
```



### 4.5 运算符重载

运算符重载概念：对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的自定义数据类型

可通过全局函数重载或者成员函数重载, 选择哪一种跟情况而定

#### 4.5.1 加号运算符重载

作用：实现两个自定义数据类型相加的运算

```C++
class Person {
public:
	Person() {};
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
	//成员函数实现 + 号运算符重载
	Person operator+(const Person& p) {
		Person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}


public:
	int m_A;
	int m_B;
};

//全局函数实现 + 号运算符重载
//Person operator+(const Person& p1, const Person& p2) {
//	Person temp(0, 0);
//	temp.m_A = p1.m_A + p2.m_A;
//	temp.m_B = p1.m_B + p2.m_B;
//	return temp;
//}

//运算符重载 可以发生函数重载 
Person operator+(const Person& p2, int val)  
{
	Person temp;
	temp.m_A = p2.m_A + val;
	temp.m_B = p2.m_B + val;
	return temp;
}

void test() {

	Person p1(10, 10);
	Person p2(20, 20);

	//成员函数方式
	Person p3 = p2 + p1;  //相当于 p2.operaor+(p1)
	cout << "mA:" << p3.m_A << " mB:" << p3.m_B << endl;


	Person p4 = p3 + 10; //相当于 operator+(p3,10)
	cout << "mA:" << p4.m_A << " mB:" << p4.m_B << endl;

}

int main() {

	test();

	system("pause");

	return 0;
}
```

```C++
#include <iostream>
using namespace std;

class Person {
public:
	// constuctor
	Person() {};
	Person(int a, int b) :m_A(a), m_B(b) {};

	// + 号运算符重载(成员函数)
	//Person operator+(const Person &p);	

	// + 号运算符重载的函数重载版本(成员函数)
	Person operator+(int num);

	// getter
	int getM_A() const { return m_A; }	// 常函数
	int getM_B() const { return m_B; }	// 常函数
	// setter
	void setM_A(int a) { m_A = a; }
	void setM_B(int b) { m_B = b; }

private:
	int m_A;
	int m_B;
};

// + 号运算符重载(成员函数重载)
//Person Person::operator+(const Person &p) {
//	Person temp;
//	temp.m_A = p.m_A + this->m_A;
//	temp.m_B = p.m_B + this->m_B;
//	cout << "成员运算符函数重载" << endl;
//	return temp;
//}

Person Person::operator+(int num) {
	Person temp;
	temp.m_A = this->m_A + num;
	temp.m_B = this->m_B + num;
	return temp;
}

// + 号全局函数运算符重载
Person operator+(const Person &p1, const Person &p2) {
	Person temp;
	temp.setM_A(p1.getM_A() + p2.getM_A());
	temp.setM_B(p1.getM_B() + p2.getM_B());
	cout << "全局运算符函数重载" << endl;
	return temp;
}

void func() {
	Person p1(10, 10);
	Person p2(20, 20);

	Person p3 = p1 + p2;	// 等价于调用运算符重载函数
	//Person p3 = operator+(p1, p2);	//---全局函数
	cout << "p3.m_A = " << p3.getM_A() << endl;
	cout << "p3.m_B = " << p3.getM_B() << endl;

	Person p4 = p1 + 50;	// 等价于调用运算符重载
	//Person p4 = p1.operator+(50);		//---成员函数
	cout << "p4.m_A = " << p4.getM_A() << endl;
	cout << "p4.m_B = " << p4.getM_B() << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
```

> 总结1：对于内置的数据类型的表达式的的运算符是不可能改变的

> 总结2：不要滥用运算符重载



#### 4.5.2 左移运算符重载

作用：可以输出自定义数据类型



```C++
class Person {
	friend ostream& operator<<(ostream& out, Person& p);

public:

	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}

	//成员函数 实现不了  p << cout 不是我们想要的效果
	//void operator<<(Person& p){
	//}

private:
	int m_A;
	int m_B;
};

//全局函数实现左移重载
//ostream对象只能有一个
ostream& operator<<(ostream& out, Person& p) {
	out << "a:" << p.m_A << " b:" << p.m_B;
	return out;
}

void test() {

	Person p1(10, 20);

	cout << p1 << "hello world" << endl; //链式编程
}

int main() {

	test();

	system("pause");

	return 0;
}
```

```C++
#include <string>
#include <iostream>
using namespace std;

// 重载左移运算符 << 无法通过成员函数实现, 只能通过全局函数实现
class Person {
	friend ostream& operator<<(ostream &out, const Person &p);	// 友元全局函数, 访问私有属性
public:
	Person() : m_name(""), m_value(0) {}
	Person(string name, double value) : m_name(name), m_value(value) {}

private:
	string m_name;
	double m_value;
};

// << 左移运算符号重载
ostream& operator<<(ostream &out, const Person &p) {		// 需要返回 ostream& 的引用才能链式调用
	out << "{m_name = " << p.m_name << ", m_value = " << p.m_value << "}";
	return out;
}

void func() {
	Person p("圆周率", 3.14159);
	Person p2;
	cout << "输出: " << p << endl << p2 << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
```

> 总结：重载左移运算符配合友元可以实现输出自定义数据类型



#### 4.5.3 递增运算符重载

作用： 通过重载递增运算符，实现自己的整型数据



```C++

class MyInteger {

	friend ostream& operator<<(ostream& out, MyInteger myint);

public:
	MyInteger() {
		m_Num = 0;
	}
	//前置++
	MyInteger& operator++() {
		//先++
		m_Num++;
		//再返回
		return *this;
	}

	//后置++
	MyInteger operator++(int) {		// 后置++ 需要用到占位参数
		//先返回
		MyInteger temp = *this; //记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
		m_Num++;
		return temp;
	}

private:
	int m_Num;
};


ostream& operator<<(ostream& out, MyInteger myint) {
	out << myint.m_Num;
	return out;
}


//前置++ 先++ 再返回
void test01() {
	MyInteger myInt;
	cout << ++myInt << endl;
	cout << myInt << endl;
}

//后置++ 先返回 再++
void test02() {

	MyInteger myInt;
	cout << myInt++ << endl;
	cout << myInt << endl;
}

int main() {

	test01();
	//test02();

	system("pause");

	return 0;
}
```

> 总结： 前置递增返回引用，后置递增返回值

```C++
#include <iostream>
#include <string>
using namespace std;

class MyInteger {
	// 友元全局函数--运算符重载
	friend ostream& operator<<(ostream& cout, const MyInteger &integer);
public:
	MyInteger() : m_value(0) {}
	MyInteger(int value) : m_value(value) {}
	// 前置递减运算符重载
	MyInteger& operator--() {
		this->m_value++;	// 先++ 然后再返回
		return *this;
	}
	// 后置递减运算符重载
	MyInteger operator--(int) {
		MyInteger temp = *this;		//记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
		this->m_value++;
		return temp;
	}

private:
	int m_value;
};

// << 输出运算符重载
ostream& operator<<(ostream& cout, const MyInteger &integer) {
	cout << integer.m_value;
	return cout;
}

void func() {
	MyInteger num(20);
	cout << --num << endl;
	cout << num << endl;

	MyInteger num1(30);
	cout << num1-- << endl;
	cout << num1 << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
```



#### 4.5.4 赋值运算符重载



c++编译器至少给一个类添加4个函数

1. **默认构造函数(无参，函数体为空)**
2. **默认析构函数(无参，函数体为空)**
3. **默认拷贝构造函数，对属性进行值拷贝**
4. **赋值运算符 operator= 重载函数, 对属性进行值拷贝**



**注意**: 在重写赋值运算符号时. 一定要加上自我赋值检测: (不仅仅是为了效率, 更是为了正确性)

```C++		if (this == &p) {	
	// 赋值运算符重载 需要返回自身引用
	Person& operator=(const Person &p) {
		// 自我赋值检测, 必须要有这个自我赋值检测, 为了保证正确性, 而不是单纯为了效率
		if (this == &p) {	
			return *this;
		}
		// 释放原有得资源
		if (this->m_Age != nullptr){
			delete this->m_Age;
		}
		this->m_Age = new int(p.getM_Age());	// 深拷贝
		cout << "Person& operator=(const Person &p) is called." << endl;
		return *this;
	}
```

如果类中有属性指向堆区，做赋值操作时也会出现深浅拷贝问题

**示例：**

```C++
class Person
{
public:

	Person(int age)
	{
		//将年龄数据开辟到堆区
		m_Age = new int(age);
	}

	//重载赋值运算符 
	Person& operator=(Person &p)
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
		//编译器提供的代码是浅拷贝
		//m_Age = p.m_Age;

		//提供深拷贝 解决浅拷贝的问题
		m_Age = new int(*p.m_Age);

		//返回自身
		return *this;
	}
	~Person()
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
	}
	//年龄的指针
	int *m_Age;

};


void test01()
{
	Person p1(18);

	Person p2(20);

	Person p3(30);

	p3 = p2 = p1; //赋值操作

	cout << "p1的年龄为：" << *p1.m_Age << endl;

	cout << "p2的年龄为：" << *p2.m_Age << endl;

	cout << "p3的年龄为：" << *p3.m_Age << endl;
}

int main() {

	test01();

	//int a = 10;
	//int b = 20;
	//int c = 30;

	//c = b = a;
	//cout << "a = " << a << endl;
	//cout << "b = " << b << endl;
	//cout << "c = " << c << endl;

	system("pause");

	return 0;
}
```

```C++
#include <iostream>
#include <string>

using namespace std;

//c++编译器至少给一个类添加4个函数
//
//1. **默认构造函数(无参，函数体为空)**
//2. **默认析构函数(无参，函数体为空)**
//3. **默认拷贝构造函数，对属性进行值拷贝**
//4. **赋值运算符 operator=, 对属性进行值拷贝**

class Person
{
public:
	Person() : m_Age(nullptr) {}
	Person(int age)
	{
		//将年龄数据开辟到堆区
		m_Age = new int(age);
	}

	Person(const Person &p)
	{
		//将年龄数据开辟到堆区
		this->m_Age = new int(p.getM_Age());
		cout << "Person(const Person &p) is called." << endl;
	}

	// 赋值运算符重载 需要返回自身引用
	Person& operator=(const Person &p) {
        // 自我赋值检测, 必须要有这个自我赋值检测, 为了保证正确性, 而不是单纯为了效率
		if (this == &p) {	
			return *this;
		}
        
		if (this->m_Age != nullptr){
			delete this->m_Age;
		}
		this->m_Age = new int(p.getM_Age());	// 深拷贝
		cout << "Person& operator=(const Person &p) is called." << endl;
		return *this;
	}

	// 析构函数释放内存
	~Person() {
		if (this->m_Age != nullptr) {
			delete m_Age;						// 注意深浅拷贝问题, 重写拷贝构造和赋值运算重载
			m_Age = nullptr;
		}
	}

	// getter 
	int getM_Age() const { return *m_Age; }

private:
	int *m_Age;
};

void func() {
	Person p1(20);
	Person p2(30);
	Person p5;
	p5 = p2 = p1;		// 这是赋值操作, 调用的是赋值运算符重载函数
	cout << "p1 = " << p1.getM_Age() << endl;
	cout << "p2 = " << p2.getM_Age() << endl;

	Person p3 = p1;		// 这是初始化p3, 调用的是拷贝构造函数;
	Person p4(p2);		// 这也是初始化p4, 调用的是拷贝构造函数;
	cout << "p3 = " << p3.getM_Age() << endl;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
```



#### 4.5.5 关系运算符重载

**作用：**重载关系运算符，可以让两个自定义类型对象进行对比操作

**示例：**

```C++
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	};

	bool operator==(Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	string m_Name;
	int m_Age;
};

void test01()
{
	Person a("孙悟空", 18);
	Person b("孙悟空", 18);

	if (a == b)
	{
		cout << "a和b相等" << endl;
	}
	else
	{
		cout << "a和b不相等" << endl;
	}

	if (a != b)
	{
		cout << "a和b不相等" << endl;
	}
	else
	{
		cout << "a和b相等" << endl;
	}
}
int main() {
	test01();
	system("pause");
	return 0;
}
```



#### 4.5.6 函数调用运算符重载



* 函数调用运算符 ()  也可以重载
* 由于重载后使用的方式非常像函数的调用，因此称为仿函数
* 仿函数没有固定写法，非常灵活

**示例：**

```C++
class MyPrint
{
public:
	void operator()(string text)
	{
		cout << text << endl;
	}

};
void test01()
{
	//重载的（）操作符 也称为仿函数
	MyPrint myFunc;
	myFunc("hello world");
}

class MyAdd
{
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

void test02()
{
	MyAdd add;
	int ret = add(10, 10);
	cout << "ret = " << ret << endl;

	//匿名对象调用  MyAdd()为匿名对象, 本语句运行完就立即释放;
	cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl;
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}
```





### 4.6  继承

**继承是面向对象三大特性之一**

有些类与类之间存在特殊的关系，例如下图中：

![1544861202252](assets/1544861202252.png)

我们发现，定义这些类时，下级别的成员除了拥有上一级的共性，还有自己的特性。

这个时候我们就可以考虑利用继承的技术，减少重复代码



#### 4.6.1 继承的基本语法



例如我们看到很多网站中，都有公共的头部，公共的底部，甚至公共的左侧列表，只有中心内容不同

接下来我们分别利用普通写法和继承的写法来实现网页中的内容，看一下继承存在的意义以及好处

**普通实现：** 代码重复, 有很多冗余的代码.

```C++
//Java页面
class Java 
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
	void content()
	{
		cout << "JAVA学科视频" << endl;
	}
};
//Python页面
class Python
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
	void content()
	{
		cout << "Python学科视频" << endl;
	}
};
//C++页面
class CPP 
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
	void content()
	{
		cout << "C++学科视频" << endl;
	}
};

void test01()
{
	//Java页面
	cout << "Java下载视频页面如下： " << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "--------------------" << endl;

	//Python页面
	cout << "Python下载视频页面如下： " << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	cout << "--------------------" << endl;

	//C++页面
	cout << "C++下载视频页面如下： " << endl;
	CPP cp;
	cp.header();
	cp.footer();
	cp.left();
	cp.content();

}

int main() {

	test01();

	system("pause");

	return 0;
}
```



**继承实现：** 减少重复的代码, 代码复用性高

```C++
//公共页面
class BasePage
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}

	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}

};

//Java页面
class Java : public BasePage // 继承BasePage类
{
public:
	void content()
	{
		cout << "JAVA学科视频" << endl;
	}
};
//Python页面
class Python : public BasePage // 继承BasePage类
{
public:
	void content()
	{
		cout << "Python学科视频" << endl;
	}
};
//C++页面
class CPP : public BasePage // 继承BasePage类
{
public:
	void content()
	{
		cout << "C++学科视频" << endl;
	}
};

void test01()
{
	//Java页面
	cout << "Java下载视频页面如下： " << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "--------------------" << endl;

	//Python页面
	cout << "Python下载视频页面如下： " << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	cout << "--------------------" << endl;

	//C++页面
	cout << "C++下载视频页面如下： " << endl;
	CPP cp;
	cp.header();
	cp.footer();
	cp.left();
	cp.content();


}

int main() {

	test01();

	system("pause");

	return 0;
}
```



**总结：**

继承的好处：==可以减少重复的代码==

class A : public B; 

A 类称为子类 或 派生类

B 类称为父类 或 基类



**派生类中的成员，包含两大部分**：

一类是从基类继承过来的，一类是自己增加的成员。

从基类继承过过来的表现其共性，而新增的成员体现了其个性。



#### 4.6.2 继承方式

继承的语法：`class 子类 : 继承方式  父类`

**继承方式一共有三种：**

* 公共继承
* 保护继承
* 私有继承



（1） 公有继承(public)

公有继承的特点是基类的公有成员和保护成员作为派生类的成员时，它们都保持原有的状态，而基类的私有成员仍然是私有的，不能被这个派生类的[子类](https://so.csdn.net/so/search?q=子类&spm=1001.2101.3001.7020)所访问。

（2）私有继承(private)

私有继承的特点是基类的公有成员和保护成员都作为派生类的私有成员，并且不能被这个派生类的子类所访问。

（3）保护继承(protected)

保护继承的特点是基类的所有公有成员和保护成员都成为派生类的保护成员，并且只能被它的派生类成员函数或友元访问，基类的私有成员仍然是私有的。





![img](assets/clip_image002.png)

private能够对外部和子类保密，即除了成员所在的类本身可以访问之外，别的都不能直接访问。

protected能够对外部保密，但允许子类直接访问这些成员。

- 不管是哪种继承方式， 在派生类内部都可以访问基类的公有成员和保护成员 ， 基类的私有成员存在但是在子类中不可见（ 不能访问） 。
-  使用关键字class时默认的继承方式是private， 使用struct时默认的继承方式是public， 不过最好显式的写出继承方式。
-  在实际运用中一般使用都是public继承， 极少场景下才会使用protetced/private继承。

```C++
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
```

**示例：**

```C++
class Base1
{
public: 
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

//公共继承
class Son1 :public Base1
{
public:
	void func()
	{
		m_A; //可访问 public权限
		m_B; //可访问 protected权限
		//m_C; //不可访问
	}
};

void myClass()
{
	Son1 s1;
	s1.m_A; //其他类只能访问到公共权限
}

//保护继承
class Base2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son2:protected Base2
{
public:
	void func()
	{
		m_A; //可访问 protected权限
		m_B; //可访问 protected权限
		//m_C; //不可访问
	}
};
void myClass2()
{
	Son2 s;
	//s.m_A; //不可访问
}

//私有继承
class Base3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son3:private Base3
{
public:
	void func()
	{
		m_A; //可访问 private权限
		m_B; //可访问 private权限
		//m_C; //不可访问
	}
};
class GrandSon3 :public Son3
{
public:
	void func()
	{
		//Son3是私有继承，所以继承Son3的属性在GrandSon3中都无法访问到
		//m_A;
		//m_B;
		//m_C;
	}
};
```



#### 4.6.3 继承中的对象模型

**问题：**从父类继承过来的成员，哪些属于子类对象中？

父类中私有成员也是被子类继承下去了，只是由编译器给隐藏后访问不到

注意: 类中的静态成员不在类对象模型中

**示例：**

```C++
class Base
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C; //私有成员只是被隐藏了，但是还是会继承下去
    static int s_cout;		// 静态的成员不在类对象模型中
};
int Base1::s_cout = 0;	//静态属性类外初始化

//公共继承
class Son :public Base
{
public:
	int m_D;
};

void test01()
{
	cout << "sizeof Son = " << sizeof(Son) << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

```C++
#include <iostream>
#include <string>
using namespace std;

class Base1 {
public:
	int m_a;
protected:
	int m_b;
private:
	int m_c;
};

class Base2 {
private:
	int m_k;
	char m_cha;		// 注意内存对齐的问题
};

class Son : public Base1, protected Base2 {
private:
	int m_d;
};

int main()
{
	cout << "sizeof(Base) = " << sizeof(Base1) << endl;			// 12
	cout << "sizeof(Base) = " << sizeof(Base2) << endl;			// 8 内存对齐的原因
	cout << "sizeof(Son) = " << sizeof(Son) << endl;			// 24
	std::cout << "Hello World!\n";
}
```

![image-20220908225304501](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220908225304501.png)

利用工具查看：



![1545881904150](assets/1545881904150.png)



打开工具窗口后，定位到当前CPP文件的盘符

然后输入： `cl /d1 reportSingleClassLayout查看的类名   所属文件名`

效果如下图：

![1545882158050](assets/1545882158050.png)



> 结论： 父类中私有成员也是被子类继承下去了，只是由编译器给隐藏后访问不到

 

#### 4.6.4 继承中构造和析构顺序

子类继承父类后，当创建子类对象，也会调用父类的构造函数

问题：父类和子类的构造和析构顺序是谁先谁后？

继承中 先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反

**示例：**

```C++
class Base 
{
public:
	Base()
	{
		cout << "Base构造函数!" << endl;
	}
	~Base()
	{
		cout << "Base析构函数!" << endl;
	}
};

class Son : public Base
{
public:
	Son()
	{
		cout << "Son构造函数!" << endl;
	}
	~Son()
	{
		cout << "Son析构函数!" << endl;
	}

};


void test01()
{
	//继承中 先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反
	Son s;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



> 总结：继承中 先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反



#### 4.6.5 继承同名成员处理方式

问题：当子类与父类出现同名的成员，如何通过子类对象，访问到子类或父类中同名的数据呢？

* 访问子类同名成员   直接访问即可
* 访问父类同名成员   需要==加作用域==

**示例：**

```C++
class Base {
public:
	Base()
	{
		m_A = 100;
	}

	void func()	//同名函数
	{
		cout << "Base - func()调用" << endl;
	}

	void func(int a)
	{
		cout << "Base - func(int a)调用" << endl;
	}

public:
	int m_A;		//同名属性
};

class Son : public Base {
public:
	Son()
	{
		m_A = 200;
	}

	//当子类与父类拥有同名的成员函数，子类会隐藏父类中所有版本的同名成员函数
	//如果想访问父类中被隐藏的同名成员函数，需要加父类的作用域
	void func()	//同名函数
	{
		cout << "Son - func()调用" << endl;
	}
public:
	int m_A;		//同名属性
};

void test01()
{
	Son s;

	cout << "Son下的m_A = " << s.m_A << endl;
	cout << "Base下的m_A = " << s.Base::m_A << endl;

	s.func();
	s.Base::func();
	s.Base::func(10);	// 必须添加作用域, 因为父类中的所有同名函数被子类中的同名函数隐藏了

}
int main() {

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

总结：

1. 子类对象可以直接访问到子类中同名成员
2. 子类对象加作用域可以访问到父类同名成员
3. **当子类与父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数**



#### 4.6.6 继承同名静态成员处理方式

问题：继承中同名的静态成员在子类对象上如何进行访问？

静态成员和非静态成员出现同名，处理方式一致

- 访问子类同名成员   直接访问即可
- 访问父类同名成员   需要加作用域

**示例：**

```C++
#include <iostream>
using namespace std;
class Base {
public:
	static void func()
	{
		cout << "Base - static void func()" << endl;
	}
	static void func(int a)
	{
		cout << "Base - static void func(int a)" << endl;
	}

	static int m_A;
};

int Base::m_A = 100;		// 静态成员类外初始化

class Son : public Base {
public:
	static void func()
	{
		cout << "Son - static void func()" << endl;
	}
	static int m_A;
};

int Son::m_A = 200;

//同名成员属性
void test01()
{
	//通过对象访问
	cout << "通过对象访问： " << endl;
	Son s;
	cout << "Son  下 m_A = " << s.m_A << endl;
	cout << "Base 下 m_A = " << s.Base::m_A << endl;

	//通过类名访问
	cout << "通过类名访问： " << endl;
	cout << "Son  下 m_A = " << Son::m_A << endl;
	// 第一个::表示通过类名的方式访问, 第二个::表示访问父类作用域
	cout << "Base 下 m_A = " << Son::Base::m_A << endl;
}

//同名成员函数
void test02()
{
	//通过对象访问
	cout << "通过对象访问： " << endl;
	Son s;
	s.func();
	s.Base::func();

	cout << "通过类名访问： " << endl;
	Son::func();
	Son::Base::func();
	//出现同名，子类会隐藏掉父类中所有同名成员函数，需要加作作用域访问
	Son::Base::func(100);
}
int main() {

	//test01();
	test02();

	system("pause");

	return 0;
}
```

> 总结：同名静态成员处理方式和非静态处理方式一样，只不过有两种访问的方式（通过对象 和 通过类名）



#### 4.6.7 多继承语法

C++允许**一个类继承多个类**

语法：` class 子类 ：继承方式 父类1 ， 继承方式 父类2...`

多继承可能会引发父类中有同名成员出现，需要加作用域区分

**C++实际开发中不建议用多继承**



**示例：**

```C++
class Base1 {
public:
	Base1()
	{
		m_A = 100;
	}
public:
	int m_A;	// 同名
};

class Base2 {
public:
	Base2()
	{
		m_A = 200;  //开始是m_B 不会出问题，但是改为mA就会出现不明确
	}
public:
	int m_A; // 同名
};

//语法：class 子类：继承方式 父类1 ，继承方式 父类2 
class Son : public Base2, public Base1 
{
public:
	Son()
	{
		m_C = 300;
		m_D = 400;
	}
public:
	int m_C;
	int m_D;
};


//多继承容易产生成员同名的情况
//通过使用类名作用域可以区分调用哪一个基类的成员
void test01()
{
	Son s;
	cout << "sizeof Son = " << sizeof(s) << endl;
	cout << s.Base1::m_A << endl;	//需要添加作用域避免二义性
	cout << s.Base2::m_A << endl; 	//需要添加作用域避免二义性
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

> 总结： 多继承中如果父类中出现了同名情况，子类使用时候要加作用域



#### 4.6.8 菱形继承



**菱形继承概念：**

​	两个派生类继承同一个基类

​	又有某个类同时继承者两个派生类

​	这种继承被称为菱形继承，或者钻石继承



**典型的菱形继承案例：**



![IMG_256](assets/clip_image002.jpg)



**菱形继承问题：**



1.     羊继承了动物的数据，驼同样继承了动物的数据，当草泥马使用数据时，就会产生**二义性**。

2. 草泥马继承自动物的数据继承了两份，其实我们应该清楚，这份数据我们只需要一份就可以, **数据冗余**。

**示例1:**

```C++
// 动物类
class Animal {
public:
	int m_age; // 年龄
};

// 羊类
class Sheep : public Animal {};
// 驼类
class Camel : public Animal {};
// 羊驼类
class Alpaca : public Sheep, public Camel {};	// 菱形继承

void func() {
	Alpaca alpaca;
	//alpaca.m_age = 5;			// 在没有使用虚继承之前会出现二义性, 因为不知道m_age来自于那个父类;
	// 可以通过添加类名作用域区分
	alpaca.Camel::m_age = 10;
	alpaca.Sheep::m_age = 8;

	cout << "alpaca.Camel::m_age = " << alpaca.Camel::m_age << endl;	// 添加作用域区分		10
	cout << "alpaca.Sheep::m_age = " << alpaca.Sheep::m_age << endl;	// 添加作用域区分		8
	// 虽然解决了二义性的问题, 但是已经脱离了m_age本身的含义, 一个羊驼不可能有两个年龄
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
```

此时的Alpaca类的继承对象模型为下图:  **存在两份m_age, 造成二义性,并且造成空间浪费**

![image-20220909002730354](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909002730354.png)



使用虚继承实现:    **继承前加virtual关键字后，变为虚继承**

```C++
#include <iostream>
using namespace std;

//继承前加virtual关键字后，变为虚继承
//此时公共的父类Animal称为虚基类

// 动物类
class Animal {	// 此时为虚基类
public:
	int m_age; // 年龄
};

// 羊类
class Sheep :virtual public Animal {};		// virtual 虚继承
// 驼类
class Camel :virtual public Animal {};		// virtual 虚继承
// 羊驼类
class Alpaca : public Sheep, public Camel {};	// 菱形继承

void func() {
	Alpaca alpaca;
	//alpaca.m_age = 5;			// 在没有使用虚继承之前会出现二义性, 因为不知道m_age来自于那个父类;
	alpaca.m_age = 5;			// 使用虚继承后不会出现二义性
	// 可以通过添加类名作用域区分
	alpaca.Camel::m_age = 10;
	alpaca.Sheep::m_age = 88;
	
	cout << "alpaca.Camel::m_age = " << alpaca.Camel::m_age << endl; //88	// 添加作用域区分		
	cout << "alpaca.Sheep::m_age = " << alpaca.Sheep::m_age << endl; //88	// 添加作用域区分		
	cout << "alpaca.Sheep::m_age = " << alpaca.m_age << endl;		 //88  使用虚继承后不会出现二义性, 修改的也是同一份数据
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}

```

此时的Alpaca类的继承对象模型为下图:  **只会存在一份m_age, 修改任何一个都会改变**

![image-20220909004239126](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909004239126.png)

**虚拟继承**可以解决菱形继承的二义性和数据冗余的问题。需要注意的是，虚拟继承**不要**在其他地方去使用。

虚继承是一种机制，类通过虚继承指出它希望共享虚基类的状态。对给定的虚基类，无论该类在派生层次中作为虚基类出现多少次，只继承一个共享的基类子对象，共享基类子对象称为虚基类。虚基类用virtual声明继承关系就行了。

- **虚继承实现原理:**

虚继承底层实现原理与编译器相关，一般通过**虚基类指针**和**虚基类表**实现，每个虚继承的子类都有一个虚基类指针（占用一个指针的存储空间，4字节）和虚基类表（不占用类对象的存储空间）（需要强调的是，虚基类依旧会在子类里面存在拷贝，只是仅仅最多存在一份而已，并不是不在子类里面了）；当虚继承的子类被当做父类继承时，虚基类指针也会被继承。

实际上，vbptr指的是虚基类表指针（virtual base table pointer），该指针指向了一个虚基类表（virtual table），虚表中记录了虚基类与本类的偏移地址；通过偏移地址，这样就找到了虚基类成员，而虚继承也不用像普通多继承那样维持着公共基类（虚基类）的两份同样的拷贝，节省了存储空间。

![image-20220909010539343](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909010539343.png)



注意:

- 支持到基类的常规转换。也就是说即使基类是虚基类，也照样可以通过基类指针或引用来操纵派生类的对象。
- 虚继承只是解决了菱形继承中派生类多个基类内存拷贝的问题，并没有解决多重继承的二义性问题。



总结：

* 菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及毫无意义
* 利用虚继承可以解决菱形继承问题

建议: 我们应该**尽可能少地使用多继承**，只有在比较简单或者实在有必要时才使用，能用单一继承解决的问题就不要使用多继承。也正是这个原因，C++之后的很多面向对象的语言，例如Java、C#、PHP等，都不支持多继承。





### 4.7  多态

#### 4.7.1 多态的基本概念



**多态是C++面向对象三大特性之一**

多态分为两类

* 静态多态: 函数重载 和 运算符重载属于静态多态，复用函数名
* 动态多态: 派生类和虚函数实现运行时多态
  * 可以用父类的引用或者指针 指向子类对象`Dog dog; Animal &animal = dog;`




静态多态和动态多态区别：

* **静态多态的函数地址早绑定  -  编译阶段确定函数地址**
* **动态多态的函数地址晚绑定  -  运行阶段确定函数地址**



下面通过案例进行讲解多态

C++多态(polymorphism)是通过虚函数来实现的，虚函数允许子类重新定义成员函数，而子类重新定义父类的做法称为覆盖(override)，或者称为重写。

案例1:  正常的继承, 使用了同名函数 `void speak()` , 函数地址早绑定(编译时期就绑定了)

```C++
#include <iostream>				// 多态
using namespace std;

class Animal {
public:
	void speak() {		// 常规函数
		cout << "动物在说话!" << endl;
	}
};

class Dog : public Animal {
public:
	void speak() {
		cout << "小狗在说话" << endl;
	}
};

class Cat : public Animal {
public:
	void speak() {
		cout << "小猫在说话" << endl;
	}
};
//我们希望传入什么对象，那么就调用什么对象的函数
//如果函数地址在编译阶段就能确定，那么静态联编
//如果函数地址在运行阶段才能确定，就是动态联编
void doSpeak(Animal &animal) {	
	animal.speak();			// 在没有使用动态多态的时候, 函数地址早绑定
}

void func() {
	Dog dog;			// Animal &animal = dog
	doSpeak(dog);		// 输出: 动物在说话

	Cat cat;			// Animal &animal cat
	doSpeak(cat);		// 输出: 动物在说话
}

int main()
{
	func();
	cout << "sizeof(Animal) = " << sizeof(Animal) << endl;	// sizeof(Animal) = 1
	cout << "sizeof(Dog) = " << sizeof(Dog) << endl;		// sizeof(Dog) = 1
	cout << "sizeof(Cat) = " << sizeof(Cat) << endl;		// sizeof(Cat) = 1

    std::cout << "Hello World!\n";
}
```

![image-20220909155546309](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909155546309.png)

可以看到`doSpeak(Animal &animal)`函数执行的任然是Animal类中的函数, 并且类对象都只占1个字节. 通过vs工具查看此时的Dog类布局: 

![image-20220909164900166](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909164900166.png)



案例2: 使用 **virtual** 关键字实现动态多态, 函数地址晚绑定(运行时绑定)

```C++
#include <iostream>				// 多态
using namespace std;
//多态满足条件： 
//1、有继承关系
//2、子类重写父类中的虚函数
//多态使用：
//父类指针或引用指向子类对象

class Animal {
public:
    //speak函数就是虚函数
	//函数前面加上virtual关键字，变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
	virtual void speak() {		// 虚函数 仅仅添加一个 virtual 关键字
		cout << "动物在说话!" << endl;
	}
};

class Dog : public Animal {
public:
	void speak() override {		// 重写父类中的虚函数建议添加 override 关键字
		cout << "小狗在说话" << endl;
	}
};

class Cat : public Animal {
public:
	virtual void speak() override {		// 子类中重写的函数 virtual 关键字可加可不加
		cout << "小猫在说话" << endl;
	}
};
//我们希望传入什么对象，那么就调用什么对象的函数
//如果函数地址在编译阶段就能确定，那么静态联编
//如果函数地址在运行阶段才能确定，就是动态联编
void doSpeak(Animal &animal) {
	animal.speak();			// 在没有使用动态多态的时候, 函数地址早绑定
}

void func() {
	Dog dog;
	doSpeak(dog);		// 输出: 小狗在说话

	Cat cat;
	doSpeak(cat);		// 输出: 小猫在说话

	Animal animal;
	doSpeak(animal);	// 输出: 动物在说话
}

int main()
{
	func();
	cout << "sizeof(Animal) = " << sizeof(Animal) << endl;	// sizeof(Animal) = 4
	cout << "sizeof(Dog) = " << sizeof(Dog) << endl;		// sizeof(Dog) = 4
	cout << "sizeof(Cat) = " << sizeof(Cat) << endl;		// sizeof(Cat) = 4

    std::cout << "Hello World!\n";
}
```

![image-20220909160833070](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909160833070.png)

当在基类Animal中的 `virtual void speak(){}` 添加virtual关键字后就变为虚函数, 此时的`animal.speak();` 函数就是晚绑定(运行时确定函数地址),  ==并且此时的类对象模型的sizeof为4==, 不再是之前的1了. (多了虚函数表指针), 通过vs开发者工具查看Dog类布局:

![image-20220909165058984](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909165058984.png)

**总结：**

多态满足条件

* 有==继承==关系
* 父类中的函数需要是==virtual虚函数==
* ==子类重写父类中的虚函数== / 重写父类中的虚函数建议添加 **override** 关键字, 重写的函数virtual关键字可加可不加

多态使用条件

* ==父类指针或引用指向子类对象==

**重写：**函数返回值类型  函数名 参数列表 **完全一致**称为重写



- ### 虚函数的底层实现机制

**实现原理：虚函数表+虚表指针**

编译器处理虚函数的方法是：为每个类对象添加一个隐藏成员，隐藏成员中保存了一个指向函数地址数组的指针，称为虚函数表指针（vfptr），这种数组成为虚函数表（virtual function table, vftbl），即，**每个类使用一个虚函数表，每个类对象用一个虚表指针。**

举个例子：基类对象包含一个虚表指针，指向基类中所有虚函数的地址表。派生类对象也将包含一个虚表指针，指向派生类虚函数表。看下面两种情况：

- 如果派生类重写了基类的虚方法，**该派生类虚函数表将保存重写(覆盖)的虚函数的地址，而不是基类的虚函数地址。**

- 如果基类中的虚方法没有在派生类中重写，那么派生类将继承基类中的虚方法，而且派生类中虚函数表将保存基类中未被重写的虚函数的地址。注意，如果派生类中定义了新的虚方法，则该虚函数的地址也将被添加到派生类虚函数表中。



**编译器处理虚函数的方法是：**
给每个对象添加一个指针，存放了指向虚函数表的地址，虚函数表存储了为类对象进行声明的虚函数地址。比如基类对象包含一个指针，该指针指向基类所有虚函数的地址表，派生类对象将包含一个指向独立地址表的指针，如果派生类提供了虚函数的新定义，该虚函数表将保存新函数的地址，如果派生类没有重新定义虚函数，该虚函数表将保存函数原始版本的地址。如果派生类定义了新的虚函数，则该函数的地址将被添加到虚函数表中，注意虚函数无论多少个都只需要在对象中添加一个虚函数表的地址。

调用虚函数时，程序将查看存储在对象中的虚函数表地址，转向相应的虚函数表，使用类声明中定义的第几个虚函数，程序就使用数组的第几个函数地址，并执行该函数。

**使用虚函数后的变化：**
（1） 对象将增加一个存储地址的空间（32位系统为4字节，64位为8字节）。
（2） 每个类编译器都创建一个虚函数地址表
（3） 对每个函数调用都需要增加在表中查找地址的操作。

**虚函数的注意事项**

总结前面的内容
（1） 基类方法中声明了方法为虚后，该方法在基类派生类中是虚的。
（2） 若使用指向对象的引用或指针调用虚方法，程序将根据对象类型来调用方法，而不是指针的类型。
（3）如果定义的类被用作基类，则应将那些要在派生类中重新定义的类方法声明为虚。
构造函数不能为虚函数。
基类的析构函数应该为虚函数。
友元函数不能为虚，因为友元函数不是类成员，只有类成员才能是虚函数。
如果派生类没有重定义函数，则会使用基类版本。
重新定义继承的方法若和基类的方法不同（协变除外），会将基类方法隐藏；如果基类声明方法被重载，则派生类也需要对重载的方法重新定义，否则调用的还是基类的方法。

![image-20220909173625784](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220909173625784.png)



#### 4.7.2 多态案例一-计算器类



案例描述：

分别利用普通写法和多态技术，设计实现两个操作数进行运算的计算器类



多态的优点：

* 代码组织结构清晰
* 可读性强
* 利于前期和后期的扩展以及维护



**普通实现示例：**

```C++
//普通实现
class Calculator {
public:
	int getResult(string oper)
	{
		if (oper == "+") {
			return m_Num1 + m_Num2;
		}
		else if (oper == "-") {
			return m_Num1 - m_Num2;
		}
		else if (oper == "*") {
			return m_Num1 * m_Num2;
		}
		//如果要提供新的运算，需要修改源码
	}
public:
	int m_Num1;
	int m_Num2;
};

void test01()
{
	//普通实现测试
	Calculator c;
	c.m_Num1 = 10;
	c.m_Num2 = 10;
	cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.getResult("+") << endl;

	cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.getResult("-") << endl;

	cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.getResult("*") << endl;
}
```

**多态实现示例:**

```C++
//多态实现
//抽象计算器类
//多态优点：代码组织结构清晰，可读性强，利于前期和后期的扩展以及维护
class AbstractCalculator
{
public :

	virtual int getResult()
	{
		return 0;
	}

	int m_Num1;
	int m_Num2;
};

//加法计算器
class AddCalculator :public AbstractCalculator
{
public:
	int getResult()
	{
		return m_Num1 + m_Num2;
	}
};

//减法计算器
class SubCalculator :public AbstractCalculator
{
public:
	int getResult()
	{
		return m_Num1 - m_Num2;
	}
};

//乘法计算器
class MulCalculator :public AbstractCalculator
{
public:
	int getResult()
	{
		return m_Num1 * m_Num2;
	}
};

void test02()
{
	//创建加法计算器
	AbstractCalculator *abc = new AddCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;
	delete abc;  //用完了记得销毁

	//创建减法计算器
	abc = new SubCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->getResult() << endl;
	delete abc;  

	//创建乘法计算器
	abc = new MulCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->getResult() << endl;
	delete abc;
}

int main() {
	//test01();
	test02();
	system("pause");
	return 0;
}
```

> 总结：C++开发提倡利用多态设计程序架构，因为多态优点很多
>
> 多态优点：代码组织结构清晰，可读性强，利于前期和后期的扩展以及维护.......

















#### 4.7.3 纯虚函数和抽象类



在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容

因此可以将虚函数改为**纯虚函数**

纯虚函数语法：`virtual 返回值类型 函数名 （参数列表）= 0 ;`, 不能省略virtual关键字.

当类中有了纯虚函数，这个类也称为==抽象类==



**抽象类特点**：

 * 无法实例化对象
 * 子类必须重写抽象类中的纯虚函数，否则也属于抽象类



**示例：**

```C++
class Base
{
public:
	//纯虚函数
	//类中只要有一个纯虚函数就称为抽象类
	//抽象类无法实例化对象
	//子类必须重写父类中的纯虚函数，否则也属于抽象类
	virtual void func() = 0;   // 纯虚函数
};

class Son :public Base
{
public:
	virtual void func() override
	{
		cout << "func调用" << endl;
	};
};

void test01()
{
	Base * base = NULL;
	//base = new Base; // 错误，抽象类无法实例化对象
	base = new Son;
	base->func();
	delete base;//记得销毁
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

```C++
#include <iostream>
using namespace std;

class Animal {	// 抽象类: 只要类中有纯虚函数, 该类就是一个抽象类
public:
	virtual void speak() = 0;		// 纯虚函数, 子类必须实现该纯虚函数, 否则子类依然是抽象类
};

class Cat :public Animal {
	virtual void speak() override // 重写父类的函数最好加上 override 关键字
	{		
		cout << "猫在说话!!!" << endl;
	}
};

class Dog :public Animal {
	//virtual void speak() override {		// 重写父类的函数最好加上 override 关键字
	//	cout << "狗在说话!!!" << endl;
	//}
};

void func() {
	//Animal animal;  //		抽象类无法实例化对象
	//Dog dog;	// Dog类没有重写 speak() 纯虚函数, 所以也是抽象类, 无法实例化对象
	Animal * animal = new Cat();
	animal->speak();
	delete animal;
}

int main()
{
	func();
	std::cout << "Hello World!\n";
}
```



#### 4.7.4 多态案例二-制作饮品

**案例描述：**

制作饮品的大致流程为：煮水 -  冲泡 - 倒入杯中 - 加入辅料

利用多态技术实现本案例，提供抽象制作饮品基类，提供子类制作咖啡和茶叶

![1545985945198](assets/1545985945198.png)

**示例：**

```C++
// 45多态案例2-制作饮品.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
using namespace std;

//抽象制作饮品
class AbstractDrinking {
public:
	//烧水
	virtual void Boil() = 0;
	//冲泡
	virtual void Brew() = 0;
	//倒入杯中
	virtual void PourInCup() = 0;
	//加入辅料
	virtual void PutSomething() = 0;
	//规定流程
	void makeDrink() {
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};

class Coffee : public AbstractDrinking
{
private:
	//烧水
	virtual void Boil() override {		
		cout << "煮农夫山泉水" << endl;
	}
	//冲泡
	virtual void Brew() override {
		cout << "冲泡咖啡" << endl;
	}
	//倒入杯中
	virtual void PourInCup() override {
		cout << "倒入咖啡杯中" << endl;
	}
	//加入辅料
	virtual void PutSomething() override {
		cout << "添加猫屎" << endl;
	}
};

class Tea :public AbstractDrinking
{
private:
	//烧水
	virtual void Boil() override {	// 默认为私有
		cout << "煮开水" << endl;
	}
	//冲泡
	virtual void Brew() override {
		cout << "冲泡茶叶" << endl;
	}
	//倒入杯中
	virtual void PourInCup() override {
		cout << "倒入保温杯中" << endl;
	}
	//加入辅料
	virtual void PutSomething() override {
		cout << "添加枸杞" << endl;
	}
};

void doWork(AbstractDrinking * drink) {
	drink->makeDrink();
	delete drink;
}

int main()
{
	doWork(new Tea);
	cout << "======================" << endl;
	doWork(new Coffee);
	std::cout << "Hello World!\n";
}
```



#### 4.7.5 虚析构和纯虚析构



==**多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码**==

解决方式：将父类中的析构函数改为**虚析构**或者**纯虚析构**

虚析构和纯虚析构共性：

* 可以解决父类指针释放子类对象
* 都需要有具体的函数实现

虚析构和纯虚析构区别：

* 如果是纯虚析构，该类属于抽象类，无法实例化对象



虚析构语法：

`virtual ~类名(){}`

纯虚析构语法：

` virtual ~类名() = 0;`

`类名::~类名(){}`



**案例1: 存在内存泄漏问题, 也还有double free问题:**

```C++
#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
	Animal()
	{
		cout << "Animal 父类构造函数调用" << endl;
	}

	~Animal() {
		cout << "Animal 父类析构函数调用" << endl;
	}

	// 纯虚函数
	virtual void speak() = 0;
};

class Cat :public Animal {
public:
	Cat(string name) : m_name(new string(name))	// 初始化列表
	{
		cout << "Cat 子类构造函数调用" << endl;
	}

	~Cat() {
		if (m_name != nullptr) {
			delete m_name;	//释放资源
			m_name = nullptr;
		}
		cout << "Cat 子类析构函数调用" << endl;
	}

	virtual void speak() override
	{
		cout << *m_name << "猫在说话!" << endl;
	}

private:
	string *m_name;
};

void doWork(Animal * animal) {
	animal->speak();
	delete animal;		// 存在内存泄漏, 无法释放子类对象
}

void func() {
	doWork(new Cat("TOM"));	// 父类指针指向子类对象
}

int main()
{
	func();
}
```

![image-20220910220333804](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220910220333804.png)



**案例2: 使用虚析构函数或纯虚析构, 能正确释放资源.**

```C++
#include <iostream>
#include <string>
using namespace std;

class Animal {
public:
	Animal()
	{
		cout << "Animal 父类构造函数调用" << endl;
	}

	//virtual ~Animal() {	// 虚析构函数
	//	cout << "Animal 父类析构函数调用" << endl;
	//}

	virtual ~Animal() = 0; // 纯虚函数, 当有纯虚函数时, 该类为抽象类, 无法实例化对象

	// 纯虚函数
	virtual void speak() = 0;
};

Animal::~Animal() {
	cout << "Animal 父类析构函数调用" << endl;
}


class Cat :public Animal {
public:
	Cat(string name) : m_name(new string(name))	// 初始化列表
	{
		cout << "Cat 子类构造函数调用" << endl;
	}

	~Cat() {	// 析构函数中释放资源, 此时需要注意 拷贝构造函数 和 赋值运算符重载 问题
		if (m_name != nullptr) {
			delete m_name;	//释放资源
			m_name = nullptr;
		}
		cout << "Cat 子类析构函数调用" << endl;
	}

	// 重写拷贝构造函数
	Cat(const Cat &cat) {
		this->m_name = new string(*(cat.m_name));	// 深拷贝;
	}

	// 重写赋值运算符重载
	Cat& operator=(const Cat &cat) {		// 必须返回引用
		if (this->m_name != nullptr) {
			delete this->m_name;
		}
		this->m_name = new string(*(cat.m_name));	// 使用深拷贝
		return *this;	// 返回自身的引用
	}

	virtual void speak() override
	{
		cout << *m_name << "猫在说话!" << endl;
	}

private:
	string *m_name;
};

void doWork(Animal * animal) {
	animal->speak();
	delete animal;
}

void func() {
	doWork(new Cat("TOM"));	// 父类指针指向子类对象
}

int main()
{
	func();
}
```

![image-20220911094705591](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220911094705591.png)



**示例：**

```C++
class Animal {
public:

	Animal()
	{
		cout << "Animal 构造函数调用！" << endl;
	}
	virtual void Speak() = 0;

	//析构函数加上virtual关键字，变成虚析构函数
	//virtual ~Animal()
	//{
	//	cout << "Animal虚析构函数调用！" << endl;
	//}


	virtual ~Animal() = 0;
};

Animal::~Animal()
{
	cout << "Animal 纯虚析构函数调用！" << endl;
}

//和包含普通纯虚函数的类一样，包含了纯虚析构函数的类也是一个抽象类。不能够被实例化。

class Cat : public Animal {
public:
	Cat(string name)
	{
		cout << "Cat构造函数调用！" << endl;
		m_Name = new string(name);
	}
	virtual void Speak()
	{
		cout << *m_Name <<  "小猫在说话!" << endl;
	}
	~Cat()
	{
		cout << "Cat析构函数调用!" << endl;
		if (this->m_Name != NULL) {
			delete m_Name;
			m_Name = NULL;
		}
	}

public:
	string *m_Name;
};

void test01()
{
	Animal *animal = new Cat("Tom");
	animal->Speak();

	//通过父类指针去释放，会导致子类对象可能清理不干净，造成内存泄漏
	//怎么解决？给基类增加一个虚析构函数
	//虚析构函数就是用来解决通过父类指针释放子类对象
	delete animal;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

​	1. 虚析构或纯虚析构就是用来解决通过父类指针释放子类对象

​	2. 如果子类中没有堆区数据，可以不写为虚析构或纯虚析构

​	3. 拥有纯虚析构函数的类也属于抽象类





#### 4.7.6 多态案例三-电脑组装

**案例描述：**

电脑主要组成部件为 CPU（用于计算），显卡（用于显示），内存条（用于存储）

将每个零件封装出抽象基类，并且提供不同的厂商生产不同的零件，例如Intel厂商和Lenovo厂商

创建电脑类提供让电脑工作的函数，并且调用每个零件工作的接口

测试时组装三台不同的电脑进行工作



**示例：**

```C++
#include<iostream>
using namespace std;

//抽象CPU类
class CPU
{
public:
	//抽象的计算函数
	virtual void calculate() = 0;
};

//抽象显卡类
class VideoCard
{
public:
	//抽象的显示函数
	virtual void display() = 0;
};

//抽象内存条类
class Memory
{
public:
	//抽象的存储函数
	virtual void storage() = 0;
};

//电脑类
class Computer
{
public:
	Computer(CPU * cpu, VideoCard * vc, Memory * mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}

	//提供工作的函数
	void work()
	{
		//让零件工作起来，调用接口
		m_cpu->calculate();

		m_vc->display();

		m_mem->storage();
	}

	//提供析构函数 释放3个电脑零件
	~Computer()
	{

		//释放CPU零件
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}

		//释放显卡零件
		if (m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}

		//释放内存条零件
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}

private:

	CPU * m_cpu; //CPU的零件指针
	VideoCard * m_vc; //显卡零件指针
	Memory * m_mem; //内存条零件指针
};

//具体厂商
//Intel厂商
class IntelCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Intel的CPU开始计算了！" << endl;
	}
};

class IntelVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Intel的显卡开始显示了！" << endl;
	}
};

class IntelMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel的内存条开始存储了！" << endl;
	}
};

//Lenovo厂商
class LenovoCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Lenovo的CPU开始计算了！" << endl;
	}
};

class LenovoVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了！" << endl;
	}
};

class LenovoMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Lenovo的内存条开始存储了！" << endl;
	}
};


void test01()
{
	//第一台电脑零件
	CPU * intelCpu = new IntelCPU;
	VideoCard * intelCard = new IntelVideoCard;
	Memory * intelMem = new IntelMemory;

	cout << "第一台电脑开始工作：" << endl;
	//创建第一台电脑
	Computer * computer1 = new Computer(intelCpu, intelCard, intelMem);
	computer1->work();
	delete computer1;

	cout << "-----------------------" << endl;
	cout << "第二台电脑开始工作：" << endl;
	//第二台电脑组装
	Computer * computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);;
	computer2->work();
	delete computer2;

	cout << "-----------------------" << endl;
	cout << "第三台电脑开始工作：" << endl;
	//第三台电脑组装
	Computer * computer3 = new Computer(new LenovoCPU, new IntelVideoCard, new LenovoMemory);;
	computer3->work();
	delete computer3;

}
```

**案例2:**

```C++
#include <iostream>
#include <string>
using namespace std;

// 处理器抽象类
class CPU {
public:
	virtual void calculate() = 0; // 纯虚函数
	virtual ~CPU() {}		// 虚析构函数
};

// 显卡抽象类
class DisplayCard {
public:
	virtual void display() = 0; // 纯虚函数
	virtual ~DisplayCard() {}		// 虚析构函数

};

// 内存抽象类
class Memory {
public:
	virtual void storage() = 0; // 纯虚函数
	virtual ~Memory() {		// 虚析构函数
		cout << "Memory 析构函数调用" << endl;
	}
};

// 联想电脑
class LenovoComputer {
public:
	LenovoComputer(CPU *cpu, DisplayCard *dispayCard, Memory *memory) : // 构造函数
		m_cpu(cpu),
		m_display(dispayCard),
		m_memory(memory)
	{

	}

	~LenovoComputer() {	// 析构函数, 释放资源
		if (m_cpu != nullptr) {
			delete m_cpu;
			m_cpu = nullptr;
		}
		if (m_display != nullptr) {
			delete m_display;
			m_display = nullptr;
		}
		if (m_memory != nullptr) {
			delete m_memory;
			m_memory = nullptr;
		}
		cout << "LenovoComputer 析构函数调用" << endl;
	}

	void doWork() {
		m_cpu->calculate();	// 计算
		m_display->display(); // 显示	
		m_memory->storage(); // 存储
	}

private:
	CPU *m_cpu;
	DisplayCard *m_display;
	Memory *m_memory;
};


// Intel的CPU
class IntelCPU : public CPU {
	virtual void calculate() override
	{
		cout << "Intel CPU 正在计算" << endl;
	}
};

// AMD的CPU
class AMDCPU : public CPU {
	virtual void calculate() override
	{
		cout << "AMD CPU 正在计算" << endl;
	}
};

// NVIDIA的显卡
class NvidiaDisplayCard :public DisplayCard {
	virtual void display() override
	{
		cout << "NVIDIA 显卡正在计算" << endl;
	}
};

// AMD的显卡
class AMDDisplayCard :public DisplayCard {
	virtual void display() override
	{
		cout << "AMD 显卡正在计算" << endl;
	}
};

// Samsung的内存条
class SamsungMemory :public Memory {
	virtual void storage() override
	{
		cout << "samsung 的内存条正在存储" << endl;
	}
	~SamsungMemory() {
		cout << "SamsungMemory 析构函数调用" << endl;
	}
};

void func() {
	cout << "-------------------------第一台电脑工作:" << endl;
	// 创建Lenovo电脑
	LenovoComputer lenovo(new IntelCPU(), new NvidiaDisplayCard(), new SamsungMemory);
	lenovo.doWork();		// 栈变量, 函数结束会自动释放

	cout << "-------------------------第二台电脑工作:" << endl;
	LenovoComputer * computer = new LenovoComputer(new AMDCPU, new AMDDisplayCard, new SamsungMemory);
	computer->doWork();
	delete computer;	// 手动释放: 如果不释放则造成内存泄漏

	cout << "-------------------------第三台电脑工作:" << endl;
	CPU *cpu = new IntelCPU();
	DisplayCard *display = new AMDDisplayCard();
	Memory * memory = new SamsungMemory;
	LenovoComputer *computer2 = new LenovoComputer(cpu, display, memory);
	computer2->doWork();
	delete computer2;	// 手动释放: 如果不释放则造成内存泄漏

	cout << "--------------函数结束-----------------" << endl;
}

int main()
{
	func();
}
```

![image-20220911112852146](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220911112852146.png)



## 5 文件操作



程序运行时产生的数据都属于临时数据，程序一旦运行结束都会被释放

通过**文件可以将数据持久化**

C++中对文件操作需要包含头文件 ==&lt; fstream &gt;==



文件类型分为两种：

1. **文本文件**     -  文件以文本的**ASCII码**形式存储在计算机中
2. **二进制文件** -  文件以文本的**二进制**形式存储在计算机中，用户一般不能直接读懂它们



操作文件的三大类:

1. ofstream：写操作
2. ifstream： 读操作
3. fstream ： 读写操作



### 5.1文本文件

#### 5.1.1写文件

   写文件步骤如下：

1. 包含头文件   

     \#include <fstream\>

2. 创建流对象  

   ofstream ofs;

3. 打开文件

   ofs.open("文件路径",打开方式);

4. 写数据

   ofs << "写入的数据";

5. 关闭文件

   ofs.close();

   

文件打开方式：

| 打开方式        | 解释                       |
| --------------- | -------------------------- |
| **ios::in**     | 为读文件而打开文件         |
| **ios::out**    | 为写文件而打开文件         |
| **ios::ate**    | 初始位置：文件尾           |
| **ios::app**    | 追加方式写文件             |
| **ios::trunc**  | 如果文件存在先删除，再创建 |
| **ios::binary** | 二进制方式                 |

**注意：** 文件打开方式可以配合使用，利用|操作符

**例如：**用二进制方式写文件 `ios::binary |  ios:: out`



**示例：**

```C++
#include <fstream>

void test01()
{
	ofstream ofs;	// 创建输出流对象
	ofs.open("test.txt", ios::out);	// 打开文件

    // 写内容
	ofs << "姓名：张三" << endl;
	ofs << "性别：男" << endl;
	ofs << "年龄：18" << endl;

	ofs.close();	// 关闭流
}

int main() {
	test01();
	system("pause");
	return 0;
}
```

总结：

* 文件操作必须包含头文件` #include <fstream>`
* 读文件可以利用 `ofstream ` ，或者`fstream`类
* 打开文件`open()`时候需要指定操作文件的路径path，以及打开方式
* 利用 << 可以向文件中写数据
* 操作完毕，要关闭文件`close()`



#### 5.1.2读文件

读文件与写文件步骤相似，但是读取方式相对于比较多

读文件步骤如下：

1. 包含头文件   

     \#include <fstream\>

2. 创建流对象  

   ifstream ifs;

3. 打开文件并判断文件是否打开成功

   ifs.open("文件路径",打开方式);

4. 读数据

   四种方式读取

5. 关闭文件

   ifs.close();



**示例：**

```C++
#include <fstream>
#include <string>
void test01()
{
	ifstream ifs;
	ifs.open("test.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//第一种方式
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}

	//第二种
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

	//第三种
	//string buf;
	//while (getline(ifs, buf))
	//{
	//	cout << buf << endl;
	//}

	char c;
	while ((c = ifs.get()) != EOF)
	{
		cout << c;
	}

	ifs.close();


}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

- 读文件可以利用 ifstream  ，或者fstream类
- 利用is_open函数可以判断文件是否打开成功
- close 关闭文件 















### 5.2 二进制文件

以二进制的方式对文件进行读写操作

打开方式要指定为 ==ios::binary==



#### 5.2.1 写文件

二进制方式写文件主要利用流对象调用成员函数write

函数原型 ：`ostream& write(const char * buffer,int len);`

参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数



**示例：**

```C++
#include <fstream>
#include <string>

class Person
{
public:
	char m_Name[64];
	int m_Age;
};

//二进制文件  写文件
void test01()
{
	//1、包含头文件

	//2、创建输出流对象
	ofstream ofs("person.txt", ios::out | ios::binary);
	
	//3、打开文件
	//ofs.open("person.txt", ios::out | ios::binary);

	Person p = {"张三"  , 18};

	//4、写文件， 需要强制转换为 const char *
	ofs.write((const char *)&p, sizeof(p));

	//5、关闭文件
	ofs.close();
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

* 文件输出流对象 可以通过write函数，以二进制方式写数据



#### 5.2.2 读文件

二进制方式读文件主要利用流对象调用成员函数read

函数原型：`istream& read(char *buffer,int len);`

参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数

示例：

```C++
#include <fstream>
#include <string>

class Person
{
public:
	char m_Name[64];
	int m_Age;
};

void test01()
{
	ifstream ifs("person.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}

	Person p;
	ifs.read((char *)&p, sizeof(p));

	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

- 文件输入流对象 可以通过read函数，以二进制方式读数据

```C++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Birthday {
public:
	Birthday(int y, int m, int d) :year(y), mouth(m), day(d) {}
	int year;
	int mouth;
	int day;
};

class Person {
	friend ostream& operator<<(ostream &out, const Person &person); // 友元
public:
	char m_name[64];
	//string m_name;		// 二进制读写不能使用string, 会读取文件时导致程序崩溃
	int m_age;
	Birthday *birthday;		// 指正变量也能正常转换
};

ostream& operator<<(ostream &out, const Person &person) {
	out << "{" << person.m_name << ","
		<< person.m_age << ",{"
		<< person.birthday->year
		<< "," << person.birthday->mouth
		<< "," << person.birthday->day << "}}";
	return out;
}

void writeFile() {
	ofstream ofs;
	ofs.open("Person.dat", ios::out | ios::binary);
	Person person = {
		"张三丰【】",
		50,
		nullptr
	};
	person.birthday = new Birthday(1999, 10, 23);
	// 注意: 需要将对应的地址强转换为 const char *
	ofs.write((const char *)&person, sizeof(Person));	// 二进制的方式写文件
	ofs.close();
}

void test() {
	ifstream ifs;
	ifs.open("Person.dat", ios::in | ios::binary);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	// 读取数据
	Person person;
	// 注意: 需要将对应的地址强转换为 char *
	ifs.read((char *)&person, sizeof(Person));
	cout << person.m_name << endl;
	cout << person.m_age << endl;
	cout << person.birthday->year << endl;
	cout << person.birthday->mouth << endl;
	cout << person.birthday->day << endl;
	cout << person << endl;
}

int main()
{
	writeFile();
	test();
	std::cout << "Hello World!\n";
}
```

![image-20220911193557400](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20220911193557400.png)
