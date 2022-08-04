# 指针常量和常量指针

[指针常量和常量指针](https://blog.csdn.net/weixin_41028621/article/details/89159896)



## 常量指针

常量指针:  **指针指向的内容是不可修改的, 指针本身可以修改**, 意思就是不能通过常量指针来修改指针指向的值, 但是指针的指向是可以修改的.



两种写法均为常量指针

**const int *ptr;**
**int const *ptr;**



代码演示:指针b指向的地址内容不能修改，而指针b可以指向其他地址

```C
#改变指针b指向地址的内容
int main()
{
	int a = 2;
	int const *b = &a;
	*b = 3;          //报错：expression must be a modifiable lvalue	
	printf("albert:%d\n",a);
}
----------------------------------------------------------------------------
#改变指针b的指向
int main()
{
	int a = 2;
	int b = 3;
	int const *c = &a;
	printf("albert:%p\n", c);    
	c = &b;
	printf("albert:%p\n",c);
}

```





## 指针常量

指针常量: **指针的指向是不可修改的, 指针指向的内容可以修改**, 意思是指针的指向是不能改变的(声明的时候就需要初始化), 后面不能修改指针常量的指向, 但是可以修改指针指向的内容.



下面写法为指针常量

**int *const ptr;**



代码演示:指针指向的地址不可以重新赋值，但内容可以改变。

```C
int main()
{
	int a = 2;
	int b = 3;
	int *const c = &a;
	printf("albert:%p\n", c);
	c = &b;                     //报错：expression must be a modifiable lvalue	
	printf("albert:%p\n",c);
}
--------------------------------------------------------------------------
int main()
{
	int a = 2;
	int b = 3;
	int *const c = &a;
	*c = 4;
	printf("albert:%d\n",*c);   //4
}

```





## 指向常量的指针常量

指针的指向和指针指向的内容都是不可以修改的.

**const int *const ptr;**

都不可以修改