#include <iostream>
#include <vector>
#include <random>

template <typename T>
void printDatas(T &datas)
{
    // 检查数据量,超过100个元素则不打印数据
    if (datas.size() > 100)
    {
        std::cout << "data size > 100, no print";
        return;
    }
    for (auto &item : datas)
    {
        std::cout << item << " ";
    }
}

std::vector<int> randomDatas(int low, int hgt, int count)
{
    static std::default_random_engine e(count * 13 % 317); // 随机数引擎
    static std::uniform_int_distribution<int> d(low, hgt); // 随机数分布
    e.discard(20);
    std::vector<int> arr;
    for (int i = 0; i < count; ++i)
    {
        arr.push_back(d(e));
    }
    return arr;
}