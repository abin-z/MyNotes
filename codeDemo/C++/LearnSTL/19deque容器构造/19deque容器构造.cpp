#include <iostream>
#include <deque>
using namespace std;

/*
* `deque<T>` deqT;                      //默认构造形式
* `deque(beg, end);`                  //构造函数将[beg, end)区间中的元素拷贝给本身。
* `deque(n, elem);`                    //构造函数将n个elem拷贝给本身。
* `deque(const deque &deq);`   //拷贝构造函数
*/

void printDeque(const deque<int> &deq) {
	// 使用只读迭代器const_iterator
	for (deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}


void test() {
	deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i + 100);
	}
	printDeque(d1);

	deque<int> d2(d1.begin(), d1.end());
	printDeque(d2);

	deque<int> d3(5,999);
	printDeque(d3);

	deque<int> d4(d3);
	printDeque(d4);


	/*
	* `deque& operator=(const deque &deq); `         //重载等号操作符
	* `assign(beg, end);`                            //将[beg, end)区间中的数据拷贝赋值给本身。
	* `assign(n, elem);`                             //将n个elem拷贝赋值给本身。
	*/

	deque<int> d5;
	d5 = d4;
	printDeque(d5);

	deque<int> d6;
	d6.assign(6, 8888);
	printDeque(d6);

	deque<int> d7;
	d7.assign(d6.begin(), d6.end());
	printDeque(d7);
}


int main()
{
	test();
	std::cout << "Hello World!\n";
}
