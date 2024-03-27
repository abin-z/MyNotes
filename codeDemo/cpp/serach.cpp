#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include <chrono>

#include "tools.cpp"

using namespace std;

int partition(vector<int> &nums, int left, int right)
{
    // 随机选取pivot
    default_random_engine e(right * 13);
    uniform_int_distribution<int> d(left, right);
    int pivot = d(e);
    using std::swap;
    swap(nums[pivot], nums[right]);
    int i = left;
    for (int j = left; j < right; ++j)
    {
        if (nums[j] <= nums[right])
        {
            swap(nums[j], nums[i]);
            ++i;
        }
    }
    swap(nums[i], nums[right]);
    return i;
}

void quickSort(vector<int> &nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

// 快速排序
void quickSort(vector<int> &nums)
{
    // 使用闭区间
    quickSort(nums, 0, nums.size() - 1);
}

void merge(vector<int> &nums, int left, int mid, int right)
{
    // 拷贝左右子序列
    vector<int> leftNums(nums.cbegin() + left, nums.cbegin() + mid);
    vector<int> rightNums(nums.cbegin() + mid, nums.cbegin() + right);
    leftNums.push_back(numeric_limits<int>::max());
    rightNums.push_back(numeric_limits<int>::max());
    int i = 0, j = 0, k = left;
    while (k != right)
    {
        if (leftNums[i] < rightNums[j])
        {
            nums[k++] = leftNums[i++];
        }
        else
        {
            nums[k++] = rightNums[j++];
        }
    }
}

void mergeSort(vector<int> &nums, int left, int right)
{
    if (right - left <= 1)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid, right);
    merge(nums, left, mid, right);
}

// 归并排序
void mergeSort(vector<int> &nums)
{
    // 使用左闭右开区间
    mergeSort(nums, 0, nums.size());
}

int lowerBound(vector<int> &nums, int target)
{
    // 使用开区间写法
    int left = -1, right = nums.size(), mid;
    while (left + 1 != right)
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
    return right;
}

auto test() -> void
{
    cout << "hello world" << endl;
    auto nums = randomDatas(0, 99, 60);
    auto nums2 = nums;
    printDatas(nums);
    quickSort(nums);
    cout << "\nquick sorted = ";
    printDatas(nums);
    mergeSort(nums2);
    cout << "\nmerge sorted = ";
    printDatas(nums2);
    int index = lowerBound(nums, 12);
    cout << "\nlowerBound(nums, 12) = " << index << endl;
}

int main()
{
    test();
}