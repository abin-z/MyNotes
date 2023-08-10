#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <string>
#include <hash_fun.h>

using namespace std;

void test01();

int main()
{
    std::cout << "hello" << endl;
    test01();
}

class Student
{
    Student() = default;
    Student(const string &name, const int age) : name(name),
                                                 age(age){};

public:
    string name;
    int age;
};

struct StudentHash
{
    size_t operator()(const Student &s) const
    {
        return hash_val(s.name, s.age));
    }
};

void test01()
{
    unordered_set<Student, StudentHash> sset;
    sset.insert(Student("zhagnsan", 16));
}