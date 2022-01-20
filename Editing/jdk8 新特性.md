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
package com.abin.lambda;

/**
 * @author Abin
 * @date 2022/01/19
 */
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
package com.abin.lambda;

/**
 * @author Abin
 * @date 2022/01/19
 */
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
package com.abin.lambda.userService;

/**
 * @author Abin
 * @date 2022/01/19
 */
@FunctionalInterface
public interface UserService {
  void show();
}
```

在main方法中使用Lambda表达式:

```Java
package com.abin.lambda;

import com.abin.lambda.userService.UserService;

/**
 * @author Abin
 * @date 2022/01/19
 */
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
package com.abin.lambda;

import com.abin.lambda.Entity.Person;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/19
 */
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
package com.abin.lambda;

import com.abin.lambda.Entity.Person;
import com.abin.lambda.userService.PersonService;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * @author Abin
 * @date 2022/01/19
 */
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
package com.abin.interfaceboost;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.interfaceboost;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.interfaceboost;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.Locale;

/**
 * @author Abin
 * @date 2022/01/20
 */
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

**供应者: 无参有放回值接口**  泛型是指定返回值的类型

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
package com.abin.functionalinterface;

import java.util.Arrays;
import java.util.function.Supplier;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.Locale;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.Locale;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.Locale;
import java.util.function.Consumer;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.function.Function;

/**
 * @author Abin
 * @date 2022/01/20
 */
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

Function的andZhen方法:  ` f1.andThen(f2).apply(str); `//先执行f1, 然后在执行f2;

```Java
package com.abin.functionalinterface;

import java.util.function.Function;

/**
 * @author Abin
 * @date 2022/01/20
 */
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

Function的默认compose方法: ` f1.compose(f2).apply(str); ` // 是先执行f2, 然后在执行f1;

```Java
package com.abin.functionalinterface;

import java.util.function.Function;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.function.Predicate;

/**
 * @author Abin
 * @date 2022/01/20
 */
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
package com.abin.functionalinterface;

import java.util.function.Predicate;

/**
 * @author Abin
 * @date 2022/01/20
 */
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





















**Java8 之 lambda 表达式、方法引用、函数式接口、默认方式、静态方法**: https://zhuanlan.zhihu.com/p/68347633







