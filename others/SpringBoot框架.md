# Spring Boot框架

## 1. Spring Boot入门

**简介**	

​	Spring Boot来简化Spring应用开发，约定大于配置，去繁从简，仅仅只需要运行就能创建一个独立的，产品级别的应用。

**背景：**

​	J2EE笨重的开发、繁多的配置、低下的开发效率、复杂的部署流程、第三方技术集成难度大，所以就有了Spring Boot的开发

**解决：**

​	“Spring” 全家桶时代

​	Spring Boot —> J2EE一站式解决方案

​	Spring Cloud —>分布式整体解决方案

SpringBoot的底层也是使用的Spring

**优点：**

- 快速创建独立运行的Spring项目以及主流框架集成
- 使用嵌入式的Servlet容器，应用不需要打包成var包（不需要配置tomcat或者其他的，直接打包成jar包）
- starters(**启动器**)自动依赖与版本控制（如果想要使用web就可以直接把相关的jar包下载下来使用）
- 大量的自动配置，简化开发，也可以修改默认值
- 不需要配置XML，无代码生成、开箱即用（SpringBoot提供相应的API就可以直接使用了）
- 准生产环境的运行时应用监控（可以监控服务的状态）
- 与云计算的天然集成



**微服务简介**

- 2021，martin fowler
- 微服务：架构风格（服务微化）
- 一个应用用该是一组小型服务；可以通过HTTP的方式进行互通。
- 每一个功能元素最终都是一个可独立替换和独立升级的软件单元
- 详细参照微服务文档 

## 2. Spring Boot配置

**SpringBoot环境搭配**

- **创建maven工程**

- **导入springboot依赖**

  ```xml
  <parent>
          <groupId>org.springframework.boot</groupId>
          <artifactId>spring-boot-starter-parent</artifactId>
          <version>1.5.2.RELEASE</version>
      </parent>
      <dependencies>
          <dependency>
              <groupId>org.springframework.boot</groupId>
              <artifactId>spring-boot-starter-web</artifactId>
          </dependency>
      </dependencies>
  ```

- **编写一个主程序，来启动SpringBoot应用**

  ```java
  /**
   * @author
   * @SpringBootApplication 来标注SpringBoot主程序类，说明这是一个Spring Boot应用
   */
  @SpringBootApplication
  public class HelloWorldMainApplication {
  
      public static void main(String[] args){
  
          //SpringBoot启动起来
          SpringApplication.run(HelloWorldMainApplication.class);
      }
  }
  ```

- **编写相关的Controller、Service**

  ```java
  /**
   * @author
   */
  @Controller
  public class HelloController {
  
      @ResponseBody
      @RequestMapping("/hello")
      public String hello(){
          return "hello world";
      }
  }
  ```

- **运行主程序进行测试**

- **简化部署**

  ```java
  <!--导入生成可执行jar包的依赖，简化部署-->
      <build>
          <plugins>
              <plugin>
                  <groupId>org.springframework.boot</groupId>
                  <artifactId>spring-boot-maven-plugin</artifactId>
              </plugin>
          </plugins>
      </build>
  ```

  将这个应用打包成jar包，直接cmd命令提示符使用java-jar的命令进行执行。

### SpringBoot探究

#### 1、POM文件

1. ```XML
   <parent>
       <groupId>org.springframework.boot</groupId>
       <artifactId>spring-boot-starter-parent</artifactId>
       <version>1.5.2.RELEASE</version>
   </parent>
   他的父项目是，按住Ctrl点进去看<artifactId>spring-boot-starter-parent</artifactId>
   <parent>
   		<groupId>org.springframework.boot</groupId>
   		<artifactId>spring-boot-dependencies</artifactId>
   		<version>1.5.2.RELEASE</version>
   		<relativePath>../../spring-boot-dependencies</relativePath>
   	</parent>
   按住Ctrl点进去看<artifactId>spring-boot-dependencies</artifactId>
   <properties>
   		<!-- Dependency versions -->
   		<activemq.version>5.14.3</activemq.version>
   		<antlr2.version>2.7.7</antlr2.version>
   		<appengine-sdk.version>1.9.49</appengine-sdk.version>
   		<artemis.version>1.5.3</artemis.version>
   		<aspectj.version>1.8.9</aspectj.version>
   		<assertj.version>2.6.0</assertj.version>
   		<atomikos.version>3.9.3</atomikos.version>
   		<bitronix.version>2.1.4</bitronix.version>
   		<caffeine.version>2.3.5</caffeine.version>
   		<cassandra-driver.version>3.1.4</cassandra-driver.version>
   		<classmate.version>1.3.3</classmate.version>
   		<commons-beanutils.version>1.9.3</commons-beanutils.version>
   		<commons-collections.version>3.2.2</commons-collections.version>
   		<commons-codec.version>1.10</commons-codec.version>
   		<commons-dbcp.version>1.4</commons-dbcp.version>
   		<commons-dbcp2.version>2.1.1</commons-dbcp2.version>
       。。。。
   </properties>
   对后面需要用到的都进行了依赖管理，
   -------------他的作用就是管理了所有的SpringBoot应用里面的所有依赖版本--------------
   ```

   SpringBoot的版本仲裁中心，以后导入版本依赖是不需要写版本的；（没有在dependencies里面管理的依赖自然需要声明版本号）

#### 2、启动器

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>
```

**spring-boot-starter-web:**

​	spring-boot-starter:spring-boot场景启动器；帮我们导入web模板正常运行所依赖的组件；

SpringBoot将所有的功能场景都抽取出来，做成一个个的starters（启动器），只需要在项目里面引入这些starter相关场景的所有依赖都会导入进来。要用什么功能就导入什么场景的启动器。

#### 3、主程序类、启动类

```java
/**
 * @author
 * @SpringBootApplication 来标注SpringBoot主程序类，说明这是一个Spring Boot应用
 */
@SpringBootApplication
public class HelloWorldMainApplication {

    public static void main(String[] args){

        //SpringBoot启动起来
        SpringApplication.run(HelloWorldMainApplication.class);
    }
}
```

**@SpringBootApplication：**Spring Boot应用标注在某个类上，说明这个类是Spring Boot的主配置类，SpringBoot就应该运行该类的main方法来启动SpringBoot应用

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@SpringBootConfiguration
@EnableAutoConfiguration
@ComponentScan(
    excludeFilters = {@Filter(
    type = FilterType.CUSTOM,
    classes = {TypeExcludeFilter.class}
), @Filter(
    type = FilterType.CUSTOM,
    classes = {AutoConfigurationExcludeFilter.class}
)}
)
public @interface SpringBootApplication {}
```

**@SpringBootConfiguration**：SpringBoot的配置类：

​		标注在某个类上，表示这是一个Spring Boot的配置类

​		**@Configuration**：配置类上来标注这个注解，这个注解是Spring定义的

​				配置类 ----- 配置文件；配置类也是容器中的一个组件；@Component

​		**@EnableAutoConfiguration**：开启自动装配的功能

​				以前我们需要配置的东西，SpringBoot帮我们自动配置；@EnableAutoConfiguration告诉SpringBoot开启自动配置的功能，这样自动配置才能生效。

```java
@AutoConfigurationPackage
@Import({EnableAutoConfigurationImportSelector.class})
public @interface EnableAutoConfiguration {}
```

​	**@AutoConfigurationPackage:自动配置包,作用就是将该注解标注的类(有可能是启动类，也有可能是非启动类)所在的包下面的所有组件都扫描**

​		**@Import({EnableAutoConfigurationImportSelector.class})**；

​		Spring的底层注解@Import，给容器中导入一个组件；导入的组件由AutoConfigurationPackages.Register.class

​	**@Import({EnableAutoConfigurationImportSelector.class})**；

​			作用：给容器中导入组件

​			**EnableAutoConfigurationImportSelector：**导入哪些组件？

​			将所有需要导入的组件以全类名的方式返回；这些组件就会被添加到容器中

​			会给容器中导入非常多的自动配置类（XXXAutoConfiguration）；就是容器中导入这个场景需要的所有组件，并配置好这些组件

​			节省了手动编写配置类的工作

​				SpringFactoriesLoader.loadFactoryNames(EnableAutoConfiguration.class,classLoader);

​				SpringBoot启动的时候从类路径下的META—INF/spring.factories中获取EnableAutoConfiguration指定的值，这个地方就在springboot的自动配置jar包里面，刚好95个，将这些值作为自动配置类导入到容器中，自动配置类就生效了，帮我们进行自动配置的工作。以前我们需要手动配置的东西，自动配置类都帮我们做了。

​				j2EE的整体整合解决方案和自动配置都在spring-boot-autoconfigure-1.5.2.RELEASE.jar包的org包里面

​				@Bean给容器中添加一个组件

**使用Spring initializer快速创建Spring Boot项目**

idea支持使用Spring的项目创建向导快速创建一个SpringBoot项目 

默认生成的SpringBoot项目已经完成

- 主程序已经好了，还需要我们自己的逻辑
- resources文件夹中的目录结构（资源文件夹）
  - static文件夹：保存所有的静态资源；js、css、images
  - templates：保存所有模板页面（SpringBoot默认jar包使用嵌入式的Tomcat，默认不支持JSP页面）；可以使用模板引擎（freemarker，thymeleaf，相当于就是前端页面嘛）；
  - application.properties:SpringBoot默认的配置文件；可以修改一些默认配置。

#### **配置文件**

- SpringBoot使用一个全局配置文件
  - application.properties
  - application.yml
- 配置文件放在src/main/resources目录或者类路径/config下
- .yml是YAML（YAML Ain‘t Markup Language）语言的文件，以数据为中心，比json、xml等更适合做配置文件
  - http://www.yaml.org/参考语法规范
- 全局配置文件的可以对一些默认配置值进行修改

#### **配置文件的作用**

- 修改SpringBoot的自动配置的默认值

- SpringBoot在底层都给我们配置好了

- yml

  ```xml
  server:
    port: 8080
  ```

##### **1、yml的基本语法**

- 使用缩进表示层级关系
- 以**空格**的缩进来控制层级关系
- 只要左对齐的一列数据，都是同一层级的
- 大小写敏感

##### **2、YML支持的三种数据结构**

- 对象：键值对的集合(k:(空格)value);
- 数组：一组按次序排序的值
- 字面量：单个的、不可再分的值

```xml
server:
	port: 8081
	path: /xxx
```

- 属性和值都是大小写敏感的

##### 3、值的写法

- 字面量：普通的值（数字、字符串、布尔）
  - k: (空格)v：字面量直接来写：
    - 字符串默认不用加上双引号或者单引号：
    - "":双引号；会转义字符串里面的特殊字符；特殊字符会作为本身想表示的意思
      - name:(空格)"zz \n lisi"；输出；zz 换行 lisi
    - “:单引号；不会转义特殊字符，特殊字符最终只是一个普通的字符串数据,****
      - name:(空格)"zz \n lisi"；输出；zz  \n  lisi
- **对象、Map(属性和值)（键值对）：**
  - k:(空格)v:在下一行来写对象的属性和值的关系；注意缩进
    - 对象还是k:(空格)v的方式

**方式一：**

```yaml
friends:
	lastName: zz
	age: 20
```

**方式二：行内写法**

```yaml
friends: {lastName: zz,age: 20}
```

- **数组（List、Set）：**
  - 用-(空格)值表示数组中的一个元素

```yaml
pets:
	- cat
	- dog
	- pig
```

**第二种方式：行内写法**

```yaml
pets:(空格)[cat,dog,pig]
```

- 复合结构。以上写法的任意组合
- 字面量：
  - 数字

##### 配置文件值注入

```yaml
person:
    name: hello
    age: 20
    birthDay: 2021/7/28
    map: {k1:v1,k2:12}
    list:
      - zz
      - aa
      - bb
    dog:
      name: 旺财
      age: 5
```

**javaBean**

```java
/**
 * @author
 * 将配置文件中配置的每一个属性的值，映射到这个组件中
 * @ConfigurationProperties:告诉SpringBoot将本类中的所有属性和配置文件中相关的配置进行绑定
 * prefix = "person":配置文件中哪一个下面的所有属性进行一一映射
 * 只有这个组件是容器中的组件，才能使用容器提供的@ConfigurationProperties功能，
 * 就是说必须要加一个@Component注解才能够证明是容器中的组件，也才能够使用容器中的
 * @ConfigurationProperties注解的功能
 */
@Data
@Component
@ConfigurationProperties(prefix = "person")
public class Person {
    private String name;
    private Integer age;
    private String birthDay;

    private Map<String,Object> map;
    private List<Object> list;
    private Dog dog;
}
```

**注意：**

- 使用@ConfigurationProperties(prefix = "person")注解的时候必须添加@Component注解，只有这个组件是容器中的组件，才能使用容器提供的@ConfigurationProperties功能,就是说必须要加一个@Component注解才能够证明是容器中的组件，也才能够使用容器中的@ConfigurationProperties注解的功能。
- @Component注解就是把该类加载到容器中

**导入配置文件处理器，配置文件进行绑定就会有提示**

```xml
<!--导入配置文件处理器，配置文件进行绑定就会有提示-->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-configuration-processor</artifactId>
            <version>2.4.1</version>
        </dependency>
```

**@Value语法展示**

```java
/**
 * @author
 * @ConfigurationProperties(prefix ="user")该注解的意思就是该类与配置文件的属性名称进行一一映射，
 * 但是不能单独使用，因为该注解是配置注解里面的，而配置注解又是容器里面的，所以需要添加一个@Component指明这是一个组件，
 * 容器就可以识别。
 */
@Data
@Component
//@ConfigurationProperties(prefix ="user")
public class User {

    /**
     * <bean class="User">
     *     <property name="lastName" value="字面量/${key}从环境变量、配置文件中获取值/#{SpEL}"></property>
     *     </bean>
     */
    @Value("${user.name}")
    private String name;
    @Value("#{11*2}")
    private Integer age;
    @Value("true")
    private Boolean isStudent;
    private Date birthday;
    private List<Object> list;
    private Map<String,Object> map;
    private Student student;
}
```

**注意：**

- 还是需要指定该类是组件到容器里面@Component
- 使用@Value注解可以在里面写计算（SpEL），比如说这个@Value("#{11*2}")

#### **@Value和@Configuration注解的区别**

|                            | @Configuration         | @Value       |
| -------------------------- | ---------------------- | ------------ |
| 功能分析                   | 批量指定该类的所有属性 | 单个指定属性 |
| 松散绑定（松散语法）       | 支持                   | 不支持       |
| SpEL计算                   | 不支持                 | 支持         |
| JSR303数据校验(@Validated) | 支持                   | 不支持       |
| 复杂类型封装               | 支持                   | 不支持       |

**复杂类型**

```java
@Value("${user.map}")
private Map<String,Object> map;
```

使用@Configuration是可以解析的，但是使用**@Value不可以**

**松散绑定**

- 松散绑定表示一个属性可以用下划线或者小驼峰来设置，比如说：private String lastName;类的属性是这个，配置文件里面可以写last-name，也可以写lastName。但是使用@Value不支持这样写。

**JSR303数据校验**

- @Validated注解使用来校验数据的，写个例子

```java
@Data
@Component
@Validated
@ConfigurationProperties(prefix ="user")
public class User {

    /**
     * <bean class="User">
     *     <property name="lastName" value="字面量/${key}从环境变量、配置文件中获取值/#{SpEL}"></property>
     *     </bean>
     */
//    @Value("${user.name}")
    @Email
    private String lastName;
//    @Value("#{11*2}")
    private Integer age;
//    @Value("true")
    private Boolean idStudent;
    private Date birthday;
    private List<Object> list;
    private Map<String,Object> map;
    private Student student;
}
```

**注意**

- 使用该注解还是需要指定到容器里面
- @Value注解使用这个@Validated注解是**无效的**

**SpEL**

- SpEL（Spring Expression Language），即Spring表达式语言，是比JSP的EL更强大的一种表达式语言。为什么要总结SpEL，因为它可以在运行时查询和操作数据，尤其是数组列表型数据，因此可以缩减代码量，优化代码结构。个人认为很有用。

- 使用方式

  - @Value注解

    ```java
    //@Value能修饰成员变量和方法形参
        //#{}内就是表达式的内容
        @Value("#{表达式}")
        public String arg;
    ```

  - bean的配置

    ```java
    <bean id="xxx" class="com.java.XXXXX.xx">
        <!-- 同@Value,#{}内是表达式的值，可放在property或constructor-arg内 -->
        <property name="arg" value="#{表达式}">
    </bean>
    ```

  - Expression

  ```java
  import org.springframework.expression.Expression;
  import org.springframework.expression.ExpressionParser;
  import org.springframework.expression.spel.standard.SpelExpressionParser;
  import org.springframework.expression.spel.support.StandardEvaluationContext;
   
  public class SpELTest {
   
      public static void main(String[] args) {
   
          //创建ExpressionParser解析表达式
          ExpressionParser parser = new SpelExpressionParser();
          //表达式放置
          Expression exp = parser.parseExpression("表达式");
          //执行表达式，默认容器是spring本身的容器：ApplicationContext
          Object value = exp.getValue();
          
          /**如果使用其他的容器，则用下面的方法*/
          //创建一个虚拟的容器EvaluationContext
          StandardEvaluationContext ctx = new StandardEvaluationContext();
          //向容器内添加bean
          BeanA beanA = new BeanA();
          ctx.setVariable("bean_id", beanA);
          
          //setRootObject并非必须；一个EvaluationContext只能有一个RootObject，引用它的属性时，可以不加前缀
          ctx.setRootObject(XXX);
          
          //getValue有参数ctx，从新的容器中根据SpEL表达式获取所需的值
          Object value = exp.getValue(ctx);
      }
  }
  ```

**使用案例**

字面量赋值

```xml
<!-- 整数 -->
<property name="count" value="#{5}" />
<!-- 小数 -->
<property name="frequency" value="#{13.2}" />
<!-- 科学计数法 -->
<property name="capacity" value="#{1e4}" />
<!-- 字符串  #{"字符串"} 或  #{'字符串'} -->
<property name="name" value="#{'我是字符串'}" />
<!-- Boolean -->
<property name="enabled" value="#{false}" />
```

引用Bean、属性和方法（必须是public修饰的）

```xml
<property name="car" value="#{car}" />
<!-- 引用其他对象的属性 -->
<property name="carName" value="#{car.name}" />
<!-- 引用其他对象的方法 -->
<property name="carPrint" value="#{car.print()}" />
```

算术运算符：+,-,*,/,%,^

```xml
<!-- 3 -->
<property name="num" value="#{2+1}" />
<!-- 1 -->
<property name="num" value="#{2-1}" />
<!-- 4 -->
<property name="num" value="#{2*2}" />
<!-- 3 -->
<property name="num" value="#{9/3}" />
<!-- 1 -->
<property name="num" value="#{10%3}" />
<!-- 1000 -->
<property name="num" value="#{10^3}" />
```

字符串连接符：+

```xml
<!-- 10年3个月 -->
<property name="numStr" value="#{10+'年'+3+'个月'}" />
```

比较运算符：<(<),>(>),==,<=,>=,lt,gt,eq,le,ge

```xml
<!-- false -->
<property name="numBool" value="#{10&lt;0}" />
<!-- false -->
<property name="numBool" value="#{10 lt 0}" />
<!-- true -->
<property name="numBool" value="#{10&gt;0}" />
<!-- true -->
<property name="numBool" value="#{10 gt 0}" />
<!-- true -->
<property name="numBool" value="#{10==10}" />
<!-- true -->
<property name="numBool" value="#{10 eq 10}" />
<!-- false -->
<property name="numBool" value="#{10&lt;=0}" />
<!-- false -->
<property name="numBool" value="#{10 le 0}" />
<!-- true -->
<property name="numBool" value="#{10&gt;=0}" />
<!-- true -->
<property name="numBool" value="#{10 ge 0}" />
```

逻辑运算符：and,or,not,&&(&&),||,!

```xml
<!-- false -->
<property name="numBool" value="#{true and false}" />
<!-- false -->
<property name="numBool" value="#{true&amp;&amp;false}" />
<!-- true -->
<property name="numBool" value="#{true or false}" />
<!-- true -->
<property name="numBool" value="#{true||false}" />
<!-- false -->
<property name="numBool" value="#{not true}" />
<!-- false -->
<property name="numBool" value="#{!true}" />
```

条件运算符：?true:false

```xml
<!-- 真 -->
<property name="numStr" value="#{(10>3)?'真':'假'}" />
```

正则表达式：matches

```xml
!-- true -->
<property name="numBool" value="#{user.email matches '[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,4}'}" />
```

调用静态方法或静态属性

```xml
<!-- 3.141592653589793 -->
<property name="PI" value="#{T(java.lang.Math).PI}" />
```

获取容器内的变量，可以使用“#bean_id”来获取。有两个特殊的变量，可以直接使用。

```java
 String result2 = parser.parseExpression("#root").getValue(ctx, String.class);  
 
        String s = new String("abcdef");
        ctx.setVariable("abc",s);
        //取id为abc的bean，然后调用其中的substring方法
        parser.parseExpression("#abc.substring(0,1)").getValue(ctx, String.class);
```

方法调用

```java
Method parseInt = Integer.class.getDeclaredMethod("parseInt", String.class); 
 ctx.registerFunction("parseInt", parseInt); 
 ctx.setVariable("parseInt2", parseInt); 
```

Elvis运算符：是三目运算符的特殊写法，可以避免null报错的情况

```csharp
name != null? name : "other"
 
    //简写为：
    name?:"other"
```

安全保证：为了避免操作对象本身可能为null，取属性时报错，定义语法
语法： “对象?.变量|方法”

```cpp
list?.length
```

直接使用java代码new/instance of

```cpp
 Expression exp = parser.parseExpression("new Spring('Hello World')");
```

**其他的看地址https://www.jianshu.com/p/e0b50053b5d3**

**使用yaml或者properties配置文件都可以**

**小结：**

- 如果我们只需要获取配置文件中的某个值，就使用@Value

  ```java
  /**
   * @author
   */
  @RestController
  public class HelloController {
  
      @Value("${user.last-name}")
      private String name;
  
      @RequestMapping("/sayHello")
      public String sayHello(){
          return "hello"+this.name;
      }
  }
  ```
  
- 如果说我们需要编写一个javabean来和配置文件进行映射，我们就直接使用@ConfigurationProperties；

  ```java
  /**
   * @author
   * @ConfigurationProperties(prefix ="user")该注解的意思就是该类与配置文件的属性名称进行一一映射，
   * 但是不能单独使用，因为该注解是配置注解里面的，而配置注解又是容器里面的，所以需要添加一个@Component指明这是一个组件，
   * 容器就可以识别。
   */
  @Data
  @Component
  //@Validated
  @ConfigurationProperties(prefix ="user")
  public class User {
  
      /**
       * <bean class="User">
       *     <property name="lastName" value="字面量/${key}从环境变量、配置文件中获取值/#{SpEL}"></property>
       *     </bean>
       */
  //    @Value("${user.name}")
      private String lastName;
  //    @Value("#{11*2}")
      private Integer age;
  //    @Value("true")
      private Boolean isStudent;
      private Date birthday;
      private List<Object> list;
      private Map<String,Object> map;
      private Student student;
  }
  ```

**@ConfigurationProperties：默认从全局配置文件中获取值**

- 与@Bean结合为属性赋值
- 与@PropertySource（只能用于properties文件）结合读取指定文件

**@ConfigurationProperties @Validated**

- 支持JSR303进行配置文件值校验

**@ImportResource读取外部配置文件**



**@PropertySource和@ImportResource的使用**

- **@PropertySource：加载指定的配置文件**

```java
/**
 * @author
 * @ConfigurationProperties(prefix ="user")该注解的意思就是该类与配置文件的属性名称进行一一映射，
 * 但是不能单独使用，因为该注解是配置注解里面的，而配置注解又是容器里面的，所以需要添加一个@Component指明这是一个组件，
 * 容器就可以识别。
 */
@Data
@Component
@PropertySource(value = {"classpath:user.properties"})
//@Validated
@ConfigurationProperties(prefix ="user")
public class User {

    /**
     * <bean class="User">
     *     <property name="lastName" value="字面量/${key}从环境变量、配置文件中获取值/#{SpEL}"></property>
     *     </bean>
     */
//    @Value("${user.name}")
    private String lastName;
//    @Value("#{11*2}")
    private Integer age;
//    @Value("true")
    private Boolean idStudent;
    private Date birthday;
    private List<Object> list;
    private Map<String,Object> map;
    private Student student;
}
```

**自定义配置文件（user.properties）**

```xml
user.lastname=zhangsan
user.age=12
user.list=a,b,c
user.map.k1=v1
user.map.k2=v2
user.student.name=zz
user.student.sno123456
```

**注意：**

- @ConfigurationProperties(prefix ="user")配合全局配置注解进行使用
- 如果全局配置文件里面的属性值优先级要高于自定义的配置文件优先级，所以要想使用到自定义的配置文件，那么全局配置文件需要将相应的注释掉或者删掉。



**@ImportResource**：作用就是导入spring的配置文件，让配置文件里面的内容生效

- Spring Boot里面没有Spring的配置文件，我们自己编写的配置文件，也不能识别
- 如果想要识别到该配置文件，就可以使用@ImportResource放在配置类上面，一般就是放在启动类上面

```java
/**
 * @author
 */
@ImportResource(locations = {"classpath:beans.xml"})
@SpringBootApplication
public class SpringBoot02Application {

    public static void main(String[] args) {
        SpringApplication.run(SpringBoot02Application.class, args);
    }

}
```

**注意：**

- 该注解里面的参数是可以配置多个配置文件的
- 导入spring的配置文件，让其生效

**案例**

```
//类里面添加
@Data
@Component
@PropertySource(value = {"classpath:user.properties"})
//@Validated
@ConfigurationProperties(prefix ="user")
public class User {

    /**
     * <bean class="User">
     *     <property name="lastName" value="字面量/${key}从环境变量、配置文件中获取值/#{SpEL}"></property>
     *     </bean>
     */
//    @Value("${user.name}")
    private String lastName;
//    @Value("#{11*2}")
    private Integer age;
//    @Value("true")
    private Boolean isStudent;
    private Date birthday;
    private List<Object> list;
    private Map<String,Object> map;
    private Student student;
}

============
com.cg.XX下面添加类
public class HelloService {
}
============
resouces包下面添加beans.xml文件
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <beans>
        <bean id="helloService" class="com.cg.springboot02.service.HelloService">

        </bean>
    </beans>
</beans>
============
启动类添加
/**
 * @author
 */
@ImportResource(locations = {"classpath:beans.xml"})
@SpringBootApplication
public class SpringBoot02Application {

    public static void main(String[] args) {
        SpringApplication.run(SpringBoot02Application.class, args);
    }

}
============
进行单元测试，如果没有就需要添加单元测试依赖
@SpringBootTest
class SpringBoot02ApplicationTests {

    @Autowired
    User user;

    @Autowired
    ApplicationContext ioc;

    @Test
    public void testHelloService(){
        boolean b = ioc.containsBean("helloService");
        System.out.println(b);
    }

    @Test
    void contextLoads() {
        System.out.println(user);
    }

}
结果：
true
```

**注意：**

- 这里自动注入了ApplicationContext的依赖ioc
- 根据这个ioc.containsBean("helloService")去判断配置文件的bean是否在容器里面



#### **SpringBoot支持给容器添加组件的条件：推荐使用全注解的方式来实现，就是添加一个包（在com.cg包下面），config包里面添加配置**

- 配置类=======Spring配置文件
- 使用@Bean给容器中添加组件

```java
/**
 * @author
 * @Configuration:指明当前类是一个配置类；就是来替代之前的Spring配置文件
 * <bean></bean>在配置文件中使用该标签添加组件
 */
@Configuration
public class MyConfig {
    /**
     * 将方法的返回值添加到容器中；容器中这个组件默认的id就是方法名
     * @return
     */
    @Bean
    public HelloService helloService(){
        System.out.println("配置类@Bean给容器中添加组件了");
        return new HelloService();
    }
}
```

**注意：**

- 使用这种配置类必须要添加@Configuration注解
- @bean注解的意思就是将方法的返回值添加到容器中；容器中这个组件的默认id就是方法名
- 使用调试的时候boolean b = ioc.containsBean("helloService");方法里面的参数名称要和@Bean注解的方法名称保持一致，不然找不到。



#### 配置文件占位符

- **RandomValuePropertySource：**配置文件中可以使用随机数

  - ${random.value}、${random.int}、${random.long}
  - ${random.int(10)}、${random.int[1024,65536]}

- **属性占位符**

  ```xml
  app.name=MyApp
  app.description=${app.name} is a Spring Boot application
  ```

  - 可以在配置文件中引入前面配置过的属性（优先级前面配置过的这里都能用）

  - ${app.name:默认值}来指定找不到属性时的默认值

  - ```xml
    user.lastname=zhangsan${random.uuid}
    user.age=${random.int}
    user.id-student=true
    user.list=a,b,c
    user.map.k1=v1
    user.map.k2=v2
    user.student.name=${user.hello:hello}_zz
    user.student.sno=123456
    ```

    使用占位符可以获取到原来配置文件里面的值，如果没有这个属性值就可以设置默认值。

#### **Profile**

profile是Spring对不同环境提供不同配置功能的支持，可以通过激活、指定参数等方式快速切换环境

##### 1、多个profile文件形式：

​	格式：application-{profile}.properties

​		application-dev.properties、application-prod.properties

**我们在主配置文件编写的时候，文件名可以是application-{profile}.properties/yml，默认使用application.properties的配置**

##### 2、多个profile文档块模式：

```yml
server:
  port: 8080
spring:
  profiles:
    active: prod #指定开启哪个环境
---

server:
  port: 8081
spring:
  profiles: dev #指定属于那个环境
---

server:
  port: 8082
spring:
  profiles: prod #指定属于那个环境
```

##### 3、激活方式：

**1、在配置文件中指定 spring.profiles.active=prod**

**2、命令行**

这种是打包之后使用命令：java -jar spring-boot02-0.0.1-SNAPSHOT.jar --spring.profiles.active=dev

​	   --spring.profiles.active=dev

可以直接在测试的时候，配置传入命令行参数

![命令行方式执行profile切换配置](../image/命令行方式执行profile.png)

**3、jvm虚拟机参数**

​	  -Dspring.profiles.active=dev

​	![](../image/虚拟机配置切换方式.png)



#### **配置文件加载位置**

- springboot启动会扫描以下位置的application.properties或者application.yml文件作为SpringBoot的默认配置文件
  - file:./config/
  - file:./
  - classpath:/config/
  - classpath:/
  - 以上是按照优先级从高到低的顺序，所有位置的文件都会被加载，**高优先级配置**内容**会覆盖低优先级配置内容**
  - 我们也可以通过配置spring.config.location来改变默认配置

![配置文件加载优先级](../image/配置文件优先级.png)

SpringBoot会从这四个位置全部加载主要配置文件；**互补配置**

```xml
#配置项目的访问路径
server.servlet.context-path=/boot02
```

我们还可以通过spring.config.location来改变默认的配置文件位置

**项目打包好以后，我们可以使用命令行参数的方式，启动项目的时候来指定配置文件的新位置；指定配置文件和默认加载的这些配置文件共同起作用形成互补配置。**

java -jar spring-boot-02-config-02-0.0.1-SNAPSHOT.jar --spring.config.location+"配置文件路径"

2.1.1版本的是java -jar spring-boot-02-config-02-0.0.1-SNAPSHOT.jar --spring.config.additional.location+"配置文件路径"

##### 外部加载顺序

**Spring Boot 支持多种外部配置方式：按照优先级从高到低(加粗的表示重要一点的)，高优先级的配置会覆盖低优先级的配置，如果配置属性有些不同的时候，就会形成互补配置。**

1. **命令行参数**

   java -jar spring-boot-02-config-02-0.0.1-SNAPSHOT.jar --server.port=8087（空格）--server.context-path=/zz

   多个配置用空格分开： --配置项=值

2. 来自java:comp/env的JNDI属性

3. Java的系统属性（System.getProperties()）

4. 操作系统环境变量

5. RandomValuePropertySource配置的random.*属性值

   **优先加载带profile，仍然是从jar包外向jar包内寻找**

6. **jar包外部的application-{profile}.properties或者application.yml（带spring.profile）配置文件**

7. **jar包内部的application-{profile}.properties或者application.yml（带spring.profile）配置文件**

   **之后加载不带profile的**

8. **jar包外部的application-{profile}.properties或者application.yml（不带spring.profile）配置文件**

9. **jar包内部的application-{profile}.properties或者application.yml（不带spring.profile）配置文件**

10. @Configuration注解类上的@PropertySource

11. 通过SpringApplication.setDefaultProperties指定的默认属性

更多的配置文件参考官方文档



##### 自动装配原理

配置文件到底能写什么？怎么写？自动配置原理；

[配置文件参照](官方文档)

**自动配置原理：**

- springboot启动的时候加载主配置类，开启了自动配置功能@EnableAutoConfiguration

  - @EnableAutoConfiguration作用：给容器中导入一些组件

    - 可以查看selectImports()**方法的内容**

    - this.getAutoConfigurationEntry(annotationMetadata);方法里面

    - List<String> configurations = this.getCandidateConfigurations(annotationMetadata, attributes);作用：获取候选的配置

    - ```java
      SpringFactoriesLoader.loadFactoryNames(this.getSpringFactoriesLoaderFactoryClass(), this.getBeanClassLoader());
      扫描所有jar包类路径下 META-INF/spring.factories
      把扫描到的这些文件的内容包装成properties对象
      从properties中获取到EnableAutoConfiguration.class类（类名）对应的值，然后把他们添加到容器中
      return new AutoConfigurationImportSelector.AutoConfigurationEntry(configurations, exclusions);
      ```

**将类路径下META-INF/spring.factories的EnableAutoConfiguration的所有值都添加到容器中**

```xml
# Auto Configure
org.springframework.boot.autoconfigure.EnableAutoConfiguration=\
org.springframework.boot.autoconfigure.admin.SpringApplicationAdminJmxAutoConfiguration,\
org.springframework.boot.autoconfigure.aop.AopAutoConfiguration,\
org.springframework.boot.autoconfigure.amqp.RabbitAutoConfiguration,\
org.springframework.boot.autoconfigure.batch.BatchAutoConfiguration,\
org.springframework.boot.autoconfigure.cache.CacheAutoConfiguration,\
org.springframework.boot.autoconfigure.cassandra.CassandraAutoConfiguration,\
org.springframework.boot.autoconfigure.context.ConfigurationPropertiesAutoConfiguration,\
org.springframework.boot.autoconfigure.context.LifecycleAutoConfiguration,\
org.springframework.boot.autoconfigure.context.MessageSourceAutoConfiguration,\
org.springframework.boot.autoconfigure.context.PropertyPlaceholderAutoConfiguration,\
org.springframework.boot.autoconfigure.couchbase.CouchbaseAutoConfiguration,\
org.springframework.boot.autoconfigure.dao.PersistenceExceptionTranslationAutoConfiguration,\
org.springframework.boot.autoconfigure.data.cassandra.CassandraDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.cassandra.CassandraReactiveDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.cassandra.CassandraReactiveRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.cassandra.CassandraRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.couchbase.CouchbaseDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.couchbase.CouchbaseReactiveDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.couchbase.CouchbaseReactiveRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.couchbase.CouchbaseRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.elasticsearch.ElasticsearchDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.elasticsearch.ElasticsearchRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.elasticsearch.ReactiveElasticsearchRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.elasticsearch.ReactiveElasticsearchRestClientAutoConfiguration,\
org.springframework.boot.autoconfigure.data.jdbc.JdbcRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.jpa.JpaRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.ldap.LdapRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.mongo.MongoDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.mongo.MongoReactiveDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.mongo.MongoReactiveRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.mongo.MongoRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.neo4j.Neo4jDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.neo4j.Neo4jReactiveDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.neo4j.Neo4jReactiveRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.neo4j.Neo4jRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.r2dbc.R2dbcDataAutoConfiguration,\
org.springframework.boot.autoconfigure.data.r2dbc.R2dbcRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.redis.RedisAutoConfiguration,\
org.springframework.boot.autoconfigure.data.redis.RedisReactiveAutoConfiguration,\
org.springframework.boot.autoconfigure.data.redis.RedisRepositoriesAutoConfiguration,\
org.springframework.boot.autoconfigure.data.rest.RepositoryRestMvcAutoConfiguration,\
org.springframework.boot.autoconfigure.data.web.SpringDataWebAutoConfiguration,\
org.springframework.boot.autoconfigure.elasticsearch.ElasticsearchRestClientAutoConfiguration,\
org.springframework.boot.autoconfigure.flyway.FlywayAutoConfiguration,\
org.springframework.boot.autoconfigure.freemarker.FreeMarkerAutoConfiguration,\
org.springframework.boot.autoconfigure.groovy.template.GroovyTemplateAutoConfiguration,\
org.springframework.boot.autoconfigure.gson.GsonAutoConfiguration,\
org.springframework.boot.autoconfigure.h2.H2ConsoleAutoConfiguration,\
org.springframework.boot.autoconfigure.hateoas.HypermediaAutoConfiguration,\
org.springframework.boot.autoconfigure.hazelcast.HazelcastAutoConfiguration,\
org.springframework.boot.autoconfigure.hazelcast.HazelcastJpaDependencyAutoConfiguration,\
org.springframework.boot.autoconfigure.http.HttpMessageConvertersAutoConfiguration,\
org.springframework.boot.autoconfigure.http.codec.CodecsAutoConfiguration,\
org.springframework.boot.autoconfigure.influx.InfluxDbAutoConfiguration,\
org.springframework.boot.autoconfigure.info.ProjectInfoAutoConfiguration,\
org.springframework.boot.autoconfigure.integration.IntegrationAutoConfiguration,\
org.springframework.boot.autoconfigure.jackson.JacksonAutoConfiguration,\
org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration,\
org.springframework.boot.autoconfigure.jdbc.JdbcTemplateAutoConfiguration,\
org.springframework.boot.autoconfigure.jdbc.JndiDataSourceAutoConfiguration,\
org.springframework.boot.autoconfigure.jdbc.XADataSourceAutoConfiguration,\
org.springframework.boot.autoconfigure.jdbc.DataSourceTransactionManagerAutoConfiguration,\
org.springframework.boot.autoconfigure.jms.JmsAutoConfiguration,\
org.springframework.boot.autoconfigure.jmx.JmxAutoConfiguration,\
org.springframework.boot.autoconfigure.jms.JndiConnectionFactoryAutoConfiguration,\
org.springframework.boot.autoconfigure.jms.activemq.ActiveMQAutoConfiguration,\
org.springframework.boot.autoconfigure.jms.artemis.ArtemisAutoConfiguration,\
org.springframework.boot.autoconfigure.jersey.JerseyAutoConfiguration,\
org.springframework.boot.autoconfigure.jooq.JooqAutoConfiguration,\
org.springframework.boot.autoconfigure.jsonb.JsonbAutoConfiguration,\
org.springframework.boot.autoconfigure.kafka.KafkaAutoConfiguration,\
org.springframework.boot.autoconfigure.availability.ApplicationAvailabilityAutoConfiguration,\
org.springframework.boot.autoconfigure.ldap.embedded.EmbeddedLdapAutoConfiguration,\
org.springframework.boot.autoconfigure.ldap.LdapAutoConfiguration,\
org.springframework.boot.autoconfigure.liquibase.LiquibaseAutoConfiguration,\
org.springframework.boot.autoconfigure.mail.MailSenderAutoConfiguration,\
org.springframework.boot.autoconfigure.mail.MailSenderValidatorAutoConfiguration,\
org.springframework.boot.autoconfigure.mongo.embedded.EmbeddedMongoAutoConfiguration,\
org.springframework.boot.autoconfigure.mongo.MongoAutoConfiguration,\
org.springframework.boot.autoconfigure.mongo.MongoReactiveAutoConfiguration,\
org.springframework.boot.autoconfigure.mustache.MustacheAutoConfiguration,\
org.springframework.boot.autoconfigure.neo4j.Neo4jAutoConfiguration,\
org.springframework.boot.autoconfigure.netty.NettyAutoConfiguration,\
org.springframework.boot.autoconfigure.orm.jpa.HibernateJpaAutoConfiguration,\
org.springframework.boot.autoconfigure.quartz.QuartzAutoConfiguration,\
org.springframework.boot.autoconfigure.r2dbc.R2dbcAutoConfiguration,\
org.springframework.boot.autoconfigure.r2dbc.R2dbcTransactionManagerAutoConfiguration,\
org.springframework.boot.autoconfigure.rsocket.RSocketMessagingAutoConfiguration,\
org.springframework.boot.autoconfigure.rsocket.RSocketRequesterAutoConfiguration,\
org.springframework.boot.autoconfigure.rsocket.RSocketServerAutoConfiguration,\
org.springframework.boot.autoconfigure.rsocket.RSocketStrategiesAutoConfiguration,\
org.springframework.boot.autoconfigure.security.servlet.SecurityAutoConfiguration,\
org.springframework.boot.autoconfigure.security.servlet.UserDetailsServiceAutoConfiguration,\
org.springframework.boot.autoconfigure.security.servlet.SecurityFilterAutoConfiguration,\
org.springframework.boot.autoconfigure.security.reactive.ReactiveSecurityAutoConfiguration,\
org.springframework.boot.autoconfigure.security.reactive.ReactiveUserDetailsServiceAutoConfiguration,\
org.springframework.boot.autoconfigure.security.rsocket.RSocketSecurityAutoConfiguration,\
org.springframework.boot.autoconfigure.security.saml2.Saml2RelyingPartyAutoConfiguration,\
org.springframework.boot.autoconfigure.sendgrid.SendGridAutoConfiguration,\
org.springframework.boot.autoconfigure.session.SessionAutoConfiguration,\
org.springframework.boot.autoconfigure.security.oauth2.client.servlet.OAuth2ClientAutoConfiguration,\
org.springframework.boot.autoconfigure.security.oauth2.client.reactive.ReactiveOAuth2ClientAutoConfiguration,\
org.springframework.boot.autoconfigure.security.oauth2.resource.servlet.OAuth2ResourceServerAutoConfiguration,\
org.springframework.boot.autoconfigure.security.oauth2.resource.reactive.ReactiveOAuth2ResourceServerAutoConfiguration,\
org.springframework.boot.autoconfigure.solr.SolrAutoConfiguration,\
org.springframework.boot.autoconfigure.sql.init.SqlInitializationAutoConfiguration,\
org.springframework.boot.autoconfigure.task.TaskExecutionAutoConfiguration,\
org.springframework.boot.autoconfigure.task.TaskSchedulingAutoConfiguration,\
org.springframework.boot.autoconfigure.thymeleaf.ThymeleafAutoConfiguration,\
org.springframework.boot.autoconfigure.transaction.TransactionAutoConfiguration,\
org.springframework.boot.autoconfigure.transaction.jta.JtaAutoConfiguration,\
org.springframework.boot.autoconfigure.validation.ValidationAutoConfiguration,\
org.springframework.boot.autoconfigure.web.client.RestTemplateAutoConfiguration,\
org.springframework.boot.autoconfigure.web.embedded.EmbeddedWebServerFactoryCustomizerAutoConfiguration,\
org.springframework.boot.autoconfigure.web.reactive.HttpHandlerAutoConfiguration,\
org.springframework.boot.autoconfigure.web.reactive.ReactiveWebServerFactoryAutoConfiguration,\
org.springframework.boot.autoconfigure.web.reactive.WebFluxAutoConfiguration,\
org.springframework.boot.autoconfigure.web.reactive.error.ErrorWebFluxAutoConfiguration,\
org.springframework.boot.autoconfigure.web.reactive.function.client.ClientHttpConnectorAutoConfiguration,\
org.springframework.boot.autoconfigure.web.reactive.function.client.WebClientAutoConfiguration,\
org.springframework.boot.autoconfigure.web.servlet.DispatcherServletAutoConfiguration,\
org.springframework.boot.autoconfigure.web.servlet.ServletWebServerFactoryAutoConfiguration,\
org.springframework.boot.autoconfigure.web.servlet.error.ErrorMvcAutoConfiguration,\
org.springframework.boot.autoconfigure.web.servlet.HttpEncodingAutoConfiguration,\
org.springframework.boot.autoconfigure.web.servlet.MultipartAutoConfiguration,\
org.springframework.boot.autoconfigure.web.servlet.WebMvcAutoConfiguration,\
org.springframework.boot.autoconfigure.websocket.reactive.WebSocketReactiveAutoConfiguration,\
org.springframework.boot.autoconfigure.websocket.servlet.WebSocketServletAutoConfiguration,\
org.springframework.boot.autoconfigure.websocket.servlet.WebSocketMessagingAutoConfiguration,\
org.springframework.boot.autoconfigure.webservices.WebServicesAutoConfiguration,\
org.springframework.boot.autoconfigure.webservices.client.WebServiceTemplateAutoConfiguration
```

**每一个这样的 xxxAutoConfiguration类都是容器中的一个组件，都加入到容器中；用他们来做自动配置**

- 每一个自动配置类进行自动配置功能；

- 以**HttpEncodingAutoConfiguration（http编码自动配置）**为例解释自动配置原理；

  ```java
  @Configuration(
      proxyBeanMethods = false
  )
  @EnableConfigurationProperties({ServerProperties.class})
  @ConditionalOnWebApplication(
      type = Type.SERVLET
  )
  @ConditionalOnClass({CharacterEncodingFilter.class})
  @ConditionalOnProperty(
      prefix = "server.servlet.encoding",
      value = {"enabled"},
      matchIfMissing = true
  )
  public class ServerProperties {
      //他已经和springboot的配置文件映射了
      private final Encoding properties;
      
      //只有一个有参构造器的时候，参数的值就会从容器中取数据
      public HttpEncodingAutoConfiguration(ServerProperties properties) {
          this.properties = properties.getServlet().getEncoding();
      }
      
    	@Bean //给容器中添加一个组件，这个组件的某些值需要从properties中获取
      @ConditionalOnMissingBean //判断容器中没有这个组件
      public CharacterEncodingFilter characterEncodingFilter() {
          CharacterEncodingFilter filter = new OrderedCharacterEncodingFilter();
          filter.setEncoding(this.properties.getCharset().name());
          filter.setForceRequestEncoding(this.properties.shouldForce(org.springframework.boot.web.servlet.server.Encoding.Type.REQUEST));
          filter.setForceResponseEncoding(this.properties.shouldForce(org.springframework.boot.web.servlet.server.Encoding.Type.RESPONSE));
          return filter;
      }
  }
  ```

  **注意：**

  - **@Configuration：这是一个配置类，以前编写的配置文件一样，也可以给容器中添加组件**

  - **@EnableConfigurationProperties({ServerProperties.class})；启动指定类ConfigurationProperties功能，将配置文件中的值和ServerProperties.class这个类的属性绑定起来。放在spring的ioc容器中**

    - ```java
      @ConfigurationProperties(
          prefix = "server",
          ignoreUnknownFields = true
      )
      public class ServerProperties {}
      ```

  - **@ConditionalOnWebApplication(type = Type.SERVLET)：spring的@Condition注解，根据不同的条件，如果满足指定的条件，整个配置类里面的配置都会生效；作用：判断当前应用是否是web应用，如果是，当前配置类生效**

  - **@ConditionalOnClass({CharacterEncodingFilter.class})判断当前项目有无这个类，CharacterEncodingFilter这个类就是SpringMVC中进行乱码解决的过滤器**

  **注意：**

  - **@ConfigurationProperties从配置文件中获取指定的值和bean的属性进行绑定。**
  - **@ConditionalOnProperty(prefix = "server.servlet.encoding",value = {"enabled"},matchIfMissing = true)；判断配置文件中是否存在某个配置 某个====server.servlet.encoding.value;matchIfMissing = true这个的意思就是如果不存在，也是默认生效的。**
  - 根据当前不同的条件判断，决定这个类是否生效
    - 一旦这个配置类生效；这个配置类就会给容器中添加各种组件；这些组件的属性是从对应的properties类中获取的，这些类里面的每一个属性又是和配置文件绑定的，

- **所有在配置文件中能配置的属性都是在xxxxProperties类中封装着。配置文件能配置什么就可以参照某个功能对应的这个属性类**

  ```java
  @ConfigurationProperties(
      prefix = "server",
      ignoreUnknownFields = true
  )
  public class ServerProperties {}
  ```

**总结：**

- SpringBoot启动会加载大量的自动配置类
- 我们需要的功能有没有SpringBoot默认写好的自动配置类
- 自动配置类到底配置了哪些组件，只要我们用的组件有，我们就不需要再来配置了
- 给容器中自动配置类添加组件的时候，会从properties类中获取某些属性，我们就可以在配置文件中指定这些属性的值
- xxxxAutoConfiguration：自动配置类；给容器中添加组件
- xxxxProperties：封装配置文件中相关属性

**细节**

- @Conditional派生的注解（Spring注解版原生的@Conditional作用）
  - 作用：必须是@Conditional指定的条件成立，才给容器中添加组件，配置里面的所有内容才会生效

| @Conditional扩展注解            | 作用（判断是否满足当前指定条件）                 |
| ------------------------------- | ------------------------------------------------ |
| @ConditionalOnJava              | 系统的java版本是否符合要求                       |
| @ConditionalOnBean              | 容器中存在指定的Bean                             |
| @ConditionalOnMissingBean       | 容器中不存在指定的Bean                           |
| @ConditionalOnExpression        | 满足SpEL表达式指定                               |
| @ConditionalOnClass             | 系统中有指定的类                                 |
| @ConditionalOnMissingClass      | 系统中没有指定的类                               |
| @ConditionalOnSingleCandidate   | 容器中只有一个指定的bean，或者这个Bean是首选Bean |
| @ConditionalOnProperty          | 系统中指定的属性是否有指定的值                   |
| @ConditionalOnResource          | 类路径下是否存在指定资源文件                     |
| @ConditionalOnWebApplication    | 当前是web环境                                    |
| @ConditionalOnNotWebApplication | 当前不是web环境                                  |
| @ConditionalOnJndi              | JNDI存在指定项                                   |



**自动配置类必须在一定的条件下才能生效；**

我们怎么知道哪些配置类生效？

我们可以通过启动 debug = true属性；来让控制台打印自动配置报告，这样我们就可以很方便的知道哪些自动配置类生效

```java
server.port=8081

#使用debug方式可以查看哪些配置类被加载了
debug=true
#我们能配置的属性都是来源于这个功能的properties类
spring.http.encoding.charset=GB2312
spring.http.encoding.enabled=true
spring.http.encoding.force=false
    
==========（启用成功了的一部分截图）
============================

CONDITIONS EVALUATION REPORT
============================


Positive matches:
-----------------

   AopAutoConfiguration matched:

   - @ConditionalOnProperty (spring.aop.auto=true) matched (OnPropertyCondition)

   AopAutoConfiguration.ClassProxyingConfiguration matched:
      - @ConditionalOnMissingClass did not find unwanted class 'org.aspectj.weaver.Advice' (OnClassCondition)
      - @ConditionalOnProperty (spring.aop.proxy-target-class=true) matched (OnPropertyCondition)

   DispatcherServletAutoConfiguration matched:

   - @ConditionalOnClass found required class 'org.springframework.web.servlet.DispatcherServlet' (OnClassCondition)
     found 'session' scope (OnWebApplicationCondition)
       
--------------------------------------（没有启动，没有匹配的）
SessionAutoConfiguration:
      Did not match:
         - @ConditionalOnClass did not find required class 'org.springframework.session.Session' (OnClassCondition)

   SolrAutoConfiguration:
      Did not match:
         - @ConditionalOnClass did not find required class 'org.apache.solr.client.solrj.impl.CloudSolrClient' (OnClassCondition)
```

## 3. Spring Boot与日志

### 1、日志框架

xx：开发一个大型系统：

​	1、System.out.println("")；将关键数据打印在控制台；去掉？写在一个文件里面

​	2、框架来记录系统的一些运行时信息；日志框架；xxxloggin.jar

​	3、高达上的几个功能?异步模式？自动归档？xxxx？xxxx-logging-good.jar?

​	4、将以前框架卸下来？换上新的框架，重新修改之前的API；xxxx-perfect.jar；

​	5、JDBC--数据库驱动；

​			写了一个统一的接口层；日志门面（日志的一个抽象层）；logging-abstract.jar；

​			给项目中导入具体的日志实现就行了；我们之前的日志框架都是实现的抽象层。

**市场上的日志框架**

JUL、JCL、Jboos-logging、logback、log4j、log4j2、slf4j.....

| 日志门面（日志的抽象层）                                     | 日志实现                                     |
| ------------------------------------------------------------ | -------------------------------------------- |
| ~~JCL（jakarta Commons Logging）~~SLF4j（Simple Logging Facade for java）~~jboos-logging~~ | Log4j JUL（java.util.logging）Log4j2 Logback |

左边写一个门面（抽象层），右边来选一个实现。

日志门面：SLF4J；

日志实现：Logback；

SpringBoot：底层使用Spring框架，Spring框架默认是JCL；

​		**SpringBoot选用SLF4J和logback**

### 2、SLF4J的使用

#### 1、如何在系统中使用SLF4J

以后开发的时候，日志记录方法的调用；不应该直接调用日志的实现类，而是调用日志的抽象层里面的方法

给系统里面导入slf4j的jar和logback的实现jar

```java
import org.slf4j.logger;
import org.slf4j.LoggerFactory;

public class HelloWorld{
    public static void mian(String[] args){
        Logger logger = LoggerFactory.getLogger(HelloWorld.class);
        logger.info("hello world");
    }
    
}
```

![java日志类](../image/java日志-1627627736850.png)



每一个日志的实现框架都有自己的配置文件。使用slf4j以后，**配置文件还是做成日志实现框架自己本身的配置文件**

#### 2、遗留问题

a（slf4j+logback）：Spring（commons-logging）、hibernate（jboos-logging）、MyBatis、xxx

统一记录日志，即使是别的框架统一使用slf4j进行输出

![统一不同框架的日志](../image/统一不同框架的日志-1627627757904.png)

#### **如何让系统中所有的日志统一到slf4j；**

- 排除掉其余框架中的日志框架
- 用中间包来替换原有的日志框架
- 导入slf4j的其他的实现



### SpringBoot日志关系

```java
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter</artifactId>
  <version>2.5.3</version>
  <scope>compile</scope>
</dependency>
```

**SpringBoot使用他来做日志工能；**

```java
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-logging</artifactId>
  <version>2.5.3</version>
  <scope>compile</scope>
</dependency>
```

![springboot日志底层依赖关系](../image/springboot日志.png)

**注意：**

- loback-classic：使用logback记录日志
- jul-to-slf4j、log4j-over-slf4j、jcl-over-slf4j把其他日志转换为slf4j日志
- slf4j-api写入日志抽象层（接口）slf4j

**总结：**

- SpringBoot底层日志框架使用了slf4j+logback方式记录日志

- SpringBoot也把其他日志都替换成了slf4j

- 中间替换包？

  - ```java
    @SuppressWarnings("rawtypes")
    public abstract class LogFactoy{
        ... 
        static LogFactory logFactory = new SLF4JLogFactory();
    }
    ```

- 如果需要引入其他的框架？一定要把这个框架的默认日志依赖移除掉

  - Spring框架用的是commons-logging：SpringBoot框架是否移除掉了Spring框架的日志框架？

  - ```java
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-core</artifactId>
      <exclusions>
        <exclusion>
        	<groupId>commons-logging</groupId>
        	<artifactId>commons-logging</artifactId>
        </exclusion>
       </exclusions>
      <scope>compile</scope>
    </dependency>
    ```

**SpringBoot能自动适配所有的日志，而且底层使用slf4j+logback的方式记录日志，引入其他框架的时候，只需要把这个框架依赖的日志排除掉 **

#### 4、日志使用

SpringBoot默认帮我们配置好了日志；

```java
/**
 * 记录器
 */
Logger logger = LoggerFactory.getLogger(getClass());

@Test
void contextLoads() {
    //日志的级别
    //由低到高   trace<debug<info<warn<error
    //可以调整输出的日志级别：日志就只会在这个级别以后的高级级别生效
    logger.trace("这是trace日志...");
    logger.debug("这是debug日志...");
    //SpringBoot默认给我们的是info级别,没有指定级别的就用SpringBoot默认规定的级别：root级别
    logger.info("这是info日志...");
    logger.warn("这是warn日志...");
    logger.error("这是error日志...");
}
=============配置文件定义日志级别
logging.level.com.cg=trace
logging.file=spring.log
logging.path=/spring/log
logging.pattern.console=%d{yyyy-MM-dd} [%thread] %-5level %logger{50} - %msg%n
logging.pattern.file=%d{yyyy-MM-dd} === [%thread] ==== %-5level === %logger{50} === %msg%n
```

**注意：**

- 如果没有设置日志级别，SpringBooot默认是从info开始执行
- 日志的级别：由低到高   trace<debug<info<warn<error
- **logging.file=spring.log:**这段的意思是可以创建一个日志文件，用来记录日志，也可以设置绝对路径在c盘或者d盘，一旦启动类完成之后，就会在相应的地址生成一个日志文件。
- **logging.path=/spring/log：**会在当前项目的根目录下面创建Spring文件夹和里面的log文件夹；使用spring.log作为默认文件
- **logging.pattern.console：**指定在控制台日志输出的格式
- **logging.pattern.file：**指定文件中日志输出的格式

```java
日志输出格式：
    %d表示日期时间
    %thread表示线程名
    %-5level：级别从左显示5个字符宽度
    %logger{50}表示logger名字最长50个字符，否则按照句点分割
    %msg：日志消息，
    %n是换行符
```

SpringBoot修改日志的默认配置

```java
#logging.path=
#不指定路径在当前项目下生成的springboot.log日志
#可以指定完整的路径；
#在当前磁盘的根路径下创建spring文件夹和里面的log文件夹；使用spring.log作为默认文件
logging.file.path=spring.log
logging.pattern.console=%d{yyyy-MM-dd} [%thread] %-5level %logger{50} - %msg%n
logging.pattern.file=%d{yyyy-MM-dd} === [%thread] ==== %-5level === %logger{50} === %msg%n
```



**配置日志**

| logging.file | logging.path | example  | Description                      |
| ------------ | ------------ | -------- | -------------------------------- |
| （none）     | （none）     |          | 只在控制台输出                   |
| 指定文件名   | （none）     | my.log   | 输出日志到my.log文件             |
| （none）     | 指定目录     | /var/log | 输出到指定目录的spring.log文件中 |

#### 5、指定配置

给类路径下放上每个日志框架自己的配置文件即可；SpringBoot就不会使用他的默认配置

| Logging System         | Customization                                                |
| ---------------------- | ------------------------------------------------------------ |
| Logback                | logbac-spring.xml,logback-spring.groovy,logback.xml or logback.groovy |
| Log4j2                 | log4j2-spring.xml or log4j2.xml                              |
| JDK(Java Util Logging) | logging.properties                                           |

logback.xml:直接被日志框架识别了

**logback-spring.xml:**日志框架就不直接加载日志的配置项，由SpringBoot解析日志配置，可以使用SpringBoot的高级Profile功能

```java
<springProfile name="staging">
    <!-- configuration to be enabled when the "staging" profile is active-->
    可以指定某段属性只在某个环境下生效
</springProfile>
```

如果使用log.back.xml使用功能springProfile就会报错

```java
no applicate action for [springProfile]
```

#### 6、切换日志框架

可以按照slf4j的日志适配图，进行相关依赖；

slf4j + log4j的方式

```java
<dependency>
            <groupId>org.slf4j</groupId>
            <artifactId>slf4j-log4j12</artifactId>
</dependency>
```

**切换为log4j2**

```java
<dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-log4j2</artifactId>
        </dependency>
```

## 4. Spring Boot与Web开发

使用SpringBoot：

**1）、创建SpringBoot应用，选中我们需要的模块；**

**2）、SpringBoot已经默认讲这些场景配置好了，只需要在配置文件中指定少量配置就可以运行起来；**

**3）、	自己编写业务代码；**



**自动配置原理**

这个场景SpringBoot帮我们配置了什么？能不能修改？能修改哪些配置？能不能扩展？xxx

```java
xxxxAutoConfiguration:帮我们给容器中自动配置组件
xxxxProperties：配置类用来封装配置文件的内容
```



### SpringBoot对静态资源的映射规则；

```
@ConfigurationProperties("spring.web")
public class WebProperties {
	//可以设置和静态资源相关的参数，缓存事件等
```



```java
public void addResourceHandlers(ResourceHandlerRegistry registry) {
    if (!this.resourceProperties.isAddMappings()) {
        logger.debug("Default resource handling disabled");
    } else {
        this.addResourceHandler(registry, "/webjars/**", "classpath:/META-INF/resources/webjars/");
        this.addResourceHandler(registry, this.mvcProperties.getStaticPathPattern(), (registration) -> {
            registration.addResourceLocations(this.resourceProperties.getStaticLocations());
            if (this.servletContext != null) {
                ServletContextResource resource = new ServletContextResource(this.servletContext, "/");
                registration.addResourceLocations(new Resource[]{resource});
            }

        });
    }
}
```

**1）、所有的/webjars/**，都去classpath:/META-INF/resources/webjars/查找资源

webjars：以jar包的方式引入静态资源，[webjars官网](https://www.webjars.org/)

![引入webjar包](../image/引入webjar实例.png)

localhost:8080/webjars/jquery/3.6.0/jquery.js

```xml
<!--引入jquery-webjar-->在访问的时候只需要写webjars下面的资源名称即可
<dependency>
    <groupId>org.webjars</groupId>
    <artifactId>jquery</artifactId>
    <version>3.6.0</version>
</dependency>
```

**2）、“/**”访问的当前项目的任何资源**

```java
"classpath:/META-INF/resources"
"classpath:/resources/",
"classpath:/static/",
"classpath:/public/",
"/":当前项目根路径
```

localhost:8080/abc 如果没有该路径，就去上面的资源文件夹路径里面找abc







**3）、配置欢迎页面的映射**

```
@Bean
public WelcomePageHandlerMapping welcomePageHandlerMapping(ApplicationContext applicationContext, FormattingConversionService mvcConversionService, ResourceUrlProvider mvcResourceUrlProvider) {
    WelcomePageHandlerMapping welcomePageHandlerMapping = new WelcomePageHandlerMapping(new TemplateAvailabilityProviders(applicationContext), applicationContext, this.getWelcomePage(), this.mvcProperties.getStaticPathPattern());
    welcomePageHandlerMapping.setInterceptors(this.getInterceptors(mvcConversionService, mvcResourceUrlProvider));
    welcomePageHandlerMapping.setCorsConfigurations(this.getCorsConfigurations());
    return welcomePageHandlerMapping;
}

==============配置图标
public static class FaviconConfiguration{
	//所有的**/favicon.ico
}
```

静态资源文件夹下的所有index.html页面；被“/**”映射

localhost:8080/

**4）、所有的favicon.ico都是在静态资源文件下找**

**设置默认静态资源路径**

```java
spring.web.resources.static-locations=classpath:/hello,classpath:/zz
```



### 模板引擎

JSP、Velocity、FreeMarker、Thymeleaf；

SpringBoot推荐的Thymeleaf

语法更简单、功能更强大

#### 1、引入Thymeleaf

```xml
<properties>
    <java.version>1.8</java.version>
    <thyemleaf>3.0.9.RELEASE</thyemleaf>
    <!-- 布局功能的支持程序， thymeleaf3主程序 layout2以上版本-->
    <!-- thymeleaf2 layout1-->
    <thyemleaf-layout-dialect-version>2.2.2</thyemleaf-layout-dialect-version>
</properties>
<dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

#### 2、thymeleaf的使用&语法

```java
@ConfigurationProperties(
    prefix = "spring.thymeleaf"
)
public class ThymeleafProperties {
    private static final Charset DEFAULT_ENCODING;
    public static final String DEFAULT_PREFIX = "classpath:/templates/";
    public static final String DEFAULT_SUFFIX = ".html";
    private boolean checkTemplate = true;
    private boolean checkTemplateLocation = true;
    private String prefix = "classpath:/templates/";
    private String suffix = ".html";
    private String mode = "HTML";
}
```

只要我们把html页面放在classpath：/templates/，thymeleaf就能自动渲染

使用：

1、导入thymeleaf的名称空间；

```java
<html lang="en" xmlns:th="http://www.thymeleaf.org">
```

2、使用thymeleaf的语法；

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
<h1>success!</h1>
<div>
    <!--th:text 将div里面的文本内容设置为-->
    <div th:text="${success}">这是显示欢迎信息</div>
</div>
</body>
</html>
```

#### 3、语法规则

1）、th:text;改变当前元素里面的文件内容

​	th:任意html属性；来替换原生属性的值 

| 方法                                  | 解释                                                  |
| ------------------------------------- | ----------------------------------------------------- |
| th:insert,th:replace                  | 片段包含：jsp：include                                |
| th:each                               | 遍历，相当于c：forEach                                |
| th:if,th:unless,th:switch,th:case     | 条件判断：c:if                                        |
| th:object,th:with                     | 声明变量：c:set                                       |
| th:attr,th:attraprepend,th:attrappend | 任意属性修改，支持prepend和append                     |
| th:value,th:href,th:src。。。。       | 修改指定属性默认值                                    |
| th:text,th.utext                      | 修改标签体内容，utext表示非转义字符，text表示转义字符 |
| th:framgment                          | 声明片段                                              |

2）、表达式

```properties
表达式语法：
    ${...}:获取变量值;OGNL
    	1)、获取对象的属性、调用方法
    	2）、使用内置的对象
    		#ctx：
    		#vars：
    		#locale：
    		#request：
    		#response：
    		#session：
    		#servletContext：
    	3）、内置的一些工具对象：
    		#execInfo：
    		#message：
    		#uris：
    		#conversions：
    		#dates：
    		#calandars：
    		#numbers：
    		#strings：
    		#objects：
 			#bools：
    		#arrays：
    		#lists：
    		#sets：
    		#maps：
    		#aggregates：
    		#ids：
    *{...}:变量的选择表达式 ：和${}在功能上是一样；
    	补充：配合 th：object="${session.user}"
	#{...}:获取国际化内容
	@{...}:定义URL
    	@{/order/process{execId},execType='FAST'}
	~{...}:片段引用表达式
        <div th:insert="${commons: main}">...</div>
字面量
   'a',1,tru,null
文本操作：
	+：字符串拼接
	|：字符串
数学运算：
	+，-，*，/，%
布尔运算：
	and,or,!,not
比较运算：
    >,<,=,>=,<=,==,!=
条件运算：
	(if)?(then)
	(if)?(then):(else)
	(value):(default)
成立运算：
    _
```

 #### 4、SpringMVC配置

SpringBoot提供了SpringMVC工作时大多数场景的自动配置

以下是SpringBoot对SpringMVC的默认配置；

- 自动配置了ViewResolver（视图解析器：根据方法的返回值得到视图对象（View），视图对象决定如何渲染（转发？重定向？））

```java
		@Bean
        @ConditionalOnBean({ViewResolver.class})
        @ConditionalOnMissingBean(name = {"viewResolver"},value = {ContentNegotiatingViewResolver.class})
        public ContentNegotiatingViewResolver viewResolver(BeanFactory beanFactory) {
            ContentNegotiatingViewResolver resolver = new ContentNegotiatingViewResolver();
            resolver.setContentNegotiationManager((ContentNegotiationManager)beanFactory.getBean(ContentNegotiationManager.class));
            resolver.setOrder(-2147483648);
            return resolver;
        }
```

 **ContentNegotiatingViewResolver：组合所有的视图解析器的；如何定制：我们可以自己给容器中添加一个视图解析器；自动的将其组合进来**

```java
protected void doDispatch(HttpServletRequest request, HttpServletResponse response) throws Exception {
    HttpServletRequest processedRequest = request;
    HandlerExecutionChain mappedHandler = null;
    boolean multipartRequestParsed = false;
    WebAsyncManager asyncManager = WebAsyncUtils.getAsyncManager(request);

    try {
        ModelAndView mv = null;
        Object dispatchException = null;

        try {
            processedRequest = this.checkMultipart(request);
            multipartRequestParsed = processedRequest != request;
            mappedHandler = this.getHandler(processedRequest);
            if (mappedHandler == null) {
                this.noHandlerFound(processedRequest, response);
                return;
            }

            HandlerAdapter ha = this.getHandlerAdapter(mappedHandler.getHandler());
            String method = request.getMethod();
            boolean isGet = HttpMethod.GET.matches(method);
            if (isGet || HttpMethod.HEAD.matches(method)) {
                long lastModified = ha.getLastModified(request, mappedHandler.getHandler());
                if ((new ServletWebRequest(request, response)).checkNotModified(lastModified) && isGet) {
                    return;
                }
            }

            if (!mappedHandler.applyPreHandle(processedRequest, response)) {
                return;
            }

            mv = ha.handle(processedRequest, response, mappedHandler.getHandler());
            if (asyncManager.isConcurrentHandlingStarted()) {
                return;
            }

            this.applyDefaultViewName(processedRequest, mv);
            mappedHandler.applyPostHandle(processedRequest, response, mv);
        } catch (Exception var20) {
            dispatchException = var20;
        } catch (Throwable var21) {
            dispatchException = new NestedServletException("Handler dispatch failed", var21);
        }

        this.processDispatchResult(processedRequest, response, mappedHandler, mv, (Exception)dispatchException);
    } catch (Exception var22) {
        this.triggerAfterCompletion(processedRequest, response, mappedHandler, var22);
    } catch (Throwable var23) {
        this.triggerAfterCompletion(processedRequest, response, mappedHandler, new NestedServletException("Handler processing failed", var23));
    } finally {
        if (asyncManager.isConcurrentHandlingStarted()) {
            if (mappedHandler != null) {
                mappedHandler.applyAfterConcurrentHandlingStarted(processedRequest, response);
            }
        } else if (multipartRequestParsed) {
            this.cleanupMultipart(processedRequest);
        }

    }

}
```

**DispatcherServlet类下面的doDispatchServlet可以加在你自己定义的视图解析器**

- 静态资源文件夹路径
- 静态首页访问
- favcon.ico
- 自动注册了Converter，GeneriConverter，Formatter beans
  - Converter：转换器；类型转换使用Converter，比如说：你传递过来的参数是18，此时就需要将它转换成int或其他的类型
  - Formatter：格式化器；如果传递了2021-8-3的时候就需要转换成Date日期格式

```java
public DateTimeFormatters() {
    }

    public DateTimeFormatters dateFormat(String pattern) {
        if (isIso(pattern)) {
            this.dateFormatter = DateTimeFormatter.ISO_LOCAL_DATE;
            this.datePattern = "yyyy-MM-dd";//配置日期格式规则
        } else {
            this.dateFormatter = formatter(pattern);
            this.datePattern = pattern;
        }

        return this;
    }
============================================
		@Bean
        public FormattingConversionService mvcConversionService() {
            Format format = this.mvcProperties.getFormat();
    		//日期格式化组件
            WebConversionService conversionService = new WebConversionService((new DateTimeFormatters()).dateFormat(format.getDate()).timeFormat(format.getTime()).dateTimeFormat(format.getDateTime()));
    	
            this.addFormatters(conversionService);
            return conversionService;
        }

```

**自己添加的格式化转换器，我们只需要放在容器中即可**

- HttpMessageConverter：SpringMVC用来转换Http请求和响应的：比如说我有一个User对象，但是我想把它转换成json格式，就可以使用它。

```java
public WebMvcAutoConfigurationAdapter(ResourceProperties resourceProperties, WebProperties webProperties, WebMvcProperties mvcProperties, ListableBeanFactory beanFactory, ObjectProvider<HttpMessageConverters> messageConvertersProvider, ObjectProvider<WebMvcAutoConfiguration.ResourceHandlerRegistrationCustomizer> resourceHandlerRegistrationCustomizerProvider, ObjectProvider<DispatcherServletPath> dispatcherServletPath, ObjectProvider<ServletRegistrationBean<?>> servletRegistrations) {
    this.resourceProperties = (Resources)(resourceProperties.hasBeenCustomized() ? resourceProperties : webProperties.getResources());
    this.mvcProperties = mvcProperties;
    this.beanFactory = beanFactory;
    this.messageConvertersProvider = messageConvertersProvider;
    this.resourceHandlerRegistrationCustomizer = (WebMvcAutoConfiguration.ResourceHandlerRegistrationCustomizer)resourceHandlerRegistrationCustomizerProvider.getIfAvailable();
    this.dispatcherServletPath = dispatcherServletPath;
    this.servletRegistrations = servletRegistrations;
    this.mvcProperties.checkConfiguration();
}
```

**是从容器中确定；获取容器中所有的HttpMessageConverter，如果自己给容器中添加HttpMessageConverter，只需要将自己的组件注册到容器中(@Bean，@Component)**

- MessageCodesResolver:定义错误代码生成规则
- ConfigurableWebBindingInitializer：我们可以配置一个ConfigurableWebBindingInitializer来替换默认的；（添加到容器中）

```java
初始化WebDateBinder
请求数据======JavaBean
```

**org.springframework.boot.autoconfigure.web:web的所有自动场景**

**扩展SpringMVC**

```java
<mvc:view-controller path="/hello" view-name="success" />
<mvc:interceptors>
    <mvc:interceptor>
        <mvc:mapping path="/hello"/>
        <bean></bean>
    </mvc:interceptor>
</mvc:interceptors>
```

**编写一个配置类@Configuration，是WebMvcConfigurationAdapter类型；不能标注@EnableWebMvc**

```java
/**
 * @author
 * WebMvcConfigurer该类接口可以扩展SpringMVC的功能
 */
@Configuration
public class SpringMvcConfiguration implements WebMvcConfigurer {

    /**
     * 当浏览器的接口路径是localhost:端口号/zz的时候，就会跳转到success.html页面
     * 
     * @param registry
     */
    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/zz").setViewName("success");
    }
}
```

**注意：**

- 既保留了原来的默认配置，也保留了自定义的配置。

**原理**

- WebMvcConfiguration是SpringMVC自动配置类
- 在做其他自动配置导入；@Import（EnableWebMvcConfiguration.class）

```java
public static class EnableWebMvcConfiguration extends DelegatingWebMvcConfiguration implements ResourceLoaderAware {
    
=============DelegatingWebMvcConfiguration
@Autowired(required = false)、
    //从容器中获取所有的webMvcConfigurer
    public void setConfigurers(List<WebMvcConfigurer> configurers) {
        if (!CollectionUtils.isEmpty(configurers)) {
            this.configurers.addWebMvcConfigurers(configurers);
            
            //一个参考实现这个类WebMvcConfigurerComposite，该方法的作用就是将webMvcConfigurer所有的相关配置都调用一下
            public void addViewControllers(ViewControllerRegistry registry) {
        	Iterator var2 = this.delegates.iterator();

       		while(var2.hasNext()) {
            WebMvcConfigurer delegate = (WebMvcConfigurer)var2.next();
            delegate.addViewControllers(registry);
        }

    }     
        }
    }
```

3）、容器中所有的WebMvcConfigurer都会一起作用

4）、我们的配置类也会被调用：效果就是SpringMVC的自动配置和我们扩展配置都会被一起调用

#### 全面接管SpringMVC：

**SpringBoot对SpringMVC的自动配置不需要了，所有都是我们自己配置，所有的SpringMVC的自动配置都失效（静态资源等）；**

**只需要我们在配置类中添加注解@EnableWebMvc**

```java
/**
 * @author
 * WebMvcConfigurer该类接口可以扩展SpringMVC的功能
 */
@EnableWebMvc
@Configuration
public class SpringMvcConfiguration implements WebMvcConfigurer {

    /**
     * 当浏览器的接口路径是localhost:端口号/zz的时候，就会跳转到success.html页面
     *
     * @param registry
     */
    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/zz").setViewName("success");
    }
```

**原理**

为什么@EnableWebMvc自动配置就失效了

```java
@Import({DelegatingWebMvcConfiguration.class})
public @interface EnableWebMvc {
}
```

1）、EnableWebMvc的核心

```java
@Import({DelegatingWebMvcConfiguration.class})
public @interface EnableWebMvc {}
```

2）、

```java
@Configuration(proxyBeanMethods = false)
public class DelegatingWebMvcConfiguration extends WebMvcConfigurationSupport {}
```

3)、

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnWebApplication(type = Type.SERVLET)
@ConditionalOnClass({Servlet.class, DispatcherServlet.class, WebMvcConfigurer.class})
//容器中没有这个组件的时候，这个自动配置类才会生效
@ConditionalOnMissingBean({WebMvcConfigurationSupport.class})
@AutoConfigureOrder(-2147483638)
@AutoConfigureAfter({DispatcherServletAutoConfiguration.class, TaskExecutionAutoConfiguration.class, ValidationAutoConfiguration.class})
public class WebMvcAutoConfiguration {
    public static final String DEFAULT_PREFIX = "";
    public static final String DEFAULT_SUFFIX = "";
    private static final String SERVLET_LOCATION = "/";

    public WebMvcAutoConfiguration() {
    }
```

4）、@EnableWebMvc将WebMvcConfigurationSupport组件导入进来

5）、导入的WebMvcConfigurationSupport只是SpringBoot的基本功能

#### 5、如何修改SpringBoot的默认配置

模式：

1）、SpringBoot在自动配置很多组件的时候，先看容器中有没有用户自己配置的(@Bean、@Component)如果有就用用户自己配置的，如果没有就会使用默认的配置。如果有些组件可以有多个（ViewResolver）就会将用户配置和默认配置的组合起来。

2）、在SpringBoot中有很多的xxxConfigurer帮我们进行配置

```java
/**
 * @author
 * WebMvcConfigurer该类接口可以扩展SpringMVC的功能
 */
@EnableWebMvc
@Configuration
public class SpringMvcConfiguration implements WebMvcConfigurer {

    /**
     * 当浏览器的接口路径是localhost:端口号/zz的时候，就会跳转到success.html页面
     *
     * @param registry
     */
    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/zz").setViewName("success");
    }

    /**
     * 将组件注册到容器中
     * @return
     */
    @Bean
    public WebMvcConfigurer webMvcConfigurer(){
        WebMvcConfigurer webMvcConfigurer = new WebMvcConfigurer(){
            @Override
            public void addViewControllers(ViewControllerRegistry registry) {
                registry.addViewController("/").setViewName("index");
                registry.addViewController("/index.html").setViewName("index");
            }
        };
        return webMvcConfigurer;
    }
}
```

#### 国际化

**1)、编写国际化配置文件；**

2）、使用ResourcesBundleMessageSource管理国际化资源文件

3）、在页面使用fmt:message取出国际化的内容



**步骤：**

- 编写国际化配置文件，抽取页面需要显示的国际化消息

![国际化处理](../image/国际化处理.png)

- SpringBoot自动配置好了管理国际化资源文件的组件

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnMissingBean(name = {"messageSource"},search = SearchStrategy.CURRENT)
@AutoConfigureOrder(-2147483648)
@Conditional({MessageSourceAutoConfiguration.ResourceBundleCondition.class})
@EnableConfigurationProperties
public class MessageSourceAutoConfiguration {
    private static final Resource[] NO_RESOURCES = new Resource[0];
    public MessageSourceAutoConfiguration() {
    }
@Bean
@ConfigurationProperties(prefix = "spring.messages")
public MessageSourceProperties messageSourceProperties() {
return new MessageSourceProperties();
}
@Bean
    public MessageSource messageSource(MessageSourceProperties properties) {
        ResourceBundleMessageSource messageSource = new ResourceBundleMessageSource();
        if (StringUtils.hasText(properties.getBasename())) {
            //设置国际化资源文件的基础名（去掉语言国家代码的）
            messageSource.setBasenames
                (StringUtils.commaDelimitedListToStringArray(StringUtils.trimAllWhitespace(properties.getBasename())));
        }

        if (properties.getEncoding() != null) {
            messageSource.setDefaultEncoding(properties.getEncoding().name());
        }

        messageSource.setFallbackToSystemLocale(properties.isFallbackToSystemLocale());
        Duration cacheDuration = properties.getCacheDuration();
        if (cacheDuration != null) {
            messageSource.setCacheMillis(cacheDuration.toMillis());
        }

        messageSource.setAlwaysUseMessageFormat(properties.isAlwaysUseMessageFormat());
        messageSource.setUseCodeAsDefaultMessage(properties.isUseCodeAsDefaultMessage());
        return messageSource;
    }
//我们的配置文件可以放在类路径下叫messages.properties
```

- **去页面获取国际化的值**
-  **根据浏览器的语言设置的信息切换了国际化**

原理：

​		国际化Locale（区域信息对象）；localeResolver（获取区域信息对象）；

```java
@Bean
@ConditionalOnMissingBean(name = {"localeResolver"})
public LocaleResolver localeResolver() {
    if (this.webProperties.getLocaleResolver() == org.springframework.boot.autoconfigure.web.WebProperties.LocaleResolver.FIXED) {
        return new FixedLocaleResolver(this.webProperties.getLocale());
    } else if (this.mvcProperties.getLocaleResolver() == org.springframework.boot.autoconfigure.web.servlet.WebMvcProperties.LocaleResolver.FIXED) {
        return new FixedLocaleResolver(this.mvcProperties.getLocale());
    } else {
        AcceptHeaderLocaleResolver localeResolver = new AcceptHeaderLocaleResolver();
        Locale locale = this.webProperties.getLocale() != null ? this.webProperties.getLocale() : this.mvcProperties.getLocale();
        localeResolver.setDefaultLocale(locale);
        return localeResolver;
    }
}
```

**注意:**

- **WebMvcAutoConfiguration类里面的区域信息解析器,这是一个默认解析器，根据传递的时候区域解析器会去解析这个是英文还是中文**
- **可以自定义个解析器**。

```java
/**
 * @author
 * 可以连接上携带区域信息
 */
public class MyLocaleResolver implements LocaleResolver {
    @Override
    public Locale resolveLocale(HttpServletRequest request) {
        String l = request.getParameter("l");
        Locale locale = Locale.getDefault();
        if(!StringUtils.isEmpty(l)){
            String[] split = l.split("-");
            locale = new Locale(split[0],split[1]);
        }
        return locale;
    }

    @Override
    public void setLocale(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Locale locale) {

    }
}
```

- **点击连接切换国际化**

```java
@Bean
public LocaleResolver localeResolver(){
    return new MyLocaleResolver();
}

========配置文件
spring.messages.basename=i18n.login设置自定义的的国际化配置文件
```

- **登录**

  - 开发期间模板引擎修改以后，要实时生效

    - 禁用模板引擎的缓存

    ```java
    # 禁用缓存
    spring.thymeleaf.cache=false
    ```

    - 页面修改完成以后**ctrl+F9:刷新页面**，重新编译

  - 拦截器登录检查

  ```java
  /**
   * @author
   * 进行登录检查
   */
  public class LoginHandlerInterceptor implements HandlerInterceptor {
      /**
       * 目标方法执行之前
       */
      @Override
      public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
          Object user = request.getSession().getAttribute("loginUser");
          if(user==null){
              //未登录
              request.setAttribute("msg","没有权限，请先登录!");
              request.getRequestDispatcher("/index.html").forward(request,response);
              return false;
          }else{
              //已登录
              return true;
          }
      }
      @Override
      public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {}
      @Override
      public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {}
  }
  
  ====================
  	/**
       * 注册拦截器
       * @param registry
       */
      @Override
      public void addInterceptors(InterceptorRegistry registry) {
          // "/**"表示拦截任意路径下的任意请求
          //SpringBoot已经做好了静态资源映射，不需要来拦截。
          registry.addInterceptor(new LoginHandlerInterceptor()).addPathPatterns("/**")
                  .excludePathPatterns("/","/index.html","/user/login");
      }
  ```

**注意：**

-  registry.addInterceptor(new LoginHandlerInterceptor())；添加拦截器对象
- .addPathPatterns("/**")；添加拦截器路径，参数是所有的路径（这里可以自己定义）
- .excludePathPatterns("/","/index.html","/user/login");移除某些指定的拦截路径

#### 6、CRUD-员工列表

实验要求：

​	1）**、RestfulCRUD：CRUD满足Rest风格；**

URL：/资源名称/资源标识    HTTP请求方式区分对资源CRUD操作

|      | 普通的CRUD（uri来区分操作） | RestfulCRUD       |
| ---- | --------------------------- | ----------------- |
| 查询 | getEmp                      | emp---GET         |
| 新增 | addEmp？xxx                 | emp---POST        |
| 修改 | updateEmp?id=xxx&xxx=xx     | emp/{id}---PUT    |
| 删除 | deleteEmp?id=1              | emp/{id}---DELETE |

**1）、实验请求架构**

| 实验功能                             | 请求URI | 请求方式 |
| ------------------------------------ | ------- | -------- |
| 查询所有员工                         | emps    | GET      |
| 查询某个员工(来到修改页面)           | emp/1   | GET      |
| 来到添加页面                         | emp     | GET      |
| 添加员工                             | emp     | POST     |
| 来到修改页面（查出员工进行信息回显） | emp/1   | GET      |
| 修改员工                             | emp     | PUT      |
| 删除员工                             | emp/1   | DELETE   |

**3）、员工列表**

**thymeleaf公共页面元素抽取**

```java
1、抽取公共片段
<div th:fragment="copy">
&copy;2011 The Good Thymes Virtual Grocery    
</div>
2、引入公共片段
    <div th:insert="~{footer :: copy}"></div>
	~{templatename::selector}:模板名::选择器
	~{templatename::fragementname}:模板名::片段名
3、默认效果
    insert的公共片段在div标签中
如果使用th:insert等属性进行引入，可以不用写~{}
行内写法可以加上：[[~{}]];[(~{})]
```

**三种引入功能片段的th属性**

- th:insert：将公共片段整个插入到声明引入的元素中
- th:replace：将声明引入的元素替换为公共片段
- th:include：将被引入片段的内容包含进这个标签中

#### 7、错误处理机制

**1）、SpringBoot默认的错误处理机制**

![SpringBoot错误信息](../image/springBoot错误信息.png)

**2）、如果是其他客户端、默认响应一个json数据**

```json
{
    "timestamp":1215121,
    "status":404,
    "error":"Not Found",
    "message":"No Message available",
    "path":"/crud/aaa"
}
```



**浏览器发送请求的请求头**

![浏览器发送的请求头](../image/浏览器发送的请求头.png)





原理：

​	可以参照ErrorMvcAutoConfiguration：错误处理的自动配置；

​	给容器中添加了以下组件

​	1、DefaultErrorAttributes：

```java
//帮我们在页面共享信息
@Override
private Map<String, Object> getErrorAttributes(ServerRequest request, boolean includeStackTrace) {
        Map<String, Object> errorAttributes = new LinkedHashMap();
        errorAttributes.put("timestamp", new Date());
        errorAttributes.put("path", request.path());
        Throwable error = this.getError(request);
        MergedAnnotation<ResponseStatus> responseStatusAnnotation = MergedAnnotations.from(error.getClass(), SearchStrategy.TYPE_HIERARCHY).get(ResponseStatus.class);
        HttpStatus errorStatus = this.determineHttpStatus(error, responseStatusAnnotation);
        errorAttributes.put("status", errorStatus.value());
        errorAttributes.put("error", errorStatus.getReasonPhrase());
        errorAttributes.put("message", this.determineMessage(error, responseStatusAnnotation));
        errorAttributes.put("requestId", request.exchange().getRequest().getId());
        this.handleException(errorAttributes, this.determineException(error), includeStackTrace);
        return errorAttributes;
    }
```



​	2、BasicErrorController：处理默认/error请求

```java
@Controller
@RequestMapping({"${server.error.path:${error.path:/error}}"})
public class BasicErrorController extends AbstractErrorController {
.....
@RequestMapping(produces = {"text/html"})//产生html数据，浏览器发送的请求来到这个方法处理
    public ModelAndView errorHtml(HttpServletRequest request, HttpServletResponse response) {
        HttpStatus status = this.getStatus(request);
        Map<String, Object> model = Collections.unmodifiableMap(this.getErrorAttributes(request, this.getErrorAttributeOptions(request, MediaType.TEXT_HTML)));
        response.setStatus(status.value());
        //去哪个页面作为错误页面，包含页面地址和页面内容
        ModelAndView modelAndView = this.resolveErrorView(request, response, status, model);
        return modelAndView != null ? modelAndView : new ModelAndView("error", model);
    }

    @RequestMapping//产生json数据，其他客户端发送请求来到这个方法处理
    public ResponseEntity<Map<String, Object>> error(HttpServletRequest request) {
        HttpStatus status = this.getStatus(request);
        if (status == HttpStatus.NO_CONTENT) {
            return new ResponseEntity(status);
        } else {
            Map<String, Object> body = this.getErrorAttributes(request, this.getErrorAttributeOptions(request, MediaType.ALL));
            return new ResponseEntity(body, status);
        }
    }
}
```



​	3、ErrorPageCustomizer：

```java
@Value("${error.path:/error}")
private String path = "/error";//系统出现错误以后来到error请求进行处理；（web.xml注册的错误页面规则）
```

​	4、DefaultErrorViewResolver：

​	

​	**步骤**

​		一但系统出现4xx或者5xx之类的错误；ErrorPageCustomizer就会生效（定制错误响应的规则）；就会来到/error请求；之后就会被BasicErrorController进行处理，

​	1）、响应页面：去哪个页面是由**DefaultErrorViewResolver**解析得到的

```java
protected ModelAndView resolveErrorView(HttpServletRequest request, HttpServletResponse response, HttpStatus status, Map<String, Object> model) {
    Iterator var5 = this.errorViewResolvers.iterator();
    ModelAndView modelAndView;
    do {
        if (!var5.hasNext()) {
            return null;
        }
        //所有的ErrorViewResolver得到ModeAndView
        ErrorViewResolver resolver = (ErrorViewResolver)var5.next();
        modelAndView = resolver.resolveErrorView(request, status, model);
    } while(modelAndView == null);

    return modelAndView;
}

================
private ModelAndView resolve(String viewName, Map<String, Object> model) {
    	//默认SpringBoot可以去找一个页面？ error/404
        String errorViewName = "error/" + viewName;
    	//模板引擎可以解析这个页面地址就用模板引擎
        TemplateAvailabilityProvider provider = this.templateAvailabilityProviders.getProvider(errorViewName, this.applicationContext);
    	//模板引擎可用的情况下返回到errorViewName指定的试视图地址，如果不存在就在静态资源文件夹下找errorViewName对应的页面 error/404.html
        return provider != null ? new ModelAndView(errorViewName, model) : this.resolveResource(errorViewName, model);
    }
```

**3）、如何定制错误响应：**

​		1）、如何定制错误的页面；

​					1）、**有模板引擎的情况下；error/状态码；**【将错误页面命名为 错误状态码.html 放在模板引起文件夹里面的error文件夹下】，发生此状态码的错误就会来到对应的页面；

​				我们可以使用4xx和5xx作为错误页面的模板，如果有精确地错误状态码.html那么久使用精确的，如果没有就使用4xx或者5xx.html;

​					页面能够获取的信息：

​					timestamp：时间戳

​					status：状态码

​					error：错误提示

​					exception：异常对象
​					message：异常消息

​					errors：JSR303数据校验的错误都在这里

​			2）、没有模板引擎（模板引擎找不到这个错误页面），静态资源文件夹下找。

​			3）、如果都没有错误页面，就默认来到SpringBoot默认的错误提示页面

 2）、如何定制错误的json数据；

- **自定义异常处理&返回定制json数据**

```java
/**
 * @author
 */
@ControllerAdvice
public class MyExceptionHandler {
	
    @ResponseBody
    @ExceptionHandler(UserPrincipalNotFoundException.class)
    public Map<String, Object> handlerException(Exception e){

        Map<String,Object> map = new HashMap<>();
        map.put("code","user.notexist");
        map.put("message",e.getMessage());
        return map;
    }
}
```

**注意：**

1. 此时是没有自适应效果的
2. 浏览器和客户端都是返回的json数据



- **转发到/error进行自适应响应效果处理**

```
@ExceptionHandler(UserPrincipalNotFoundException.class)
    public String handlerException(Exception e, HttpServletRequest request){
        //传入我们自己的错误状态码
        request.setAttribute("javax.servlet.error.status_code",500);
        Map<String,Object> map = new HashMap<>();
        map.put("code","user.notexist");
        map.put("message",e.getMessage());
        return "forward:/error";
    }
```

**注意**

1. 不要忘记写错误状态码
2. 传入我们自己的错误状态码，否则就不会进入自己定制的错误页面信息



- **将我们定制数据携带出去**

出现错误以后，会来到/error请求，会被BasicErrorController处理，响应出去可以获取的数据是由getErrorAttributes得到的（是AbstractErrorController（ErrorController）规定的方法）。

1. 完全来编写一个ErrorController的实现类【或者是编写AbstractErrorController的子类】，放在容器中；
2. 页面上能用的数据，或者是json返回能用的数据都是通过errorAttributes.getErrorAttributes()得到的；

自定义ErrorAttributes

```java
/**
 * @author
 */
@Component
public class MyErrorAttributes extends DefaultErrorAttributes {

    /**
     * 返回值的map就是页面和json能获取的所有字段
     * @param webRequest
     * @param options
     * @return
     */
    @Override
    public Map<String, Object> getErrorAttributes(WebRequest webRequest, ErrorAttributeOptions options) {
        Map<String, Object> map = super.getErrorAttributes(webRequest, options);
        map.put("company","zz");
        //我们的异常处理器携带的数据
        Map<String,Object> ext = (Map<String, Object>) webRequest.getAttribute("ext", 0);
        ext.put("ext",ext);
        return map;
    }
}
```

**最终效果：响应是自适应的，可以通过定制ErrorAttributes改变需要返回的内容**



#### 8、配置嵌入式Servlet容器

SpringBoot默认使用tomcat作为嵌入式的Servlet容器（Tomcat）；

![SpringBoot内置Sevlet服务器](../image/SpringBoot内置tomcat.png)

问题？

1）、如何定制和修改Servlet容器的相关配置；

1. 修改和server有关的配置（ServerProperties[底层还是使用配置文件，映射之后调用EmbeddedServletContainerCustomizer里面的方法设置端口号]）

```properties
server.port=8081
server.servlet.context-path=/zz
server.tomcat.uri-encoding=UTF-8


//通用的Servlet容器设置
server.xxx
//tomcat的配置
server.tomcat.xxx
```

2. 编写一个EmbeddedServletContainerCustomizer：嵌入式的Servlet容器的定制器；来修改Servlet容器的配置

```java
@Bean
private EmbeddedServletContainerCustomizer embeddedServletContainerCustomizer(){
    return new EmbeddedServletContainerCustomizer(){

        //定制嵌入式的Servlet容器相关的规则
        @Override
        public void customize(ConfigurableEmbeddedServletContainer container){
                container.setPort(8083);
        }
    }
}
```

3. 在SpringBoot中会有很多的xxxCustomizer帮助我们进行定制配置
4. **注册Servlet三大组件（Servlet、Filter、Listener）**

由于SpringBoot默认是jar包的方式启动嵌入式的servlet容器来启动SpringBoot应用，没有web.xml文件。

​	注册三大组件用以下方式：

​	ServletRegistrationBean：

```java
/**
 * 注册三大组件
 * @return
 */
@Bean
public ServletRegistrationBean myServlet(){
    ServletRegistrationBean registrationBean = new ServletRegistrationBean<>(new MyServlet(),"/myServlet");
    return registrationBean;
}
```

​	FilterRegistrationBean：

```java
@Bean
public FilterRegistrationBean myFilter(){
    FilterRegistrationBean<Filter> registrationBean = new FilterRegistrationBean<>();
    registrationBean.setFilter(new MyFilter());
    registrationBean.setUrlPatterns(Arrays.asList("/hello","/myServlet"));
    return registrationBean;
}
```

​	ServletListenerRegistrationBean：

```java
@Bean
public ServletListenerRegistrationBean myListener(){
    ServletListenerRegistrationBean<MyListener> registrationBean = new ServletListenerRegistrationBean<>(new MyListener());
    return registrationBean;
}
```

SpringBoot帮我们自动配置SpringMVC的时候，自动的注册SpringMVC的前端控制器；DispathServlet；

```java
@Bean(name = {"dispatcherServletRegistration"})
@ConditionalOnBean(value = {DispatcherServlet.class},name = {"dispatcherServlet"})
public DispatcherServletRegistrationBean dispatcherServletRegistration(DispatcherServlet dispatcherServlet, WebMvcProperties webMvcProperties, ObjectProvider<MultipartConfigElement> multipartConfig) {
    DispatcherServletRegistrationBean registration = new DispatcherServletRegistrationBean(dispatcherServlet, webMvcProperties.getServlet().getPath());
    //默认拦截：/  所有请求：不包括静态资源，但不拦截jsp请求：/*会拦截jsp
    //可以通过server.servletPath来修改SpringMVC前端控制器默认拦截的请求路径
    registration.setName("dispatcherServlet");
    registration.setLoadOnStartup(webMvcProperties.getServlet().getLoadOnStartup());
    multipartConfig.ifAvailable(registration::setMultipartConfig);
    return registration;
}
```

**2）、SpringBoot能不能支持其他的Servlet容器；**

![SpringBoot其他的容器](../image/其他servlet容器.png)

**默认支持：**

Tomcat（默认使用）

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId
	<!--引入web模块默认就是使用嵌入式的tomcat作为Servlet容器-->
</dependency>
```

Jetty

```xml
<!--引入其他的Servlet容器-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-jetty</artifactId>
</dependency>
```

Undertow

```xml
<!--引入其他的Servlet容器-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-undertow</artifactId>
</dependency>
```

**3)、嵌入式Servlet容器的自动配置原理；**

ServletWebServerFactoryAutoConfiguration:嵌入式的Servlet容器自动配置

```java
@Configuration(proxyBeanMethods = false)
@AutoConfigureOrder(-2147483648)
@ConditionalOnClass({ServletRequest.class})
@ConditionalOnWebApplication(type = Type.SERVLET)
@EnableConfigurationProperties({ServerProperties.class})
@Import({ServletWebServerFactoryAutoConfiguration.BeanPostProcessorsRegistrar.class, EmbeddedTomcat.class, EmbeddedJetty.class, EmbeddedUndertow.class})
public class ServletWebServerFactoryAutoConfiguration {
    
    @Bean
    //判断当前是否引入tomcat依赖；
    @ConditionalOnClass(name = {"org.apache.catalina.startup.Tomcat"})
    //判断当前容器有没有用户自己定义的ConfigurableWebServerFactory：嵌入式的Servlet容器工厂：作用；创建嵌入式的Servlet容器
    public TomcatServletWebServerFactoryCustomizer tomcatServletWebServerFactoryCustomizer(ServerProperties serverProperties) {
        return new TomcatServletWebServerFactoryCustomizer(serverProperties);
    }
}
```

1）、ConfigurableWebServerFactory（嵌入式的Servlet容器工厂）



2）、



3)、以TomcatServletWebServerFactory为例

```java
public WebServer getWebServer(ServletContextInitializer... initializers) {
    if (this.disableMBeanRegistry) {
        Registry.disableRegistry();
    }
	//创建tomcat对象
    Tomcat tomcat = new Tomcat();
    //配置tomcat的基本环节
    File baseDir = this.baseDirectory != null ? this.baseDirectory : this.createTempDir("tomcat");
    tomcat.setBaseDir(baseDir.getAbsolutePath());
    Connector connector = new Connector(this.protocol);
    connector.setThrowOnFailure(true);
    tomcat.getService().addConnector(connector);
    this.customizeConnector(connector);
    tomcat.setConnector(connector);
    tomcat.getHost().setAutoDeploy(false);
    this.configureEngine(tomcat.getEngine());
    Iterator var5 = this.additionalTomcatConnectors.iterator();

    while(var5.hasNext()) {
        Connector additionalConnector = (Connector)var5.next();
        tomcat.getService().addConnector(additionalConnector);
    }

    this.prepareContext(tomcat.getHost(), initializers);
    //将配置好的Tomcat传入进去，返回一个TomcatWebServer服务器对象，里面包含了tomcat容器
    return this.getTomcatWebServer(tomcat);
}

===================================this.getTomcatWebServer(tomcat);配置tomcat并且初始化；tomcat并且启动了
private void initialize() throws WebServerException {
        logger.info("Tomcat initialized with port(s): " + this.getPortsDescription(false));
        synchronized(this.monitor) {
            try {
                this.addInstanceIdToEngineName();
                Context context = this.findContext();
                context.addLifecycleListener((event) -> {
                    if (context.equals(event.getSource()) && "start".equals(event.getType())) {
                        this.removeServiceConnectors();
                    }

                });
                //启动tomcat服务器
                this.tomcat.start();
                this.rethrowDeferredStartupExceptions();

                try {
                    ContextBindings.bindClassLoader(context, context.getNamingToken(), this.getClass().getClassLoader());
                } catch (NamingException var5) {
                }

                this.startDaemonAwaitThread();
            } catch (Exception var6) {
                this.stopSilently();
                this.destroySilently();
                throw new WebServerException("Unable to start embedded Tomcat", var6);
            }

        }
    }
```

4）、我们对嵌入式容器的配置修改是怎么生效的？

```java
serverProperties、WebServerFactoryCustomizer
```



**WebServerFactoryCustomizer：**定制器帮我们修改了Servlet容器的配置？

原理：

​	BeanPostProcessorsRegistrar：给容器中导入一些组件；

​	导入了WebServerFactoryCustomizerBeanPostProcessor：后置处理器：bean初始化前后（创建完对象，还没有属性赋值）执行初始化工作。

5）、容器中导入了WebServerFactoryCustomizerBeanPostProcessor

```java
public class WebServerFactoryCustomizerBeanPostProcessor implements BeanPostProcessor, BeanFactoryAware {
    private ListableBeanFactory beanFactory;
    private List<WebServerFactoryCustomizer<?>> customizers;

    public WebServerFactoryCustomizerBeanPostProcessor() {
    }

    public void setBeanFactory(BeanFactory beanFactory) {
        Assert.isInstanceOf(ListableBeanFactory.class, beanFactory, "WebServerCustomizerBeanPostProcessor can only be used with a ListableBeanFactory");
        this.beanFactory = (ListableBeanFactory)beanFactory;
    }

    public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
        if (bean instanceof WebServerFactory) {
            this.postProcessBeforeInitialization((WebServerFactory)bean);
        }

        return bean;
    }

    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        return bean;
    }

    private void postProcessBeforeInitialization(WebServerFactory webServerFactory) {
        ((Callbacks)LambdaSafe.callbacks(WebServerFactoryCustomizer.class, this.getCustomizers(), webServerFactory, new Object[0]).withLogger(WebServerFactoryCustomizerBeanPostProcessor.class)).invoke((customizer) -> {
            customizer.customize(webServerFactory);
        });
    }

    private Collection<WebServerFactoryCustomizer<?>> getCustomizers() {
        if (this.customizers == null) {
            this.customizers = new ArrayList(this.getWebServerFactoryCustomizerBeans());
            this.customizers.sort(AnnotationAwareOrderComparator.INSTANCE);
            this.customizers = Collections.unmodifiableList(this.customizers);
        }

        return this.customizers;
    }

    private Collection<WebServerFactoryCustomizer<?>> getWebServerFactoryCustomizerBeans() {
        //定制Servlet容器，给容器中添加一个WebServerFactoryCustomizer类型的组件
        return this.beanFactory.getBeansOfType(WebServerFactoryCustomizer.class, false, false).values();
    }
}
==============================================
		@Bean
        TomcatServletWebServerFactory tomcatServletWebServerFactory(ObjectProvider<TomcatConnectorCustomizer> connectorCustomizers, ObjectProvider<TomcatContextCustomizer> contextCustomizers, ObjectProvider<TomcatProtocolHandlerCustomizer<?>> protocolHandlerCustomizers) {
            //从容器中获取这个类型的组件： WebServerFactoryCustomizer
            TomcatServletWebServerFactory factory = new TomcatServletWebServerFactory();
           factory.getTomcatConnectorCustomizers().addAll((Collection)connectorCustomizers.orderedStream().collect(Collectors.toList()));
            factory.getTomcatContextCustomizers().addAll((Collection)contextCustomizers.orderedStream().collect(Collectors.toList()));
            factory.getTomcatProtocolHandlerCustomizers().addAll((Collection)protocolHandlerCustomizers.orderedStream().collect(Collectors.toList()));
            return factory;
        }
ServerProperties也是定制器
```

步骤：

​	1）、SpringBoot根据导入的依赖情况，给容器中添加相应的容器；TomcatServletWebServerFactory

​	2）、容器中某个组件要创建对象就会惊动后置处理器；WebServerFactoryCustomizerBeanPostProcessor

只要是嵌入式的Servlet容器工厂，后置处理器就会工作。

​	3）、后置处理器，从容器中获取所有的**ServletWebServerFactoryCustomizer**，调用定制器处理方法



**5）、嵌入式Servlet容器启动原理**

什么时候创建嵌入式的Servlet容器工厂？什么时候获取嵌入式的Servlet容器并启动tomcat；

1）、SpringBoot应用启动运行run方法

2）、refreshContext(context);SpringBoot刷新IOC容器（创建IOC容器对象并且初始化，创建容器中的每一个组件，创建容器中的每一个组件）；如果是web应用创建**AnnotationConfigWebApplicationContext**：否则：**AnnotationConfigServletWebServerApplicationContext**；

3）、refresh(context);刷新刚才创建好的ioc容器

```java
public void refresh() throws BeansException, IllegalStateException {
    synchronized(this.startupShutdownMonitor) {
        StartupStep contextRefresh = this.applicationStartup.start("spring.context.refresh");
        this.prepareRefresh();
        ConfigurableListableBeanFactory beanFactory = this.obtainFreshBeanFactory();
        this.prepareBeanFactory(beanFactory);
        try {
            this.postProcessBeanFactory(beanFactory);
            StartupStep beanPostProcess = this.applicationStartup.start("spring.context.beans.post-process");
            this.invokeBeanFactoryPostProcessors(beanFactory);
            this.registerBeanPostProcessors(beanFactory);
            beanPostProcess.end();
            this.initMessageSource();
            this.initApplicationEventMulticaster();
            this.onRefresh();
            this.registerListeners();
            this.finishBeanFactoryInitialization(beanFactory);
            this.finishRefresh();
        } catch (BeansException var10) {
            if (this.logger.isWarnEnabled()) {
                this.logger.warn("Exception encountered during context initialization - cancelling refresh attempt: " + var10);
            }

            this.destroyBeans();
            this.cancelRefresh(var10);
            throw var10;
        } finally {
            this.resetCommonCaches();
            contextRefresh.end();
        }
    }
}
```

4）、this.onRefresh();web的ioc容器重写了onRefresh方法

5）、web的ioc容器会创建嵌入式的Servlet容器；**this.createWebServer();**

6）、ServletWebServerFactory factory = this.getWebServerFactory();获取嵌入式的Servlet容器工厂

​		从ioc容器中获取ServletWebServerFactory组件；

**TomcatServletWebServerFactory创建对象**，后置处理器一看是这个对象，就获取所有的定制器先来定制Servlet容器的相关配置；

 7）、this.webServer = factory.getWebServer(new ServletContextInitializer[]{this.getSelfInitializer()});**使用容器工厂获取Servlet容器**

 8）、嵌入式的Servlet容器创建对象并启动容器

 9）、this.finishBeanFactoryInitialization(beanFactory);**先启动嵌入式的Servlet容器，再将ioc容器中剩下没有创建出的对象获取出来**（包括自己定义的一些配置）；

**ioc容器启动创建嵌入式的Servlet容器**

#### 9、使用外置的Servlet容器

嵌入式的Servlet容器：应用打成可执行的jar包

​			优点：简单、便携

​			缺点：默认不支持jsp、优化定制比较复杂（使用定制器【ServerProperties、自定义WebServerFactoryCustomizer】，自己编写嵌入式Servlet容器的创建工厂【ConfigurableWebServerFactory】）；



外置的Servlet容器：外面安装Tomcat---应用w ar包的方式打包；

步骤：

​	1）、必须创建一个war项目；（利用idea创建好目录结构）

​	2）、将嵌入式的Tomcat指定为provided；

```java
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-tomcat</artifactId>
    <scope>provided</scope>
</dependency>
```

3）、必须编写一个SpringBootServletInitializer的子类，并调用Configure方法

```java
public class ServletInitializer extends SpringBootServletInitializer {

    @Override
    protected SpringApplicationBuilder configure(SpringApplicationBuilder application) {
        //传入SpringBoot应用的主程序
        return application.sources(DemoApplication.class);
    }

}
```

4）、启动服务器就可以使用；



##### 原理

​	jar包：执行SpringBoot主类的main方法，启动ioc容器，创建嵌入式的Servlet容器；

​	war包：启动服务器，**服务器启动SpringBoot应用**【SpringBootServletInitializer】，启动ioc容器；

Servlet3.0：

规则：

​	1）、服务器启动（web应用启动）会创建当前web应用里面每一个jar包里面ServletContainerInitializer实例：

​	2）、ServletContainerInitializer的实现放在jar包的META-INF/services文件夹下面，有一个名为javax.servlet.ServletContainerInitializer的文件，内容就是ServletContainerInitializer的实现类的全类名；

​	3）、还可以使用@HandlesTypes，在应用启动的时候加载我们感兴趣的类；

流程：

​	1）、启动tomcat

​	2）、/org/springframework/spring-web/5.3.9/spring-web-5.3.9.jar!/META-INF/services/javax.servlet.ServletContainerInitializer

​	spring-web的jar包模块里面有这个文件：**org.springframework.web.SpringBootServletInitializer**

​	3）、SpringServletContainerInitializer将@HandlesTypes({WebApplicationInitializer.class})所标注的这个类型的类都传到onStartup方法的Set<Class<?>>；为这些WebApplicationInitializer类型的类创建实例。

​	4）、每一个WebApplicationInitializer都调用自己的onStartup方法；

![WebApplicationInitializer的实现类](../image/WebApplicationInitializer的实现类.png)



​	5）、相当于我们的SpringServletContainerInitializer的类会被创建对象，并且执行onStartup方法

​	6）、SpringServletContainerInitializer的实例对象执行onStartup的时候会执行，WebApplicationContext rootApplicationContext = this.createRootApplicationContext(servletContext);这个方法创建容器

```java
protected WebApplicationContext createRootApplicationContext(ServletContext servletContext) {
    //创建SpringApplicationBuilder对象
    SpringApplicationBuilder builder = this.createSpringApplicationBuilder();
    builder.main(this.getClass());
    ApplicationContext parent = this.getExistingRootWebApplicationContext(servletContext);
    if (parent != null) {
        this.logger.info("Root context already created (using as parent).");
        servletContext.setAttribute(WebApplicationContext.ROOT_WEB_APPLICATION_CONTEXT_ATTRIBUTE, (Object)null);
        builder.initializers(new ApplicationContextInitializer[]{new ParentContextApplicationContextInitializer(parent)});
    }

    builder.initializers(new ApplicationContextInitializer[]{new ServletContextApplicationContextInitializer(servletContext)});
    builder.contextFactory((webApplicationType) -> {
        return new AnnotationConfigServletWebServerApplicationContext();
    });
    //调用configurer方法，子类重写了这个方法，将SpringBoot的主程序类传入进来
    builder = this.configure(builder);
    builder.listeners(new ApplicationListener[]{new SpringBootServletInitializer.WebEnvironmentPropertySourceInitializer(servletContext)});
    //使用builder创建了一个Spring应用
    SpringApplication application = builder.build();
    if (application.getAllSources().isEmpty() && MergedAnnotations.from(this.getClass(), SearchStrategy.TYPE_HIERARCHY).isPresent(Configuration.class)) {
        application.addPrimarySources(Collections.singleton(this.getClass()));
    }

    Assert.state(!application.getAllSources().isEmpty(), "No SpringApplication sources have been defined. Either override the configure method or add an @Configuration annotation");
    if (this.registerErrorPageFilter) {
        application.addPrimarySources(Collections.singleton(ErrorPageFilterConfiguration.class));
    }

    application.setRegisterShutdownHook(false);
    //启动Spring应用
    return this.run(application);
}
```

​	7）、Spring的应用就启动，并且创建IOC容器

```java
public ConfigurableApplicationContext run(String... args) {
    StopWatch stopWatch = new StopWatch();
    stopWatch.start();
    DefaultBootstrapContext bootstrapContext = this.createBootstrapContext();
    ConfigurableApplicationContext context = null;
    this.configureHeadlessProperty();
    SpringApplicationRunListeners listeners = this.getRunListeners(args);
    listeners.starting(bootstrapContext, this.mainApplicationClass);

    try {
        ApplicationArguments applicationArguments = new DefaultApplicationArguments(args);
        ConfigurableEnvironment environment = this.prepareEnvironment(listeners, bootstrapContext, applicationArguments);
        this.configureIgnoreBeanInfo(environment);
        Banner printedBanner = this.printBanner(environment);
        context = this.createApplicationContext();
        context.setApplicationStartup(this.applicationStartup);
        this.prepareContext(bootstrapContext, context, environment, listeners, applicationArguments, printedBanner);
        //ioc容器的初始化。刷新IOC容器
        this.refreshContext(context);
        this.afterRefresh(context, applicationArguments);
        stopWatch.stop();
        if (this.logStartupInfo) {
            (new StartupInfoLogger(this.mainApplicationClass)).logStarted(this.getApplicationLog(), stopWatch);
        }

        listeners.started(context);
        this.callRunners(context, applicationArguments);
    } catch (Throwable var10) {
        this.handleRunFailure(context, var10, listeners);
        throw new IllegalStateException(var10);
    }

    try {
        listeners.running(context);
        return context;
    } catch (Throwable var9) {
        this.handleRunFailure(context, var9, (SpringApplicationRunListeners)null);
        throw new IllegalStateException(var9);
    }
}
```

先启动Servlet容器，在启动SpringBoot应用

## 5. Spring Boot与Docker

### 1、Docker简介

**Docker**是一个开源的应用容器引擎，基于Go语言并遵循从Apache2.0协议开源，他不是虚拟机，但是却实现了虚拟机里面的资源隔离技术，他的性能远远高于以前使用的jvm（虚拟机）的。启动虚拟机可能需要几分钟，但是启动Docker只需要几秒甚至于毫秒级别。

Docker可以支持将已经安装好的软件可以打包成一个镜像，比如说在linux系统里面安装好了mysql，就可以将mysql打包成一个对象。如果其它人的linux系统需要安装mysql，就可以安装Docker，然后将镜像放在自己的服务器里面运行这个镜像就可以安装mysql。运行起来的镜像就是一个容器。如果是运行Redis镜像，是分配一个新的容器，mysql和Redis两个容器之间隔离机制非常好。

**核心**：Docker支持将软件编译成一个镜像；然后在镜像中各种软件做好配置，将镜像发布出去，其他使用者可以使用这个镜像。运行中的这个镜像称之为容器，容器启动是非常快的。类似于Windows里面ghost操作系统，安装好以后什么都有了。每个容器都是使用沙箱机制，相互之间不能有任何接口，更重要的是容器性能开销极低。

很多都支持docker容器技术，比如阿里云、百度云、SpringCloud、WindowsServer 

![docker简介](../image/Docker简介.png)

### 2、Docker的核心概念

- docker镜像(images)：Docker镜像用于创建Docker容器的模板。**软件打包好的镜像，放在docker仓库中**
- docker容器（Container）：容器是独立运行的一个或一组应用。**镜像启动后的实例称为一个容器，镜像仓库的一个镜像加载到本机之后开始运行，运行时就是一个容器**
- docker客户端(Client)：客户端通过命令行或者其他工具使用DockerAPI（https://docs.docker.com/engine/api/）与Docker的守护进程通信。**连接docker主机进行操作**
- docker主机（Host）：一个物理或者虚拟的机器用于执行Docker守护进程和容器。**安装了Docker程序的机器（Docker直接安装在操作系统上的）**
- docker仓库（Registry）：Docker仓库用来保存镜像，可以理解为代码控制中的代码仓库。DockerHub(https://www.paddlepaddle.org.cn/install/quick?docurl=/documentation/docs/zh/install/pip/linux-pip.html)提供了庞大的镜像集合供使用。**用来保存打包好的镜像**

**使用Dockerd的步骤：**

1. 安装Docker
2. 去Docker仓库找到该软件对应的镜像
3. 使用Docker运行这个镜像，这个镜像就会生成一个Docker容器
4. 对容器的启动停止或对软件的启动停止

### 3、安装Docker

**1）、安装linux虚拟机**

1. VMWare、VirtualBox（安装）；

2. 导入虚拟机文件；

3. 双击启动linux虚拟机；使用账号密码登录；

4. 使用客户端链接linux服务器进行命令操作；

5. 设置虚拟机网络；

   1. 桥接网络
   2. 选择网卡
   3. 接入网线

6. 设置好网络以后使用命令重启虚拟机的网络：

   1. ```shell
      service network restart
      ```

7. 查看linux的ip地址：

   1. ```shell
      ip addr
      ```

8. 使用客户端连接：

**查看centos版本：uname     -r**

Docker要求Centos系统的内核版本高于3.10

**升级软件包及内核；yum **

**安装Docker：yum  install   docker**

**启动docker：systemctl   start docker**

**将docker服务设为开机自启：systemctl   enable  docker**

### 4、常用操作

#### 1、镜像操作

| 操作 | 命令                                           | 说明                                                    |
| ---- | ---------------------------------------------- | ------------------------------------------------------- |
| 检索 | docker search关键字   eg:docker  search  redis | 我们经常去docker hub上检索镜像的详细信息，如镜像的tag   |
| 拉取 | docker pull 镜像名:tag                         | :tag是可选的，tag表示标签，多为软件的版本，默认是latest |
| 列表 | docker images                                  | 查看所有本地镜像网站                                    |
| 删除 | docker rmi image-id                            | 删除制定的本地对象                                      |

#### 2、容器操作

软件镜像（QQ安装程序）----运行镜像----产生一个容器（正在运行的软件，运行的QQ）；

| 操作     | 命令                                                         | 说明                                                         |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 运行     | docker --name container-name -d image-name<br />eg:docker run -name myredis -d redis | --name：自定义容器名；-d：后台运行；image-name：指定镜像模板 |
| 列表     | docker ps（查看运行中的容器）                                | 加上-a；可以查看所有的容器                                   |
| 停止     | docker stop container-name/container-id                      | 停止当前你运行的容器                                         |
| 启动     | docker start container-name/container-id                     | 启动容器                                                     |
| 删除     | docker rm container-id                                       | 删除指定的容器                                               |
| 端口映射 | -p 6379：6379 <br />eg：docker run -d -p 6379:6379 --name myredis docker.io/redis | -p:主机端口（映射到）容器内部的端口                          |
| 容器日志 | docker logs container-name/container-id                      |                                                              |
| 更多命令 |                                                              |                                                              |

步骤：

```shell
1、搜索镜像
[root@localhost ~]# docker search tomcat
2、拉取镜像
[root@localhost ~]# docker pull tomcat
3、根据镜像启动容器
[root@localhost ~]# docker run --name mytomcat -d tomcat:latest
4、查看当前运行中的容器
[root@localhost ~]# docker ps
5、停止运行中的容器
[root@localhost ~]# docker stop 容器的id
6、查看所有的容器
[root@localhost ~]# docker ps -a
7、启动容器
[root@localhost ~]# docker start 容器的id
8、删除一个容器
[root@localhost ~]# docker rm 容器的id
9、启动一个做了端口映射的tomcat
[root@localhost ~]# docker run -d -p 8888:8080 tomcat
-d:后台运行
-p:将主机的端口映射到容器的一个端口 主机端口:容器内部的端口

10、为了能够简单运行出来关闭了linux的防火墙
[root@localhost ~]# service firewalld status；查看防火墙的状态
[root@localhost ~]# service firewall stop；关闭linux的防火墙

11、查看容器的日志
[root@localhost ~]# docker logs 容器的id或者是容器的名称

更多命令参考官方文档
可以参考每一个文档

一个镜像启动多个容器，这是三个都可以访问
[root@localhost ~]# docker run -d -p 8887:8080 tomcat
[root@localhost ~]# docker run -d -p 8888:8080 tomcat
[root@localhost ~]# docker run -d -p 8889:8080 tomcat
```

### 5、环境搭建

#### 1、安装mysql

#### 2、安装redis

#### 3、安装rabbitmq

#### 4、安装elasticsearch



**安装mysql示例**

```shell
[root@localhost ~]# docker run --name mysql01 -e MYSQL_ROOT_PASSWORD=123456 -d mysql
[root@localhost ~]# docker ps
此时使用navicat仍然访问不到mysql，因为该端口没有开放出来
[root@localhost ~]# docker stop 容器id
此时做映射
[root@localhost ~]# docker run -p 3306:3306 --name -e MYSQL_ROOT_PASSWORD=123456 -d mysql
```

**高级操作**

```shell
[root@localhost ~]# docker -run --mysql03 -v /my/custom:etc/mysql/conf.d -e MYSQL_ROOT_PASSWORD=my-secret-pw -d
mysql:tag
-v:把主机的/my/custom文件夹挂载到 mysqldocker容器的etc/mysql/conf.d文件夹里面，这样mysql就可以按照我们的配置化文件启动
需要修改mysql的配置文件的时候，就只需要把mysql配置文件放在主机的/my/custom文件夹下面

[root@localhost ~]# docker run --name some-mysql -e MYSQL_ROOT_PASSWORD=my-secret-pw -d mysql:tag --character-set-server=utf8mb4 --collation-server=utf8mb4_unicode_ci
指定mysql的一些参数
```



## 6. Spring Boot与数据访问

### 1、简介

对于数据访问层，无论是SQL 还是NoSQL，SpringBoot默认采用整合Spring Data的方式进行统一处理，添加大量自动配置，屏蔽了很多的设置，引入各种xxxTemplate，xxxRepository来简化我们对数据访问层的操作。对我们来说只需要进行简单的设置即可。我们将在数据访问章节测试使用SQL相关、NOSQL在缓存、消息、检索等章节测试。

- JDBC
- MyBatis
- JPA

### 2、整合基本JDBC与数据源

1. 引入starter；spring-boot-starter-jdbc

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-jdbc</artifactId>
</dependency>
<dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <scope>runtime</scope>
        </dependency>
```

1. 配置application.yml

```xml
spring:
  datasource:
    username: root
    password: root
    url: jdbc:mysql://localhost:3306/smis
    driver-class-name: com.mysql.cj.jdbc.Driver

```

1. 测试

```xml
@SpringBootTest
class Springboot05ApplicationTests {

    @Autowired
    DataSource dataSource;
    @Test
    void contextLoads() throws SQLException {
        System.out.println(dataSource.getClass());

        Connection connection = dataSource.getConnection();
        System.out.println(connection);
        connection.close();
    }

}
结果：
org.apache.tomcat.jdbc.pool.DataSource
```

效果：

​		默认使用：org.apache.tomcat.jdbc.pool.DataSource作为数据源

​		数据源的相关配置都在DataSourceProperties里面

自动配置原理：

org.springframework.boot.autoconfigure.jdbc:

​	1、参考DataSourceConfiguration，根据配置创建数据源，默认使用Tomcat连接池；可以使用spring.datasource.type指定自定义的数据源类型；

​	2、SpringBoot默认可以支持

```java
org.apache.tomcat.jdbc.pool.DataSource、HikariDataSource、BasicDataSource、Dbcp2
```

​	3、自定义数据源类型

```java
@ConditionalOnMissingBean({DataSource.class})
    @ConditionalOnProperty(name = {"spring.datasource.type"})
    static class Generic {
        Generic() {}
        @Bean
        DataSource dataSource(DataSourceProperties properties) {
            //使用DataSourceBuilder创建数据源，利用反射创建相应的数据源，并且绑定相关属性
            return properties.initializeDataSourceBuilder().build();
        }
    }
```

​	4、InitializationSpecificCredentialsDataSourceInitializationConfiguration：ApplicationListener；

​		作用：

​				1）、运行建表语言

​				2）、运行插入数据的sql语句

默认只需要将文件命名：

```
shcema-*、data-*.sql
可以使用
	schema:
		- classpath:user.sql
		指定位置
```

5、操作数据库：自动配置了JdbcTemplate操作数据库

### 3、整合druid数据源

```java
导入druid数据源
==========================================================
/**
 * @author
 */
@Configuration
public class DruidConfig {

    @ConfigurationProperties(prefix = "spring.datasource")
    @Bean
    public DataSource druid(){
        return new DruidDataSource();
    }

    /**
     * 1、配置一个管理后台的Servlet
     * @return
     */
    public ServletRegistrationBean statViewServlet(){
        ServletRegistrationBean bean = new ServletRegistrationBean(new StatViewServlet(), "/druid/*");

        HashMap<String, String> map = new HashMap<>();
        map.put("loginUsername","admin");
        map.put("loginPassword","123456");
        //默认就是允许访问所有
        map.put("allow","");
        map.put("deny","localhost");

        bean.setInitParameters(map);
        return bean;
    }

    public FilterRegistrationBean webStatFilter(){
        FilterRegistrationBean bean = new FilterRegistrationBean();
        bean.setFilter(new WebStatFilter());

        HashMap<String, String> map = new HashMap<>();
        map.put("exclusions","*.js,*.css,/druid/");
        bean.setInitParameters(map);

        bean.setUrlPatterns(Arrays.asList("/*"));

        return bean;
    }
}
```



### 4、整合MyBatis

```xml
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>2.2.0</version>
</dependency>
```

![SpringBoot整合MyBatis相关依赖](../image/SpringBoot整合mybatis.png)

步骤：

​	1）、配置数据源相关属性（见上一节Druid）

​	2）、给数据库建表

​	3）、创建JavaBean

​	4）、创建mapper

```java
/**
 * @author
 */
@Mapper
public interface UserMapper {

    /**
     * 根据用户id获取数据
     * @param id
     * @return
     */
    @Select("select * from user where id=#{id}")
    public User getUserById(Integer id);


    /**
     * 新增
     * @param user
     * @return
     */
    @Options(useGeneratedKeys = true,keyProperty = "id")
    @Insert("insert into user(name) values(#{name})")
    public int insert(User user);
}
```

**问题：数据库定义的字段是user_name,但是javabean里面是username，应该如何处理**

解决：自定义MyBatis的配置规则；给容器中添加一个ConfigurationCustomizer；

```java
/**
 * @author
 */
@Configuration
public class MyBatisConfig {

    @Bean
    public ConfigurationCustomizer configurationCustomizer(){
        return new ConfigurationCustomizer() {
            @Override
            public void customize(org.apache.ibatis.session.Configuration configuration) {
                configuration.setMapUnderscoreToCamelCase(true);
            }
        }
    }

}
```



**使用统一扫描路径：@MapperScan(value ="");扫描value值这个路径下面的包的所有的Mapper接口**

```java
@MapperScan(value = "com.cg.zz.mapper")
@SpringBootApplication
public class Springboot06Application {

    public static void main(String[] args) {
        SpringApplication.run(Springboot06Application.class, args);
    }

}
```



### 5、配置文件指定的Mapper位置

```properties
mybatis:
  config-location: classpath:mybatis/mybatis-config.xml 指定全局配置文件的位置
  mapper-locations: classpath:mybatis/mapper/*.xml 指定sql映射文件的位置
```



### 6、整合JPA

#### 简介：

Spring Data项目就是为了简化构建基于Spring框架应用的数据访问技术，包括非关系型数据库、Map-Reduce框架、云数据服务等等；另外也包含对关系型数据库的访问支持

#### SpringData特点：

SpringData为我们提供使用统一的API来对数据访问层进行操作；这主要是Spring Data Commons项目来实现的。Spring Data Commons让我们再使用关系型或非关系型数据访问技术时都基于Spring提供的统一标准，标准包含CRUD（创建、获取、更新、删除）、查询、排序和分页的相关操作。

#### 统一的Repository接口

Repository<T,ID extends Serializable>:统一接口

RevisionRepository<T,ID extends Serializable,N extends Number & Comparable<N>>:基于乐观锁机制

CrudRepository<T,ID extends Serializable>：基本的CRUD操作

PagingAndSortingRepository<T,ID extends Serializable>：基本CRUD及分页

#### 提供数据访问模板类xxxTemplate；

如：MongoTemplate、RedisTemplate

#### JPA与Spring Data

**1）、JpaRepository基本功能**

​			编写接口继承JpaRepository既有crud及分页等基本功能

**2）、定义符合规范的方法命名**

​			在接口中只需要声明符合规范的方法，即拥有对应的功能

**3）、@Query自定义查询，定制查询SQL**

**4）、Specialcations查询（Spring Data JPA支持JPA2.0的Criteria查询）**



JPA：ORM（Object relation Mapping）

- 编写一个实体类（bean）和数据表进行映射，并且配置好映射关系；

```java
/**
 * @author
 * 使用JPA注解配置映射关系
 * //@Entity 告诉JPA这是一个实体类（和数据表映射的类）
 * @Table(name= "tab_user")指定该类和哪个张表对应。如果省略默认表名就是user；
 */
@Entity
@Table(name= "tab_user")
@Data
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY) //自增主键
    private Integer id;
    //
    @Column(name="last_name")
    private String name;
    @Column //省略默认列名就是属性名
    private int age;
}
```

- 编写Dao类来操作实体类对应的数据库表（Spring Data中称之为Repository）

```java
/**
 * @author
 * 继承JpaRepository来完成对数据库的操作
 */
public interface UserRepository extends JpaRepository<User,Integer> {
}
```

- 基本的配置（JpaProperties）

```yml
  jpa:
    hibernate:
#     更新或者创建数据表结构
      ddl-auto: update
#   控制台显示SQL
    show-sql: true
```

## 7. Spring Boot启动配置原理

几个重要的事件回调机制

**配置在META-INF/spring.factories**

- **ApplicationContextInitializer**
- **SpringApplicationRunListener**



**只需要放在ioc容器中**

- **ApplicationRunner**
- **CommandLineRunner**



### 启动流程

- **创建SpringApplication对象，主要作用就是初始化这个属性**

```java
public SpringApplication(Class<?>... primarySources) {
        this((ResourceLoader)null, primarySources);
    }

============
public SpringApplication(ResourceLoader resourceLoader, Class<?>... primarySources) {
        this.sources = new LinkedHashSet();
        this.bannerMode = Mode.CONSOLE;
        this.logStartupInfo = true;
        this.addCommandLineProperties = true;
        this.addConversionService = true;
        this.headless = true;
        this.registerShutdownHook = true;
        this.additionalProfiles = Collections.emptySet();
        this.isCustomEnvironment = false;
        this.lazyInitialization = false;
        this.applicationContextFactory = ApplicationContextFactory.DEFAULT;
        this.applicationStartup = ApplicationStartup.DEFAULT;
        this.resourceLoader = resourceLoader;
        Assert.notNull(primarySources, "PrimarySources must not be null");
        this.primarySources = new LinkedHashSet(Arrays.asList(primarySources));
    	//判断当前应用是否为web应用
        this.webApplicationType = WebApplicationType.deduceFromClasspath();
        this.bootstrapRegistryInitializers = this.getBootstrapRegistryInitializersFromSpringFactories();
    	//从类路径下找到META-INF/spring.factories配置的所有ApplicationContextInitializer；然后保存起来
        this.setInitializers(this.getSpringFactoriesInstances(ApplicationContextInitializer.class));
    	//从类路径下找到META-INF/spring.factories配置的所有ApplicationListener；然后保存起来
        this.setListeners(this.getSpringFactoriesInstances(ApplicationListener.class));
    	//从多个配置类中找到有main方法的主配置类
        this.mainApplicationClass = this.deduceMainApplicationClass();
    }
```

![this.getInitializers](../image/initializer的数据.png)

![SpringBoot获取到的Listener数据](../image/SpringBoot获取到的listener数据.png)



- **运行run方法**

```java
public ConfigurableApplicationContext run(String... args) {
    //创建开始停止的监听
    StopWatch stopWatch = new StopWatch();
    stopWatch.start();
    DefaultBootstrapContext bootstrapContext = this.createBootstrapContext();
    ConfigurableApplicationContext context = null;
    this.configureHeadlessProperty();
    
    //获取SpringApplicationRunListeners；点进去this.getRunListeners(args)方法，发现仍然是从类路径下面
    //的META-INF/spring.factories里面拿到
    SpringApplicationRunListeners listeners = this.getRunListeners(args);
    //回调所有的SpringApplicationRunListeners.start()方法
    listeners.starting(bootstrapContext, this.mainApplicationClass);

    try {
        //封装命令行参数
        ApplicationArguments applicationArguments = new DefaultApplicationArguments(args);
        //准备环境
        ConfigurableEnvironment environment = this.prepareEnvironment(listeners, bootstrapContext, applicationArguments);
        
        	//准备环境里面的内容：
        	//1.创建环境完成后回调SpringApplicationRunListeners.environmentPrepared()方法；表示环境准备完成
        	//判断如果不是web环境，还需要转换成相应的环境
        	
        //忽略一些不需要的bean信息
        this.configureIgnoreBeanInfo(environment);
        //打印banner图标
        Banner printedBanner = this.printBanner(environment);
        //创建ApplicationContext(IOC容器)；决定创建的是web的ioc还是普通的ioc容器的
        context = this.createApplicationContext();
        context.setApplicationStartup(this.applicationStartup);
        //准备上下文环境；将enviroment保存到ioc中
        this.prepareContext(bootstrapContext, context, environment, listeners, applicationArguments, printedBanner);
        
        	//this.prepareContext()方法里面的
        		this.applyInitializers(context);回调之前保存的所有得ApplicationContextInitializer的initialize()方法
            //下一步执行
               	listeners.contextPrepared(context);之后回调SpringApplicationRunListeners.environmentPrepared()方法
			//日志记录：
			if (this.logStartupInfo) {
            	this.logStartupInfo(context.getParent() == null);
            	this.logStartupProfileInfo(context);
        		}
            //命令行参数注册进来
                beanFactory.registerSingleton("springApplicationArguments", applicationArguments);
        	//需要打印的banner注册进去
        	if (printedBanner != null) {
            	beanFactory.registerSingleton("springBootBanner", printedBanner);
        	}
        	//拿到主类
        		 Set<Object> sources = this.getAllSources();
        	//加载资源（这里就是加载主类，里面判断了是否为主类）
        		this.load(context, sources.toArray(new Object[0]));
        	//prepareContext运行完成以后回调所有的SpringApplicationRunListeners.contextLoaded();方法
        		listeners.contextLoaded(context);
        
        //刷新容器；ioc容器初始化的过程，就是加载ioc容器里面所有的组件，扫描所有的配置类，扫描所有的@bean等等，给我们创建对象初始化，里面还包括了Spring的			整个加载流程（也就是Ioc容器的整个初始化过程）（如果是web应用，还会创建嵌入式的Tomcat）
        //扫描，创建，加载所有组件的地方；(配置类，组件，自动配置)
        this.refreshContext(context);
        		
        	//一直点到public void refresh() throws BeansException, IllegalStateException {}这个方法来，此时就是ioc容器的整个初始化过程
        	//初始化剩下所有配置懒加载的单例
        	this.finishBeanFactoryInitialization(beanFactory);
        
        //从ioc容器中获取ApplicationRunner和CommandLineRunner进行回调
        //ApplicationRunner先回调，CommandLinewRunner再回调（点进去看），然后所有的Application都回调finished()方法
        this.afterRefresh(context, applicationArguments);
        //保存当前应用状态
        stopWatch.stop();
        if (this.logStartupInfo) {
            (new StartupInfoLogger(this.mainApplicationClass)).logStarted(this.getApplicationLog(), stopWatch);
        }
		//已经完成调用SpringApplicationRunListeners.started()方法，
        listeners.started(context);
        this.callRunners(context, applicationArguments);
    } catch (Throwable var10) {
        this.handleRunFailure(context, var10, listeners);
        throw new IllegalStateException(var10);
    }

    try {
        //调用SpringApplicationRunListeners.running()方法
        listeners.running(context);
        //整个SpringBoot应用启动完了以后返回启动的ioc容器，ioc容器里面就有了所有的组件。
        return context;
    } catch (Throwable var9) {
        this.handleRunFailure(context, var9, (SpringApplicationRunListeners)null);
        throw new IllegalStateException(var9);
    }
}
```



### 2、事件监听机制

配置在META-INF/spring.factories

**ApplicationContextInitializer**

**SpringApplicationRunListener**



只需要放在ioc容器中 

**ApplicationRunner**

**CommandLineRunner**



**测试事件监听机制**

![测试事件监听机制](../image/SpringBoot自定义相关拦截器.png)



**HelloApplicationContextController**

```java
/**
 * @author
 */
public class HelloApplicationContextInitializer implements ApplicationContextInitializer<ConfigurableApplicationContext> {
    @Override
    public void initialize(ConfigurableApplicationContext configurableApplicationContext) {
        System.out.println("ApplicationContextInitializer.....initialize"+configurableApplicationContext);
    }
}
```

**HelloSpringApplicationRunListener**

```java
/**
 * @author
 */

public class HelloSpringApplicationRunListener implements SpringApplicationRunListener {

    public HelloSpringApplicationRunListener(SpringApplication application, String[] args){

    }

    @Override
    public void starting(ConfigurableBootstrapContext bootstrapContext) {
        System.out.println("SpringApplicationRunListener.....starting.....");
    }

    @Override
    public void environmentPrepared(ConfigurableBootstrapContext bootstrapContext, ConfigurableEnvironment environment) {
        PropertySource<?> source = environment.getPropertySources().get("os.name");
        System.out.println("SpringApplicationRunListener.....environmentPrepared....."+source);
    }

    @Override
    public void contextPrepared(ConfigurableApplicationContext context) {
        System.out.println("SpringApplicationRunListener.....contextPrepared.....");
    }

    @Override
    public void contextLoaded(ConfigurableApplicationContext context) {
        System.out.println("SpringApplicationRunListener.....contextLoaded.....");
    }

    @Override
    public void started(ConfigurableApplicationContext context) {
        System.out.println("SpringApplicationRunListener.....started.....");
    }

    @Override
    public void running(ConfigurableApplicationContext context) {
        System.out.println("SpringApplicationRunListener.....running.....");
    }

    @Override
    public void failed(ConfigurableApplicationContext context, Throwable exception) {
        System.out.println("SpringApplicationRunListener.....environmentPrepared.....");
    }
}
```

**HelloApplicationRunner**

```java
/**
 * @author
 */
@Component
public class HelloApplicationRunner implements ApplicationRunner {
    @Override
    public void run(ApplicationArguments args) throws Exception {
        System.out.println("ApplicationRunner.....run.....");
    }
}
```

**HelloCommandLineRunner**

```java
/**
 * @author
 */
@Component
public class HelloCommandLineRunner implements CommandLineRunner {
    @Override
    public void run(String... args) throws Exception {
        System.out.println("CommandLineRunner.....run....."+ Arrays.asList(args));
    }
}
```

**spring.factories**

```java
org.springframework.context.ApplicationContextInitializer=\
com.example.demo.listener.HelloApplicationContextInitializer

org.springframework.boot.SpringApplicationRunListener=\
com.example.demo.listener.HelloSpringApplicationRunListener
```

## 8. Spring Boot自定义starters（和之前的7章主要是说SpringBoot的使用和基本原理）

**starter：**

​		**1、这个场景需要使用到的依赖是是什么？**

​		**2、如何编写自动配置**

```properties
@Configuration //指定这个类是配置类
@ConditionalOnXXX //在指定条件成立的情况下自动配置类生效
@AutoConfigureOrder||@AutoConfigureBefore || @AutoConfigureAfter  //指定自动配置类的顺序
@Bean  //给容器中添加组件

@ConfigurationProperties(prefix ="") //结合相关xxxProperties类来绑定相关的配置
@EnableConfigurationProperties  //让xxxProperties生效并且加入到容器中
    
//自动配置类要能加载
//将需要启动就加载的自动配置类，配置在META-INF/spring.factories
org.springframework.boot.autoconfigure.EnableAutoConfiguration=\
org.springframework.boot.autoconfigure.admin.SpringApplicationAdminJmxAutoConfiguration,\
org.springframework.boot.autoconfigure.aop.AopAutoConfiguration,\
org.springframework.boot.autoconfigure.amqp.RabbitAutoConfiguration,\
```

**启动器**

- 启动器的模块应该是一个空jar文件，仅提供辅助性依赖管理，这些依赖可能用于自动装配或者其他类库
- 命名归约：
  - 官方命名空间：
    - 前缀：“spring-boot-starter”
    - 模式：“sprng-boot-starter-模块名”
    - 举例：“spring-boot-starter-web、spring-boot-starter-actuator、spring-boot-starter-jdbc”
  - 自定义命名空间：
    - 后缀：“-spring-boot-starter”
    - 模式：模块-spring-boot-starter
    - 举例：mybatis-spring-boot-starter

​	**3、模式：**

启动器只用来做依赖导入；

专门来写一个自动配置模块；

启动器依赖自动配置；别人只需要引入启动器（starter）

mybatis-spring-boot-starter；自定义启动器名-mybatis-spring-boot-starter

## 9. Spring Boot与缓存（SpringBoot的一些高级整合）

## 10. Spring Boot与消息

## 11. Spring Boot与检索

## 12. Spring Boot与任务

## 13. Spring Boot与安全

## 14. Spring Boot与分布式

## 15. Spring Boot与开发部署

## 16. Spring Boot与监控管理