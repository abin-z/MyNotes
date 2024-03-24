#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>

#include "tools.cpp"

using namespace std;

// 归并操作
void merge(vector<int> &nums, int left, int mid, int right)
{
    // 拷贝左右两个子序列
    vector<int> leftArr(nums.cbegin() + left, nums.cbegin() + mid);
    vector<int> rightArr(nums.cbegin() + mid, nums.cbegin() + right);
    // 末尾插入哨兵
    leftArr.push_back(numeric_limits<int>::max());
    rightArr.push_back(numeric_limits<int>::max());
    // 合并操作
    int i = 0, j = 0, k = left;
    while (k != right)
    {
        if (leftArr[i] <= rightArr[j])
        {
            nums[k++] = leftArr[i++];
        }
        else
        {
            nums[k++] = rightArr[j++];
        }
    }
}

// 归并排序
void mergeSort(vector<int> &nums, int left, int right)
{
    // 使用左闭右开区间
    if (right - left <= 1)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid, right);
    merge(nums, left, mid, right);
}
// 对并排序
void mergeSort(vector<int> &nums)
{
    mergeSort(nums, 0, nums.size()); // 左闭右开区间
}

int partition(vector<int> &nums, int left, int right)
{
    // 选取pivot,采用随机数
    default_random_engine e(right * 13);
    uniform_int_distribution<int> d(left, right);
    int pivot = d(e);
    // 将pivot移动到最后面
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
    // 最后将pivot移动至i的位置并返回i
    swap(nums[i], nums[right]);
    return i;
}

// 快速排序
void quickSort(vector<int> &nums, int left, int right)
{
    // 使用闭区间写法
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
    quickSort(nums, 0, nums.size() - 1);
}

// 选择排序
void selectSort(vector<int> &nums)
{
    for (int i = nums.size() - 1; i > 0; --i)
    {
        int max = i;
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] > nums[max])
            {
                max = j;
            }
        }
        using std::swap;
        swap(nums[i], nums[max]);
    }
}

// 冒泡排序
void bubbleSort(vector<int> &nums)
{
    for (int i = nums.size() - 1; i > 0; --i)
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

// 插入排序
void insertSort(vector<int> &nums)
{
    // 第一个元素默认就是有序的, 从下标1开始
    for (int i = 1; i < nums.size(); ++i)
    {
        // 待插入的元素
        int newVar = nums[i];
        // 寻找要插入的位置
        int j = i;
        while (j > 0 && nums[j - 1] > newVar)
        {
            // 向后移动元素
            nums[j] = nums[j - 1];
            --j;
        }
        nums[j] = newVar;

        // int j = i - 1;
        // while (j >= 0 && nums[j] > newVar)
        // {
        //     nums[j + 1] = nums[j];
        //     --j;
        // }
        // nums[j + 1] = newVar;
    }
}

int main()
{
    int count = 0;
    cout << "enter random num count: ";
    cin >> count;
    auto vec01 = randomDatas(0, 9999999, count); // 随机数据
    auto vec02 = vec01;
    auto vec03 = vec01;
    auto vec04 = vec01;
    auto vec05 = vec01;

    // 归并排序
    cout << "====MergeSort Test====" << endl;
    cout << "origin data = ";
    printDatas(vec01);
    auto startTime = chrono::high_resolution_clock::now();
    mergeSort(vec01);
    auto endTime = chrono::high_resolution_clock::now();
    cout << "\nmergeSort data = ";
    printDatas(vec01);
    std::chrono::duration<double, std::milli> diff_merge_ms = endTime - startTime;

    // 快速排序
    cout << "\n====QuickSort Test====" << endl;
    cout << "origin data = ";
    printDatas(vec02);
    startTime = chrono::high_resolution_clock::now();
    quickSort(vec02);
    endTime = chrono::high_resolution_clock::now();
    cout << "\nquickSort data = ";
    printDatas(vec02);
    std::chrono::duration<double, std::milli> diff_quick_ms = endTime - startTime;

    // 选择排序
    cout << "\n====SelectSort Test====" << endl;
    cout << "origin data = ";
    printDatas(vec03);
    startTime = chrono::high_resolution_clock::now();
    selectSort(vec03);
    endTime = chrono::high_resolution_clock::now();
    cout << "\nselectSort data = ";
    printDatas(vec03);
    std::chrono::duration<double, std::milli> diff_select_ms = endTime - startTime;

    // 冒泡排序
    cout << "\n====BubbleSort Test====" << endl;
    cout << "origin data = ";
    printDatas(vec04);
    startTime = chrono::high_resolution_clock::now();
    bubbleSort(vec04);
    endTime = chrono::high_resolution_clock::now();
    cout << "\nbubbleSort data = ";
    printDatas(vec04);
    std::chrono::duration<double, std::milli> diff_bubble_ms = endTime - startTime;

    // 插入排序
    cout << "\n====InsertSort Test====" << endl;
    cout << "origin data = ";
    printDatas(vec05);
    startTime = chrono::high_resolution_clock::now();
    insertSort(vec05);
    endTime = chrono::high_resolution_clock::now();
    cout << "\ninsertSort data = ";
    printDatas(vec05);
    std::chrono::duration<double, std::milli> diff_insert_ms = endTime - startTime;

    cout << endl
         << "diff_merge_ms = " << diff_merge_ms.count() << "ms" << endl
         << "diff_quick_ms = " << diff_quick_ms.count() << "ms" << endl
         << "diff_select_ms = " << diff_select_ms.count() << "ms" << endl
         << "diff_bubble_ms = " << diff_bubble_ms.count() << "ms" << endl
         << "diff_insert_ms = " << diff_insert_ms.count() << "ms" << endl;
}
