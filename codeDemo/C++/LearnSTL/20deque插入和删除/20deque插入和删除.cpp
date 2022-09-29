#include <iostream>
#include <deque>

using namespace std;

/*
两端插入操作：

- `push_back(elem);`          //在容器尾部添加一个数据
- `push_front(elem);`        //在容器头部插入一个数据
- `pop_back();`                   //删除容器最后一个数据
- `pop_front();`                 //删除容器第一个数据

指定位置操作：
* `insert(pos,elem);`         //在pos位置插入一个elem元素的拷贝，返回新数据的位置。
* `insert(pos,n,elem);`     //在pos位置插入n个elem数据，无返回值。
* `insert(pos,beg,end);`    //在pos位置插入[beg,end)区间的数据，无返回值。
* `clear();`                           //清空容器的所有数据
* `erase(beg,end);`             //删除[beg,end)区间的数据，返回下一个数据的位置。
* `erase(pos);`                    //删除pos位置的数据，返回下一个数据的位置。
*/

void printDeque(deque<int> deq) {
	for (deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

void test() {
	deque<int> d1;
	cout << d1.empty() << endl;

	d1.push_back(100);
	d1.push_back(200);
	d1.push_back(300);
	d1.pop_front();
	d1.push_front(222);
	d1.pop_back();
	cout << d1.size() << endl;
	//d1.clear();
	d1.insert(d1.begin(), 6969);
	d1.insert(d1.begin(), 3, 888);
	d1.insert(d1.end(), d1.begin(), d1.end());
	cout << d1.size() << endl;
	d1.erase(d1.begin() + 2);
	//d1.erase(d1.end());	// 会崩溃 d1.end() 指向的是最后一个元素的下一个位置,非法访问
	//d1.erase(d1.begin(), d1.end());
	printDeque(d1);

}


int main()
{
	test();
	std::cout << "Hello World!\n";
}
