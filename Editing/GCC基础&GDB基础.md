# GCC基础&GDB基础

# GCC简介

[GCC](https://gcc.gnu.org/)（GNU C Compiler，GNU C编译器，简称GCC）GNU编译器集合，是GNU推出的功能强大、性能优越的多平台编译器。GCC编译器能将C/C++、Objective-C、Fortran、Ada源程序、汇编程序和目标程序编译、链接成可执行文件。

> GCC C编译器的原作者是大胡子Richard Stallman，也是GNU项目的奠基人。GNU项目是一个非盈利项目，用来打造一个类似Unix的开源自由的操作系统，一般每个操作系统都有配套的编译器，用来编译能在这个操作系统上运行的应用程序，GNU也不例外，也需要一个配套的编译器，GCC就是大胡子把自己关在小铁屋里，白手起家，一行一行代码敲起来的，用来编译可以在GNU操作系统上运行的C语言程序。
>
> 早期的GCC只支持X86架构、只支持C语言，后来随着不断演进迭代，开始支持越来越多的处理器架构（X86、ARM、PowerPC…），开始支持越来越多的编程语言（C、C++、ADA、Fortran…），GCC的内涵也随之发生了变化，此时不再是GNU C Compiler的简称，而是GNU Compiler Collection（GNU编译器套件）的简称。全套的GCC，不仅可以编译C语言，还可以编译C++语言。不仅可以编译在X86上运行的程序，还可以编译在ARM平台上运行的程序。

**GCC、 gcc 、 g++ 的联系和区别**

GCC:GNU Compiler Collection(GNU 编译器集合)，它可以编译C、C++、JAVA、Fortran、Pascal、Object-C、Ada等语言。

gcc是GCC中的GNU C Compiler（C 编译器里的前端程序）

g++是GCC中的GNU C++ Compiler（C++编译器的前端程序）

**gcc和g++的区别：**

- gcc 会将后缀为 .c 的文件当作 C 程序，将后缀为 .cpp 的文件当作 C++ 程序；

- g++ 会将后缀为 .c 和 .cpp 的都当成 C++ 程序；

因为 C 和 C++ 语法上有一些区别，所以有时候通过 g++ 编译的程序不一定能通过 gcc 编译。要注意的是，gcc 和 g++ 都可以用来编译 C 和 C++ 代码。

- 链接方式不同：gcc 不会自动链接 C++ 库（比如 STL 标准库），g++ 会自动链接 C++ 库；

- 预处理器宏不同：g++ 会自动添加一些预处理器宏，比如 __cplusplus ，但是 gcc 不会；



## GCC构成

一个完整的C/C++语言编译器套件，主要包括一下部分：

- 预处理器、编译器、汇编器、链接器
- C/C++标准库的实现、C/C++标准库对应的头文件
- 各种调试工具：nm、gdb、objcopy、objdump、readelf等

安装好GCC编译器后，在默认的安装路径（/usr/bin）下，我们可以看到各种安装好的编译工具（ar、as、ld、cpp）、各种调试工具（nm、objcopy、objdump、readelf）

在默认的库安装路径(/usr/lib)下，可以看到安装好的C/C++标准库文件

在默认的头文件安装路径(/usr/include)下，可以看到C/C++标准库的各种头文件。

如果你的**没有安装到默认路径**，而是安装在一个指定的路径下，打开这个安装路径，你会看到这个编译器的各种二进制工具、C标准库文件、C标准库对应的头文件。

```sh
# 以我在Ubuntu操作系统上安装的ARM交叉编译器arm-linux-gnueabi-gcc为例，安装在/usr/arm-linux-gnueabi路径下：
# cd /usr/arm-linux-gnueabi
# tree -L 1
.
├── bin
├── include
└── lib
```

在编译器的安装路径下，我们可以看到三个子目录：bin、include、lib

- bin：ARM编译器的各种二进制工具：编译器、链接器、汇编器、调试工具等
- include：存放ARM编译器实现的各种[C标准库](https://www.zhaixue.cc/c-lib/c-lib-intro.html)头文件
- lib：存放ARM编译器实现的[C标准库](https://www.zhaixue.cc/c-lib/c-lib-intro.html)函数，分为静态库和动态库



## GCC编译器工作流程

### 编译流程

我们编写源代码就是普通的文本，cpu是不能直接根据源代码(文本文件)执行指令的。源码要想运行，就必须转为CPU能理解的二进制机器指令，这就是gcc编译器编译器的任务。

例如下面的源代码`文件名: hello.cpp`

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello World\n";
}
```

执行编译指令: `g++ -o sayhello hello.cpp`, 将得到一个名为`sayhello`的可执行文件, 运行后则输出`Hello world`

```sh
[abin@rocky gccDemo]$ g++ -o sayhello hello.cpp 
[abin@rocky gccDemo]$ ll
total 32
-rw-r--r--. 1 abin abin    69 Jun  1 12:55 hello.cpp
-rwxr-xr-x. 1 abin abin 24720 Jun  1 12:59 sayhello
[abin@rocky gccDemo]$ ./sayhello 
Hello World
[abin@rocky gccDemo]$ 
```

从一个C/C++语言源文件，到生成最后的可执行文件，GCC编译过程的基本流程如下:

1. **预处理（Pre-Processing）**：将源程序（如 **.c** 文件）预处理，生成 **.i** 文件。
2. **编译（Compiling）**：将预处理后的 **.i** 文件编译成为汇编语言，生成 **.s** 文件。
3. **汇编（Assembling）**：将汇编语言文件经过汇编，生成目标文件 **.o** 文件。
4. **链接（Linking）**：将各个模块的 **.o** 文件链接起来生成一个可执行程序文件。

其中 **.i** 文件、**.s**文件、**.o**文件是中间文件或临时文件，如果使用GCC一次性完成C语言程序的编译，则这些文件会被删除。

gcc命令是GCC编译器里的一个前端程序，用来控制整个编译过程：分别调用预处理器、编译器和汇编器，完成编译的每一个过程，最后调用链接器，生成可执行文件：sayhello

![compile_single_file](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/compile_single_file.png)



默认情况下，gcc命令会自动完成上述的整个编译过程。当然，gcc还提供了一系列参数，使用这个参数，可以让用户精准控制每一个编译过程。

- -E ：只做预处理，不编译                               生成 `filename.i` 文件
  - 可以通过`gcc -E hello.cc -o hello.i`查看中间结果
- -S ：只编译，将C程序编译为汇编文件         生成 `filename.s` 文件
- -c ：只汇编，不链接                                       生成 `filename.o` 文件
- -o ：指定输出的文件名                                   生成指定名称的可执行文件, 不指定linux下默认为 `a.out` 文件

```sh
[abin@rocky gccDemo]$ ls
hello.cpp								# 目前只有hello.cpp文件
[abin@rocky gccDemo]$ cat hello.cpp 
#include <iostream>

int main()
{
    std::cout << "Hello World\n";
}
[abin@rocky gccDemo]$ g++ -E hello.cpp -o hello.i		######## 预处理操作 -E
[abin@rocky gccDemo]$ ls
hello.cpp  hello.i						# 预处理生成了hello.i预处理文件
[abin@rocky gccDemo]$ g++ -S hello.i					######## 编译操作 -S
[abin@rocky gccDemo]$ ls
hello.cpp  hello.i  hello.s				# 编译生成了hello.s汇编文件
[abin@rocky gccDemo]$ g++ -c hello.s					######## 汇编操作 -c
[abin@rocky gccDemo]$ ls				# 汇编生成了hello.o目标文件
hello.cpp  hello.i  hello.o  hello.s
[abin@rocky gccDemo]$ g++ hello.o						######## 链接操作,不需要参数
[abin@rocky gccDemo]$ ls
a.out  hello.cpp  hello.i  hello.o  hello.s		# 链接后生成了 a.out 可执行文件
[abin@rocky gccDemo]$ ./a.out 
Hello World		# 输出 Hello World	
[abin@rocky gccDemo]$ 
```

![gcc分步编译](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/gcc%E5%88%86%E6%AD%A5%E7%BC%96%E8%AF%91.png)



### GCC文件类型

对于任何给定的输入文件，文件类型决定进行何种编译。GCC常用的文件类型如表1所示。

**表 1** GCC常用的文件类型

| 扩展名（后缀） | 说明                                                         |
| :------------- | :----------------------------------------------------------- |
| .c             | C语言源代码文件。                                            |
| .C，.cc或.cxx  | C++源代码文件。                                              |
| .m             | Objective-C源代码文件。                                      |
| .s             | 汇编语言源代码文件。                                         |
| .i             | 已经预处理的C源代码文件。                                    |
| .ii            | 已经预处理的C++源代码文件。                                  |
| .S             | 已经预处理的汇编语言源代码文件。                             |
| .h             | 程序所包含的头文件。                                         |
| .o             | 编译后的目标文件。                                           |
| .so            | 动态链接库，它是一种特殊的目标文件。                         |
| .a             | 静态链接库。                                                 |
| .out           | 可执行文件，但可执行文件没有统一的后缀，<br />系统从文件的属性来区分可执行文件和不可执行文件。<br />如果没有给出可执行文件的名字，GCC将生成一个名为`a.out`的文件。 |

## 编译选项

GCC编译的命令格式为：**gcc** [*options*]  [*sourcefiles...*]

```sh
gcc(g++) <options> <sourcefiles...>

# 示例
gcc main.cpp
gcc -o main main.cpp
gcc -o main main.cpp hello.cpp fun.cpp
gcc -I../headers -o main main.cpp
g++ -o main -I../headers -L../lib -lfun1 main.cpp hello.cpp
```

其中：

*options* ：编译选项。

*sourcefiles* ：源代码文件名称。

GCC是一个功能强大的编译器，其 *options* 参数取值很多，但大部分并不常用，常用的 *options* 取值如下表所示:

### 常用选项(options)

|          选项           | 作用                                                         |
| :---------------------: | :----------------------------------------------------------- |
|          `-c`           | 编译、汇编指定的源文件生成目标文件，但不进行链接。<br />通常用于编译不包含主程序的子程序文件。 |
|     `-o <filename>`     | 指定生成文件名 `filename `  未指定时，默认为`a.out`          |
|     `-I<head-path>`     | 添加指定头文件搜索路径 `head-path`, (大写的i)                |
|     `-L<lib-path>`      | 添加指定库搜索路径 `lib-path`                                |
|      `-l<libname>`      | 指定链接库名, libname为基础名称:`lib<name>.a` `去除前缀lib,去除后缀名.a`, (小写的L) |
|   `-E -o<filename.i>`   | 预处理指定的源文件，但不进行编译。<br />需要重定向到一个文件里，`gcc -E hello.c > pre_hello.i` |
|          `-S`           | 编译指定的源文件生成以.s作为后缀的汇编语言文件，但不进行汇编。 |
|        `-static`        | 进行静态编译，及链接静态库，禁止链接动态库。                 |
|        `-shared`        | 默认选项，可省略。可以生成动态库文件。<br />进行动态编译，优先链接动态库，只有没有动态库时才会链接同名的静态库。 |
|   `-fPIC（或-fpic）`    | 生成使用相对地址的位置无关的目标代码。增加兼容性<br />通常使用-static选项从该PIC目标文件生成动态库文件。<br />生成动态链接库的目标文件时，必须添加该选项。<br />生成静态库，但被其它动态库时用时，也需要添加该选项。 |
|         `-Wall`         | 输出警告信息,可以指定特定的警告信息                          |
|        `-O(0-3)`        | 指定代码优化级别: 0-3 优化级别从低到高                       |
|          `-g`           | 在可执行程序中包含标准调试信息。`使用gdb调试的时候,需要添加该参数` |
|        `-glevel`        | 调试信息生成级别，默认为2，如`-g3`                           |
|  `-fexec-charset=GBK`   | 指定运行时编码格式                                           |
| `-finput-charset=UTF-8` | 指定源文件编码格式                                           |
|         `-std`          | 指定cpp版本  `-std=c++11`：支持c++11                         |



### 常用编译选项详细说明



#### 1. 总体选项

1. `-c`：只激活预处理、编译和汇编过程，**但不做link**，只生成目标文件
2. `-o`：指定输出文件，未指定时，默认为`a.out`
3. `-S`：只激活预处理和编译，生成`.s`的汇编文件
4. `-E`：只激活预处理，需要重定向到一个文件里，`gcc -E hello.c > pre_hello.i`

#### 2. 调试选项

1. `-g`：以操作系统的本地格式（stabs, COFF, XCOFF等）产生调试信息，以便GDB使用
2. `-glevel`：调试信息生成级别，默认为2，如`-g3`
   - level=1，输出少量调试信息，没有局部变量和行号信息
   - level=3，输出较多调试信息

#### 3. 预处理器选项

1. `-Dmacro`：相当于C语言中的`#define macro`
2. `-Dmaroc=defn`：定义宏macro的内容为defn，相当于C语言中`#define marco=defn`
3. `-Umacro`：取消宏macro，-U 选项在所有-D 选项之后使用
4. `-include file`：当某个文件需要另一个文件时，可以用它来设定，功能类似`#include <filename>`，如`gcc hello.c -include /root/ss.h`

#### 4. 链接器选项

1. `-static`：将禁止使用动态库, gcc默认先链接动态库
2. `-shared`：指定生成一个共享目标文件，常搭配`-fPIC`使用
3. `-Wl,option`：把选项`option`传递给链接器；如果`option`包含逗号，会分隔为多个选项
4. `-symbolic`：建立共享目标文件时候，把引用绑定到全局符号上

#### 5. 目录选项

1. `-l{library]}`：指定编译的时候使用的库，如`gcc -lcurses hello.c`，链接时使用
2. `-L{dir}`：指定编译时，**搜索库的路径**。如果不指定，编译器将只在标准库的目录搜索
3. `-I{dir}`：增加编译时，**搜索头文件的路径**。 当使用`#include "file"`时，`gcc/g++`会先在当前目录查找你指定的文件，若没有，则去缺省的头文件目录找。若使用`-I`指定了目录，则会优先在指定的目录找，再按照常规顺序寻找。对于`#include <file>`，`gcc/g++`会到`-I`指定目录找，若没有，则去缺省的头文件目录找。
4. `-I-`：取消前一个`-I{dir}`的参数功能
5. `-nostdinc`：告诉编译器不在系统缺省的头文件目录里找头文件，一般与`-I`联合使用
6. `-nostdinc++`：告诉编译器不在g++指定的标准路径中搜索，但仍在其他路径搜索，此选项在创建`libg++`库使用

#### 6. 警告选项

1. `-Wall`：大部分常见的警告信息。
2. `-Wextra`：比`-Wall`更多的警告信息。
3. `-Werror`：将警告视作错误，会阻止编译进行，对大多数情况下过于严厉。
4. `-pedantic`： ANSI/ISO C 标准所列出的所有警告。
5. `-Wwarning-type`：提示具体的警告类型。
6. `-Wno-warning-type`：不提示具体的警告类型。

常用的一个组合为：`-Wall -Wextra -pedantic -Werror=return-type -Winvalid-pch -Wno-unused-parameter`。

```cpp
#include <iostream>

int *getIntPtr();
int main()
{
    auto p = getIntPtr();
    std::cout << "*p = " << *p << std::endl;
    int32_t n1 = 100;
    uint32_t n2;  // 警告: 变量未初始化
    uint32_t n3;  // 警告: 未使用的变量
    if (n1 == n2) // 警告: 有符号和无符号数比较
    {
        std::cout << "n1 == n2" << std::endl;
    }
}
int *getIntPtr()
{
    int bbb = 666;
    return &bbb; // 警告: 返回局部变量地址
}
```

执行编译指令: `g++ -Wall -Wextra main.cpp`

```sh
[abin@rocky gccDemo]$ g++ -Wall -Wextra main.cpp
main.cpp: In function ‘int main()’:
main.cpp:11:12: warning: comparison of integer expressions of different signedness: ‘int32_t’ {aka ‘int’} and ‘uint32_t’ {aka ‘unsigned int’} [-Wsign-compare]
   11 |     if (n1 == n2) // 警告: 有符号和无符号数比较
      |         ~~~^~~~~
main.cpp:10:14: warning: unused variable ‘n3’ [-Wunused-variable]
   10 |     uint32_t n3;  // 警告: 未使用的变量
      |              ^~
main.cpp: In function ‘int* getIntPtr()’:
main.cpp:20:12: warning: address of local variable ‘bbb’ returned [-Wreturn-local-addr]
   20 |     return &bbb; // 警告: 返回局部变量地址
      |            ^~~~
main.cpp:19:9: note: declared here
   19 |     int bbb = 666;
      |         ^~~
main.cpp: In function ‘int main()’:
main.cpp:11:5: warning: ‘n2’ is used uninitialized [-Wuninitialized]
   11 |     if (n1 == n2) // 警告: 有符号和无符号数比较
      |     ^~
[abin@rocky gccDemo]$
```



#### 7. 优化选项

1. `-O0`：不优化
2. `-O1`：优化，对于**大函数**，优化编译占用稍微多的时间和相当大的内存
3. `-O2`：更多优化，除了空间和速度交换的优化选项，执行几乎所有的优化
   - 如：进行循环展开和函数内联
   - 会增加编译时间，但提高了生成代码的执行效率
4. `-ffloat-store`：不要在寄存器中存放浮点变量

#### 8. 代码生成选项

1. `-fpic`：如果支持这种目标机，编译器就生成**位置无关目标码**，适用与共享库
2. `-fPIC`：如果支持这种目标机，编译器就生成**位置无关目标码**，即使分支需要大范围转移

#### 9. 语言选项

1. `-std=c++11`：支持c++11
2. `-ansi`：支持符合ANSI标准的C程序
3. `-fno-asm`：用于诗词安`anis`选项中功能的一部分，禁止将`asm`，`inline`，`typeof`用作关键字
4. `-x language filename`：设定此文件使用的语言，无视后缀名，且对此参数后多个文件有效，如`gcc -x c hello.pig -x none`，指定`none`来关闭上一个选项

#### 10. 机器相关选项

1. `-mhard-float`：输出包括浮点指令的目标码，缺省选项
2. `-msoft-float`：警告:没有为SPARC提供GNU浮点库.一般说来使用该机型本地C编译器的相应部件
   - 不能直接用于交叉编译.你必须自己安排,提供用于交叉编译的库函数.
   - `-msoft-float` 改变了输出文件中的调用约定;因此只有用这个选项编译整个程序才有意义

#### 11. 宏和优化级别

`-DMACRO`或者`-DMACRO=value`可以指定宏。其中最重要的一个是`-DNDEBUG`，用于取消生产版本里的`assert`指令（注意`-g`并不会取消`assert`指令）。

`-g`则用于生成 debug 信息，`-O0`、`-O1`、`-O2`、`-O3`则是不同的优化级别。

我们在编译时经常会碰到`make release`或者`make debug`，事实上它们分别是上面指令的组合：

- make release: `-DNDEBUG -O2`。
- make debug: `-g -O0`。

#### 12. 其它选项

- `-MD`：会生成`.d`依赖文件，记录头文件的依赖关系，方便编译器根据修改情况来决定是否需要重新编译。通常会加上。
- `-pipe`：中间文件直接放在内存，而不是显式的临时文件。通常会加上。
- `-fPIC`: 生成动态链接库的目标文件时，必须添加该选项。生成静态库，但被其它动态库时用时，也需要添加该选项。
- `-m64`：生成 64 位应用程序

#### 13. 注意事项

- **顺序问题**：通常，`-L` 和 `-l` 要放在需要链接的目标文件或对象文件之后。例如：

  `gcc main.o -Llib -lmylib -o myprogram`

- **动态库和静态库优先级:**  如果目录下既有 `libmylib.a`（静态库）又有 `libmylib.so`（动态库），GCC 默认优先链接动态库。如果你想强制使用静态库，可以用 `-static`。

​	`gcc -static -Llib -lmylib -o myprogram`



## 库library

库是写好的、现有的、成熟的、可以复用的代码。每个程序都要依赖很多基础的底层库。

库文件在命名时约定，以lib为前缀，以.so（动态库）或.a（静态库）为后缀，中间为库文件名。如libfoo.so或libfoo.a。由于所有的库文件都遵循了同样的规范，因此当在链接库时，-l 选项指定链接的库文件名时可以省去lib前缀，即GCC 在对-lfoo 进行处理时，会自动去链接名为libfoo.so 或libfoo.a的库文件。而当在创建库时，必须指定完整文件名libfoo.so或libfoo.a。

根据链接时期的不同，库分为静态库和动态库。**静态库是在链接阶段，将汇编生成的目标文件.o与引用到的库一起链接打包到可执行文件中**；**而动态库是在程序编译时并不会被链接到目标代码中，而是在程序运行时才被载入。**二者有如下差异：

- 资源利用不一样

  静态库为生成的可执行文件的一部分，而动态库为单独的文件。所以使用静态库和动态库的可执行文件大小和占用的磁盘空间大小不一样，导致资源利用不一样。

- 扩展性与兼容性不一样

  静态库中某个函数的实现变了，那么可执行文件必须重新编译，而对于动态链接生成的可执行文件，只需要更新动态库本身即可，不需要重新编译可执行文件。

- 依赖不一样

  静态库的可执行文件不需要依赖其他的内容即可运行，而动态库的可执行文件必须依赖动态库的存在。所以静态库更方便移植。

- 加载速度不一样

  静态库在链接时就和可执行文件在一块了，而动态库在加载或者运行时才链接，因此，对于同样的程序，静态链接的要比动态链接加载更快。

![构建过程](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/%E6%9E%84%E5%BB%BA%E8%BF%87%E7%A8%8B.png)





### 静态链接库

#### 命名规则

静态链接库命名采用**lib<name>.a**的形式，例如libmangle.a，libpng.a, 基础名称为<name>部分

#### 生成静态链接库

创建一个静态链接库，需要先将源文件编译为目标文件`.o`，然后再使用ar命令将目标文件打包成静态链接库`.a`。

##### ar 归档打包指令

其中ar是一个备份压缩命令，可以将多个文件打包成一个备份文件（也叫归档文件），也可以从备份文件中提取成员文件。ar最常见的用法是将目标文件打包为静态链接库。

ar将目标文件打包成静态链接库的命令格式为：

```shell
$ ar rcs <Sllfilename> <Targetfilelist>
```

- *Sllfilename* ：静态库文件名。
- *Targetfilelist* ：目标文件列表。
- r： 替换库中已有的目标文件，或者加入新的目标文件。
- c： 创建一个库，不管库是否存在，都将创建。
- s： 创建目标文件索引，在创建较大的库时能提高速度。

示例：创建一个main.c文件来使用静态库。

```sh
# 其中libraryDIR为libtest.a库的路径。
$ gcc main.c -L libraryDIR -ltest -o test.out
```



示例：将源文件test1.c，test2.c，test3.c编译并打包成静态库。

```sh
$ gcc -c test1.c test2.c test3.c		# 1. 先生成.o目标文件
$ ar rcs libtest.a test1.o test2.o test3.o	# 2. ar 打包为.a文件
```

先将需要归档到库的源文件编译成.o文件，再用下列命令归档

```sh
ar rcs <libname> <objfilelist...>
# 示例
ar rcs libfun.a fun1.o fun2.o fun3.o # 将3个.o文件归档到同一库文件当中
```

#### 使用

先将使用到对应静态库的源文件编译为.o目标文件，再进行链接

```sh
gcc(g++) <ofilelist...> -L<dir> -l<lib>
# 示例
gcc main.o hello.o -L../lib -lfun1 -lfun2 -lfun3
# 或者
gcc main.o hello.o ../lib/libfun1.a ../lib/libfun2.a ../lib/libfun3.a
```

### 动态链接库

#### 命名规则

动态链接库命名规则为lib<name>.dll (Windows) / lib<name>.so (Linux) ,   例如：libmangle.dll/libmangle.so，libpng.dll/libpng.so

#### 生成动态链接库

使用`-shared`选项 和`-fPIC`选项，可直接使用源文件、汇编文件或者目标文件创建一个动态库。**其中`-fPIC `选项作用于编译阶段**，在生成目标文件时就需要使用该选项，以生成位置无关的代码。

```shell
# 分步进行
gcc(g++) -c -fPIC <sourcefilelist ...>
gcc(g++) -o <libname> -shared <objfilelist ...>
# 示例
gcc -c -fPIC fun1.c fun2.c fun3.c
gcc -o libfun.dll -shared fun1.o fun2.o fun3.o

# 一步到位
gcc(g++) -o <libname> -fPIC -shared <sourcefilelist ...>
# 示例
gcc -o libfun.dll -fPIC  -shared fun1.c fun2.c fun3.c
```

#### 使用

先将使用到对应静态库的源文件编译为.o文件，再进行链接

```sh
gcc(g++) <ofilelist...> -L<dir> -l<lib>
# 示例
gcc main.o hello.o -L../lib -lfun1 -lfun2 -lfun3
# 或者
gcc main.o hello.o ../lib/libfun1.dll ../lib/libfun2.dll ../lib/libfun3.dll
```



`-Wl,-rpath,<dir>` 是一个编译器选项，用于设置可执行文件运行时查找共享库的位置。这个选项将指定的目录 `<dir>` 添加到可执行文件的运行时库搜索路径中。

- `-Wl`：告诉编译器将后续选项传递给链接器（`ld`）。
- `-rpath,<dir>`：链接器选项，设置运行时库搜索路径为 `<dir>`。

例如，如果你在编译一个程序时希望它在运行时查找共享库的目录是 `src`，你可以使用以下命令：

```sh
g++ -o my_program my_program.cpp -Wl,-rpath,src -Lsrc -lmy_library
```

这个命令做了以下几件事：

1. `-o my_program`：指定输出可执行文件名为 `my_program`。
2. `my_program.cpp`：源文件。
3. `-Wl,-rpath,src`：告诉链接器在运行时将 `src` 目录添加到库搜索路径。
4. `-Lsrc`：告诉编译器在编译时从 `src` 目录中查找库。
5. `-lmy_library`：链接名为 `my_library` 的库（编译器将会查找名为 `libmy_library.so` 或 `libmy_library.a` 的文件）。

##### 为什么使用 `-rpath`

使用 `-rpath` 可以使得可执行文件在运行时自动查找并加载指定目录中的共享库，而不需要用户手动设置 `LD_LIBRARY_PATH` 环境变量。这对于确保程序能够找到其依赖的共享库尤其有用，特别是在共享库不在标准系统库路径中的情况下。





[C与CPP常见编译工具链与构建系统简介 ](https://www.cnblogs.com/w4ngzhen/p/17695080.html)



# GDB简介

### 前言

GDB是Linux下非常好用且强大的调试工具。GDB可以调试C、C++、Go、java、 objective-c、PHP等语言。对于一名Linux下工作的c/c++程序员，GDB是必不可少的工具，本篇以C语言来调试。

### 1. GDB简介

UNIX及UNIX-like下的调试工具。虽然它是命令行模式的调试工具，但是它的功能强大到你无法想象，能够让用户在程序运行时观察程序的内部结构和内存的使用情况。

一般来说，GDB主要帮助你完成下面四个方面的功能：

- 1、按照自定义的方式启动运行需要调试的程序。
- 2、可以使用指定位置和条件表达式的方式来设置断点。
- 3、程序暂停时的值的监视。
- 4、动态改变程序的执行环境。



### 2. 编译带调试信息的程序

为了使用GDB调试程序，你需要在编译程序时加入调试信息。通常通过`-g`选项来完成。例如：

```
bash
Copy code
gcc -g -o myprogram myprogram.c
```

### 3. 启动GDB

在终端中输入以下命令启动GDB并加载你的程序：

```
bash
Copy code
gdb myprogram
```

### 4. 基本命令的操作

GDB中的命令很多，但我们只需掌握其中十个左右的命令，就大致可以完成日常的基本的程序调试工作。

| 命令               | 简写  | 说明                                                      |
| ------------------ | ----- | --------------------------------------------------------- |
| `run`              | `r`   | 重新开始运行程序                                          |
| `start`            |       | 开始程序执行，并在`main`函数的第一行处暂停                |
| `break`            | `b`   | 设置断点, 例如：`break main`或`break filename:line`       |
| `info breakpoints` | `i b` | 查看所有断点                                              |
| `step`             | `s`   | 单步执行, 进入函数内部                                    |
| `next`             | `n`   | 单步执行, 不进入函数内部                                  |
| `continue`         | `c`   | 继续执行程序，直到遇到下一个断点或程序结束                |
| `print`            | `p`   | 打印变量值, 例如：`print variable_name`或`print *pointer` |
| `backtrace`        | `bt`  | 查看调用栈                                                |
| `quit`             | `q`   | 退出GDB                                                   |
| `list`             | `l`   | 查看源代码                                                |
| `frame`            | `f`   | 选择调用栈中的一个帧，例如：`frame 2`                     |
| `info`             | `i`   | 用于显示各种类型的调试信息, 有很多子命令                  |
| `set variable`     |       | 修改程序中变量的值，例如：`set variable a=10`             |
| `set args`         |       | 设置程序运行时的命令行参数，例如：`set args arg1 arg2`    |
| `help`             |       | 获取帮助信息                                              |

#### 常用 `info` 子命令

| 命令                 | 说明                                     |
| -------------------- | ---------------------------------------- |
| `info breakpoints`   | 显示所有断点的信息                       |
| `info frame`         | 显示当前堆栈帧的信息                     |
| `info registers`     | 显示当前寄存器的内容                     |
| `info threads`       | 显示所有线程的信息                       |
| `info locals`        | 显示当前堆栈帧的局部变量                 |
| `info args`          | 显示当前堆栈帧的函数参数                 |
| `info functions`     | 显示程序中定义的所有函数                 |
| `info variables`     | 显示程序中定义的全局和静态变量           |
| `info source`        | 显示当前源文件的信息                     |
| `info line`          | 显示当前行的源代码及其地址               |
| `info sharedlibrary` | 显示加载的共享库信息                     |
| `info signals`       | 显示信号处理的信息                       |
| `info files`         | 显示加载的可执行文件和调试符号文件的信息 |
