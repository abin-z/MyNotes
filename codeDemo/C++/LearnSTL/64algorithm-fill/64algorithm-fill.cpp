#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;

void printInt(int val) {
	cout << val << " ";
}

void test() {
	vector<int> v;

	v.resize(10);
	for_each(v.begin(), v.end() ,printInt);

	cout << endl;
	fill(v.begin(), v.end(), 10);
	for_each(v.begin(), v.end(), printInt);
}


int main()
{
	test();
    std::cout << "Hello World!\n";
}