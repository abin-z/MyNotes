# Qt中窗体的属性设置



### 设置窗口模态属性

```c++
this->setWindowModality(Qt::ApplicationModal);
```



### 设置窗口最大化

```c++
this->setWindowState(Qt::WindowMaximized);
```



### 设置窗口关闭时立即释放资源

```c++
this->setAttribute(Qt::WA_DeleteOnClose);
```



### 设置窗口始终置顶显示(非模态)

```
 this->setWindowFlags(Qt::WindowStaysOnTopHint);
```



### 设置背景透明

```C++
setAttribute(Qt::WA_TranslucentBackground, true);

setWindowOpacity(0.5); //设置背景透明度 0为完全透明
```



### 使头文件只编译一次

1. **在头文件中可以使用#pragma once 防止头文件重复编译, 提升编译效率**

```c++
#pragma once
```

2. **另一种方式是使用预编译, 推荐使用第二种方式**

```c++
#ifndef CUSTOM_NAME
#define CUSTOM_NAME

//你写的代码,包括 #include 头文件的
//CUSTOM_NAME是随便定义的名字,一般是大写字母
//头文件中推荐这么写, 可以防止头文件之间的重复包含include


#endif
```



### 设置程序使用的字符集

**设置字符集为utf8**

```C++
#pragma execution_character_set("utf-8")
```



### setwindowflags的属性总结



#### [setwindowflags的属性总结](https://blog.csdn.net/Vichael_Chan/article/details/100599052?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_title~default-0.essearch_pc_relevant&spm=1001.2101.3001.4242)

#### [qt setWindowFlags各种标志位的窗口样式](https://blog.csdn.net/yhc166188/article/details/80437708)

####  [flags](https://blog.csdn.net/zoukp12345/article/details/78014850)



[参考链接](https://blog.csdn.net/chenhongwei610/article/details/86668684?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.essearch_pc_relevant&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.essearch_pc_relevant)

```c++
setWindowFlags(Qt::CustomizeWindowHint);//设置窗口标题栏自定义

setWindowFlags(Qt::WindowMinimizeButtonHint);//设置窗口的标题栏只有最小化的按钮

setWindowFlags(Qt::WindowCloseButtonHint);//设置窗口的标题栏只有关闭的按钮

setWindowFlags(Qt::WindowStaysOnTopHint);//设置窗体一直置顶，并且不会抢焦点

setWindowFlags(this->windowFlags());//设置窗口为QT的默认属性

setWindowFlags(Qt::FramelessWindowHint));//设置窗体无边框，不可拖动拖拽拉伸

setWindowModality(Qt::WindowModal); //设置窗体为模态

this->setWindowFlags(this->windowFlags()&~Qt::WindowMinimizeButtonHint);//设置最小化按钮不能使用,但是还是存在(无法点击)

this->setWindowFlags(this->windowFlags()&Qt::WindowMinimizeButtonHint);//设置除了最小化按钮能使用,其他按钮都不能使用,但是还是存在

setWindowFlags(Qt::SubWindow);//窗口没有按钮但是有标题栏 任务里什么也看不到
```





