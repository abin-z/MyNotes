#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <numeric>
#include <set>

using namespace std;

/// @brief 选择排序算法
/// @param
/// @return
vector<int> selectSort(vector<int> vec) // 值传递
{
    // 先排最大的
    for (int i = vec.size() - 1; i > 0; --i)
    {
        // 找出未排序的最大值
        int maxIndex = i;
        for (int j = 0; j < i; ++j)
        {
            if (vec[j] > vec[maxIndex])
            {
                maxIndex = j;
            }
        }
        // 交换元素
        // int temp = vec[i];
        // vec[i] = vec[maxIndex];
        // vec[maxIndex] = temp;
        using std::swap;
        swap(vec[i], vec[maxIndex]);
    }
    return vec;
}

/// @brief 冒泡排序
/// @param nums
/// @return
vector<int> bubbleSort(vector<int> nums) // 值传递
{
    bool swapped = false;
    for (int i = nums.size() - 1; i > 0; --i)
    {
        swapped = false;
        for (int j = 0; j < i; ++j)
        {
            swapped = false;
            if (nums[j] > nums[j + 1])
            {
                using std::swap;
                swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) // 若未交换则说明数组已经有序,提前退出
        {
            break;
        }
    }
    return nums;
}

/// @brief 插入排序
/// @param nums
/// @return
vector<int> insertSort(vector<int> nums) // 值传递
{
    // 从第二个元素开始
    for (int i = 1; i < nums.size(); ++i)
    {
        /// for循环版本, i指针不动
        // for (int j = i - 1; j >= 0; --j)
        // {
        //     if (nums[j] > nums[j + 1])
        //     {
        //         using std::swap;
        //         swap(nums[j], nums[j + 1]);
        //     }
        //     else
        //     {
        //         break;
        //     }
        // }

        /// while循环版本1
        // int j = i - 1;
        // while (j >= 0 && nums[j] > nums[j + 1])
        // {
        //     using std::swap;
        //     swap(nums[j], nums[j + 1]);
        //     --j;
        // }

        /// while循环版本2
        int j = i - 1;
        int newCard = nums[i];
        while (j >= 0 && nums[j] > newCard)
        {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = newCard;
    }
    return nums;
}

auto test() -> void
{
    vector<int> arr{60, 30, 20, 30, 40, 10, 50, 60, 100, 20, 10, 30, 40, 20, 10};
    cout << "origin arr = ";
    for (auto item : arr)
    {
        cout << item << " ";
    }
    cout << endl
         << "seletctSrot arr = ";
    for (auto item : selectSort(arr))
    {
        cout << item << " ";
    }
    cout << endl
         << "bubbleSort arr = ";
    for (auto item : bubbleSort(arr))
    {
        cout << item << " ";
    }
    cout << endl
         << "insertSort arr = ";
    for (auto item : insertSort(arr))
    {
        cout << item << " ";
    }
}

int main()
{
    std::cout << "hello world" << std::endl;
    test();
    return 0;
}