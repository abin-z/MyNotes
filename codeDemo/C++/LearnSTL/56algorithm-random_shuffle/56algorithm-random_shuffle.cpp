#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

void printInt(int val) {
	cout << val << " ";
}

void test() {
	vector<int> v;

	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for_each(v.cbegin(), v.cend(), printInt);
	cout << endl;
	random_shuffle(v.begin(), v.end());
	for_each(v.cbegin(), v.cend(), printInt);
}

int main()
{
	srand((unsigned int)time(nullptr));
	test();
    std::cout << "Hello World!\n";
}
