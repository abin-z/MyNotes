#pragma once
#include <iostream>
using namespace std;

//��������:  ʵ��һ��ͨ�õ������࣬Ҫ�����£�
//
//	* ���Զ��������������Լ��Զ����������͵����ݽ��д洢			// ʹ��ģ��
//	* �������е����ݴ洢������								// new
//	* ���캯���п��Դ������������							// capacity
//	* �ṩ��Ӧ�Ŀ������캯���Լ�operator = ��ֹǳ��������		// ���
//	* �ṩβ�巨��βɾ���������е����ݽ������Ӻ�ɾ��			// �������
//	* ����ͨ���±�ķ�ʽ���������е�Ԫ��						// ���������
//	* ���Ի�ȡ�����е�ǰԪ�ظ��������������					// Getter

template <class T>
class GeneralArray {
public:
	// ���캯��
	GeneralArray(const int capacity) {
		this->m_capacity = capacity;
		this->m_size = 0;
		this->m_dataArray = new T[this->m_capacity]; // �ڶ������ٿռ�
	}

	// �������캯�� - ���
	GeneralArray(const GeneralArray &arr) {
		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		this->m_dataArray = new T[arr.m_capacity];	// ���
		// ��������
		for (int i = 0; i < arr.m_size; ++i)
		{
			this->m_dataArray[i] = arr.m_dataArray[i];
		}
	}

	// ��д��ֵ����� - ���
	GeneralArray& operator=(const GeneralArray &arr) {
		if (this == &arr) {	// ���Ҹ�ֵ���, һ��Ҫ�������
			return *this;
		}

		if (this->m_dataArray != nullptr) {	// ���this�������������ɾ���ͷ�
			delete[] this->m_dataArray;
			this->m_capacity = 0;
			this->m_size = 0;
		}
		this->m_capacity = arr.m_capacity;
		this->m_size = arr.m_size;
		this->m_dataArray = new T[arr.m_capacity];	// ���
		// �����ݽ�����һ����
		for (int i = 0; i < arr.m_size; ++i) {	// ֻ��Ҫ�������е����ݾ���
			this->m_dataArray[i] = arr.m_dataArray[i];
		}
		return *this;	// ���ر��������
	}

	// ͨ���±�������� - ����[]�������
	T& operator[](int index) {
		return this->m_dataArray[index];	// ����T���͵�����, T[1] = 100; ������Ϊ��ֵ
	}

	// β�巨
	bool push_back(const T &item) {
		// �ж��Ƿ����㹻����, ���������������ʧ��
		if (m_size >= m_capacity) {
			return false;
		}
		// ��β����������
		m_dataArray[m_size] = item;
		m_size++;
		return true;
	}

	// βɾ��
	bool pop_back() {
		// �ж��Ƿ�������
		if (m_size == 0) {
			return false;
		}
		m_size--;		// �߼�ɾ��
		return true;
	}

	// ��ȡ������,���ݸ���
	int getSize() const {
		return m_size;
	}

	// ��ȡ����
	int getCapacity() const {
		return m_capacity;
	}

	//��������
	~GeneralArray() {
		if (this->m_dataArray != nullptr) {
			delete[] m_dataArray;	// �ͷŶ�������
			m_dataArray = nullptr;	// ��ֹҰָ��
			this->m_capacity = 0;
			this->m_size = 0;
		}
	}

private:
	// ��ʵ����,�����洢���ݵĵط�
	T * m_dataArray;	// ָ��, ��Ҫע���������
	// ��������
	int m_capacity;
	// Ԫ�ظ���(������)
	int m_size;
};
