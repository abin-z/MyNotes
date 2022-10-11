#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void test() {
	srand((unsigned int)time(nullptr));
	vector<int> v;
	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	random_shuffle(v.begin(), v.end());
	for (vector<int>::const_iterator cit = v.cbegin(); cit != v.cend(); ++cit)
	{
		cout << *cit << " ";
	}
	cout << endl;
	reverse(v.begin(), v.end());
	for (vector<int>::const_iterator cit = v.cbegin(); cit != v.cend(); ++cit)
	{
		cout << *cit << " ";
	}
	cout << endl;
}

int main()
{
	test();
    std::cout << "Hello World!\n";
}