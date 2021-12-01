# Qt开发过程问题记录



##  一. 头文件相互包含错误



### 1. VS报错如下:

![](F:\截图\头文件相互包含时VS报错.png)





### 2. 错误原因:

- **两个(.h)头文件之间相互包含, 导致递归包含, 编译无法通过**



### 3. 错误重现:

- head01.h

  ```c++
  #pragma once
  #include "head02.h"
  class ClassA
  {
  public:
  	ClassA();
  	~ClassA();
  private:
  	void doit(ClassB *instanceB);
  };
  ```



- head02.h

  ```c++
  #pragma once
  #include "head01.h"
  class ClassB
  {
  public:
  	ClassB();
  	~ClassB();
  private:
  	ClassA * instanceA;
  };
  ```

  

- source01.cpp

  ```c++
  #include "head01.h"
  ClassA::ClassA()
  {
  }
  
  ClassA::~ClassA()
  {
  }
  
  void ClassA::doit(ClassB *instanceB) {
  	//dosomething
  }
  ```

  

- source02.cpp

  ```c++
  #include "head02.h"
  ClassB::ClassB()
  {
  }
  
  ClassB::~ClassB()
  {
  }
  
  ClassA * instanceA = new ClassA();
  ```



- main.cpp

  ```c++
  #include <iostream>
  using namespace std;
  
  int main() {
  	cout << "hello word!"<<endl;
  	system("pause");
  	return 0;
  }
  ```





### 4. 解决方案

1. **在(.h)头文件在使用类的前置声明,而不是包含头文件 **
2. **在(.cpp)文件中才包含头文件**



- #### **可以将以上错误代码修改为如下代码:**


- head02.h

  ```c++ 
  #pragma once
  class ClassA;//在此处使用ClassA的前置声明
  class ClassB
  {
  public:
  	ClassB();
  	~ClassB();
  private:
  	ClassA * instanceA;
  };
  ```

  

- source02.cpp

  ```c++ 
  #include "head02.h"
  #include "head01.h" //在这必须使用#include 因为涉及类对象的具体实现
  ClassB::ClassB()
  {
  }
  
  ClassB::~ClassB()
  {
  }
  
  ClassA * instanceA = new ClassA();
  ```

  #### 其他文件代码不变

### 5.参考资料

网址链接: [C/C++ 中头文件相互包含引发的问题](https://blog.csdn.net/hazir/article/details/38600419)



C++ 中头文件(.h)和源文件(.cpp)该写那些: [C++头文件和源文件该写那些](https://www.cnblogs.com/fenghuan/p/4794514.html)

