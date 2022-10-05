#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;

/*
* 公司今天招聘了10个员工（ABCDEFGHIJ），10名员工进入公司之后，需要指派员工在那个部门工作
* 员工信息有: 姓名  工资组成；部门分为：策划、美术、研发
* 随机给10名员工分配部门和工资
* 通过multimap进行信息的插入  key(部门编号) value(员工)
* 分部门显示员工信息
*/

constexpr auto CEHUA = 1;
constexpr auto MEISHU = 2;
constexpr auto YANFA = 3;

class Worker {
public:
	string m_name;
	int m_salary;
};

void creatWorker(vector<Worker> &v) {
	string wStr = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++)
	{
		Worker w;
		w.m_name = "员工";
		w.m_name += wStr[i];
		w.m_salary = rand() % 10000 + 10000;		// 使用随机数 10000-19999
		v.push_back(w);		// 插入数据
	}
}

void setGroup(const vector<Worker> &vtr, multimap<int, Worker> &mMap) {
	for (vector<Worker>::const_iterator cit = vtr.cbegin(); cit != vtr.cend(); ++cit) {
		int deptNo = rand() % 3 + 1;		// 随机部门号 1 2 3
		mMap.insert(make_pair(deptNo, *cit));
	}
}


void showWorkerByDeptNo(const multimap<int, Worker> &mMap) {
	cout << "======策划部门:" << endl;
	// 查找策划部门
	multimap<int, Worker>::const_iterator cit = mMap.find(CEHUA);
	int count = mMap.count(CEHUA);
	for (int i = 0; cit != mMap.cend() && i < count; ++cit, ++i) {
		cout << "    部门编号: " << cit->first << " 姓名: " << cit->second.m_name << " 工资: " << cit->second.m_salary << endl;
	}

	cout << "======美术部门:" << endl;
	// 查找美术部门
	cit = mMap.find(MEISHU);
	count = mMap.count(MEISHU);
	for (int i = 0; cit != mMap.cend() && i < count; ++cit, ++i) {
		cout << "    部门编号: " << cit->first << " 姓名: " << cit->second.m_name << " 工资: " << cit->second.m_salary << endl;
	}

	cout << "======研发部门:" << endl;
	// 查找研发部门
	cit = mMap.find(YANFA);
	count = mMap.count(YANFA);
	for (int i = 0; cit != mMap.cend() && i < count; ++cit, ++i) {
		cout << "    部门编号: " << cit->first << " 姓名: " << cit->second.m_name << " 工资: " << cit->second.m_salary << endl;
	}

}

void test() {
	vector<Worker> vWorker;
	creatWorker(vWorker);
	//for (vector<Worker>::const_iterator cit = vWorker.cbegin(); cit != vWorker.cend(); ++cit) {
	//	cout << cit->m_name << ", " << cit->m_salary << endl;
	//}
	multimap<int, Worker> mWorker;
	setGroup(vWorker, mWorker);
	showWorkerByDeptNo(mWorker);
}

int main()
{
	// 随机数种子
	srand((unsigned int)time(nullptr));
	test();
	return 0;
}



