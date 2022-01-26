# 一.Lambda表达式



## 1.Lambda 表达式

Lambda 表达式，也可称为闭包，它是推动 Java 8 发布的最重要新特性。

Lambda 允许把函数作为一个方法的参数（函数作为参数传递进方法中）。

使用 Lambda 表达式可以使代码变的更加简洁紧凑。



在使用Lambda表达式之前先了解什么是函数式接口

### 函数式接口

- ==**只有函数式接口，才可以转换为lambda表达式**==

- ==**有且只有一个抽象方法的接口被称为函数式接口！**==

- **函数式接口可以显式的被@FunctionalInterface所表示，当被标识的接口不满足规定时，编译器会提示报错**

- 同时只要接口只定义了一个抽象方法，那它就还是一个函数式接口，哪怕这个接口有好多默认的方法实现，如Comparator接口类



**@FunctionalInterface`修饰函数式接口的，要求接口中的抽象方法只有一个。有多个抽象方法编译将报错**

加不加@FunctionalInterface对于接口是不是函数式接口没有影响，该注解知识提醒编译器去检查该接口是否仅包含一个抽象方法

Runnable接口就是一个函数式接口

![image-20220119155918160](https://gitee.com/abin_z/pic_bed/raw/master/image-20220119155918160.png)

**总结:**

**只要接口只定义了一个抽象方法，那它就是一个函数式接口,还有在上述Java Api中都有个@FunctionalInterface注解，这表示着该接口会设计成一个函数式接口，不符合规范的话，就会编译报错。**



### 使用Lambda表达式的前提

**对应接口==有且只有一个抽象方法==！！！**(函数式接口)



- **创建一个新的线程来执行要执行的任务, 普通的匿名内部类实现**

```java 
public class LambdaDemo01 {

  public static void main(String[] args) {
    functionOrdinary(); //调用普通的方法
  }

  public static void functionOrdinary() {
    //开启一个新线程
    new Thread(new Runnable() {
      @Override
      public void run() {
        System.out.println("新线程的输出语句..." + Thread.currentThread().getName());
      }
    }).start();
    System.out.println("主线程的输出语句..." + Thread.currentThread().getName());
  }
}
```

代码分析: 

1. Thread类需要一个Runnable接口作为参数，其中的抽象方法run方法是用来指定线程任务内容的核心
2. 为了指定run方法体，不得不需要Runnable的实现类
3. 为了省去定义一个Runnable 的实现类，不得不使用匿名内部类
4. 必须覆盖重写抽象的run方法，所有的方法名称，方法参数，方法返回值不得不都重写一遍，而且不能出错
5. 而实际上，我们只在乎方法体中的代码



- **使用Lambda表达式**

```Java
public class LambdaDemo01 {

  public static void main(String[] args) {
//    functionOrdinary(); //调用普通的方法
    functionLambda(); //调用使用了Lambda的方法
  }

  public static void functionOrdinary() {
    //开启一个新线程
    new Thread(new Runnable() {
      @Override
      public void run() {
        System.out.println("新线程的输出语句..." + Thread.currentThread().getName());
      }
    }).start();
    System.out.println("主线程的输出语句..." + Thread.currentThread().getName());
  }

  public static void functionLambda() {
    //开启一个新线程,使用Lambda表达式
    new Thread(() -> {
      System.out.println("新线程lambda表达式执行的语句..." + Thread.currentThread().getName());
    }).start();
    System.out.println("主线程的输出语句..." + Thread.currentThread().getName());
  }
}
```

主要区别:

匿名内部类方式:

```Java
    new Thread(new Runnable() {
      @Override
      public void run() {
        System.out.println("新线程的输出语句..." + Thread.currentThread().getName());
      }
    }).start();
```

Lambda表达式方式:

```Java
	new Thread(() -> {
      System.out.println("新线程lambda表达式执行的语句..." + Thread.currentThread().getName());
    }).start();
```



- **Lambda表达式优点**

1. 简化了匿名内部类的使用, 语法更加的简单



## 2.Lambda表达式的语法

```Java
(parameters) -> expression			(参数列表) -> 表达式				表达式-风格
    或
(parameters) ->{ statements; }		(参数列表) -> { 多条语句 }			块-风格
```

- **参数列表**：其中 () 用来描述参数列表
- **箭头**：`->`  为 lambda运算符 ，读作(goes to) , 作用是把参数列表和主体分隔为两个部分。
- **主体**：{} 用来描述方法体, 当块中只有一条语句的时候可以省略

```Java
maskList.sort((Mask o1, Mask o2) -> o1.getBrand().compareTo(o2.getBrand()));
```

![image-20220119175547389](https://gitee.com/abin_z/pic_bed/raw/master/image-20220119175547389.png)



以下是lambda表达式的重要特征:

- **可选类型声明：**不需要声明参数类型，编译器可以统一识别参数值。
- **可选的参数圆括号：**一个参数无需定义圆括号，但多个参数和无参需要定义圆括号。
- **可选的大括号：**如果主体包含了一个语句，就不需要使用大括号。
- **可选的返回关键字：**如果主体只有一个表达式返回值则编译器会自动返回值，大括号需要指定表达式返回了一个数值。

```Java
// 1. 不需要参数,返回值为 5  
() -> 5  
  
// 2. 接收一个参数(数字类型),返回其2倍的值  
x -> 2 * x  
  
// 3. 接受2个参数(数字),并返回他们的差值  
(x, y) -> x – y  
  
// 4. 接收2个int型整数,返回他们的和  
(int x, int y) -> x + y  
  
// 5. 接受一个 string 对象,并在控制台打印,不返回任何值(看起来像是返回void)  
(String s) -> System.out.print(s)
```

- #### Demo01: 完成一个无参无返回的demo


直接打印输出

定义函数式接口: userService

```Java
@FunctionalInterface
public interface UserService {
  void show();
}
```

在main方法中使用Lambda表达式:

```Java
public class LambdaDemo02 {

  public static void main(String[] args) {
    System.out.println("==================匿名内部类实现==================");
    function(new UserService() {
      @Override
      public void show() {
        System.out.println("匿名内部类实现方法....");
      }
    });
    System.out.println("==================Lambda方式实现==================");
    function(() -> {
      System.out.println("Lambda表达式方法实现....");
    });
    function(() -> System.out.println("Lambda的最简写法..."));
  }

  public static void function(UserService userService) {
    userService.show();
  }
}

```

- #### Demo02: 完成一个有两个参数有返回Demo


在List集合中保存多个Person对象，然后对这些对象做根据age排序操作

```Java
public class LambdaDemo03 {

  public static void main(String[] args) {
    List<Person> persons = new ArrayList<>();
    persons.add(new Person("tom", 18));
    persons.add(new Person("jack", 13));
    persons.add(new Person("marry", 16));
    persons.add(new Person("tony", 28));
    persons.add(new Person("keb", 26));

    //使用匿名内部类实现进行排序输出, 升序
    Collections.sort(persons, new Comparator<Person>() {
      @Override
      public int compare(Person o1, Person o2) {
        return o1.getAge() - o2.getAge();
      }
    });
    //使用Lambda表达式实现, 降序
    Collections.sort(persons, (o1, o2) -> o2.getAge() - o1.getAge());

    //遍历输出
    for (Person person : persons) {
      System.out.println(person);
    }
  }
}
```

- #### Demo03: 完成一个只有一个参数且有返回值的Demo


定义一个函数式接口PersonService

```Java
package com.abin.lambda.userService;

import com.abin.lambda.Entity.Person;

/**
 * @author Abin
 * @date 2022/01/19
 */
@FunctionalInterface
public interface PersonService {
  Integer getPersonAge( Person person);
}

```

main方法中使用Lambda表达式

```Java
public class LambdaDemo04 {

  public static void main(String[] args) {
    Person person = new Person("张三", 19);
    //使用匿名内部类的方式
    Integer age = function(person, new PersonService() {
      @Override
      public Integer getPersonAge(Person person) {
        return person.getAge();
      }
    });
    System.out.println("age = " + age);

    //使用Lambda表达式
    Integer age1 = function(person, p -> p.getAge()); //这里的p 只是形参
    System.out.println("age1 = " + age1);

    Integer integer = function(person, Person::getAge); //方法引用
    System.out.println(integer);
  }

  public static Integer function(Person person, PersonService personService) {
    return personService.getPersonAge(person);
  }
}

```

## 3.Lambda原理分析

### 匿名内部类的原理

**匿名内部类的本质是在==编译的时候==产生一个.class的文件**   XXXX$1.class 文件

![image-20220119201000251](https://gitee.com/abin_z/pic_bed/raw/master/image-20220119201000251.png)

可以使用反编译工具XJad查看编译时**匿名内部类生成**的代码:

```Java
// Decompiled by Jad v1.5.8e2. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://kpdus.tripod.com/jad.html
// Decompiler options: packimports(3) fieldsfirst ansi space 
// Source File Name:   LambdaDemo01.java

package com.abin.lambda;

import java.io.PrintStream;

// Referenced classes of package com.abin.lambda:
//			LambdaDemo01

static class LambdaDemo01$1
	implements Runnable
{

	public void run()
	{
		System.out.println((new StringBuilder()).append("新线程的输出语句...").append(Thread.currentThread().getName()).toString());
	}

	LambdaDemo01$1()
	{
	}
}
```



### Lambda表达式的实现原理

https://segmentfault.com/a/1190000023747150?utm_source=tag-newest

Lambda表达式的原理(写有lambda表达式的.class文件不能通过XJad查看)

我们可以通过JDK自带的工具javap对字节码文件进行反编译操作

```sh
javap -c -p filename.class
-c 表示对字节码文件进行反汇编
-p 表示显示所有的类和成员
```

对LambdaDemo01.class文件进行反汇编

```Java
javap -c -p LambdaDemo01.class
Compiled from "LambdaDemo01.java"
public class com.abin.lambda.LambdaDemo01 {
  public com.abin.lambda.LambdaDemo01();
    Code:
       0: aload_0
       1: invokespecial #1                  // Method java/lang/Object."<init>":()V
       4: return

  public static void main(java.lang.String[]);
    Code:
       0: invokestatic  #2                  // Method functionLambda:()V
       3: return

  public static void functionLambda();
    Code:
       0: new           #3                  // class java/lang/Thread
       3: dup
       4: invokedynamic #4,  0              // InvokeDynamic #0:run:()Ljava/lang/Runnable;
       9: invokespecial #5                  // Method java/lang/Thread."<init>":(Ljava/lang/Runnable;)V
      12: invokevirtual #6                  // Method java/lang/Thread.start:()V
      15: getstatic     #7                  // Field java/lang/System.out:Ljava/io/PrintStream;
      18: new           #8                  // class java/lang/StringBuilder
      21: dup
      22: invokespecial #9                  // Method java/lang/StringBuilder."<init>":()V
      25: ldc           #10                 // String 主线程的输出语句...
      27: invokevirtual #11                 // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      30: invokestatic  #12                 // Method java/lang/Thread.currentThread:()Ljava/lang/Thread;
      33: invokevirtual #13                 // Method java/lang/Thread.getName:()Ljava/lang/String;
      36: invokevirtual #11                 // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      39: invokevirtual #14                 // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
      42: invokevirtual #15                 // Method java/io/PrintStream.println:(Ljava/lang/String;)V
      45: return

  private static void lambda$functionLambda$0();
    Code:
       0: getstatic     #7                  // Field java/lang/System.out:Ljava/io/PrintStream;
       3: new           #8                  // class java/lang/StringBuilder
       6: dup
       7: invokespecial #9                  // Method java/lang/StringBuilder."<init>":()V
      10: ldc           #16                 // String 新线程lambda表达式执行的语句...
      12: invokevirtual #11                 // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      15: invokestatic  #12                 // Method java/lang/Thread.currentThread:()Ljava/lang/Thread;
      18: invokevirtual #13                 // Method java/lang/Thread.getName:()Ljava/lang/String;
      21: invokevirtual #11                 // Method java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
      24: invokevirtual #14                 // Method java/lang/StringBuilder.toString:()Ljava/lang/String;
      27: invokevirtual #15                 // Method java/io/PrintStream.println:(Ljava/lang/String;)V
      30: return
}
```

**可以看到反编译的源码中看到生成了一个静态方法**` private static void lambda$functionLambda$0();`

在Debug模式下查看lambda表达式的执行:

![image-20220119224025199](https://gitee.com/abin_z/pic_bed/raw/master/image-20220119224025199.png)

可以直观的看到方法体中的Lambda代码是在`lambda$functionLambda$0`方法中执行的

上面的效果可以理解为如下(可以这样理解):

```Java
public class LambdaDemo01 {

  public static void main(String[] args) {
	......
  }

  //可以这样理解为LambdaDemo01类中有lambda$functionLambda$0这么一个静态方法
  private static void lambda$functionLambda$0() {
    System.out.println("新线程lambda表达式执行的语句..." + Thread.currentThread().getName());
  }
}
```

---

---

为了更加直观的理解这个内容, 在运行的时候添加`-Djdk.internal.lambda.dumpProxyClasses`参数, 作用是将内部的.class字节码输出到文件中

```sh
java -Djdk.internal.lambda.dumpProxyClasses 包名.类名
```

```sh
java -Djdk.internal.lambda.dumpProxyClasses com.abin.lambda.LambdaDemo01
```

这是在类文件中会生成一个`LambdaDemo01$$Lambda$1.class`的字节码文件

使用反编译工具XJad查看编译时候生成的代码:

```Java
// Decompiled by Jad v1.5.8e2. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://kpdus.tripod.com/jad.html
// Decompiler options: packimports(3) fieldsfirst ansi space 

package com.abin.lambda;


// Referenced classes of package com.abin.lambda:
//			LambdaDemo01

final class LambdaDemo01$$Lambda$1
	implements Runnable
{

	public void run()
	{
		LambdaDemo01.lambda$functionLambda$0();
	}

	private LambdaDemo01$$Lambda$1()
	{
	}
}
```

可以看到这个LambdaDemo01$$Lambda$1匿名内部类实现了Runnable接口,重写了run()方法, 然后在run()方法中调用了LambdaDemo01类中的生成的静态方法lambda$functionLambda$0(), 也就是调用了Lambda中的内容

---

总结 : 由此可以知道Lambda表达式，**编译器在类中生成一个静态函数，运行时==以内部类形式==调用该静态函数**。

本质上可以理解为如下代码:

```Java
public class LambdaDemo01 {

  public static void main(String[] args) {
	//开启一个新线程, 以匿名内部类的方式调用静态函数lambda$functionLambda$0
    new Thread(new Runnable() {
      @Override
      public void run() {
        LambdaDemo01.lambda$functionLambda$0();
      }
    }).start();
  }

  //可以这样理解为LambdaDemo01类中有lambda$functionLambda$0这么一个静态方法
  private static void lambda$functionLambda$0() {
    System.out.println("新线程lambda表达式执行的语句..." + Thread.currentThread().getName());
  }
}
```

小结:

-  匿名内部类在编译的时候会生成一个xxx$1.class 的字节码文件
-  Lambda表达式在运行的时候会形成一个类
  1. 在类中新增一个静态方法lambda$xxx$0(), 这个方法体内就是Lambda表达式中的代码
  2. 还会形成一个匿名内部类xxx$$Lambda$1, 实现接口, 重写接口中的抽象方法
  3. 在接口中重写的方法中调用新生成的静态方法lambda$xxx$0(), 也就执行了Lambda表达式中的代码

## 4.Lambda和匿名内部类的对比

1. 所需类型不一样
  - 匿名内部类的类型可以是 类，抽象类，接口
  - Lambda表达式需要的类型==必须是接口==
2. 抽象方法的数量不一样
  - 匿名内部类所需的接口中的抽象方法的数量是随意的
  - Lambda表达式所需的接口中==只能有一个抽象方法==
3. 实现原理不一样
  - 匿名内部类是在编译后形成一个class
  - Lambda表达式是在==程序运行的时候==动态生成class





# 二.接口默认方法和静态方法

## 1. JDK8 中针对接口有增强.  

**在JDK8以前,接口中只能有静态常量和抽象方法**

```Java
interface 接口名{
    静态常量;
    抽象方法;
}
```

**而在JDK8以后对接口进行了增强, 接口中可以有默认方法和静态方法**

```Java
interface 接口名{
    静态常量;
    抽象方法;
    默认方法;
    静态方法;
}
```



## 2.默认方法default

### 2.1 为什么增加默认方法

在JDK8以前接口中只能有静态常量和抽象方法,抽象方法不能有方法实现

```Java
public class InterfaceBoost {
  public static void main(String[] args) {
    AAA aaa = new AAA();
    aaa.abstractFunc();
  }
}

interface III {
  public static final Integer number = 12;   //静态常量
  public void abstractFunc();                //抽象方法
}

class AAA implements III {

  @Override
  public void abstractFunc() {
    System.out.println("实现类AAA中的重写的方法...");
  }
}

class BBB implements III{

  @Override
  public void abstractFunc() {

  }
}
```

问题: 这个接口中可以有多个抽象方法的, **当我们想去拓展接口增加抽象方法的时候, ==所有的实现类都需要去重写==这个新增的抽象方法** (这是一个很繁琐的事情, 例如JDK8中的Map接口中新增了一个forEach方法, 如果按原来的模式就必须在Map接口的164个实现类中都要重写这个forEach方法...)

### 2.2 JDK8之后接口的默认方法

接口中默认方法可以有默认方法体,  需要添加default关键字, 需要给出默认方法体, 作用是为了接口的拓展

接口中默认方法的语法格式是:

```Java
interface 接口名{
    修饰符 default 返回类型 方法名(){
        默认方法体;
    }
}
```

```Java
public class InterfaceBoost {
  public static void main(String[] args) {
    AAA aaa = new AAA();
    BBB bbb = new BBB();
    aaa.abstractFunc();
    aaa.defaultFunc();
    bbb.defaultFunc();
  }
}

interface III {
  //接口中有些关键字可以省略
  public static final Integer number = 12;   //静态常量
  public void abstractFunc();                //抽象方法

  public default void  defaultFunc(){		//默认方法: 添加关键字default
    System.out.println("接口中的默认default方法");
  }

}

//此时AAA类可以不用实现接口中存在的默认方法defaultFunc
class AAA implements III {
  @Override
  public void abstractFunc() {
    System.out.println("实现类AAA中的重写的方法...");
  }
}

class BBB implements III{

  //也可以在实现类中重写接口中存在的默认方法
  @Override
  public void defaultFunc() {
    III.super.defaultFunc();
    System.out.println("实现类中重写接口中的默认方法...");
  }

  //必须实现这个abstractFunc抽象方法
  @Override
  public void abstractFunc() {
  }
}
```

![image-20220120111009823](https://gitee.com/abin_z/pic_bed/raw/master/image-20220120111009823.png)

### 2.3 接口中默认方法的使用

接口中的默认方法有两种使用方式:

1. **实现类中可以==直接调用==接口中的默认方法**
2. **实现类中可以==重写==接口中的默认方法**



## 3.静态方法static

JDK8 中为接口新增了静态方法, 作用也是为了接口的拓展

### 3.1静态方法的语法

```Java
interface 接口名{
    修饰符 static 返回类型 方法名称(){
        方法体;
    }
}
```

```Java
public class InterfaceBoost {
  public static void main(String[] args) {
    AAA aaa = new AAA();
    //aaa.staticFunc(); 不能这样调用
    III.staticFunc(); //接口中的静态方法只能通过接口来调用
  }
}

interface III {
  //接口中有些关键字可以省略
  public static final Integer number = 12;   //静态常量
  public void abstractFunc();                //抽象方法

  //接口中的默认方法, 添加关键字default
  public default void  defaultFunc(){
    System.out.println("接口中的默认default方法");
  }
    
  //接口中的静态方法,添加关键字static
  public static void staticFunc(){			
    System.out.println("接口中的静态方法, 不能被实现类重写, 只能通过接口名.静态方法名调用");
  }
}

class AAA implements III {
  @Override
  public void abstractFunc() {
    System.out.println("实现类AAA中的重写的方法...");
  }
}
```

### 3.2接口中的静态方法的使用

- 接口中的静态方法不能被实现类重写
- 调用的时候只能通过: 接口名.静态方法名  的方式来调用



## 4.接口中默认方法和静态方法的区别

- 接口默认方法通过 **对象.默认方法名** 调用,  接口静态方法通过 **接口名.静态方法名** 调用
- 实现类可以直接调用接口的默认方法, 也可以重写接口的默认方法
- 实现类不能重写接口的静态方法, 只能使用接口名调用



# 三.函数式接口

## 1.函数式接口的由来

使用Lambda表达式的前提是接口是函数式接口, 而Lambda表达式使用时不关心接口名,  抽象方法名. **只关心抽象方法的参数列表和返回值类型**。因此为了让我们使用Lambda表达式更加的方法，在IDK中提供了大量常用的函数式接口

```Java
public class FuncInterface {

  public static void main(String[] args) {
    String str = "Hello World!";
    String s = fun1(msg -> msg.toUpperCase(Locale.ROOT), str); //只关心传入的参数,和返回值
    System.out.println(s);
  }

  public static String fun1(Operator operator, String argument){
    return operator.handle(argument);
  }
}

@FunctionalInterface
interface Operator{			//函数式接口
  String handle(String s);
}
```

## 2.常用的函数式接口

在JDK8 中, 提供了一些函数式接口, 主要是在java.util.function包中, 主要作用是方便使用不用自己定义接口

### 2.1 Supplier

**供应者: 无参有返回值接口**  泛型是指定返回值的类型

 get()方法

```Java
@FunctionalInterface
public interface Supplier<T> {

    /**
     * Gets a result.
     *
     * @return a result
     */
    T get();
}
```

使用如下:

```Java
public class SupplierTest {

  public static void main(String[] args) {
    printMax(() -> {
      int[] array = {41, 56, 69, 83, 38, 59};
      Arrays.sort(array);
      return array[array.length - 1];
    });
  }

  public static void printMax(Supplier<Integer> supplier) {   //这里的泛型Integer 是指定的返回类型
    System.out.println("supplier.get() = " + supplier.get());
  }
}
```



### 2.2 Consumer

**消费者: 有参无返回接口**   泛型是指定参数的类型

accept()方法

```Java
@FunctionalInterface
public interface Consumer<T> {

    /**
     * Performs this operation on the given argument.
     *
     * @param t the input argument
     */
    void accept(T t);

    /**
     * Returns a composed {@code Consumer} that performs, in sequence, this
     * operation followed by the {@code after} operation. If performing either
     * operation throws an exception, it is relayed to the caller of the
     * composed operation.  If performing this operation throws an exception,
     * the {@code after} operation will not be performed.
     *
     * @param after the operation to perform after this operation
     * @return a composed {@code Consumer} that performs in sequence this
     * operation followed by the {@code after} operation
     * @throws NullPointerException if {@code after} is null
     */
    default Consumer<T> andThen(Consumer<? super T> after) {
        Objects.requireNonNull(after);
        return (T t) -> { accept(t); after.accept(t); };
    }
}
```

抽象方法accept的基本使用:

```Java
public class ConsumerTest {

  public static void main(String[] args) {
    String s = "Consumer接口的使用...";
    funTest(arg -> {
      System.out.println("arg = " + arg.toUpperCase(Locale.ROOT));
    }, s);
  }

  public static void funTest(Consumer<String> consumer, String str) { //泛型是指定参数的类型
    consumer.accept(str);     //有参数,没有返回值
  }
}

```

**默认方法andThen**的基本使用:

```Java
public class ConsumerAndThenTest {

  public static void main(String[] args) {
    String s = "Consumer接口的使用...";
    funTest(arg -> {
      System.out.println("arg = " + arg.toUpperCase(Locale.ROOT));
    }, msg -> {
      System.out.println("msg = " + msg.toLowerCase(Locale.ROOT));
    }, s);
  }

  public static void funTest(Consumer<String> c1, Consumer<String> c2, String str) { //泛型是指定参数的类型
    c1.accept(str);     //步骤1
    c2.accept(str);     //步骤2
  }
}
```

存在一步接一步的流程, 那么上面的代码可以修改为如下:

```Java
public class ConsumerAndThenTest {

  public static void main(String[] args) {
    String s = "Consumer接口的使用...";
    funTest(arg -> {
      System.out.println("arg = " + arg.toUpperCase(Locale.ROOT));
    }, msg -> {
      System.out.println("msg = " + msg.toLowerCase(Locale.ROOT));
    }, s);
  }

  public static void funTest(Consumer<String> c1, Consumer<String> c2, String str) { //泛型是指定参数的类型
//    c1.accept(str);     //有参数,没有返回值
//    c2.accept(str);     //有参数,没有返回值
    c1.andThen(c2).accept(str);     //先执行c1然后再执行c2; 看源码理解
    c2.andThen(c1).accept(str);     //先执行c2然后再执行c1
  }
}
```

**Consumer的default方法andThen()的理解:** (andThen然后)

如果一个方法的参数和返回值全部都是Consumer类型, 那么可以实现这样的效果: 消费一个数据的时候, 首先做一个操作,然后在做一个操作,实现组合, 这个方法就是Consumer接口中的default方法 andThen方法;

```Java
    default Consumer<T> andThen(Consumer<? super T> after) {
        Objects.requireNonNull(after);
        return (T t) -> { accept(t); after.accept(t); };
    }
```



### 2.3 Function

**函数: 有参有返回的接口**  Function接口是根据一个类型的数据得到另外一个类型的数据, 前者称为前置条件, 后者称为后置条件, 有参数也有返回值;

apply()方法

```Java
@FunctionalInterface
public interface Function<T, R> {

    /**
     * Applies this function to the given argument.
     *
     * @param t the function argument
     * @return the function result
     */
    R apply(T t);
}
```

基本使用: 

```Java
public class FunctionTest {

  public static void main(String[] args) {
    function(arg -> arg.length(), "hello");  //返回字符串的长度
  }

  public static void function(Function<String, Integer> function, String str) {
    Integer apply = function.apply(str);
    System.out.println("apply = " + apply); //打印字符串的长度
  }
}
```

Function的andThen方法:  ` f1.andThen(f2).apply(str); `//**先执行f1, 然后在执行f2;**

```Java
public class FunctionAndThenTest {

  public static void main(String[] args) {
    function(arg -> {
      int length = arg.length();
      System.out.println(length);
      return length;
    }, msg -> msg * 10, "hello world");
  }

  public static void function(Function<String, Integer> f1, Function<Integer, Integer> f2,
      String str) {
    Integer apply = f1.andThen(f2).apply(str); //先执行f1, 然后在执行f2;
    System.out.println("apply = " + apply);
  }
}
```

Function的默认compose方法: ` f1.compose(f2).apply(str); ` // **是先执行f2, 然后在执行f1;**

```Java
public class FunctionAndThenTest {

  public static void main(String[] args) {
    function(arg -> {
      int length = arg.length();
      System.out.println(length);
      return length;
    }, msg -> msg * 10, "hello world");
  }

  public static void function(Function<String, Integer> f1, Function<Integer, Integer> f2,
      String str) {
//    Integer apply = f1.andThen(f2).apply(str); //先执行f1, 然后在执行f2;
    // 默认方法compose和andThen的执行顺序是刚好相反的
    Integer apply = f2.compose(f1).apply(str);  // 同样的是先执行f1, 然后在执行f2;
    System.out.println("apply = " + apply);
  }
}

```

Function接口的andThen方法源码:

```Java
    default <V> Function<T, V> andThen(Function<? super R, ? extends V> after) {
        Objects.requireNonNull(after);
        return (T t) -> after.apply(apply(t));
    }
```

Function接口的compose方法源码:

```Java
    default <V> Function<V, R> compose(Function<? super V, ? extends T> before) {
        Objects.requireNonNull(before);
        return (V v) -> apply(before.apply(v));
    }
```

**可以看到默认方法andThen默认方法compose的执行顺序刚好相反**

Function接口中还有一个静态方法identity: 作用是传入的什么参数就返回什么参数, 源码如下

```Java
    static <T> Function<T, T> identity() {
        return t -> t;
    }
```



### 2.4 Predicate

**有参返回boolean类型的接口**  作用是接受一个参数,返回boolean类型的值

 test()方法

```Java
@FunctionalInterface
public interface Predicate<T> {

    /**
     * Evaluates this predicate on the given argument.
     *
     * @param t the input argument
     * @return {@code true} if the input argument matches the predicate,
     * otherwise {@code false}
     */
    boolean test(T t);
```

使用: 

```Java
public class PredicateTest {

  public static void main(String[] args) {
    function(arg -> {
      boolean equals = arg.equals(1000);
      return equals;
    });
  }

  public static void function(Predicate<Integer> pred) {
    System.out.println("pred.test(100) = " + pred.test(100));
  }
}
```

Predicate接口中的and方法使用: 

```Java
public class PredicateDefaultTest {

  public static void main(String[] args) {
    function(n1 -> n1 >= 60, n2 -> n2 <= 100, 80);
  }

  public static void function(Predicate<Integer> p1, Predicate<Integer> p2, Integer s) {
    // s 同时满足p1,p2;
    if (p1.and(p2).test(s)) {
      System.out.println("成绩合格");
    } else {
      System.out.println("成绩不合格");
    }
  }
}
```

在Predicate接口中提供了很多的默认方法, 逻辑处理 and , or , negate , isEqual 方法

源码如下: 

```Java
package java.util.function;
import java.util.Objects;

@FunctionalInterface
public interface Predicate<T> {
    boolean test(T t);
	//and 
    default Predicate<T> and(Predicate<? super T> other) {
        Objects.requireNonNull(other);
        return (t) -> test(t) && other.test(t);
    }
	//negate
    default Predicate<T> negate() {
        return (t) -> !test(t);
    }
	//or
    default Predicate<T> or(Predicate<? super T> other) {
        Objects.requireNonNull(other);
        return (t) -> test(t) || other.test(t);
    }
	//isEqual
    static <T> Predicate<T> isEqual(Object targetRef) {
        return (null == targetRef)
                ? Objects::isNull
                : object -> targetRef.equals(object);
    }
}
```



# 四.方法引用

Java8 方法引用的细节:  https://www.cnblogs.com/xiaoxi/p/7099667.html

## 1.方法引用的由来

使用普通的lambda表达式有时候也会很显得冗余

```Java
public class FunctionRefTest01 {

  // TODO: 2022/1/21 计算数组的和

  public static void main(String[] args) {
    int[] array = {10, 20, 30};

    getSum(arg -> {
      int sum = 0;
      for (int item : arg) {
        sum += item;
      }
      return sum;
    }, array);
  }


  public static void getSum(Function<int[], Integer> function, int[] array) {
    Integer sum = function.apply(array);
    System.out.println("sum = " + sum);
  }
}
```

**方法引用**是用来直接访问类或者实例的已经存在的方法或者构造方法

```Java
public class FunctionRefTest02 {

  public static void main(String[] args) {
    getTotal(FunctionRefTest02::getSum);	//方法引用
  }

  public static void getSum(int[] array) {
    int sum = 0;
    for (int item : array) {
      sum += item;
    }
    System.out.println("sum = " + sum);
  }

  public static void getTotal(Consumer<int[]> consumer) {
    int[] array = {10, 20, 30};
    consumer.accept(array);
  }
}
```





## 2.方法引用的概述

方法引用（Method References）

- **当要传递给Lambda体的操作，已经有了实现方法，可以使用方法引用。**

- ==**方法引用是用来直接访问类或者实例的已经存在的方法或者构造方法**。==

- 方法引用提供了一种引用而不执行方法的方式，它需要由兼容的函数式接口构成的目标类型上下文。计算时，方法引用会创建函数式接口的一个实例。

- 当Lambda表达式中只是执行一个方法调用时，不用Lambda表达式，直接通过方法引用的形式可读性更高一些。
- 方法引用是一种更简洁易懂的Lambda表达式。

- 注意方法引用是一个Lambda表达式，其中方法引用的操作符是双冒号"::"。



**常见的方法引用方式**

1. instanceName::methodName  对象::方法名
2. ClassName::staticmethodName  类名::静态方法名
3. ClassName::methodName 类名::普通方法名
4. ClassName::new     类名::new 调用的构造器
5. TypeName[]::new   String[]::new  调用数组的构造器

| 方法引用类别       | 举例             |
| ------------------ | ---------------- |
| 引用静态方法       | `Integer::sum`   |
| 引用某个对象的方法 | `list::add`      |
| 引用某个类的方法   | `String::length` |
| 引用构造方法       | `HashMap::new`   |

### 2.1 对象名::方法名

这是最常用的方法, 如果一个类中已经存在了一个成员方法, 则可以通过对象名::方法名调用

```Java
public class FunctionRefTest03 {

  public static void main(String[] args) {
    Date now  = new Date();
    //使用lambda表达式
    Supplier<Long> supplier = ()-> now.getTime();
    System.out.println("supplier = " + supplier.get());

    //使用方法引用    对象::方法名
    Supplier<Long> supplier1 = now::getTime;
    System.out.println("supplier1 = " + supplier1.get());
  }
}
```

方法引用的注意事项:

1. 被引用的方法, 参数要和接口中的抽象方法的参数一致
2. 当接口的抽象方法有返回值的时候, 被引用的方法也必须要有返回值

### 2.2 类名::静态方法名

这个写法也是比较常用的

```Java
public class FunctionRefTest04 {

  public static void main(String[] args) {
    //使用lambda表达式
    Supplier<Long> currentTime = ()->System.currentTimeMillis();
    System.out.println("currentTime.get() = " + currentTime.get());
    //使用方法引用     类名::静态方法名
    Supplier<Long> currentTime1 = System::currentTimeMillis;
    System.out.println("currentTime1.get() = " + currentTime1.get());
  }
}
```

### 2.3 类名::普通方法名

Java面向对象中, 类名只能调用静态方法, 类名引用示例方法是有前提的, ==实际上`类名::普通方法名`是拿第一个参数作为方法的调用者;==

```Java
public class FunctionRefTest05 {

  public static void main(String[] args) {
    Function<String, Integer> function = (s -> s.length());
    System.out.println("function.apply(\"hello\") = " + function.apply("hello"));
	//使用方法引用, 类名::普通方法名     其实是用第一个参数作为方法的调用者
    Function<String, Integer> function1 = (String::length);
    System.out.println("function1.apply(\"str\") = " + function1.apply("str"));
	//两个参数一个返回值使用BiFunction
    BiFunction<String, String, String> biFunction = String::concat;
    String apply = biFunction.apply("hello ", "world");
    System.out.println("apply = " + apply);
  }
}
```

### 2.4 类名::构造器

**由于构造器的名称和类名完全一致, 所有构造器引用使用**`类名::new`

```Java
public class FunctionRefTest06 {

  public static void main(String[] args) {
    Supplier<Person> supplier = () -> new Person();
    System.out.println("supplier.get() = " + supplier.get());
    //使用方法引用   类名::new    返回一个对象
    Supplier<Person> p = Person::new;
    System.out.println("p.get() = " + p.get());

    //使用全参构造器的方法引用
    BiFunction<String, Integer, Person> personBiFunction = Person::new;
    Person person = personBiFunction.apply("小明", 18);
    System.out.println("person = " + person);
  }
}
```

### 2.5 数组[]::构造器

使用方法引用构造一个数组:

```Java
public class FunctionRefTest07 {

  public static void main(String[] args) {
    Function<Integer, String[]> function = (n) -> {
      return new String[n];
    };
    String[] apply1 = function.apply(5);
    System.out.println("apply1.length = " + apply1.length);

    //使用方法引用   类型类名[]::new  返回一个数组
    Function<Integer, String[]> func = String[]::new;
    String[] apply = func.apply(10);
    System.out.println("apply.length = " + apply.length);
  }
}
```

### 小结

- 方法引用是对lambda表达式符合特定情况下的一种缩写形式, 可以使得lambda表达式更加精简
- 不过要注意方法引用只能引用已经存在的方法



# 五.Stream流 API

Java8 Stream:     https://blog.csdn.net/mu_wind/article/details/109516995

深入理解Java函数式编程: https://www.cnblogs.com/CarpenterLee/category/965121.html

![stream](https://gitee.com/abin_z/pic_bed/raw/master/73063862340e4cfcbb31fb53b3f5db0d.jpg)

## 1. 集合处理数据的弊端

当我们在需要对集合中的元素进行操作的时候,除了必需的添加,删除,获取外,最典型的操作就是集合遍历

```java 
public class StreamTest01 {

  public static void main(String[] args) {
    List<String> list = Arrays.asList("张三", "张三丰", "小明", "佩奇", "爱迪生", "张培培");
    List<String> tempList = new ArrayList<>();
    //获取姓张的用户
    for (String s : list) {
      if (s.startsWith("张")){
        tempList.add(s);
      }
    }
    ArrayList<String> tempList2 = new ArrayList<>();
    //获取名称长度为3的用户
    for (String s : tempList) {
      if(s.length() == 3){
        tempList2.add(s);
      }
    }

    //遍历输出
    for (String s : tempList2) {
      System.out.println("s = " + s);
    }
  }
}
```

上面的代码也可以实现想要的功能, 但是存在诸多问题: 只要操作数据就要进行遍历, 只要操作就要for循环,而且还要定义很多的中间的集合容器. 代码是比较冗余的, 而Java8中的stream可以解决这些问题

```Java
public class StreamTest01 {

  public static void main(String[] args) {
    List<String> list = Arrays.asList("张三", "张三丰", "小明", "佩奇", "爱迪生", "张培培");

    //使用Java8中的stream流
    list.stream()
        .filter(s -> s.startsWith("张"))
        .filter(s->s.length() == 3)
        .forEach(System.out::println);
  }
}
```

上面的streamAPI的含义: 获取流, 过滤"张", 过滤长度, 逐一打印, 代码相比于前面更加简洁直观

## 2.Stream流式思想概述

- Stream和IO流 (inputstream/outputstream) 没有任何关系,请暂时忘记对传统IO流的固有印象.
- Stream流式思想类似于工厂车间的“生产流水线", 只对数据进行处理.
- **Stream流不是一种数据结构,不保存数据,而是对数据进行加工处理.**
- Stream可以看作是流水线上的一个工序。在流水线上,通过多个工序让一个原材料加工成一个商品.

![image-20220124174248859](https://gitee.com/abin_z/pic_bed/raw/master/image-20220124174248859.png)

![image-20220124174633807](https://gitee.com/abin_z/pic_bed/raw/master/image-20220124174633807.png)

stream API 能让我们快速完成许多复杂的操作, 如筛选, 切片, 映射, 查找, 去重, 统计, 匹配和归约等操作

## 3.Stream流的获取方法

### 3.1根据Collocation获取

首先, java.util.Collection接口中加入了default方法stream, 则说明实现了Collocation接口的集合都可以使用.stream()方式获取Stream流

```Java
public class StreamTest02 {

  public static void main(String[] args) {
   //实现了Collocation接口的集合都可以使用.stream()方式获取流
    ArrayList<String> arrayList = new ArrayList<>();
    Stream<String> stream = arrayList.stream();

    HashSet<String> hashSet = new HashSet<>();
    Stream<String> stream1 = hashSet.stream();

    Vector<Integer> vector = new Vector<>();
    Stream<Integer> stream2 = vector.stream();
  }
}
```

但是Map集合没有实现Collocation接口, 所以Map集合不能直接获取Stream流, 这时怎么办呢, 可以根据Map集合获取相应的 Key Value 的集合.

```Java
public class StreamTest03 {

  public static void main(String[] args) {
    HashMap<String, String> hashMap = new HashMap<>();

    Set<String> keySet = hashMap.keySet();
    Stream<String> stream = keySet.stream();

    Collection<String> values = hashMap.values();
    Stream<String> stream1 = values.stream();

    Set<Entry<String, String>> entrySet = hashMap.entrySet();
    Stream<Entry<String, String>> stream2 = entrySet.stream();
  }
}
```



### 3.2通过Stream的of方法

在实际开发过程中, 不可避免的使用数组, 由于数组对象不可能添加默认方法, **所以在Stream接口中提供了一个static静态方法of()方法, 可以获取数组对象的Stream流,** 但是需要注意: ==使用数组对象的时候不能使用基本类型的数组==

```Java
  public static void main(String[] args) {
    //当在实际操作过程中, 如果只对数组进行操作, 怎么将数组转化为Stream?

    Stream<String> stream = Stream.of("s1", "s2", "s3", "s4");

    String[] array = {"tom", "jack", "marry"};
    Stream<String> stream1 = Stream.of(array);

    Integer[] arr = {1, 2, 3, 4, 5};
    Stream<Integer> stream2 = Stream.of(arr);

    stream2.forEach(System.out::println);

    //注意, 使用Stream.of()方法的时候,只能使用包装类, 不能使用基本数据类型
    int[] arrays = {55, 66, 77, 88};
    Stream<int[]> stream3 = Stream.of(arrays); // 不能使用基本数据类型, 基本数据类型的数据是不行的

    stream3.forEach(System.out::println);
  }
}
```

![image-20220124182816731](https://gitee.com/abin_z/pic_bed/raw/master/image-20220124182816731.png)

虽然大部分情况下*stream*是容器调用`Collection.stream()`方法得到的，但*stream*和*collections*有以下不同：

- **无存储**。*stream*不是一种数据结构，它只是某种数据源的一个视图，数据源可以是一个数组，Java容器或I/O channel等。
- **为函数式编程而生**。对*stream*的任何修改都不会修改背后的数据源，比如对*stream*执行过滤操作并不会删除被过滤的元素，而是会产生一个不包含被过滤元素的新*stream*。
- **惰式执行**。*stream*上的操作并不会立即执行，只有等到用户真正需要结果的时候才会执行。
- **可消费性**。*stream*只能被“消费”一次，一旦遍历过就会失效，就像容器的迭代器那样，想要再次遍历必须重新生成。



## 4.Stream常用方法

`Stream`可以由数组或集合创建，对流的操作分为两种：

- 中间操作，==每次返回一个**新的Stream**，支持链式调用==。

- 终端操作，==每个流只能进行一次终端操作，终端操作结束后流无法再次使用。==,也不支持链式调用, 终端操作会产生一个新的集合或值。

另外，`Stream`有几个特性：

1. ==stream不存储数据==，而是按照特定的规则对数据进行计算，一般会输出结果。
2. ==stream不会改变数据源==，通常情况下会产生一个新的集合或一个值。
3. ==stream具有延迟执行特性==，只有调用终端操作时，中间操作才会执行。



对*stream*的操作分为为两类，**中间操作(intermediate operations)和结束操作(terminal operations)**，二者特点是：

1. **中间操作总是会惰式执行**，调用中间操作只会生成一个标记了该操作的新*stream*，仅此而已。
2. **结束操作会触发实际计算**，计算发生时会把所有中间操作积攒的操作以*pipeline*的方式执行，这样可以减少迭代次数。计算完成之后*stream*就会失效。

如果你熟悉Apache Spark RDD，对*stream*的这个特点应该不陌生。

下表汇总了`Stream`接口的部分常见方法：

| 操作类型 | 接口方法                                                     |
| -------- | ------------------------------------------------------------ |
| 中间操作 | concat() distinct() filter() flatMap() limit() map() peek() skip() sorted() parallel() sequential() unordered() |
| 结束操作 | allMatch() anyMatch() collect() count() findAny() findFirst() forEach() forEachOrdered() max() min() noneMatch() reduce() toArray() |

区分中间操作和结束操作最简单的方法，**就是看方法的返回值，返回值为*stream*的大都是中间操作，否则是结束操作**。



### 4.1 forEach

forEach方法是用来遍历流中的数据的 **【结束操作】**

```java
    void forEach(Consumer<? super T> action);
```

该方法接受一个Consumer接口， 会将每一个流元素交给函数处理

```Java
public class StreamTest05ForEach {

  public static void main(String[] args) {
    List<String> list = Arrays.asList("xiaoming", "peiqi", "zhangsan");
    Stream<String> stream = list.stream();
    stream.forEach((s) -> {			//forEach是一个结束操作
      System.out.println(s);
    });

    list.stream().forEach(System.out::println);
  }
}
```

### 4.2 count

count 方法用来统计Stream流中元素的个数**【结束操作】**

```Java
    long count();
```

```Java
public class StreamTest06Count {

  public static void main(String[] args) {
    long count = Stream.of("tom", "java", "mybatis", "marry").count();		//count也是一个结束操作
    System.out.println("count = " + count);		//count = 4
  }
}
```

### 4.3 filter

filter 方法的作用是用来过滤数据的, 返回符合条件的数据流 (中间操作) 

```Java
Stream<T> filter(Predicate<? super T> predicate);  //在使用filter的时候使用的需要接受一个 Predicate 函数式接口参数
```

![image-20220126101032485](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126101032485.png)

```Java
  public static void main(String[] args) {
    Stream.of("A1", "a1", "a2", "b3", "f4", "a3", "l5")
        .filter((s) -> s.contains("a"))
        .forEach(System.out::println);
  }
```

输出:

```Java
a1
a2
a3
```

### 4.4 limit

limit方法可以对流进行截取,只取前n个数据, (中间操作),返回的是一个新的流对象

```Java
    Stream<T> limit(long maxSize);
```

![image-20220126104217940](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126104217940.png)

```Java
  public static void main(String[] args) {
    Stream.of("A1", "a1", "a2", "b3", "f4", "a3", "l5")
        .limit(4)     //只截取前面4个数字
        .forEach(System.out::println);
  }
```

输出: 

```Java
A1
a1
a2
b3
```

### 4.5 skip

skip方法的作用是跳过前面的n个元素(中间操作), 返回的是一个新的流对象, 作用是和limit是相反的

```Java
    Stream<T> skip(long n);
```

![image-20220126104514020](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126104514020.png)

```Java
  public static void main(String[] args) {
    Stream.of("A1", "a1", "a2", "b3", "f4", "a3", "l5")
        .skip(4)     //跳过前面4个数字
        .forEach(System.out::println);
  }
```

输出:

```Java
f4
a3
l5
```

### 4.6 map

如果我们需要将流中的元素映射到另一个流中,可以使用map方法, 使用得时候需要传入Function函数式接口参数

```Java
    <R> Stream<R> map(Function<? super T, ? extends R> mapper);
```

![image-20220126110546121](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126110546121.png)

```Java
  public static void main(String[] args) {
    Stream.of("1", "9", "7", "4", "2", "6")
        .map(s -> Integer.parseInt(s) + 100)      //将传入的字符串类型转换为int型再加上100
        .forEach(System.out::println);
  }
```

输出: 

```Java
101
109
107
104
102
106
```

### 4.7 sorted

sorted方法可以将流中的数据进行排序, (中间操作) 这个方法存在一个重载函数

```Java
    Stream<T> sorted();				//sorted排序函数: 无需传入参数
    Stream<T> sorted(Comparator<? super T> comparator);			//重载的sorted排序函数: 需要传入Comparator的函数式接口
```

```Java
  public static void main(String[] args) {
    Stream.of("1", "9", "7", "4", "2", "6")
        .map(s -> Integer.parseInt(s) + 100)      //将传入的字符串类型转换为int型再加上100
        .sorted()				//进行默认排序, 递增
        .forEach(System.out::println);
  }
```

```Java
  public static void main(String[] args) {
    Stream.of("1", "9", "7", "4", "2", "6")
        .map(s -> Integer.parseInt(s) + 100)      //将传入的字符串类型转换为int型再加上100
//        .sorted()
        .sorted((a1, a2) -> a2 - a1)        //传入一个Comparator的函数式接口,可以自定义排序规则
        .forEach(System.out::println);
  }
```

 ### 4.8 distinct

distinct方法的作用是去掉重复数据, 但是需要注意的是什么情况下才算重复(通过重写equals()和hashcode()方法) 返回一个新的Stream流(中间操作)

注意: **Stream类中的 distinct 方法对于基本数据类型是可以直接去重的, 但是对于自定义类型的数据, 需要手动重写hashcode和equals方法来移除重复元素**

```java 
    Stream<T> distinct();
```

![image-20220126112619285](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126112619285.png)

```java 
  public static void main(String[] args) {
    Stream.of("1", "9", "7", "4", "2", "6","2")   //重复的2
        .map(s -> Integer.parseInt(s) + 100)      //将传入的字符串类型转换为int型再加上100
//        .sorted()
        .sorted((a1, a2) -> a2 - a1)        //传入一个Comparator的函数式接口,可以自定义排序规则
        .distinct()     //去重
        .forEach(System.out::println);
  }
```

输出: 

```Java
109
107
106
104
102			//只有一个102
101	
```

注意: **==distinct方法对自定义的数据类型去重, 一定要重写 equals 方法和 hashcode 方法==**,  否则去重结果可能不符合预想结果

```Java
  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三", 19));
    people.add(new Person("李四", 19));
    people.add(new Person("张三", 19));
    people.add(new Person("小明", 23));
    people.add(new Person("张三", 19, 175.0));

    people.stream()
        .distinct()    //自定义类型没有重写equals和hashcode方法时可能不是自己想要的去重
        .forEach(System.out::println);
  }

输出结果:
Person{name='张三', age=19, height=null}
Person{name='李四', age=19, height=null}
Person{name='张三', age=19, height=null}
Person{name='小明', age=23, height=null}
Person{name='张三', age=19, height=175.0}
```

只根据name和age 重写Person的equals和hashcode方法

```Java
  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (o == null || getClass() != o.getClass()) {
      return false;
    }
    Person person = (Person) o;
    return Objects.equals(name, person.name) && Objects.equals(age, person.age);
  }

  @Override
  public int hashCode() {
    return Objects.hash(name, age);
  }
```

再次执行之前的distinct方法

```Java
  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三", 19));
    people.add(new Person("李四", 19));
    people.add(new Person("张三", 19));
    people.add(new Person("小明", 23));
    people.add(new Person("张三", 19, 175.0));

    people.stream()
        .distinct()    //自定义类型重写了equals和hashcode方法
        .forEach(System.out::println);
  }

输出结果:			只用根据person的name和age去重
Person{name='张三', age=19, height=null}
Person{name='李四', age=19, height=null}
Person{name='小明', age=23, height=null}
```

**== 和 equals 和 hashcode 详解**:  https://www.cnblogs.com/kexianting/p/8508207.html#:~:text=Java%E5%AF%B9%E4%BA%8Eeqauls%E6%96%B9%E6%B3%95%E5%92%8ChashCode%E6%96%B9%E6%B3%95%E6%98%AF%E8%BF%99%E6%A0%B7%E8%A7%84%E5%AE%9A%E7%9A%84%EF%BC%9A%20%281%29%E5%90%8C%E4%B8%80%E5%AF%B9%E8%B1%A1%E4%B8%8A%E5%A4%9A%E6%AC%A1%E8%B0%83%E7%94%A8hashCode%28%29%E6%96%B9%E6%B3%95%EF%BC%8C%E6%80%BB%E6%98%AF%E8%BF%94%E5%9B%9E%E7%9B%B8%E5%90%8C%E7%9A%84%E6%95%B4%E5%9E%8B%E5%80%BC%E3%80%82,%282%29%E5%A6%82%E6%9E%9Ca.equals%28b%29%EF%BC%8C%E5%88%99%E4%B8%80%E5%AE%9A%E6%9C%89a.hashCode%28%29%20%E4%B8%80%E5%AE%9A%E7%AD%89%E4%BA%8E%20b.hashCode%28%29%E3%80%82

### 4.9 match

如果需要判断数据是否满足指定的条件, 则可以使用match的相关方法, 【终结操作】

```Java
boolean anyMatch(Predicate<? super T> predicate);		//是否任意一个元素满足条件 anyMatch
boolean allMatch(Predicate<? super T> predicate);		//是否所有元素都要满足条件 allMatch
boolean noneMatch(Predicate<? super T> predicate);		//是否所有元素都不满足条件 noneMatch
```

使用: 

```Java
    Stream<String> stringStream = Stream.of("1", "9", "7", "4", "2", "6");
    boolean match = stringStream
        //.map(s -> Integer.parseInt(s))
        .map(Integer::parseInt)
        .anyMatch(i -> i > 5);			//任意一个元素大于5
    System.out.println("match = " + match);
  }
输出: 
match = true
```

```Java
  public static void main(String[] args) {
    Stream<String> stringStream = Stream.of("1", "9", "7", "4", "2", "6");
    boolean match = stringStream
        .map(Integer::parseInt)
        .allMatch(integer -> integer > 5);		//所有元素大于5
    System.out.println("match = " + match);
  }
输出: 
match = false
```

```Java
  public static void main(String[] args) {
    Stream<String> stringStream = Stream.of("1", "9", "7", "4", "2", "6");
    boolean match = stringStream
        .map(Integer::parseInt)
        .noneMatch(integer -> integer > 10);	//所有元素都不大于10
    System.out.println("match = " + match);
  }
输出: 
match = true
```

### 4.10 find

查找流中的元素可以使用find 的相应方法,  findAny()方法返回Stream中的任何元素的Optional，而findFirst()方法返回Stream中的第一个元素的Optional

https://blog.csdn.net/weixin_39132705/article/details/107338638

```java 
    Optional<T> findFirst(); //返回Stream中的第一个元素
    Optional<T> findAny(); //返回Stream中的任何元素, 很可能返回Stream中的第一个元素，但不保证这一点
```

![image-20220126160247845](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126160247845.png)

```java 
  public static void main(String[] args) {
    Optional<String> first = Stream.of("10", "9", "7", "4", "2", "6").findFirst();
    System.out.println("first.get() = " + first.get());

    Optional<String> any = Stream.of("10", "9", "7", "4", "2", "6").findAny();
    System.out.println("any.get() = " + any.get());
  }

输出： 
first.get() = 10
any.get() = 10
```

###  4.11 max和min

max 和 min 返回流中元素最大值和最小值的Optional

```Java
    Optional<T> max(Comparator<? super T> comparator);		//获取最大值
    Optional<T> min(Comparator<? super T> comparator);       //获取最小值
```

![img](https://gitee.com/abin_z/pic_bed/raw/master/20201109145217354.png)

```Java
  public static void main(String[] args) {
    Optional<Integer> max = Stream.of("10", "90", "7", "4", "2", "6")
        .map(Integer::parseInt)
        .max((o1, o2) -> o1 - o2);      //需要传入一个Comparator, 可以自定义规则
    System.out.println("max.get() = " + max.get());

    Optional<Integer> min = Stream.of("10", "90", "7", "4", "2", "6")
        .map(Integer::parseInt)
        .max((o1, o2) -> o2 - o1);      //需要传入一个Comparator, 可以自定义规则
    System.out.println("min.get() = " + min.get());
  }
输出:
max.get() = 90
min.get() = 2
```

### 4.12  *reduce   

归约，也称缩减，顾名思义，**是把一个流缩减成一个值**，能实现对集合求和、求乘积和求最值操作。

将流中的所有数据进行归纳得到一个数据, 可以使用reduce方法

*reduce*操作可以实现从一组元素中生成一个值，`sum()`、`max()`、`min()`、`count()`等都是*reduce*操作，将他们单独设为函数只是因为常用。

```Java
    <U> U reduce(U identity,
                 BiFunction<U, ? super T, U> accumulator,
                 BinaryOperator<U> combiner);
------------------------------------------------------------------------------------------
    Optional<T> reduce(BinaryOperator<T> accumulator);
------------------------------------------------------------------------------------------
    T reduce(T identity, BinaryOperator<T> accumulator);		//主要使用的是这一个方法
```



![image-20220126202537978](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126202537978.png)

```Java
  public static void main(String[] args) {
    Integer sum = Stream.of(1, 2, 3, 4, 5)
        //identity是默认值
        //第一次的时候会将默认值给x
        //之后的每一次操作会将上一次操作的结果赋值给x, y就只是从数据中获取元素
        .reduce(0, (x, y) -> {
          System.out.println("x = " + x + " y = " + y);
          return x + y;     //求和操作
        });
    System.out.println("sum = " + sum);
  }
```

输出:

```Java
x = 0 y = 1
x = 1 y = 2
x = 3 y = 3
x = 6 y = 4
x = 10 y = 5
sum = 15
```

```Java
    Integer max = Stream.of(1, 2, 3, 4, 50, 3, 1)
        .reduce(0, (x, y) -> {
          return x > y ? x : y;     //获取最大值
        });
    System.out.println("max = " + max);

输出:
max = 50
```

### 4.13 map和reduce组合

在实际开发中经常会让map和reduce一块使用

```Java
  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("小明", 19));
    people.add(new Person("小明亮", 18));
    people.add(new Person("小红", 16));
    people.add(new Person("汤姆", 26));
    people.add(new Person("佩奇", 20));

    //求出所有人员的年龄中和
    Integer maxAge = people.stream()
//        .map(p -> p.getAge())
        .map(Person::getAge)    //map对数据类型进行转换
        .reduce(0, (x, y) -> x > y ? x : y);  //reduce对数据进行归约
    System.out.println("maxAge = " + maxAge);

    //求出所有人员的年龄总和
    Integer sumAge = people.stream()
        .map(Person::getAge)
        .reduce(0, Integer::sum);
    System.out.println("sumAge = " + sumAge);

    //获取"a"出现的次数
    Integer count = Stream.of("a", "c", "v", "s", "a", "a")
        .map(s -> "a".equals(s) ? 1 : 0)
        .reduce(0, Integer::sum);
    System.out.println("count = " + count);
  }
```

输出:

```Java
maxAge = 26
sumAge = 99
count = 3
```

### 4.14 mapToInt ...

mapToInt的作用: 可以先将流中的Integer数据转换为int数据

Integer占用的内存比int多很多, 在Stream流操作中会频繁的自动拆箱和装箱, 很浪费空间

```Java
IntStream mapToInt(ToIntFunction<? super T> mapper);		//转换为基本数据类型int
LongStream mapToLong(ToLongFunction<? super T> mapper); 	//转换为基本数据类型long
DoubleStream mapToDouble(ToDoubleFunction<? super T> mapper);//转换为基本数据类型double
```

![image-20220126213717913](https://gitee.com/abin_z/pic_bed/raw/master/image-20220126213717913.png)

```Java
  public static void main(String[] args) {
    Integer[] array = {10, 20, 30, 40, 50, 60};
    //Integer占用的内存比int多很多, 在Stream流操作中会频繁的自动拆箱和装箱, 很浪费空间
    Stream.of(array)
        .filter(item -> item > 20)
        .forEach(System.out::println);

    System.out.println("=================");
    //为了提高代码的效率,可以先将流中的Integer数据转换为int数据,然后在操作数据
    Stream.of(array)
        .mapToInt(Integer::intValue)   //先将Integer数据转换为int数据
        .filter(i -> i > 20)
        .forEach(System.out::println);
  }
```

输出: 

```Java
30
40
50
60
=================
30
40
50
60
```

### 4.15 concat

concat可以将两个流合并成为一个流, 可以使用Stream类的静态方法concat

```Java
    public static <T> Stream<T> concat(Stream<? extends T> a, Stream<? extends T> b) {
        Objects.requireNonNull(a);
        Objects.requireNonNull(b);

        @SuppressWarnings("unchecked")
        Spliterator<T> split = new Streams.ConcatSpliterator.OfRef<>(
                (Spliterator<T>) a.spliterator(), (Spliterator<T>) b.spliterator());
        Stream<T> stream = StreamSupport.stream(split, a.isParallel() || b.isParallel());
        return stream.onClose(Streams.composedClose(a, b));
    }
```

```Java
  public static void main(String[] args) {
    Integer[] array = {10, 20, 30, 40, 50, 60};
    ArrayList<Integer> doubles = new ArrayList<>();
    doubles.add(12);
    doubles.add(12);
    doubles.add(12);

    Stream<Integer> stream1 = Stream.of(array);
    Stream<Integer> stream2 = doubles.stream();

    Stream<Integer> concat = Stream.concat(stream1, stream2); //合并两个流
    concat
        .mapToInt(Integer::intValue)
        .sorted()
        .filter(i -> i > 40)
        .forEach(System.out::println);
  }
```

输出:

```Java
50
60
```

### 4.16 collect

Stream的终极武器:  **将Stream转换成容器或Map**  https://www.cnblogs.com/CarpenterLee/p/6550212.html

```Java
<R, A> R collect(Collector<? super T, A, R> collector);

<R> R collect(Supplier<R> supplier,
              BiConsumer<R, ? super T> accumulator,
              BiConsumer<R, R> combiner);
```

收集器（*Collector*）是为`Stream.collect()`方法量身打造的工具接口（类）。考虑一下将一个*Stream*转换成一个Collection集合（或者*Map*）需要做哪些工作？我们至少需要三样东西：

1. 目标容器是什么？是*ArrayList*还是*HashSet*，或者是个*TreeMap*。
2. 新元素如何添加到容器中？是`List.add()`还是`Map.put()`。
3. 如果并行的进行规约，还需要告诉*collect()* 多个部分结果如何合并成一个。



- 结合以上分析，*collect()*方法定义为

  ```Java
  <R> R collect(Supplier<R> supplier,		//目标容器是什么				
                BiConsumer<R, ? super T> accumulator,  //如何添加新元素
                BiConsumer<R, R> combiner);		//并行规约, 如何合并
  ```

  三个参数依次对应上述三条分析

- 不过每次调用*collect()*都要传入这三个参数太麻烦，收集器*Collector*就是对这三个参数的简单封装,所以*collect()*的另一定义为

  ```Java
  <R, A> R collect(Collector<? super T, A, R> collector);
  ```

  *Collectors*工具类可通过静态方法生成各种常用的*Collector*。举例来说，如果要将*Stream*规约成*List*可以通过如下两种方式实现：

  ```Java
  //　将Stream规约成List	
  Stream<String> stream = Stream.of("I", "love", "you", "too");
  List<String> list = stream.collect(ArrayList::new, ArrayList::add, ArrayList::addAll);// 方式１
  //List<String> list = stream.collect(Collectors.toList());// 方式2
  System.out.println(list);
  ```

通常情况下我们不需要手动指定*collect()*的三个参数，而是调用`collect(Collector<? super T,A,R> collector)`方法，并且参数中的*Collector*对象大都是直接通过*Collectors*工具类获得。实际上传入的**收集器的行为决定了`collect()`的行为**。



#### **使用collect()生成Collection**

将*Stream*转换成*List*或*Set*是比较常见的操作，所以*Collectors*工具已经为我们提供了对应的收集器，通过如下代码即可完成：

```Java
  public static void main(String[] args) {
    Stream<String> stream = Stream.of("I", "love", "you", "too");
    List<String> list = stream.collect(Collectors.toList());    //将stream流转化为list集合
    Set<String> set = stream.collect(Collectors.toSet());     //将stream流转化为set集合
  }
```

上述代码能够满足大部分需求，但由于返回结果是接口类型，我们并不知道类库实际选择的容器类型是什么，有时候我们可能会想要人为指定容器的实际类型，这个需求可通过`Collectors.toCollection(Supplier<C> collectionFactory)`方法完成。

```Java
  public static void main(String[] args) {
    Stream<String> stream = Stream.of("I", "love", "you", "too");

    // 通过Collectors.toCollection(Supplier<C> collectionFactory)转化为集合
    ArrayList<String> arrayList = stream.collect(Collectors.toCollection(ArrayList::new));  //转化为ArrayList
    HashSet<String> hashSet = stream.collect(Collectors.toCollection(HashSet::new));   //转化为HashSet
  }
```

基本上述的两种方式足够应对collect()方法转Collection集合

```Java
  public static void main(String[] args) {
    Stream<String> stream = Stream.of("I", "love", "you", "too");
    List<String> list = stream.collect(Collectors.toList());    //将stream流转化为list集合
    ArrayList<Object> arrayList1 = stream.collect(ArrayList::new, ArrayList::add, ArrayList::addAll); //方式2

    Set<String> set = stream.collect(Collectors.toSet());     //将stream流转化为set集合
    HashSet<Object> hashSet1 = stream.collect(HashSet::new, HashSet::add, HashSet::addAll);  //方式2

    // 通过Collectors.toCollection(Supplier<C> collectionFactory)转化为集合
    ArrayList<String> arrayList = stream.collect(Collectors.toCollection(ArrayList::new));  //转化为ArrayList
    HashSet<String> hashSet = stream.collect(Collectors.toCollection(HashSet::new));   //转化为HashSet
  }
```



#### **使用collect()生成Map**

*Stream*背后依赖于某种数据源，数据源可以是数组、容器等，但不能是*Map*。反过来从*Stream*生成*Map*是可以的，但我们要想清楚*Map*的*key*和*value*分别代表什么，根本原因是我们要想清楚要干什么。通常在三种情况下`collect()`的结果会是*Map*：

1. 使用`Collectors.toMap()`生成的收集器，用户需要指定如何生成*Map*的*key*和*value*。
2. 使用`Collectors.partitioningBy()`生成的收集器，对元素进行二分区操作时用到。
3. 使用`Collectors.groupingBy()`生成的收集器，对元素做*group*操作时用到。

- 第一种情况:Collectors.toMap()

```Java
  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三", 19));
    people.add(new Person("李四", 20));
    people.add(new Person("王五", 18));
    people.add(new Person("麦克", 16));

    //将stream流转化为map集合
    Map<Person, String> map = people.stream()
        .collect(Collectors.toMap(Function.identity(),   //如何生成key
            Person::getName));  //如何生成value

    Set<Person> keySet = map.keySet();
    for (Person person : keySet) {
      System.out.println(person);
    }

    Collection<String> values = map.values();
    for (String value : values) {
      System.out.println(value);
    }
  }
```

提示: `Function.identity()`返回一个 输出 跟 输入 一样的Lambda表达式对象，等价于形如`t -> t`形式的Lambda表达式。

输出: 

```Java
Person{name='麦克', age=16, height=null}
Person{name='王五', age=18, height=null}
Person{name='张三', age=19, height=null}
Person{name='李四', age=20, height=null}
麦克
王五
张三
李四
```

- 第二种情况: 使用`partitioningBy()`生成的收集器，这种情况适用于将`Stream`中的元素依据某个二值逻辑（满足条件，或不满足）分成互补相交的两部分，比如男女性别、成绩及格与否等。下列代码展示将人员分为成年和未成年。

```Java
  public static void main(String[] args) {
    ArrayList<Person> people = new ArrayList<>();
    people.add(new Person("张三", 21));
    people.add(new Person("李四", 20));
    people.add(new Person("王五", 17));
    people.add(new Person("麦克", 16));

    //将人员分为成年和未成年两部分
    Map<Boolean, List<Person>> listMap = people.stream()
        .collect(Collectors.partitioningBy(person -> person.getAge() >= 18));
    System.out.println(listMap);
  }
```

输出:

```Java
{false=[Person{name='王五', age=17, height=null}, Person{name='麦克', age=16, height=null}],
 true=[Person{name='张三', age=21, height=null}, Person{name='李四', age=20, height=null}]}
```

- 第三种情况：使用`groupingBy()`生成的收集器，这是比较灵活的一种情况。跟SQL中的*group by*语句类似，这里的*groupingBy()*也是按照某个属性对数据进行分组，属性相同的元素会被对应到*Map*的同一个*key*上。下列代码展示将员工按照部门进行分组：

```Java
// Group employees by department
Map<Department, List<Employee>> byDept = employees.stream()
            .collect(Collectors.groupingBy(Employee::getDepartment));
```

更多collect()方法详情:  https://www.cnblogs.com/CarpenterLee/p/6550212.html



**Java8 之 lambda 表达式、方法引用、函数式接口、默认方式、静态方法**: https://zhuanlan.zhihu.com/p/68347633







