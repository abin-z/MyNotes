#include <iostream>
#include <random>
#include <vector>

namespace util
{
    template <typename T>
    void printData(const T &data)
    {
        for (const auto &item : data)
        {
            std::cout << item << ' ';
        }
    }

    std::vector<int> randomData(int low, int hgt, int count)
    {
        static std::default_random_engine e(count * 13 % 317); // 随机数引擎
        static std::uniform_int_distribution<int> d(low, hgt); // 随机数分布, 左闭右闭区间
        e.discard(20);
        std::vector<int> arr;
        for (int i = 0; i < count; ++i)
        {
            arr.push_back(d(e));
        }
        return arr;
    }
}