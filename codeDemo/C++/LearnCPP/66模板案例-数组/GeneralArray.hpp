#pragma once
#include <iostream>
using namespace std;

//案例描述:  实现一个通用的数组类，要求如下：
//
//	* 可以对内置数据类型以及自定义数据类型的数据进行存储			// 使用模板
//	* 将数组中的数据存储到堆区								// new
//	* 构造函数中可以传入数组的容量							// capacity
//	* 提供对应的拷贝构造函数以及operator = 防止浅拷贝问题		// 深拷贝
//	* 提供尾插法和尾删法对数组中的数据进行增加和删除			// 添加数据
//	* 可以通过下标的方式访问数组中的元素						// 重载运算符
//	* 可以获取数组中当前元素个数和数组的容量					// Getter

template <class T>
class GeneralArray {
public:
	// 构造函数
	GeneralArray(const int capacity) {
		this->m_capacity = capacity;
		this->m_size = 0;
		this->m_dataArray = new T[this->m_capacity]; // 在堆区开辟空间
	}

	// 拷贝构造函数 - 深拷贝
	GeneralArray(const GeneralArray &arr) {
		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		this->m_dataArray = new T[arr.m_capacity];	// 深拷贝
		// 拷贝数据
		for (int i = 0; i < arr.m_size; ++i)
		{
			this->m_dataArray[i] = arr.m_dataArray[i];
		}
	}

	// 重写赋值运算符 - 深拷贝
	GeneralArray& operator=(const GeneralArray &arr) {
		if (this == &arr) {	// 自我赋值检测, 一定要加上这个
			return *this;
		}

		if (this->m_dataArray != nullptr) {	// 如果this本身存在数据则删除释放
			delete[] this->m_dataArray;
			this->m_capacity = 0;
			this->m_size = 0;
		}
		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		this->m_dataArray = new T[arr.m_capacity];	// 深拷贝
		// 将数据进行逐一拷贝
		for (int i = 0; i < arr.m_size; ++i) {	// 只需要拷贝其中的数据就行
			this->m_dataArray[i] = arr.m_dataArray[i];
		}
		return *this;	// 返回本身的引用
	}

	// 通过下标访问数据 - 重载[]运算符号
	T& operator[](int index) {
		return this->m_dataArray[index];	// 返回T类型的引用, T[1] = 100; 可能作为左值
	}

	// 尾插法
	bool push_back(const T &item) {
		// 判断是否有足够容量, 当容量已满则插入失败
		if (m_size >= m_capacity) {
			return false;
		}
		// 在尾部插入数据
		m_dataArray[m_size] = item;
		m_size++;
		return true;
	}

	// 尾删法
	bool pop_back() {
		// 判断是否还有数据
		if (m_size == 0) {
			return false;
		}
		m_size--;		// 逻辑删除
		return true;
	}

	// 获取数据量,数据个数
	int getSize() const {
		return m_size;
	}

	// 获取容量
	int getCapacity() const {
		return m_capacity;
	}

	//析构函数
	~GeneralArray() {
		if (this->m_dataArray != nullptr) {
			delete[] m_dataArray;	// 释放堆区数组
			m_dataArray = nullptr;	// 防止野指针
			this->m_capacity = 0;
			this->m_size = 0;
		}
	}

private:
	// 真实数组,真正存储数据的地方
	T * m_dataArray;	// 指针, 需要注意深拷贝问题
	// 数据容量
	int m_capacity;
	// 元素个数(数据量)
	int m_size;
};
