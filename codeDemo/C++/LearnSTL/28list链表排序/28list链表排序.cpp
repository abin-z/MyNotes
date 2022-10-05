#include <iostream>
#include <list>
using namespace std;

void printList(const list<int>& L) {

	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

bool myCompare(int val1, int val2)
{
	// 降序, 就让第一个数 大于 第二个数
	return val1 > val2;
}

//反转和排序
void test01()
{
	list<int> L;
	L.push_back(90);
	L.push_back(30);
	L.push_back(20);
	L.push_back(70);
	printList(L);

	//反转容器的元素
	L.reverse();
	printList(L);

	//排序
	L.sort(); //默认的排序规则 从小到大
	printList(L);

	// 所有不支持随机访问迭代器的容器,不可以使用标准算法
	//sort(L.begin(), L.end());    // 错误, 这个会报错
	// 不支持随机访问迭代器的容器,内部会提供一些对应的算法

	L.sort();			// 默认从小到大
	L.sort(myCompare); //指定规则，从大到小, 函数指针
	printList(L);
}


int main()
{
	test01();
    std::cout << "Hello World!\n";
}