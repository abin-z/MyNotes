#include <iostream>
#include <vector>

int main()
{
    int some_val = 33;
    std::vector<int> iv = {11, 22, 33, 44, 55, 66, 77};
    std::vector<int>::iterator iter = iv.begin(), mid = iv.begin() + iv.size() / 2;
    while (iter != (iv.begin() + iv.size() / 2))
    {
        if (*iter == some_val)
        {
            iter = iv.insert(iter, 2 * some_val);
        }
        else
        {
            ++iter;
        }
    }
    for (auto &&i : iv)
    {
        std::cout << i << std::endl;
    }

    return 0;
}