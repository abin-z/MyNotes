#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
- `insert(elem); `           //在容器中插入元素。
- `clear(); `                    //清除所有元素
- `erase(pos); `              //删除pos迭代器所指的元素，返回下一个元素的迭代器。
- `erase(beg, end); `    //删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器。
- `erase(key); `            //删除容器中值为key的元素。
*/

void printMap(const map<int, string> &m) {
	for (map<int, string>::const_iterator it = m.cbegin(); it != m.cend(); it++) {
		cout << "{" << it->first << "," << it->second << "}" << endl;
	}
}


void test() {
	// 创建map容器
	map<int, string> m;

	// 第一种
	m.insert(pair<int, string>(10, string("xiaomi")));

	// 第二种
	m.insert(make_pair(20, "huawei"));

	// 第三种
	m.insert(map<int, string>::value_type(3, "apple"));

	// 第四种 - 不建议这么写
	m[40] = "oppo";
	
	// 不建议使用[key]直接访问key中的value, 
	// 因为如果没有这个key,会插入一个对组, value为默认值
	cout << m[60] << endl;

	printMap(m);

	// 删除
	m.erase(--m.end());			// 删除最后一个元素
	printMap(m);

	// 直接删除key
	m.erase(20);				
	printMap(m);

	// 删除区间
	m.erase(m.begin(),m.end());
	printMap(m);

	// 清空容器
	m.clear();
}

int main()
{
	test();
	std::cout << "Hello World!\n";
}

