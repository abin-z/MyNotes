#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <numeric>

#include "util.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/// @brief 选择排序
/// @param nums
void selectSort(std::vector<int> &nums)
{
    // 选出最大值
    int size = nums.size();
    for (int i = size - 1; i > 0; --i)
    {
        int max = i; // 假设最后一个元素是最大值
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] > nums[max])
            {
                max = j;
            }
        }
        using std::swap;
        swap(nums[max], nums[i]);
    }
}

/// @brief 冒泡排序
/// @param nums
void bubbleSort(std::vector<int> &nums)
{
    // 先排序最大的
    int size = nums.size();
    for (int i = size - 1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                using std::swap;
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

/// @brief 插入排序
/// @param nums
void insertSort(std::vector<int> &nums)
{
    // 类似排序扑克牌
    int size = nums.size();
    for (int i = 1; i < size; ++i)
    {
        int item = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > item)
        {
            nums[j + 1] = nums[j]; // 往后移动
            --j;
        }
        nums[j + 1] = item;
    }
}

/// @brief 插入排序
/// @param nums
void insertSort2(std::vector<int> &nums)
{
    // 类似排序扑克牌
    int size = nums.size();
    for (int i = 1; i < size; ++i)
    {
        int item = nums[i];
        int j;
        for (j = i - 1; j >= 0; --j)
        {
            if (nums[j] > item)
            {
                nums[j + 1] = nums[j];
            }
            else
            {
                break;
            }
        }
        nums[j + 1] = item;
    }
}

/// 归并操作
void merge(std::vector<int> &nums, int left, int mid, int right)
{
    // 拷贝对应的数据
    std::vector<int> leftArr(nums.cbegin() + left, nums.cbegin() + mid);
    std::vector<int> rightArr(nums.cbegin() + mid, nums.cbegin() + right);
    // 在左右子序列末尾添加哨兵
    leftArr.push_back(std::numeric_limits<int>::max());
    rightArr.push_back(std::numeric_limits<int>::max());
    int i = 0, j = 0, k = left;
    while (k != right)
    {
        if (leftArr[i] < rightArr[j])
        {
            nums[k++] = leftArr[i++];
        }
        else
        {
            nums[k++] = rightArr[j++];
        }
    }
}

void mergeSort(std::vector<int> &nums, int left, int right)
{
    if (left >= right - 1) // 只有一个元素时返回
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid, right);
    merge(nums, left, mid, right);
}

/// @brief 归并排序
/// @param nums
void mergeSort(std::vector<int> &nums)
{
    // 使用左闭右开区间
    mergeSort(nums, 0, nums.size());
}

int partition(std::vector<int> &nums, int left, int right)
{
    // 采用随机选取pivot
    std::default_random_engine e(right);
    std::uniform_int_distribution<int> d(left, right);
    int pivot = d(e);
    // 先将pivot移动至最后
    using std::swap;
    swap(nums[pivot], nums[right]);
    int i = left;
    for (int j = left; j < right; ++j)
    {
        if (nums[j] <= nums[right])
        {
            swap(nums[i], nums[j]);
            ++i;
        }
    }
    // 将pivot移动至原来的位置
    swap(nums[right], nums[i]);
    return i;
}

void quickSort(std::vector<int> &nums, int left, int right)
{
    // 使用闭区间
    if (left >= right)
    {
        return;
    }
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

/// @brief 快速排序
/// @param nums
void quickSort(std::vector<int> &nums)
{
    // 使用左闭右闭区间
    quickSort(nums, 0, nums.size() - 1);
}

/// @brief 二分查找
/// @param nums
/// @param target
/// @return
int binarySearch(const std::vector<int> &nums, int target)
{
    int size = nums.size();
    int left = -1, right = size, mid = 0; // 使用左开右开区间(left, right)
    while (left != right - 1)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    int index = nums[right] == target ? right : -1;
    return index;
}

int main()
{
    auto datas = util::randomData(10, 99, 30);
    cout << "\noriginData = ";
    util::printData(datas);

    // 选择排序
    auto data01 = datas;
    selectSort(data01);
    cout << "\nselectSort = ";
    util::printData(data01);

    // 冒泡排序
    auto data02 = datas;
    bubbleSort(data02);
    cout << "\nbubbleSort = ";
    util::printData(data02);

    // 插入排序
    auto data03 = datas;
    insertSort(data03);
    cout << "\ninsertSort = ";
    util::printData(data03);

    // 归并排序
    auto data04 = datas;
    mergeSort(data04);
    cout << "\nmergeSort =  ";
    util::printData(data04);

    // 快速排序
    auto data05 = datas;
    quickSort(data05);
    cout << "\nquickSort =  ";
    util::printData(data05);

    // 查找
    int target = 26;
    int index = binarySearch(data05, target);
    if (index != -1)
    {
        cout << "find index = " << index;
    }
    else
    {
        cout << "not find";
    }
}
