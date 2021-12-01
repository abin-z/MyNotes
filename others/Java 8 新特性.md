# Java8 新特性

**Java 8新特性简介**

java（又称jdk1.8）是java语言开发的一个主要版本。

java 8 是oracle公司于2014年3月发布，可以看成是自java 5以来最具革命性版本。

java 8 为java语言、编译器、类库、开发工具与jvm带来了大量新特性。

**特点**

- 速度更快
- 代码更少（增加了新的语法：lambda表达式）
- 强大的Stream API
- 便于并行
  - 并行流：就是把一个内容分成多个模块，并用不同的线程分别处理每个数据块的流。相较于串行的流，并行的流可以很大程度上提高程序的执行效率。
  - Java 8中将并行进行了优化，我们可以很容易对数据进行并行操作。
  - Stream API可以声明性通过parallel()与sequential()在并行流与顺序流之间切换
- 最大化减少空指针异常：Optional
- Nashorn引擎，允许在JVM上运行JS应用

### 1 lambda表达式

**Lambda**是一个匿名函数，我们可以把Lambda表达式理解为是一段**可以传递的代码**(将代码像数据一样进行传递)。使用它可以写出更简洁、更灵活的代码。作为一种更紧凑的代码风格，使java的语言表达能力得到了提升。

```java
/**
 * @author 
 * lambda表达式
 */
public class LambdaTest {

    @Test
    public void test01(){
        //实现runnable接口，重写run方法
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                System.out.println("java工程师");
            }
        };
        runnable.run();
        System.out.println("======================");

        Runnable runnable1 = () -> System.out.println("lambda表达式");
        runnable1.run();
        System.out.println("======================");

        //定制排序
        Comparator<Integer> comparator1 = new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return Integer.compare(o1,o2);
            }
        };
        int com1 = comparator1.compare(12, 23);
        System.out.println(com1);

        //lambda表达式
        Comparator<Integer> comparator2 =((o1, o2) -> Integer.compare(o1,o2));
        int com2 = comparator2.compare(24, 11);
        System.out.println(com2);

        //方法引用
        Comparator<Integer> comparator3 = Integer::compareTo;
        int com3 = comparator3.compare(11, 10);
        System.out.println(com3);
    }
}
结果：
java工程师
======================
lambda表达式
======================
-1
1
1 
```

**注意：**

- 使用lambda表达式的前提就是该类是一个函数式接口，就是一个接口类只有一个方法
- 定制排序的时候泛型需要标注类型
- **格式：**
  - **“->”**:lambda操作符或者箭头操作符
  - 左边：lambda形参列表（其实就是接口中的抽象方法的形参列表）
  - 右边：lambda体（其实就是重写抽象方法的方法体）0
- lambda表达式的本质：作为函数式接口类的实例化对象
  - 函数式接口类：一个接口中，只声明了一个抽象方法，还有一个注解（@FunctionalInterface）；加这个注解的意思就是去判断是否是函数式接口，自定义的时候可以不加

**lambda表达式的使用：6种情况**

~~~java
/**
 * @author
 */
public class LambdaTest02 {

    @Test
    public void test01(){
        //语法格式一：无参，无返回值
        Runnable run = new Runnable() {
            @Override
            public void run() {
                System.out.println("实例化Runnable");
            }
        };
        run.run();
        System.out.println("***********************");
        Runnable runnable = () -> {System.out.println("lambda表达式");};
        runnable.run();
    }

    /**
     * 语法格式二：lambda有一个参数，没有返回值
     */
    @Test
    public void test02(){

        Consumer<String> stringConsumer = new Consumer<String>() {
            @Override
            public void accept(String o) {
                System.out.println("实例化Consumer:"+o);
            }
        };
        stringConsumer.accept("张三");
        System.out.println("***********************");
        Consumer<String> consumer = (String o) ->{System.out.println("lambda有参没有返回值"+o);};
        consumer.accept("张三");
    }

    /**
     * 语法格式三：数据类型可以省略，因为可由编译器推断得出，称为"类型判断"
     */
    @Test
    public void test03(){
        Consumer<String> stringConsumer = new Consumer<String>() {
            @Override
            public void accept(String o) {
                System.out.println("实例化Consumer:"+o);
            }
        };
        stringConsumer.accept("张三");
        System.out.println("***********************");
        Consumer<String> consumer = (o) ->{System.out.println("形参可以不用写参数类型："+o);};
        consumer.accept("的");

        //类型推断，前面定义了一个类型，等号后面的就可以推断出类型
        ArrayList<String> list = new ArrayList<>();
        int[] arr = {1,2,3};
    }

    /**
     * 语法格式四：lambda若是只有一个参数时，参数的小括号可以省略
     */
    @Test
    public void test04(){
        Consumer<String> consumer = new Consumer<String>() {
            @Override
            public void accept(String o) {
                System.out.println("对象名称："+o);
            }
        };
        consumer.accept("张三");
        System.out.println("***********************");
        Consumer<String> con = o ->{System.out.println("形参不需要小括号："+o);};
        con.accept("的");
    }

    /**
     * 语法格式五：lambda若是有多个参数，多条执行语句，并且还有返回值
     */
    @Test
    public void test05(){
        Comparator<Integer> comparator = new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                System.out.println(o1);
                System.out.println(o2);
                return o1.compareTo(o2);
            }
        };
        int compare = comparator.compare(11, 34);
        System.out.println(compare);
        System.out.println("***********************");

        Comparator<Integer> comparator1 = (o1,o2) ->{
            System.out.println(o1);
            System.out.println(o2);
            return o1.compareTo(o2);
        };
        int compare1 = comparator1.compare(22, 21);
        System.out.println(compare1);
    }

    /**
     * 语法格式六：当lambda体只有一条语句时，return与大括号若有，都可以省略
     */
    @Test
    public void test06(){
        Comparator<Integer> comparator = (o1,o2) ->{
            return o1.compareTo(o2);
        };
        System.out.println(comparator.compare(13,2));
        System.out.println("***********************");

        Comparator<Integer> comparator1 = (o1,o2) -> o1.compareTo(o2);
        System.out.println(comparator1.compare(32,73));
    }

    @Test
    public void test07(){
        Consumer<String> consumer = (o1) -> System.out.println("lambda表达式");
        consumer.accept("s");
    }
}
结果：
实例化Runnable
***********************
lambda表达式
实例化Consumer:张三
***********************
lambda有参没有返回值张三
实例化Consumer:张三
***********************
形参可以不用写参数类型：的
对象名称：张三
***********************
形参不需要小括号：的
11
34
-1
***********************
22
21
1
1
***********************
-1
lambda表达式
~~~

**注意：**

- 左边：lambda形参列表的参数类型可以省略（类型推断）；如果lambda形参列表只有一个参数，其一对()也可以省略
- 右边：lambda体应该使用一对{}包裹，如果lambda体只有一条执行语句（可能是return语句），可以省略这一对{}和return关键字

**自定义函数式接口：**

~~~java
/**
 * 测试函数式接口
 * @author 
 * 
 */
@FunctionalInterface
public interface MyInterface {
    void method();
    
//    void method1();
}
~~~

**注意：**

- 添加这个注解之后，就会去判断是否是函数式接口
- 在java.util.function包下定义了Java 8的丰富的函数式接口
- lambda表达式主要就是依赖函数式接口
- 以前用匿名实现类表示的现在都可以用lambda表达式来写

**java内置四大函数式接口**

| 函数式接口                                                   | 参数类型                  | 返回类型                   | 用途                                                         |      |
| ------------------------------------------------------------ | ------------------------- | -------------------------- | ------------------------------------------------------------ | ---- |
| Consumer<T>消费型接口(核心)                                  | T                         | void                       | 对类型为T的对象应用操作 void accpet()                        |      |
| Supplier<T> 供给型接口（核心）                               | 无                        | T                          | 返回类型为T的对象，包含方法：T get()                         |      |
| Function<T,R>函数型接口（核心）                              | T                         | R                          | 对类型为T的对象应用操作，并返回结果。结果是R类型的对象。包含方法：R apply(T t) |      |
| Predicate<T>断定型接口（核心）                               | T                         | boolean                    | 确定类型为T的对象是否满足某约束，并返回boolean值。包含方法：boolean test(T t) |      |
| BiFunction<T U,R>                                            | T,U                       | R                          | 对类型为T，U参数应用操作，返回R类型的结果。包含方法：R apply(T t,U u); |      |
| UnaryOperator<T>(Function子接口)                             | T                         | T                          | 对类型为T的对象进行一元运算，并返回T类型的结果。包含方法：T apply(T t); |      |
| BinaryOperator（BiFunction子接口）                           | T,T                       | T                          | 对类型为T的对象进行二元运算，并返回T类型的结果。包含方法：T apply(T t1,T t2); |      |
| BiConsumer<T,U>                                              | T,U                       | void                       | 对类型为T,U参数应用操作。包含方法为：void accept(T t,U u);   |      |
| BiPredicate<T,U>                                             | T,U                       | boolean                    | 包含方法为：boolean test(T t,U u)                            |      |
| TolntFunction<T><br />ToLongFunction<T> <br />ToDoubleFunction<T> | T                         | int<br />long <br />double | 分别计算int,long,double值的函数                              |      |
| IntFunction<R><br />LongFunction<R><br />DoubleFunction<R>   | int<br />long<br />double | R                          | 参数分别为int,long,double类型的函数                          |      |

**四大核心函数式接口案例**

~~~java
/**
 * @author
 * 四大内置函数式接口：
 */
public class LambdaTest03 {

    @Test
    public void test01(){
        buy(500, new Consumer<Double>() {
            @Override
            public void accept(Double aDouble) {
                System.out.println("买了一瓶水，价格是："+aDouble);
            }
        });
        System.out.println("*********************");
        buy(400,money -> System.out.println("买了一瓶可乐，价格是："+money));
    }

    public void buy(double money,Consumer<Double> con){
        con.accept(money);
    }

    @Test
    public void test02(){
        List<String> list = Arrays.asList("北京","天津","南京","东京","西京","普京");
        List<String> fList =filterList(list, new Predicate<String>() {
            @Override
            public boolean test(String s) {
                return s.contains("京");
            }
        });
        System.out.println(fList);
        System.out.println("************************************");

        List<String> stringList = filterList(list,s -> s.contains("东"));
        System.out.println(stringList);
    }

    /**
     * 根据给定的规则，过滤集合中的字符串。此规则由Predicate的方法决定
     * @param list
     * @param pre
     * @return
     */
    public List<String> filterList(List<String> list, Predicate<String> pre){
         List<String> filterList = new ArrayList<>();

        for (String s : list) {
            if(pre.test(s)){
                filterList.add(s);
            }
        }
        return filterList;
    }
}
结果：
买了一瓶水，价格是：500.0
*********************
买了一瓶可乐，价格是：400.0
[北京, 南京, 东京, 西京, 普京]
************************************
[东京]
~~~

**注意：**

- 此时就只是测试了两个核心函数式接口（消费型和断定型）

### 2 方法引用/构造器引用

- 当要传递给lambda体的时候，已经有实现的方法了，可以使用方法引用
- 方法引用可以看做是Lambda表达式的深层次的表达。换句话说，方法引用就是Lambda表达式，也就是函数式接口的一个实例，通过方法的名字来指向一个方法，可以认为是Lambda表达式的一个语法糖
- 要求：实现接口的抽象方法的参数列表和返回值类型，必须与方法引用的方法的参数列表和返回值类型保持一致。
- 格式：使用操作符 “::” 将类（或对象名）与方法分隔开
- 如下三种主要使用情况：
  - 情况一        对象::实例方法名
  - 情况二        类::静态方法名
  - 情况三        类::实例方法名
- 方法引用使用的要求：要求接口中的抽象方法的形参列表和返回值类型与方法引用的方法的形参列表和返回值类型相同（针对情况一和情况二）

**方法引用三种实例**

~~~java
/**
 * @author
 *
 * 1.使用情景一：当要传递给Lambda体的操作，已经有实现的方法了，可以使用方法引用
 *
 * 2.方法引用，本质上就是Lambda表达式，而Lambda表达式作为函数式接口的实例，所以方法引用，也是函数式的接口
 *
 * 3.使用格式： 类(对象)：：方法名
 *
 * 4.具体分为如下的三种情况：
 *  情况一  对象:: 非静态方法
 *  情况二  类 :: 静态方法
 *  情况三  类 :: 非静态方法
 *
 */
public class MethodRefTest {

     /**
     * PrintStream中的void printIn(T t)
     * Consumer中的void accept(T t)
     * 情景一： 对象：：实例方法
     */
    @Test
    public void test01(){
        Consumer<String> con  = str -> System.out.println(str);
        con.accept("上海");
        System.out.println("********************************");
        //创建一个打印流对象
        PrintStream ps = System.out;
        Consumer<String> consumer = ps::println;
        consumer.accept("shanghai");
    }

    /**
     * Supplier中的T get()
     * 某个实体类中的get方法
     */
    @Test
    public void test02(){
        User user = new User(1L, "张三", "张三");
        Supplier<String> supplier = () ->user.getName();
        System.out.println(supplier.get());

        System.out.println("******************************");
        Supplier<String> supplier1 = user::getName;
        System.out.println(supplier1.get());
    }

    /**
     * 情况二： 类 :: 静态方法
     * Comparator中的int compare(T t1, T t2)
     * Integer中的int compare(T t1,T t2)
     */
    @Test
    public void test03(){
        Comparator<Integer> com1 = (t1,t2) ->Integer.compare(t1,t2);
        System.out.println(com1.compare(12, 23));

        System.out.println("*******************************");

        Comparator<Integer> com2 = Integer::compareTo;
        System.out.println(com2.compare(11,2));
    }

    //Function中的R apply(T t)
    //Math中的Long round(Double d)
    @Test
    public void test04(){
        Function<Double, Long> func1 = d -> Math.round(d);
        System.out.println(func1.apply(12.3));

        System.out.println("********************************");
        Function<Double,Long> func2 = Math::round;
        System.out.println(func2.apply(45.6));
    }

    //情况三：类 ：：实例方法
    //Comparator中的int compare(T t1,T t2)
    //String中的int t1.compareTo(t2)
    //此方法的意思就是两个参数中，一个参数调用相同的方法，该方法里面就是另一个参数
    //上面的t1调用compareTo(t2)方法，里面的参数就是t2
    //只是说这里其实是t1的类型
    @Test
    public void test06(){
        Comparator<String> com1 = (t1, t2) -> t1.compareTo(t2);
        System.out.println(com1.compare("abc", "abd"));

        System.out.println("********************************");
        Comparator<String> com2 = String ::compareTo;
        System.out.println(com2.compare("abs","abc"));
    }

    //BiPredicate中的boolean test(T t1,T t2)
    //String中的boolean t2.equals(t2)
    @Test
    public void test07(){
        BiPredicate<String,String> b1 = (t1,t2) ->t1.equals(t2);
        System.out.println(b1.test("abc", "abd"));

        System.out.println("********************************");
        BiPredicate<String,String> b2 = String::equals;
        System.out.println(b2.test("abc", "abc"));
    }

    //Function中的R apply(T t)
    //Employee中的String getName()
    @Test
    public void test08(){
        User user = new User(1L,"张三","ss");

        Function<User,String> f1 = e ->e.getName();
        System.out.println(f1.apply(user));

        System.out.println("********************************");
        Function<User,String> f2 = User::getName;
        System.out.println(f2.apply(user));
    }

}
结果：
上海
********************************
shanghai
张三
******************************
张三
-1
*******************************
1
12
********************************
46
-1
********************************
16
false
********************************
true
张三
********************************
张三
~~~

**注意**

- 情况一：对象调用实例方法，实例化打印流对象，调用printIn方法输出
- 情况二：类调用静态方法，这里使用了Integer这个类的静态方法compareTo()和Math的静态方法round()方法
- 情况三：类调用非静态方法，这里根据参数和返回值可以自行定义，比如说这个CompareTo方法，参数是两个，但是返回值就一个就可以使用（参数类型：：函数式接口方法）实现
- 必须是函数式接口才能够使用方法引用

**构造方法引用**

- 和方法引用类似，函数式接口抽象方法的形参列表和构造方法的形参列表一致
- 抽象方法的返回值类型即为构造器所属的类型
- 返回值其实就是构造器的返回值

**数组引用**

- 可以将数组看成是一个特殊的类型，其实和构造方法一样

~~~java
package lambdaTest;

import org.junit.Test;

import java.util.Arrays;
import java.util.function.BiFunction;
import java.util.function.BiPredicate;
import java.util.function.Function;
import java.util.function.Supplier;

/**
 * @author
 * 一   构造器引用
 * 二   数组引用
 */
public class ConstructorTest {

    /**
     * 构造器引用
     * supplier中的T get()
     * User的空参构造器：User()
     * */
    @Test
    public void test01(){
        Supplier<User> sup1  = new Supplier<User>() {
            @Override
            public User get() {
                return new User();
            }
        };
        //正常写法
        System.out.println(sup1.get());

        System.out.println("***************************");
        //Lambda表达式
        Supplier<User> sup2 = () ->new User();
        System.out.println(sup2.get());

        System.out.println("***************************");
        Supplier<User> sup3 = User::new;
        System.out.println(sup3.get());

    }

    /**
     * Function中的R apply(T t)
     */
    @Test
    public void test02(){
        //lambda表达式
        Function<Long,User> f1 = id ->new User(id);
        System.out.println(f1.apply(1L));

        System.out.println("***************************");
        //构造器方法引用
        Function<Long,User> f2 = User::new;
        System.out.println(f2.apply(3L));
    }

    /**
     * BiFunction中的 R apply(T t1,U u)
     */
    @Test
    public void test03(){
        //lambda表达式
        BiFunction<Long,String,User> f1 = (t, u) ->new User(t,u);
        System.out.println(f1.apply(2L, "张三"));

        System.out.println("***************************");
        //带两个参数的构造器方法引用
        BiFunction<Long,String,User> f2 = User::new;
        System.out.println(f2.apply(4L, "李四"));
    }

    /**
     * 数组引用
     * Function中的R apply(T t)
     */
    @Test
    public void test04(){
        Function<Integer,String[]> f1 = length -> new String[length];
        String[] apply1 = f1.apply(4);
        System.out.println(Arrays.asList(apply1));

        System.out.println("***************************");
        Function<Integer,String[]> f2 = String[] :: new;
        String[] apply2 = f2.apply(3);
        System.out.println(Arrays.asList(apply2));
    }

}
结果：
ser{id=null, name='null', remark='null'}
***************************
User{id=null, name='null', remark='null'}
***************************
User{id=null, name='null', remark='null'}
id的有参构造器
User{id=null, name='null', remark='null'}
***************************
id的有参构造器
User{id=null, name='null', remark='null'}
id和name的有参构造器
User{id=null, name='null', remark='null'}
***************************
id和name的有参构造器
User{id=null, name='null', remark='null'}
[null, null, null, null]
***************************
[null, null, null]
~~~

**注意：**

- 构造器方法的形参列表和函数式接口抽象方法形参列表一致
- 构造器方法返回值类型也是一致的
- 数组引用其实就可以看成是一个特殊的类型，和构造器方法引用差不多
- 方法引用和构造器引用其实就是函数式接口抽象方法的实例

### 3 Stream API（并行流、串行流）

- Java 8中有两大最为重要的改变。第一个就是lambda表达式；另外一个则是Stream API
- Stream API(java.util.Stream)把真正的函数式编程风格引入到java中。这是目前为止对java类库最好的补充，因为Stream API可以极大提供java程序员的生产力，让程序员写出高效率、干净、简洁的代码。
- Stream是java 8中处理集合的关键抽象概念，他可以指定你希望对集合进行的操作，可以执行非常复杂的查找、过滤和映射数据等操作。使用Stream API对集合数据进行操作，就类似于使用SQL执行数据库查询，也可以使用Stream API来执行操作。简言之，Stream API提供一种高效且易使用的处理数据的方式。
- 实际开发中，项目中多数数据源都来自于Mysql，Oracle等。但现在数据源可以更多了，有MongDB，Redis等，而这些NoSQL数据就需要java层面去处理。
- Stream和Collection集合的区别：Collection是一种静态的内存数据结构**（内存层面的容器）**，而Stream是有关计算的**（操作这个内存层面的容器）**。前者主要面向内存，存储在内存中，后者主要是面向CPU，通过CPU实现计算。
- **集合讲的是数据，Stream讲的是计算！**

**注意**

- Stream是不会存储元素
- Stream不会改变源对象。相反，他们会返回一个持有结果的新Stream
- Stream操作是延迟执行的。这意味着他们会等到需要结果的时候才执行

**Stream的三个步骤**

- 1-创建 Stream：一个数据源（如：集合、数组），获取一个流
- 2-中间操作：一个中间操作链，对数据源的数据进行处理
- 3-终止操作（终端操作）：一旦执行终止操作，就执行中间操作链，并产生结果。之后，不再使用。

**创建Stream方式**

- 方式一：通过集合
  - default Stream<E> stream():返回一个串行流(顺序流)
  - default Stream<E> parallelStream():返回一个并行流
- 方式二：通过数组
  - 调用Arrays类的static <T> Stream<T> stream(T[] array);返回一个流
- 方式三：通过Stream的of():
  - 可以调用Stream类静态方法of()，通过显示值创建一个流，他可以接收任意数量的参数
  - public static<T> Stream<T> of(T... values):返回一个流
- 方式四：创建无限流
  - 迭代：public static<T> Stream<T> iterator(final T seed,final UnaryOperator<T> f)
  - 生成：public static<T> Stream<T> generate(Supplier<T> s)

**测试实例化案例**

~~~java
/**
 * @author
 */
public class StreamApiTest {

    /**
     * 创建Stream方式一：通过集合
     */
    @Test
    public void test01(){
        List<User> users = new ArrayList<>();

        //default Stream<E> stream():返回一个顺序流
        Stream<User> stream = users.stream();

        //default Stream<E> parallelStream():返回一个并行流
        Stream<User> userStream = users.parallelStream();
    }

    /**
     * 创建Stream方式二：通过数组
     */
    @Test
    public void test02(){
        int[] ints = new int[]{1,2,3,4,5};

        //调用Arrays类的static <T> Stream<T> stream(T[] array);返回一个流
        IntStream stream = Arrays.stream(ints);

        User user = new User(1L, "zhangsan", "ss");
        User user1 = new User(2L, "zz", "zz");
        User[] users = new User[]{user,user1};
        Stream<User> stream1 = Arrays.stream(users);
    }

    /**
     * 创建Stream方式三：通过Stream的of()方法
     */
    @Test
    public void test03(){

        Stream<Integer> integerStream = Stream.of(1, 2, 3, 4, 5, 6);
    }

    /**
     * 创建Stream方式四：创建无限流
     */
    @Test
    public void test04(){
        //迭代
        //遍历前10个偶数
        Stream.iterate(0,t ->t+2).limit(10).forEach(System.out::println);

        //生成
        //遍历随机生成的10个数
        Stream.generate(Math::random).limit(10).forEach(System.out::println);
    }

}
结果：
0
2
4
6
8
10
12
14
16
18
0.03739134521598697
0.02338947171753758
0.7110159031517062
0.44034107288220814
0.4486974222351514
0.15307866440038054
0.7171714288974606
0.4582705609118082
0.20951482636865293
0.24148239414849115
~~~

**注意**

- 集合使用方式一
- 数组使用方式二
- 自定义实例化流使用方式三
- 创建无限流使用方式四

**Stream的中间操作**

多个中间操作可以连接起来形成一个流水线，除非流水线触发终止操作，否则中间操作不会执行任何的处理！而在终止操作时一次性全部处理，称为“惰性求值”。

**1- 筛选与切片**

| 方法                | 描述                                                         |
| ------------------- | ------------------------------------------------------------ |
| filter(Predicate p) | 接收lambda，从流中排除某些元素                               |
| distinct            | 筛选，通过流所生成元素的hashCode()和equals()方法去除重复元素 |
| limit(long maxSize) | 截断流，使其元素不超过给定数量                               |
| skip(long n)        | 跳过元素，返回一个扔掉了前n个元素的流。若流中元素不足n个，则返回一个空流。与limit(n)互补 |

~~~java
/**
 * @author
 */
public class StreamApiTest01 {

    /**
     * 1 -筛选与切片
     */
    @Test
    public void test01(){
        //filter筛选
        List<User> users = Users.getUsers();
        Stream<User> stream = users.stream();
        stream.filter(item ->item.getName().equals("张三")).forEach(System.out::println);
        System.out.println();

        //limit()截断
        Users.getUsers().stream().limit(2).forEach(System.out::println);
        System.out.println();

        //distinct()筛选
        List<User> users1 = Users.getUsers();
        users1.add(new User(5L,"杨柳","sada"));
        users1.stream().distinct().forEach(System.out::println);
        System.out.println();

        //skip(n)去掉前n个元素
        Users.getUsers().stream().forEach(System.out::println);
        System.out.println();

        //打印原来的数组
        Users.getUsers().forEach(System.out::println);
    }
}
结果：
User{id=1, name='张三', remark='10000'}

User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}

User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='赵六', remark='10000'}
User{id=5, name='杨柳', remark='sada'}

User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='赵六', remark='10000'}

User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='赵六', remark='10000'}
~~~

**注意**

- 一旦一个流对象执行完成，就不能够再使用这个流对象，不然会报错
- limit和skip方法相当于互补的

**2-映射**

| 方法                            | 描述                                                         |
| ------------------------------- | ------------------------------------------------------------ |
| map(Function f)                 | 接收一个函数作为参数，该函数会被应用到每个元素上，并将其映射成新的元素 |
| mapToDouble(ToDoubleFunction f) | 接收一个函数作为参数，该函数会被应用到每个元素上，产生一个新的DoubleStream |
| map ToInt(ToIntFunction f)      | 接收一个函数作为参数，该函数会被应用到每个元素上，产生一个新的IntStream |
| map ToLong(ToLongFunction f)    | 接收一个函数作为参数，该函数会被应用到每个元素上，产生一个新的LongStream |
| flatMap(Function f)             | 接收一个函数作为参数，将流中的每一个值换成另一个流，然后把所有的流连接成一个流 |

**映射案例**

~~~java
 	/**
     * 映射
     */
    @Test
    public void test02(){
        //map(Function f)
        List<String> list = Arrays.asList("aa", "bb", "cc", "dd");
        list.stream().map(String::toUpperCase).forEach(System.out::println);
        System.out.println();

        //练习1：获取用户名称长度大于2的用户名称
        Users.getUsers().stream().filter(item ->item.getName().length()>2).map(User::getName).forEach(System.out::println);
        System.out.println();

        //练习2：
        list.stream().map(StreamApiTest01::fromStringToStream).forEach(s ->{
            s.forEach(System.out::println);
        });
        System.out.println();
        list.stream().flatMap(StreamApiTest01::fromStringToStream).forEach(System.out::println);
    }

    /**
     * 字符串转换为流
     * @param str
     * @return
     */
    public static Stream<Character> fromStringToStream(String str){
        List<Character> list = new ArrayList<>();
        for (char c : str.toCharArray()) {
            list.add(c);
        }
        Stream<Character> stream = list.stream();
        return stream;
    }
结果：
AA
BB
CC
DD

马化腾

a
a
b
b
c
c
d
d

a
a
b
b
c
c
d
d
~~~

**注意**

- 练习二中：map方法和flatMap()的区别就是和list.add(list1)和list.addAll(list1)的区别，如果流中嵌套了一个流，就可以使用**flatMap()**方法进行将所有的数据输出。但是如果使用的是**map()**方法，就必须要多些一个语句，把内层嵌套的流也要输出出来。
- list的add方法和list.addAll方法的区别在于，如果形参列表也是一个list，那么list.add（list1），这个list里面就会嵌套一个list:[1,2,3,[4,5,6]];
- list.addAll(list1)就是这样子的：[1,2,3,4,5,6]

**3-排序**

| 方法                   | 描述                               |
| ---------------------- | ---------------------------------- |
| sorted()               | 产生一个新流，其中按照自然顺序排序 |
| sorted(Comparator com) | 产生一个新流，其中按照比较器排序   |

**排序案例**

~~~java
/**
     * 3 -排序
     */
    @Test
    public void test03(){

        //sorted -自然排序
        List<Integer> list = Arrays.asList(1, 22, 33, 44, 42, 13, 33);
        list.stream().sorted().forEach(System.out::println);

        //抛异常，原因：User类没有实现Comparable接口，没有进行排序
//        List<User> users = Users.getUsers();
//        users.stream().sorted().forEach(System.out::println);

        //sorted(Comparator c) -定制排序
        List<User> users = Users.getUsers();
        users.stream().sorted((e1,e2) -> {
            int i = e1.getId().compareTo(e2.getId());
            if(i!=0){
                return i;
            }   else {
                return -e1.getName().compareTo(e2.getName());
            }
        }).forEach(System.out::println);

    }
结果：
1
13
22
33
33
42
44
User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='马化腾', remark='10000'}
User{id=4, name='赵六', remark='10000'}
~~~

**注意**

- 使用stream进行对象的自然排序的时候，需要对象的类实现Comparable接口，不然会报错
- 使用stream进行对象的定制排序的时候，若根据第一个排序方式有相同的值时候，可以根据另一个属性进行排序，达到排序数据正确性

 **Stream API的终止操作**

- 终端操作会从流的流水线生成结果。其结果可以不是流的值，例如List、Integer，甚至是void
- **流进行了终止操作后不能再次使用**

**1 匹配与查找**

| 方法                   | 描述                                                         |
| ---------------------- | ------------------------------------------------------------ |
| allMatch(Predicate p)  | 检查是否匹配所有元素                                         |
| anyMatch(Predicate p)  | 检查是否至少匹配一个元素                                     |
| noneMatch(Predicate p) | 检查是否没有匹配的元素                                       |
| findFirst()            | 返回第一个元素                                               |
| findAny()              | 返回当前流中的任意元素                                       |
| count()                | 返回流中元素总数                                             |
| max(Comparator c)      | 返回流中最大值                                               |
| min(Comparator c)      | 返回流中最小值                                               |
| forEach(Consumer c)    | 内部迭代（使用Collection接口需要用户去做迭代，称为外部迭代。相反，Stream API使用内部迭代-----它帮你把迭代做了） |

**匹配与查找案例**

~~~java
/**
 * @author
 * 测试终止操作
 */
public class StreamApiTest02 {

    @Test
    public void test1(){
        //allMatch(Predicate p) 检查是否匹配所有元素
        //练习：是否所有人编号大于3
        boolean allMatch = Users.getUsers().stream().allMatch(e -> e.getId() > 4L);
        System.out.println(allMatch);
        System.out.println("*****************************");

        //anyMatch(Predicate p) 检查是否至少匹配一个元素
        //练习：是否存在一个人的编号大于3
        boolean anyMatch = Users.getUsers().stream().anyMatch(e -> e.getId() > 3L);
        System.out.println(anyMatch);

        //noneMach(Predicate p) 检查是否没有匹配的元素
        //练习：是否存在人“张。。”
        boolean noneMatch = Users.getUsers().stream().noneMatch(e -> e.getName().startsWith("张"));
        System.out.println(noneMatch);

         //findFirst 返回第一个元素
        Optional<User> user = Users.getUsers().stream().findFirst();
        System.out.println(user);

        //findAny  返回当前流中的任意元素
        Optional<User> any = Users.getUsers().parallelStream().findAny();
        System.out.println(any);
    }

    @Test
    public void test02(){
        List<User> users = Users.getUsers();

        //count  返回流中元素的总个数
        //练习：收集id大于3的数据个数
        long count = users.stream().filter(e -> e.getId() > 3L).count();
        System.out.println(count);

        //max(Comparator c)  返回流中的最大值
        //练习：返回最高的编号
        Optional<Long> max = users.stream().map(e -> e.getId()).max(Long::compareTo);
        System.out.println(max);

        //min 返回流中的最小值
        //练习 返回id最小的人员
        Optional<User> user = users.stream().min((e1, e2) -> Long.compare(e1.getId(), e2.getId()));
        System.out.println(user);
        System.out.println();

        //forEach(Consumer c) 内部迭代
        users.stream().forEach(System.out::println);
        System.out.println();

        //使用集合的遍历操作
        users.forEach(System.out::println);
    }
}
结果：
2
Optional[4]
Optional[User{id=1, name='张三', remark='10000'}]

User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='赵六', remark='10000'}
User{id=4, name='马化腾', remark='10000'}

User{id=1, name='张三', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='赵六', remark='10000'}
User{id=4, name='马化腾', remark='10000'}
false
*****************************
true
false
Optional[User{id=1, name='张三', remark='10000'}]
Optional[User{id=3, name='王五', remark='10000'}]
~~~

**注意**

- 内部迭代是在流中执行，相当于运行的对象就是流
- 外部迭代是在集合中执行，相当于运行的对象是集合

**2 -归约**

| 方法                            | 描述                                                    |
| ------------------------------- | ------------------------------------------------------- |
| reduce(T iden,BinaryOperator b) | 可以将流中元素反复结合起来，得到一个值。返回T           |
| reduce(BinaryOperator b)        | 可以将流中元素反复结合起来，得到一个值。返回Optional<T> |

**备注**：map和reduce的连接通常称为map-reduce模式，因google用它来进行网络搜索而出名。

**归约案例**

~~~java
/**
 * @author
 * 归约测试
 */
public class StreamApiTest03 {

    @Test
    public void test1(){
        //reduce(T identify,BinaryOperator)  --将流中的数据反复结合获得一个
        //练习：求和
        List<Integer> list = Arrays.asList(1, 2, 3, 4, 5, 6,7,8,9,10);
        Integer sum = list.stream().reduce(10, Integer::sum);
        System.out.println(sum);

        //reduce(BinaryOperator)  --可以将流中元素反复结合起来，得到一个值。返回Optional<>
        //练习：计算所有用户id之和
        List<User> users = Users.getUsers();
//        Optional<Long> sumId = users.stream().map(User::getId).reduce(Long::sum);
        Optional<Long> sumId = users.stream().map(User::getId).reduce((e1,e2) ->e1+e2);
        System.out.println(sumId);
    }
}
结果：
65
Optional[14]
~~~

**注意**

- reduce第一个方法，形参1表示的是初始值，形参2表示的和形参一进行相加
- reduce第二个方法，只有一个参数，没有初始值，注释掉的方法也可以执行。

**3 -收集**

| 方法                 | 描述                                                         |
| -------------------- | ------------------------------------------------------------ |
| collect(Collector c) | 将数据流转换为其他形式。接收一个Collector接口的实现，用于给Stream中元素做汇总的方法 |

Collector接口中方法的实现决定了如何对流执行收集的操作(如收集到List、Set、Map)。

另外，Collectors实用类提供了很多静态方法，可以方便地创建常见收集器实例，具体方法与实例如下表： 

| 方法                        | 返回值类型                | 作用                                                         |
| --------------------------- | ------------------------- | ------------------------------------------------------------ |
| toList                      | List<T>                   | 把流中元素收集到List                                         |
| List<User> users            | =list.stream().collect(   | Collections.toList);                                         |
| toSet                       | Set<T>                    | 把流中元素收集到Set                                          |
| Set<User> set               | =list.stream().collect(   | Collectors.toSet());                                         |
| toCollection                | Collection<T>             | 把流中元素收集到创建的集合                                   |
| Collection<User> users      | =list.stream().collect(   | Collectors.toCollection(ArrayList::new));                    |
| counting                    | Long                      | 计算流中元素的个数                                           |
| long count                  | =list.stream().collect(   | Collectors.counting);                                        |
| summingInt                  | Integer                   | 对流中元素的整数属性求和                                     |
| int total                   | =list.stream().collect(   | Collectors.summingInt(User::getAge));                        |
| averagingInt                | Double                    | 计算流中元素Integer属性的平均值                              |
| double avg                  | =list.stream().collect(   | Collectors.averagingInt(User::getAge));                      |
| summarizingInt              | IntSummaryStatistic       | 收集流中Integer属性的统计值。如：平均值                      |
| int summaryStatisticsiss    | =list.stream().collect(   | Collectors.summarizingInt(User::getAge));                    |
| join                        | String                    | 连接流中的某个字符串                                         |
| String str                  | = list.stream().map(      | e -> e.getName()).collect(Collectors.joining());             |
| maxBy                       | Optional<T>               | 根据比较器选择最大值                                         |
| Optional<User> collect      | =list.stream().collect(   | Collectors.maxBy(Comparator.comparingLong(User::getId)));    |
| minBy                       | Optional<T>               | 根据选择器选择最小值                                         |
| Optional<User> collect      | =list.stream().collect(   | Collectors.minBy(Comparator.comparingLong(User::getId)));    |
| reducing                    | 归约产生的类型            | 从一个作为累加器的初始值开始，<br />利用BinaryOperator与流中元素逐个结合，<br />从而归约成单个值 |
| Long sum                    | = users.stream().collect( | Collectors.reducing(0L, User::getId, Long::sum));            |
| collectingAndThen           | 转换函数返回类型          | 包裹另一个收集器，对其结果转换函数                           |
| Integer how                 | =list.stream().collect(   | Collectors.collectingAndThen(Collectors.toList(), List::size)); |
| groupingBy                  | Map<K,List<T>>            | 根据某个属性值对流分组，属性为k，结果为v                     |
| Map<Long, List<User>> map   | =list.stream().collect(   | Collectors.groupingBy(User::getId));                         |
| partitioningBy              | Map<Boolean,List<T>>      | 根据true或false进行分区                                      |
| Map<Boolean,List<User>>  vd | list.stream().collection( | Collectors.partitioningBy(User::getRemark));                 |

**收集相关案例**

~~~java
/**
     * 3 -收集
     */
    @Test
    public void test2(){
        List<User> users = Users.getUsers();
        //收集对象的List集合
        //查找id大于1的人员，收集为List或者Set
        List<User> userList = users.stream().filter(e ->e.getId()>1).collect(Collectors.toList());
        userList.forEach(System.out::println);
        System.out.println();

        //收集对象的Set集合
        Set<User> userSet = users.stream().filter(e ->e.getId()>1).collect(Collectors.toSet());
        userSet.forEach(System.out::println);

        //join连接每个流中的字符串
        String str = users.stream().map(e -> e.getName()).collect(Collectors.joining());
        System.out.println(str);

        //maxBy
        Optional<User> collect = users.stream().collect(Collectors.maxBy(Comparator.comparingLong(User::getId)));
        System.out.println(collect);

        //reducing
        Long sum = users.stream().collect(Collectors.reducing(0L, User::getId, Long::sum));
        System.out.println(sum);

        //collectingAndThen
        Integer how = users.stream().collect(Collectors.collectingAndThen(Collectors.toList(), List::size));

        //groupingBy
        Map<Long, List<User>> map = users.stream().collect(Collectors.groupingBy(User::getId));
        map.keySet().forEach(e ->{
            System.out.println(map.get(e));
        });
    }
结果：
User{id=2, name='李四', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=4, name='赵六', remark='10000'}
User{id=4, name='马化腾', remark='10000'}

User{id=4, name='马化腾', remark='10000'}
User{id=3, name='王五', remark='10000'}
User{id=2, name='李四', remark='10000'}
User{id=4, name='赵六', remark='10000'}
张三李四王五赵六马化腾
Optional[User{id=4, name='赵六', remark='10000'}]
14
[User{id=1, name='张三', remark='10000'}]
[User{id=2, name='李四', remark='10000'}]
[User{id=3, name='王五', remark='10000'}]
[User{id=4, name='赵六', remark='10000'}, User{id=4, name='马化腾', remark='10000'}]
~~~

**注意**

- 分组是根据某个属性值相同的进行分组
- reducing方法是将某个参数进行求和，所以参数第一个是初始值，第二个是对象的某个属性，第三个参数是操作方法（这里是求和）
- join是将某个字符串类型的数据连接在一起
- collectingAndThen是根据某个参数进行操作，比如这里参数1是一个集合，参数二是指定的集合长度，就是根据集合转换函数，有点不懂

### 4 Optional类

- 目前为止，空指针异常是导致java应用程序失败的常见原因。以前为了解决空指针异常，Google公司著名的Guava项目引入了Optional类，Guava通过检查空值的方式来放置代码污染，他鼓励程序员写更干净的代码。受到Google Guava的启发，Optional类已经成为Java 8类库的一部分。
- Optional<T>类(java.util.Optional)是一个容器类，他可以保存类型T的值，代表这个值存在。或者仅仅保存null，表示这个值不存在。原来null表示一直不存在，现在Optional可以更好的表达这个概念。并且可以避免空指针异常。
- Optional类的Javadoc描述如下：这是一个可以为null的容器对象。如果值存在，则isPresent()会返回true，调用get()方法会返回该对象。

**Optional类的方法**

- Optional提供很多有用的方法，这样我们就可以不用显式进行空值检测
- **创建Optional类对象的方法：**
  - Optional.of(T t):创建一个Optional实例，**t必须非空**
  - Optional.empty:创建一个空的Optional实例
  - Optional.ofNullable(T t):**t可以为null**

**Optional实例案例**

```java
/**
 * @author
 * 测试Optional实例
 */
public class OptionalTest {

    /**
     * Optional.of(T t) t为非空
     */
    @Test
    public void test1(){
        Girl girl = new Girl();
        girl =null;
        Optional<Girl> optionalGirl = Optional.of(girl);
        //会报空指针
        System.out.println(optionalGirl);
    }
    
    /**
     * Optional.ofNullable(T t) t可以为空
     */
    @Test
    public void test2(){
        Girl girl = new Girl();
        girl =null;
        Optional<Girl> optionalGirl = Optional.ofNullable(girl);
        System.out.println(optionalGirl);
    }
    
}
结果：
java.lang.NullPointerException
===============================
Optional.empty
```

**注意**

- Optional.of(T t)：形参列表不能为空，如果设置为空了，就会报空指针异常
- Optional.ofNullable(T t):参数可以为空，如果参数是null，那么输出的就是Optional.empty，如果不是空的就是Optional[Girl{boy=null}]

- **判断Optional容器中是否包含对象：**
  - boolean isPresent():判断是否包含对象
  - void ifPresent(Consumer<? super T> consumer):如果有值，就会执行Consumer接口的实现代码，并且该值会作为参数传给它。
- **获取Optional容器的对象：**
  - T get():如果调用对象有值，返回该值，否则抛出异常
  - T orElse(T other):如果有值则将其返回，否则返回指定的other对象
  - T orElseGet(Supplier<? extends T> other):如果有值就将其返回，否则返回有Supplier接口实现提供的对象
  - T orElse Throw(Supplier<? extends X> exceptionSupplier):如果有值则将其返回，否则抛出有Supplier接口实现提供异常

**orElse案例**

```java
/**
 * @author
 * 测试Optional实例
 */
public class OptionalTest {

    /**
     * Optional.of(T t) t为非空
     */
    @Test
    public void test1(){
        Boy boy = new Boy();
        boy =null;
        Optional<Boy> optionalGirl = Optional.of(boy);
        //会报空指针
        System.out.println(optionalGirl);
    }

    /**
     * Optional.ofNullable(T t) t可以为空
     */
    @Test
    public void test2(){
        Boy boy = new Boy();
        Optional<Boy> optionalGirl = Optional.ofNullable(boy);
        System.out.println(optionalGirl);
    }

    public String getGirlName(Boy boy){
        return boy.getGirl().getName();
    }

    @Test
    public void test03(){
        Boy boy = new Boy();
        System.out.println(getGirlName(boy));

    }

    public String getGirlName1(Boy boy){
        if(boy!=null){
            Girl girl = boy.getGirl();
            if(girl!=null){
                return girl.getName();
            }
        }
        return null;
    }

    @Test
    public void test04(){
        Boy boy = new Boy();
        System.out.println(getGirlName1(boy));

    }

    public String getGirlName2(Boy boy){
        Optional<Boy> optionalBoy = Optional.ofNullable(boy);

        Boy boy1 = optionalBoy.orElse(new Boy(new Girl("热巴")));

        Girl girl = boy1.getGirl();
        Optional<Girl> optionalGirl = Optional.ofNullable(girl);

        Girl girl1 = optionalGirl.orElse(new Girl("杨幂"));

        return girl1.getName();
    }

    /**
     * 测试orElse
     */
    @Test
    public void test05(){
        Girl girl = new Girl();
//        girl =null;
        //ofNullable(T t)参数可以null
        Optional<Girl> OptionGirl = Optional.ofNullable(girl);
        System.out.println(OptionGirl);

        //orElse(T other):如果当前的Optional内部封装的t是非空的，则返回内部的t；
        //如果内部的t是空的，则返回orElse()方法中的参数t1;
        Girl girl2 = OptionGirl.orElse(new Girl("张三"));
        System.out.println(girl2);
    }

    @Test
    public void test06(){
        Boy boy = new Boy();
        // boy =null;
        Boy boy1 = new Boy(new Girl("张三"));
        System.out.println(getGirlName2(boy1));
    }


}
结果：
ava.lang.NullPointerException

null
Optional[Boy{name='null'}]
Boy{name='null'}
张三

Optional[Girl{boy=null}]
```

**注意**

- 使用Optional.of(T t )；如果t为空，就会报错空指针异常
- 使用Optional.orNullable(T t)：如果为空：
  - 如果存在Optional.orElse方法：
    - 那么输出的值就是orElse里面对象的值
  - 如果没有就是输出Optional.empty
- 使用Optional.orNullable(T t)：如果不为空：就直接输出对象的值
- getGirlName2(Boy boy)是嵌套了一个新的对象。orElse(T other)方法中:如果当前的Optional内部封装的t是非空的，则返回内部的t；如果内部的t是空的，则返回orElse()方法中的参数t1;（套娃）
- Optional类主要是为了解决空指针异常而创建的
- 常用的方法：Optional.orNullable(T t)和orElse(T t);
  - Optional.orNullable(T t)：如果没有就执行orElse();
- **可以通过Optional对象的get()方法获取对象值，相当于在流中只要容器类型是Optional类就可以使用get()方法获取对象的值，前提是该对象存在，不然就会报空指针**



### 复习

- 代理模式的原理：
  - 使用代理对象去替换原始对象，进行操作，原始对象调用都要通过代理对象来执行。代理对象决定是否以及何时将方法调用转到原始对象上。
- 静态代理的实例：
  - 多线程实现Runnable接口，重写run方法，然后添加到Thread对象中，调用start方法，因为Runnable接口不具备开启线程方法，需要Thread对象才能开启，所以测试Thread对象就是代理类，Runnable接口就是被代理类，run方法就是需要执行的方法。
- 静态代理的缺点：
  - 代理类和目标类在编译的时候就被确定下来，不利于程序的扩展
  - 每一个代理类只能为一个接口服务，这样程序开发就会产生很多的代理类
- 动态代理的特点：
  - 动态代理就是根据代理类去调用其他对象的方法，并且是在程序运行时根据**对象的不同**动态创建代理类。意思就是代理类是根据被代理类的对象进行创建的，不同的被代理类的对象就会通过代理类调用不同的方法。
- 动态代理要解决的两个问题：
  - 如果根据加载到内存中的被代理类，动态的创建一个代理类（通过Proxy.newProxyInstance()来实现）
  - 当通过被代理类的对象调用方法a时，如何动态的去调用被代理类中的同名方法a（通过InvocationHandler接口的invoke()方法() ）
- 动态代理具体实现：

```java
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * @author
 * 被代理接口类
 */
interface Human{
    String fly();
    void eat(String food);
}
/**
 * 要想实现动态代理，需要解决的问题
 * 问题一：如何根据加载到内存中的被代理类，动态的创建一个代理类及其对象
 * 问题二：当通过代理类的对象调用方法时，如何动态的去调用被代理类中的同名方法
 *
 */
class ProxyFactory{
    /**
     * 调用此方法，返回一个代理类的对象。解决一：
     */
    public static Object getProxyInstance(Object obj){//obj:被代理的对象
        MyInvocationHandler handler = new MyInvocationHandler();
        handler.bind(obj);
        //obj.getClass().getClassLoader(): 用哪个类加载器去加载代理对象;
        //obj.getClass().getInterfaces():动态代理类需要实现的接口;
        //handler:动态代理方法在执行时，会调用handler里面的invoke方法去执行
        return Proxy.newProxyInstance(obj.getClass().getClassLoader(),obj.getClass().getInterfaces(),handler);
    }
}

/**
 * @author
 */
public class ProxyTest {

    public static void main(String[] args) {
        SuperMan superMan = new SuperMan();
        //proxyInstance:代理类对象
        Human proxyInstance = (Human) ProxyFactory.getProxyInstance(superMan);
        //当通过代理类对象调用方法时，会自动调用被代理类中同名的方法
        String fly = proxyInstance.fly();
        System.out.println(fly);
        proxyInstance.eat(" 火锅");
        System.out.println("*************************************");
    }

}

/**
 * 1.InvocationHandler接口是proxy代理实例的调用处理程序实现的一个接口，
 * 每一个proxy代理实例都有一个关联的调用处理程序；在代理实例调用方法时，方法调用被编码分派到调用处理程序的invoke方法。
 * 2.Proxy类就是用来创建一个代理对象的类，它提供了很多方法，但是我们最常用的是newProxyInstance方法。
 *
 */
class MyInvocationHandler implements InvocationHandler{
    /**
     * 需要使用被代理类的对象进行赋值
     */
    private Object obj;
    /**
     * 该方法只是一个赋值
     * @param obj
     */
    public void bind(Object obj){
        this.obj = obj;
    }
    /**
     * 当我们通过代理类的对象，调用方法a时，就会自动调用如下方法：invoke()
     * 当被代理类要执行的方法a的功能就声明在invoke（）中
     * @param proxy
     * @param method
     * @param args
     * @return
     * @throws Throwable
     */
    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        //method:即为代理类对象调用的方法，此方法也就作为了被代理类对象要调用的方法
        //obj：被代理类的对象,从中调用底层方法的对象，必须是实例化对象
        //args： 用于方法的调用，是一个object的数组，参数有可能是多个
        Object invoke = method.invoke(obj, args);
        //上述方法的返回值就是作为当前类中的invoke()的返回值
        return invoke;
    }
}
//被代理类
class SuperMan implements Human{

    @Override
    public String fly() {
        return "i believe i can fly";
    }

    @Override
    public void eat(String food) {
        System.out.println("i like eat"+ food);
    }

    public void say(){
        System.out.println("hello");
    }
}
结果：
i believe i can fly
i like eat 火锅
*************************************
```

- lambda表达式基础语法：
  - “->”:lambda操作符或者叫做箭头操作符
  - 左边：lambda形参列表
  - 右边：lambda方法体
  
- lambda表达式的六种情况：
  - 无参数，无返回值 ： () ->{System.out.printIn("lambda无参无返回值");};
  - 一个参数（有类型），无返回值：(String str) ->{System.out.printIn("lambda有参数无返回值"+str);};
  - 一个参数（形参列表不加类型，因为是根据类型推断），无返回值：（str）->{System.out.printIn("lambda一个参数的时候可以省略参数类型"+str);};
  - 一个参数（形参列表不加类型，因为根据类型推断可以得出），lambda方法体可以不用括号：str ->{System.out.printIn("lambda形参列表的参数体可以去掉"+str);};
  - 两个参数，多条执行语句，并且有返回值：Comparator<Integer> com  =(x,y) ->{
    - System.out.printIn("lambda表达式多个参数")
    - return Integer.compare(x,y);
  - }
  - lambda体只有一条语句时，return与大括号若有，都可以省略：Comparator<Inetger> com = (x,y) ->Inetger.compare(x,y);
  
- 总结六种情况：
  - 左边：lambda形参列表的参数类型可以省略(类型推断)；如果lambda形参列表只有一个参数，其一对()也可以省略
  - 右边：lambda体应该使用一对{}包裹；如果lambda体只有一条执行语句（可能是return语句，省略这一对{}和return语句）
  
- 函数式接口的使用说明：
  - 如果一个接口中，只声明了一个抽象方法，则此接口就称为函数式接口
  - 我们可以在接口类上添加@FunctionInterface注解，可以用来判断是否为函数式接口
  - lambda表达式是函数式接口的实例
  
- Java 8中关于lambda表达式提供的四种基本的函数式接口：
  - 消费型接口：Consumer<T>  ：返回值void：方法是void accept()
  - 供给型接口：Supplier<T> ：返回值T：方法是  T get()
  - 函数型接口：Function<T ,R>  ：返回值R： 方法是 R apply(T t)
  - 断定型接口：Predicate<T>：返回值Boolean：方法是 boolean test(T t)
  
- 何时使用lambda表达式：
  
  - 当需要使用函数式接口实例化的时候，可以使用lambda表达式
  
- 如何使用函数式接口：
  
  - 如果我们在开发中需要定义一个函数式接口，首先看看在已有的jdk提供的函数式接口是否提供了能满足需求的函数式接口。如果有就直接调用。不需要自己在自定义。
  
- 方法引用的理解：
  
  - 方法引用可以看做是lambda表达式的深层次的表达，相当于在lambda表达式上面进一步简化表达式，但是前提条件就是lambda表达式的方法体是已经存在某些方法可以使用。还有就是方法引用其实就是实例化函数式接口
  
- 方法引用的使用情景：
  
  - 当要传递给lambda体的操作，已经存在可以实现的方法的时候，就可以使用方法引用
  
- 方法引用的三种方式：
  - 对象 ：：非静态方法
  - 类 ：：静态方法
  - 类 ：：非静态方法
  
- 方法引用的使用要求：
  - 要求接口中的抽象方法形参列表和返回值类型与方法引用中的形参列表和返回值类型相同（**这个只针对方式一和方式二**）
  - 当函数式接口方法的第一个参数是需要引用方法的调用者，并且第二个参数是需要引用方法的参数（或无参数）时：ClassName：：methodName(**针对方法三**)
  
- 方法引用的使用建议：
  
  - 如果给函数式接口提供实例，恰好满足方法引用的使用情景，大家就可以考虑使用方法引用给函数式接口提供实例。如果不太熟悉方法引用，那么还可以使用lambda表达式。
  
- 构造器引用格式：

  - 类名：：new

- 数组引用格式：

  - 数组[] ：：new

- 构造器引用类型：

  - 和方法引用类似，函数式接口的抽象方法的形参列表和返回值类型与构造方法的形参列表和返回值类型一致。

- 构造器类型举例：

  ```java
  /**
   * @author
   * 一   构造器引用
   * 二   数组引用
   */
  public class ConstructorTest {
  
      /**
       * 构造器引用
       * supplier中的T get()
       * User的空参构造器：User()
       * */
      @Test
      public void test01(){
          Supplier<User> sup1  = new Supplier<User>() {
              @Override
              public User get() {
                  return new User();
              }
          };
          //正常写法
          System.out.println(sup1.get());
  
          System.out.println("***************************");
          //Lambda表达式
          Supplier<User> sup2 = () ->new User();
          System.out.println(sup2.get());
  
          System.out.println("***************************");
          Supplier<User> sup3 = User::new;
          System.out.println(sup3.get());
  
      }
  
      /**
       * Function中的R apply(T t)
       */
      @Test
      public void test02(){
          //lambda表达式
          Function<Long,User> f1 = id ->new User(id);
          System.out.println(f1.apply(1L));
  
          System.out.println("***************************");
          //构造器方法引用
          Function<Long,User> f2 = User::new;
          System.out.println(f2.apply(3L));
      }
  
      /**
       * BiFunction中的 R apply(T t1,U u)
       */
      @Test
      public void test03(){
          //lambda表达式
          BiFunction<Long,String,User> f1 = (t, u) ->new User(t,u);
          System.out.println(f1.apply(2L, "张三"));
  
          System.out.println("***************************");
          //带两个参数的构造器方法引用
          BiFunction<Long,String,User> f2 = User::new;
          System.out.println(f2.apply(4L, "李四"));
      }
  
      /**
       * 数组引用
       * Function中的R apply(T t)
       */
      @Test
      public void test04(){
          Function<Integer,String[]> f1 = length -> new String[length];
          String[] apply1 = f1.apply(4);
          System.out.println(Arrays.asList(apply1));
  
          System.out.println("***************************");
          Function<Integer,String[]> f2 = String[] :: new;
          String[] apply2 = f2.apply(3);
          System.out.println(Arrays.asList(apply2));
      }
  
  }
  结果：
  User{id=null, name='null', remark='null'}
  ***************************
  User{id=null, name='null', remark='null'}
  ***************************
  User{id=null, name='null', remark='null'}
  id的有参构造器
  User{id=null, name='null', remark='null'}
  ***************************
  id的有参构造器
  User{id=null, name='null', remark='null'}
  id和name的有参构造器
  User{id=null, name='null', remark='null'}
  ***************************
  id和name的有参构造器
  User{id=null, name='null', remark='null'}
  ```

- 数组引用举例

  ```java
  /**
   * 数组引用
   * Function中的R apply(T t)
   */
  @Test
  public void test04(){
      Function<Integer,String[]> f1 = length -> new String[length];
      String[] apply1 = f1.apply(4);
      System.out.println(Arrays.asList(apply1));
  
      System.out.println("***************************");
      Function<Integer,String[]> f2 = String[] :: new;
      String[] apply2 = f2.apply(3);
      System.out.println(Arrays.asList(apply2));
  }
  结果：
  [null, null, null, null]
  ***************************
  [null, null, null]
  ```

- Stream API的理解：

  - Stream API关注的是数据的**计算**，主要与CPU打交道，Collection关注的是数据的**存储**主要与内存打交道。
  - JDK1.8提供的这套api，使用这套api可以对内存中的数据进行筛选、排序、过滤、归约等操作。类似于sql语言对数据库表的相关操作。

- Stream API的注意点：

  - Stream本身不会存储元素
  - Stream不会改变源数据，它会生成一个新的Stream对象
  - Stream操作时延时的。这意味着他们需要等到结果出来的时候才回去执行

- Stream API的使用流程：

  - 实例化Stream
  - 执行一系列的中间操作（过滤、映射.....）
  - 执行终止操作

- 使用流程的注意点：

  - 一个中间操作链，对数据源的数据进行操作
  - 一旦执行终止操作，就执行中间操作链，并且产生结果。之后，就不能够再次使用

- Stream实例化：

  - 集合实例化： list.stream()
  - 数组实例化：Arrays.stream(数组对象)
  - 创建无限流：
    - 迭代：Stream.iterator(0,t->t+2).limit(10).forEach(System.out::printIn)
    - 生成：Stream.generate(Math::random).limit(10).forEach(System.out::printIn)

- 中间操作：

  - 1-筛选：
    - filter(Predicate p)：接收lambda，从流中排除某些数据
    - distinct()：筛选，根据hashCode和equals方法去掉重复的数据
    - limit(long maxSize)：截断流，使其元素不超过给定数量
    - skip(long n)：跳过元素，返回一个形参列表值后面所有的数据，如果形参的值大于流的长度，就返回一个空值
  - 2-映射：
    - map()：流中的数据映射成某个属性，比如 map(e ->e.getId())
    - mapToDouble()
    - mapToLong();
    - mapToInteger:
    - flatMap()：流中的数据映射成某个属性，但是和map方法不同的在于他可以更深层次的映射
  - 3-排序：
    - sorted()：自然排序
    - sorted(Comparator c)：按照比较器进行定制排序

- 终止操作：

  - 1-匹配和查找：
    - allMatch(Predicate p):检查是否匹配元素
    - anyMatch(Predicate p):检查是否至少存在一个匹配元素
    - noneMatch(Predicate p):检查是否不存在该匹配元素
    - findFirst():返回第一个元素
    - findAny():返回当前流中任意元素
    - count():返回流中元素总数
    - max(Comparator c):返回流中元素最大值
    - min(Comparator c):返回流中元素最小值
    - forEach(Consumer c):内部迭代，操作的是容器内的数据
  - 2-归约：
    - reduce(T iden,BinaryOperator b):可以将流中元素结合起来得到一个值,返回T
    - reduce(BinaryOperator b)：可以将流中元素结合起来得到一个值,返回Optional<T>
    - 备注：map和reduce的连接通常称为map-reduce模式，因Google用它来进行网络搜索而出名
  - 3-收集：
    - Collect(Collector c):将流转换成其他的数据类型比如：List、Set、Collection等。
    - 另外Collectors实用类提供了很多静态方法，可以方便地创建常见收集器实例。
    - Collection(Collectors.toList):转换为List
    - Collection(Collectors.toSet):转换为Set
    - Collection(Collectors.toCollection(User::new)):转换为Collection
    - 还有其他的方法

- Java.util.Optional类的理解：

  -   是为了解决java空指针异常的问题
  - Optional<T>是一个容器类，他可以保存T的值，代表这个值存在，若T为空，则表示数据不存在。

  ```java
  /**
   * @author
   */
  public class OptionalTest {
  
      @Test
      public void test1() {
          //empty()：创建的Optional对象内部的value =null
          Optional<Object> optional = Optional.empty();
          //判断是否包含数据
          if (!optional.isPresent()) {
              System.out.println("数据为空");
          }
          //如果Optional封装的数据value为空，则报错。否则，就返回value
          //System.out.println(optional.get());
      }
  
      @Test
      public void test2(){
          String str = "hello";
  //        str=null;
          //of(T t)这个方法的参数不能为空，否则就报空指针错误
          Optional<String> str1 = Optional.of(str);
          //get()方法通常与of(T t)方法搭配使用。用于获取内部封装的数据
          System.out.println(str1.get());
      }
  
      @Test
      public void test3(){
          String str = "zz";
  		// str =null;
          //ofNullable(T t),封装数据t给Optional内部的value。不要求t非空
          Optional<String> opt1 = Optional.ofNullable(str);
          //orElse(T t1):如果Optional内部的value非空，则返回此value值。如果为空，就返回t1
          String zzz = opt1.orElse("zzz");
          System.out.println(zzz);
      }
  }
  结果：
  数据为空
  hello
  zz
  ```

