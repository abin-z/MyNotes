# C++中的可调用对象

在 C++ 中，可调用对象是指那些可以通过 `operator()` 被调用的对象。C++ 提供了多种方式来创建和使用可调用对象.

以下是 C++ 中常见的几种可调用对象:

1. **普通函数(Function)**
2. **函数指针（Function Pointer）**
3. **函数对象（Functor）**
4. **Lambda 表达式**
5. **成员函数指针（Member Function Pointer）**
6. **std::function**
7. **std::packaged_task**
8. **std::bind（绑定函数参数）**
9. **std::invoke**
10. **std::mem_fn**



### 1. 普通函数（Function）

普通函数是最基本的可调用对象，适用于所有 C++ 版本。

```cpp
int add(int a, int b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 2. 函数指针（Function Pointer）

函数指针用于指向普通函数，适用于所有 C++ 版本。

```cpp
int add(int a, int b) {
    return a + b;
}

int main() {
    int (*func_ptr)(int, int) = &add;  // 指向 add 函数
    std::cout << func_ptr(3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 3. 函数对象（Functor）

函数对象是类或结构体，通过重载 `operator()` 实现可调用功能，适用于所有 C++ 版本。

```cpp
class Adder {
public:
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    Adder adder;
    std::cout << adder(3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 4. Lambda 表达式（Anonymous Functions）

Lambda 表达式是 C++11 引入的，可以快速定义匿名函数，适用于 C++11 及以上版本

```cpp
int main() {
    auto add = [](int a, int b) { return a + b; };
    std::cout << add(3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 5. 成员函数指针（Member Function Pointer）

成员函数指针用于指向类的成员函数，适用于所有 C++ 版本。

```cpp
class Adder {
public:
    int add(int a, int b) {
        return a + b;
    }
};

int main() {
    Adder adder;
    int (Adder::*func_ptr)(int, int) = &Adder::add;  // 指向成员函数
    std::cout << (adder.*func_ptr)(3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 6. std::function

`std::function` 是 C++11 引入的一个通用的可调用对象包装器，适用于 C++11 及以上版本。

```cpp
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::function<int(int, int)> add_fn = add;
    std::cout << add_fn(3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 7. std::packaged_task

`std::packaged_task` 是 C++11 引入的一个任务封装器，支持异步计算，适用于 C++11 及以上版本。

```cpp
#include <future>

int add(int a, int b) {
    return a + b;
}

int main() {
    std::packaged_task<int(int, int)> task(add);  // 封装 add 函数
    std::future<int> result = task.get_future();
    task(3, 4);  // 执行任务
    std::cout << result.get() << std::endl;  // 输出：7
    return 0;
}
```

### 8. std::bind

`std::bind` 是 C++11 引入的函数适配器，允许将函数参数绑定，适用于 C++11 及以上版本。

```cpp
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    auto add_fn = std::bind(add, 3, std::placeholders::_1);
    std::cout << add_fn(4) << std::endl;  // 输出：7 (相当于 add(3, 4))
    return 0;
}
```

### 9. std::invoke

`std::invoke` 是 C++17 引入的一个统一调用接口，用于调用可调用对象，适用于 C++17 及以上版本。

```cpp
#include <functional>

int add(int a, int b) {
    return a + b;
}

class Adder {
public:
    int add(int a, int b) {
        return a + b;
    }
};

int main() {
    std::cout << std::invoke(add, 3, 4) << std::endl;  // 输出：7
    Adder adder;
    std::cout << std::invoke(&Adder::add, adder, 3, 4) << std::endl;  // 输出：7
    return 0;
}
```

### 10. std::mem_fn

`std::mem_fn` 是 C++11 引入的，它可以将成员函数转换为一个可调用对象，适用于 C++11 及以上版本。

```cpp
#include <functional>

class Adder {
public:
    int add(int a, int b) {
        return a + b;
    }
};

int main() {
    Adder adder;
    // 使用 std::mem_fn 创建成员函数的可调用对象，并存储在 std::function 中
    std::function<int(Adder&, int, int)> add_fn = std::mem_fn(&Adder::add);
    std::cout << add_fn(adder, 3, 4) << std::endl;  // 输出：7
    return 0;
}
```







