#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <list>
#include <numeric>
#include <set>
#include <limits>
#include <random>

using namespace std;

/// @brief 计算n的阶乘,使用迭代方式的写法
/// @param n
/// @return
int func01(int n)
{
    int res = 1;
    while (n != 0)
    {
        res = res * n;
        --n;
    }
    return res;
}

/// @brief 计算n的阶乘，递归写法
/// @param n
/// @return
int func02(int n)
{
    if (n == 0)
    {
        return 1;
    }
    int temp = func02(n - 1);
    return temp * n;
}

/// @brief 斐波那契数列的第n个元素迭代版本(下标是从0开始的)
/// @param i
/// @return
int fibonacci01(int n)
{
    int arr[n + 1]{0};
    arr[0] = 0;
    arr[1] = 1;
    for (int i = 2; i < n + 1; ++i)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n];
}

/// @brief 斐波那契数列迭代版本
/// @param i
/// @return
int fibonacci02(int n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    int temp01 = fibonacci02(n - 1);
    int temp02 = fibonacci02(n - 2);
    return temp01 + temp02;
}

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

/// @brief 二分查找-闭区间写法
/// @param nums
/// @param target
/// @return
int binarySearch01(vector<int> &nums, int target)
{
    // 使用闭区间写法
    int left = 0, right = nums.size() - 1, mid = 0;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (target < nums[mid])
        {
            right = mid - 1;
        }
        else if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/// @brief 二分查找 - 左闭右开写法
/// @param nums
/// @param target
/// @return
int binarySearch02(vector<int> &nums, int target)
{
    // 左闭右开写法
    int left = 0, right = nums.size(), mid = 0;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (target < nums[mid])
        {
            right = mid; // 右开区间
        }
        else if (nums[mid] < target)
        {
            left = mid + 1; // 左闭区间
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/// @brief 二分查找 - 开区间写法
/// @param nums
/// @param target
/// @return
int binarySearch03(vector<int> &nums, int target)
{
    // 左开右开写法
    int left = -1, right = nums.size(), mid = 0;
    while (left + 1 != right)
    {
        mid = left + (right - left) / 2;
        if (target < nums[mid])
        {
            right = mid; // 开区间
        }
        else if (nums[mid] < target)
        {
            left = mid; // 开区间
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

/// @brief 二分查找开区间写法
/// @param nums
/// @param target
/// @return
int lowerBound01(vector<int> &nums, int target)
{
    // 使用开区间(left, right)写法
    int left = -1, right = nums.size(), mid;
    while (left + 1 != right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid; // 缩小区间至(mid, right)
        }
        else
        {
            right = mid; // 缩小区间至(left, mid)
        }
    }
    return right; // 返回right; 退出循环时: left始终指向红区,right始终指向蓝区
}

/// @brief 二分查找闭区间写法
/// @param nums
/// @param target
/// @return
int lowerBound02(vector<int> &nums, int target)
{
    // 使用闭区间写法
    int left = 0, right = nums.size() - 1, mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] < target)
        {
            left = mid + 1; // 缩小区间至[mid + 1, right]
        }
        else
        {
            right = mid - 1; // 缩小区间至[left, mid - 1]
        }
    }
    return left; // 此时返回left,退出循环时: left - 1始终指向红区,right + 1始终指向蓝区
}

/// @brief 二分查找左闭右开区间写法
/// @param nums
/// @param target
/// @return
int lowerBound03(vector<int> &nums, int target)
{
    // 使用左闭右开区间[left, right)写法
    int left = 0, right = nums.size(), mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (nums[mid] < target) // 区间不为空
        {
            left = mid + 1; // 缩小区间至[mid + 1, right)
        }
        else
        {
            right = mid; // 缩小区间至[left, mid)
        }
    }
    // return left;  // 返回 left和right均可
    return right; // 返回 left和right均可
}

void merge(vector<int> &nums, int left, int mid, int right)
{
    // 复制左右两部分序列
    vector<int> leftVtr(nums.cbegin() + left, nums.cbegin() + mid);
    vector<int> rightVtr(nums.cbegin() + mid, nums.cbegin() + right);
    // 在左右子序列末尾添加哨兵
    leftVtr.push_back(numeric_limits<int>::max());
    rightVtr.push_back(numeric_limits<int>::max());
    // 合并操作
    int i = 0, j = 0, k = left;
    while (k != right)
    {
        if (leftVtr[i] <= rightVtr[j])
        {
            nums[k++] = leftVtr[i++];
        }
        else
        {
            nums[k++] = rightVtr[j++];
        }
    }
}

// 归并排序
void mergeSort(vector<int> &nums, int left, int right)
{
    // 使用左闭右开区间[left, right)
    if (right - left <= 1)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid, right);
    merge(nums, left, mid, right);
}
void mergeSort(vector<int> &nums)
{
    mergeSort(nums, 0, nums.size()); // 左闭右开区间
}

int partition(vector<int> &nums, int left, int right)
{
    // 挑选pivot,采用随机数方式
    default_random_engine e(left * 13); // 随机数引擎, 设置种子
    uniform_int_distribution<uint32_t> d(left, right);
    int pivot = d(e);
    using std::swap;
    swap(nums[pivot], nums[right]); // 将pivot移动至最后面
    int i = left;
    for (int j = left; j < right; ++j)
    {
        if (nums[j] <= nums[right])
        {
            swap(nums[i], nums[j]);
            ++i;
        }
    }
    swap(nums[right], nums[i]);
    return i;
}

// 快速排序算法
void quickSort(vector<int> &nums, int left, int right)
{
    // 使用左闭右闭区间写法 [left, right]
    if (left >= right)
    {
        return;
    }
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}
void quickSort(vector<int> &nums)
{
    quickSort(nums, 0, nums.size() - 1); // 使用左闭右闭区间
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

    // 计算n的阶乘
    cout << endl
         << "n! = " << func01(6) << endl
         << "n! = " << func02(6) << endl;
    // 斐波那契数列第n项
    cout << "fibonacci01 = " << fibonacci01(22) << endl
         << "fibonacci02 = " << fibonacci02(22) << endl;
    // 测试二分查找, 没有重复元素
    vector<int> nums{10, 20, 30, 40, 50, 60, 80, 90, 100, 120, 130, 500};
    int target = 120;
    cout << "search01 result = " << binarySearch01(nums, target) << endl;
    cout << "search02 result = " << binarySearch02(nums, target) << endl;
    cout << "search03 result = " << binarySearch03(nums, target) << endl;

    vector<int> nums01{10, 20, 30, 40, 50, 60, 60, 60, 80, 90, 100, 120, 130, 500};
    cout << "lowerBound01(nums01, 60) first = " << lowerBound01(nums01, 60) << "\n";
    cout << "lowerBound02(nums01, 60) first = " << lowerBound02(nums01, 60) << "\n";
    cout << "lowerBound03(nums01, 60) first = " << lowerBound03(nums01, 60) << "\n";

    vector<int> arr02{60, 30, 20, 30, 40, 10, 50, 60, 100, 20, 10, 30, 40, 20, 10};
    // 测试归并排序
    mergeSort(arr02);
    cout << "mergeSort result = ";
    for (auto item : arr02)
    {
        cout << item << " ";
    }
    cout << endl;

    // 测试随机数发生器
    default_random_engine e;                     // 随机数引擎
    uniform_int_distribution<uint32_t> d(0, 99); // 左闭右闭区间
    vector<int> arr03;
    for (size_t i = 0; i < 50; i++)
    {
        // e.discard(314159 * (i + 13)); // 会导致程序变慢
        cout << d(e) << " ";
    }
    for (size_t i = 0; i < 100; ++i)
    {
        arr03.push_back(d(e));
    }
    cout << "\n"
         << "arr03 = ";
    for (auto &item : arr03)
    {
        cout << item << " ";
    }
    quickSort(arr03);
    cout << "\n"
         << "quick sorted = ";
    for (auto &item : arr03)
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