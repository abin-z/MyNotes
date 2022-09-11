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
	~AbstractDrinking() {
		cout << "AbstractDrinking 析构函数调用" << endl;
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
public:
	~Coffee() {
		cout << "Coffee 析构函数调用" << endl;
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

public:
	~Tea() {
		cout << "Tea 析构函数调用" << endl;
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
