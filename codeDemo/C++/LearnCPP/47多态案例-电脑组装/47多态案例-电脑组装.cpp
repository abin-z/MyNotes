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
