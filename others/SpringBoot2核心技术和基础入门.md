# SpringBoot2核心技术和基础入门



## **SpringBoot的优点**

- 创建独立的Spring应用
- 内嵌web服务器
- 自动starter依赖，简化构建配置
- 自动配置Spring以及第三方功能
- 提供生产级别的监控、健康检查及外部化配置（可以在配置文件中修改某些默认信息）
- 无代码生成、无需编写XML

> SpringBoot整合Spring技术栈的一站式框架
>
> SpringBoot是简化Spring技术栈的快速开发脚手架（脚手架就是帮我们开发我们需要的东西，我们不需要自己手动配置）





## **SpringBoot的缺点**

- 版本更新比较快，需要时刻关注变化
- 封装太深、内部原理复杂、不容易精通



## SpringBoot的大时代背景

#### 微服务

- 微服务是一种架构风格
- 一个应用拆分为一组小型服务
- 每个服务运行在自己的进程内，也就是可独立部署和升级
- 服务之间使用轻量级HTTP交互
- 服务围绕业务功能拆分
- 可以由自动部署机制独立部署
- 去中心化，服务自治。服务可以使用不同的语言、不同的存储技术

#### 分布式

- 远程调用
- 服务发现（发现哪台机器可以调用）
- 负载均衡（发现调用的机器都可以，就必须要用负载均衡进行选择调用）
- 服务容错
- 配置管理
- 服务监控
- 链路追踪
- 日志管理
- 任务调度
- 。。。



**分布式任务的解决**

- SpringBoot+SpringCloud



#### 云原生

云原生如何上云 Cloud Native

**上云的困难**

- 服务自愈
- 弹性伸缩
- 服务隔离
- 自动化部署
- 灰度发布（相当于是慢慢的替换版本）
- 流量治理
- 。。。



## SpringBoot2入门

### 系统要求

- Java 8
- maven3.3+
- idea2019.1.2+



**查看版本号**

- 查看spring-boot-dependencies里面规定的版本号

- 在当前项目里面重写配置

  ```xml
  <properties>
          <mysql.version>5.1.43</mysql.version>
      </properties>
  
  <dependency>
          <groupId>mysql</groupId>
          <artifactId>mysql-connector-java</artifactId>
  </dependency>
  ```



**starter启动器**

```xml
1.见到很多spring-boot-starter-*：*场景
2.只要引入starter，这个场景的所有常规需要的依赖我们都会自动引入。
3.springboot所有支持的场景：https://docs.spring.io/spring-boot/docs/current/reference/html/using-spring-boot.html#using-boot-starter
4.见到 *-spring-boot-starter：第三方为我们提供的简化开发的场景启动器
5.所有场景启动器最底层的依赖
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>
```



**自动版本仲裁**

```java
1.引入依赖可以默认不写版本
2.引入非版本仲裁的jar，要写版本号
```



**自动配置**

- 自动配好Tomcat

  - 引入Tomcat依赖
  - 配置Tomcat

- 自动配好SpringMVC

  - 引入SpringMVC的全套组件
  - 自动配好SpringMVC常用组件(功能)

- 自动配好Web常见功能，如：字符编码问题

  - SpringBoot帮我们配置好了所有web开发的常见场景

- 默认包结构

  - 主程序所在的包及其下面的所有子包里面的组件都会被默认扫描出来

  - 无需以前的包扫描配置项

  - 想要改变扫描路径，@SpringBootApplication(scanBasePackages="com")

    - 或者@ComponentScan指定扫描路径
    - 

    ``` java
    @SpringBootApplication
    等同于
    @SpringBootConfiguration
    @EnableAutoConfiguration
    @ComponentScan("com.zz.boot")
    ```

- 各种配置拥有默认值

  - 默认配置最终都是映射到相关类里面。例子：就是映射的类MutipartProperties这个类

  - ```xml
    server:
      port: 8081
    spring:
      servlet:
        multipart:
          max-file-size: 10MB
    ```

  - 配置文件的值最终会绑定在每个类上，这个类会在容器中创建。

- 按需加载所有自动配置项

  - 非常多的starter

  - 引入了哪些场景之后，这个场景的自动配置才开启

  - SpringBoot的所有配置功能，全都在这里

  - ```java
    <dependency>
      <groupId>org.springframework.boot</groupId>
      <artifactId>spring-boot-autoconfigure</artifactId>
      <version>2.3.4.RELEASE</version>
      <scope>compile</scope>
    </dependency>
    ```

  - 这里可以自动配置一些其他的启动器，

  - ```java
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-batch</artifactId>
    </dependency>
    ```



### 容器功能

#### 组件添加

1、@Configuration

- 基本使用
- Full模式与Lite模式
  - 实例
  - 最佳实战
    - 配置类组件之间无依赖关系用Lite模式加速容器启动过程，减少判断（Lite(proxyBeanMethods = false)）
    - 配置类组件之间有依赖关系，方法会被调用得到之前单实例组件，用Full模式（Full(proxyBeanMethods = true)）

```java
-----User类------
/**
 * @author
 */
@Data
public class User {
    private Integer id;
    private String name;
    private int age;

    private Cat cat;

    public User(int id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }
}
-----Cat类-----
/**
 * @author
 */
@Data
public class Cat {
    private String name;

    public Cat() {
    }

    public Cat(String name) {
        this.name = name;
    }
}
-----配置类MyConfig-----
/**
 * @author
 *
 * 1、配置类里面使用@Bean标注在方法上给容器注册组件，默认也是单例的。
 * 2、配置类本身也是组件
 * 3、proxyBeanMethods:代理bean的方法
 *      Full(proxyBeanMethods = true)、
 *      Lite(proxyBeanMethods = false)
 *      组件依赖：
 */
@Configuration(proxyBeanMethods = true)
public class MyConfig {

    /**
     * @Bean:给容器中添加组件。以方法名做为组件的id。返回的类型就是组件类型。返回的值，就是组件在容器中的实例。
     * @return
     */
    @Bean
    public User user(){
        User zz = new User(1, "zz", 18);
        zz.setCat(cat());
    }

    /**
     * @Bean("tom111"):表示注册容器里面作为该组件的id叫做tom111，不是原来的方法名了。
     * @return
     */
    @Bean("tom111")
    public Cat cat(){
        return new Cat("tom");
    }
}
-------启动类---------
/**
 * @author
 * 告诉SpringBoot：主程序类
 */
//@SpringBootApplication(scanBasePackages="com.zz.boot")

@SpringBootApplication
public class MainApplication {
    public static void main(String[] args) {
        ConfigurableApplicationContext run = SpringApplication.run(MainApplication.class, args);

        String[] beanDefinitionNames = run.getBeanDefinitionNames();
        for (String beanDefinitionName : beanDefinitionNames) {
            System.out.println(beanDefinitionName);
        }

        User user = run.getBean("user", User.class);
        User user1 = run.getBean("user", User.class);
        System.out.println(user == user1);


        MyConfig bean = run.getBean(MyConfig.class);
        System.out.println(bean);
        Cat cat = run.getBean("tom111", Cat.class);
        System.out.println("用户的宠物："+(user.getCat() == cat));
    }
}
```

**注意：**

- **@Configuration(proxyBeanMethods = true)：当该配置设置为true的时候。**
  - 会创建代理bean对象，不会创建重复的bean
  - 存在组件依赖，比如：User类里面的Cat对象
  - 在启动类的时候判断就会是true，因为User类里面的Cat对象就是指的Cat类里面的对象。
- **@Configuration(proxyBeanMethods = false)：当该配置类设置为false的时候。**
  - 不会代理Bean对象，意味着不会去容器里面找有没有相应的bean对象，而是创建一个新的bean对象。
  - 就会产生一个新的bean对象，所以此时的User类中的Cat对象和Cat类中的对象不同。
  - 就是说没有产生组件依赖。



#### 2、@Bean、@Component、@Controller、@Service、@Repository

- @Bean：给方法中添加组件
- @Component：给类上添加组件
- @Controller：给类上标注代表是一个**控制器**
- @Service：代表是一个业务逻辑组件
- @Repository：代表这是一个数据库使用的组件



#### 3、@ComponentScan、@Import

- @ComponentScan：指定包扫描的
- @Import：给容器中导入一个组件

```java
-----之前的配置类-----
@Import({User.class, DBHelper.class})
@Configuration(proxyBeanMethods = true)
public class MyConfig {
    /**
     * @Bean:给容器中添加组件。以方法名做为组件的id。返回的类型就是组件类型。返回的值，就是组件在容器中的实例。
     * @return
     */
    @Bean
    public User user(){
        User zz = new User(1, "zz", 18);
        zz.setCat(cat());
        return zz;
    }

    /**
     * @Bean("tom111"):表示注册容器里面作为该组件的id叫做tom111，不是原来的方法名了。
     * @return
     */
    @Bean("tom111")
    public Cat cat(){
        return new Cat("tom");
    }
}
-------启动类添加的--------
 //5、获取组件
        String[] beanNamesForType = run.getBeanNamesForType(User.class);
        System.out.println("===========");
        for (String s : beanNamesForType) {
            System.out.println(s);
        }

        DBHelper helper = run.getBean(DBHelper.class);
        System.out.println(helper);
结果：
===========
com.zz.boot.bean.User
user
ch.qos.logback.core.db.DBHelper@443effcb
```

**注意：**

- user的bean有两个，第一个@Import导入的User类，**此时这个是全类名**
- 第二个就是在MyConfig类中使用@Bean注解生成的一个bean
- 第三个是@Import导入的DBHelper类，**此时这个也是全类名**



#### @Conditional（条件装配）

条件装配：满足Conditional指定的条件，则进行组件注入，根注解，下面还有很多子注解

- @ConditionalOnBean：判断容器中存在指定的Bean的时候，我们才做某些事情。
- @ConditionalOnMissingBean：判断容器中不存在指定的Bean的时候，我们才做某些事情。
- @ConditionalOnProperty：当配置文件配置了某个属性的时候，才做某些事情。 
- @ConditionalOnJava：判断某些指定Java版本号
- @ConditionalOnClass：判断是否存在某个类的时候，该类就可以生效
- 。。。。

**案例**

```java
@Import({User.class, DBHelper.class})
@Configuration(proxyBeanMethods = false)
@ConditionalOnBean(name = "Tom")
public class MyConfig {

    /**
     * @Bean:给容器中添加组件。以方法名做为组件的id。返回的类型就是组件类型。返回的值，就是组件在容器中的实例。
     * @return
     */
    @Bean
    public User user(){
        User zz = new User(1, "zz", 18);
        zz.setCat(cat());
        return zz;
    }

    /**
     * @Bean("tom111"):表示注册容器里面作为该组件的id叫做tom111，不是原来的方法名了。
     * @return
     */
    @Bean("tom111")
    public Cat cat(){
        return new Cat("tom");
    }
}
-----启动类测试-------
boolean user = run.containsBean("user");
System.out.println("是否存在user这个bean:"+user);

boolean tom111 = run.containsBean("tom111");
System.out.println("是否存在tom111这个bean:"+tom111);
结果：
是否存在user这个bean:false
是否存在tom111这个bean:false
```

**注意：**

- @ConditionalOnBean(name = "Tom")：表示当容器中存在Tom这个bean的时候，该类里面的所有的方法都可以实现。
- @ConditionalOnMissingBean(name = "Tom")：当容器中不存在Tom这个bean的时候，该类里面的所有的方法都可以实现。
- **该注解也可以用在方法上面，代表的意思一样，就是存在或者不存在的时候，该方法是否实现。**



#### @ImportResource

导入Spring配置文件：

```
@Import({User.class, DBHelper.class})
@Configuration(proxyBeanMethods = false)
//@ConditionalOnBean(name = "Tom")
@ImportResource("classpath:bean.xml")
public class MyConfig {

    /**
     * @Bean:给容器中添加组件。以方法名做为组件的id。返回的类型就是组件类型。返回的值，就是组件在容器中的实例。
     * @return
     */
    @Bean
    public User user(){
        User zz = new User(1, "zz", 18);
        zz.setCat(cat());
        return zz;
    }

    /**
     * @Bean("tom111"):表示注册容器里面作为该组件的id叫做tom111，不是原来的方法名了。
     * @return
     */
    @Bean("tom111")
    public Cat cat(){
        return new Cat("tom");
    }
}

-------bean.xml-------
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

    <bean id="haha" class="com.zz.boot.bean.User">
        <property name="name" value="zz"></property>
    </bean>
    <bean id="hehe" class="com.zz.boot.bean.Cat">
        <property name="name" value="Tom"></property>
    </bean>
</beans>
---------启动类测试---------
System.out.println("===================");
        boolean haha = run.containsBean("haha");
        boolean hehe = run.containsBean("hehe");
        System.out.println(haha);
        System.out.println(hehe);
结果：
===================
true
true
```

**注意：**

- 该注解在任何配置类上面都可以实现，比如启动类，但是未允许配置类生效的类上面实现没有效果。
- @ImportResource("classpath:bean.xml")。



### 配置绑定

如何使用Java读取到properties文件中的内容，并且把它封装到JavaBean中，以供随时使用；

**1、@ConfigurationProperties**

**案例**

```java
@ConfigurationProperties(prefix = "mycar")
public class Car {
    private String name;
    private Integer price;
}
```

**注意：**

- 一般配合@Component注解或者@EnableConfigurationProperties一起使用
- 该注解是跟核心配置文件，前缀是mycar的属性进行绑定的



**2、@EnableConfigurationProperties + @ConfigurationProperties（适用于第三方配置类）**

- @EnableConfigurationProperties(XXX.clss)的作用：
  - 开启属性配置绑定功能、该类下面的属性配置才能够生效。
  - 把XXX这个组件自动注入到容器中。
  - 这样在XXX这个类里面就不用写@Component注解。
  - 用于在XXX这个类引用的第三方包中的情况，不是自己定义的情况。

**案例**

```java
-----配置类----------
@Import({User.class, DBHelper.class})
@Configuration(proxyBeanMethods = false)
//@ConditionalOnBean(name = "Tom")
@ImportResource("classpath:bean.xml")
@EnableConfigurationProperties(Car.class)
public class MyConfig {

    /**
     * @Bean:给容器中添加组件。以方法名做为组件的id。返回的类型就是组件类型。返回的值，就是组件在容器中的实例。
     * @return
     */
    @Bean
    public User user(){
        User zz = new User(1, "zz", 18);
        zz.setCat(cat());
        return zz;
    }

    /**
     * @Bean("tom111"):表示注册容器里面作为该组件的id叫做tom111，不是原来的方法名了。
     * @return
     */
    @Bean("tom111")
    public Cat cat(){
        return new Cat("tom");
    }
}
--------基础类------
/**
 * @author
 * 只有在容器中的组件，才会拥有SpringBoot提供的强大功能
 */
@Data
//@Component
@ConfigurationProperties(prefix = "mycar")
public class Car {
    private String name;
    private Integer price;
}
```

**注意：**

- 在基础类中就不需要配置@Component注解了，因为在配置类中指定了该类的能够自动配置不用在写@Component注解。
- 可以支持该类如果是第三方引用，就可以使用这个注解。



**3、@Component + @ComfigurationProperties（适用于自定义的配置类）**

**案例**

```java
/**
 * @author
 * 只有在容器中的组件，才会拥有SpringBoot提供的强大功能
 */
@Data
@Component
@ConfigurationProperties(prefix = "mycar")
public class Car {
    private String name;
    private Integer price;
}
------yml配置文件-----
mycar:
  name: BM
  price: 500000
------控制器测试-------
@RestController
public class HelloController {

    @Autowired
    Car car;

    @RequestMapping("/car")
    public Car car(){
        return car;
    }
```

**注意：**

- **在该类中使用的时候除了添加@ConfigurationProperties(prefix = "mycar")配置绑定配置文件中的属性之外**
- **还需要将这个类添加在Spring容器里面。使用注解@Component**



### 自动配置原理入门

#### 	引导加载自动配置类

```java
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

**注意：**

- **@SpringBootConfiguration**

  - **@Configuration：代表当前是一个配置类**

  - **@ComponentScan：指定扫描的包有哪些，这里是进行了过滤的；可以去看Spring注解**

  - **@EnableAutoConfiguration：**

    - ```java
      @AutoConfigurationPackage
      @Import({AutoConfigurationImportSelector.class})
      public @interface EnableAutoConfiguration {}
      ```

  1、**@AutoConfigurationPackage：自动配置包，点进去看看**

  ```java
  @Import({Registrar.class}) //给容器中导入一个组件
  public @interface AutoConfigurationPackage {
      Registrar() {
          }
  
          public void registerBeanDefinitions(AnnotationMetadata metadata, BeanDefinitionRegistry registry) {
              AutoConfigurationPackages.register(registry, (String[])(new AutoConfigurationPackages.PackageImports(metadata)).getPackageNames().toArray(new String[0]));
          }
  
          public Set<Object> determineImports(AnnotationMetadata metadata) {
              return Collections.singleton(new AutoConfigurationPackages.PackageImports(metadata));
          }
  }
  
  //利用registrar给容器中导入一系列的组件，
  //(registry, (String[])(new AutoConfigurationPackages.PackageImports(metadata)).getPackageNames().toArray(new String[0])：
  表示将启动类(MainApplication)注册进去了，后面会去扫描主程序类所在的包下所有的组件。
  ```

  **2、@Import({AutoConfigurationImportSelector.class})点进去看看**

```
1、利用this.getAutoConfigurationEntry(annotationMetadata)这个方法是给容器中批量导入一些组件。
2、调用List<String> configurations = this.getCandidateConfigurations(annotationMetadata, attributes);获取所有需要导入到容器中的配置类。
3、利用SpringFactoriesLoader.loadFactoryNames(this.getSpringFactoriesLoaderFactoryClass(), this.getBeanClassLoader());方法里面的
private static Map<String, List<String>> loadSpringFactories(@Nullable ClassLoader classLoader) {}方法加载得到的所有的组件。
4、从META-INF/spring.factories这个位置来加载文件的。
	默认会从当前META-INF/spring.factories位置的文件
	org.springframework.boot:spring-boot-autoconfigure下也有META-INF/spring.factories
		点进去spring.factories
		# Auto Configure
22行：org.springframework.boot.autoconfigure.EnableAutoConfiguration=\
23行：org.springframework.boot.autoconfigure.admin.SpringApplicationAdminJmxAutoConfiguration,\
。。。。。
148行：org.springframework.boot.autoconfigure.webservices.client.WebServiceTemplateAutoConfiguration
就是这个自动配置类，类名都是一样的，总共127个
配置文件写死了springboot一旦启动，就要加载所有的自动配置类的配置文件
```



#### 按需开启自动配置项

```xml
虽然我们有127个场景的所有自动配置启动的时候默认全部加载。
最终会按照需求进行配置，不一定是所有的都配置了。
```



#### 修改默认配置

```java
@Bean
@ConditionalOnBean({MultipartResolver.class})
@ConditionalOnMissingBean(name = {"multipartResolver"})
public MultipartResolver multipartResolver(MultipartResolver resolver) {
    return resolver;
}
```

**注意：**

- 该方法是给容器中添加文件上传解析器。
- @ConditionalOnBean({MultipartResolver.class})：判断容器中有这个类的bean的时候就生效。
- @ConditionalOnMissingBean(name = {"multipartResolver"})：容器中没有这个名字(multipartResolver)的组件就生效。
- 该方法就是给@Bean标注的方法传入了对象参数，这个参数的值就会从容器中找。
  - 意思就是即使没有这个名字的解析器，但是只有配置了这个类型的的名字就可以设置为文件上传解析器。
  - 防止有些用户配置文件上传解析器不符合规范，然后返回回去的时候，就又是这个名字了multipartResolver。

SpringBoot会在底层配置好所有的组件，如果用户自己配置了，就以用户的为准。

```java
@Bean
    @ConditionalOnMissingBean
    public CharacterEncodingFilter characterEncodingFilter() {
        CharacterEncodingFilter filter = new OrderedCharacterEncodingFilter();
        filter.setEncoding(this.properties.getCharset().name());
        filter.setForceRequestEncoding(this.properties.shouldForce(org.springframework.boot.web.servlet.server.Encoding.Type.REQUEST));
        filter.setForceResponseEncoding(this.properties.shouldForce(org.springframework.boot.web.servlet.server.Encoding.Type.RESPONSE));
        return filter;
    }

=======自定义的方法=======
@Bean
    @ConditionalOnMissingBean
    public CharacterEncodingFilter characterEncodingFilter() {
        CharacterEncodingFilter filter = new OrderedCharacterEncodingFilter();
//        filter.setEncoding(this.properties.getCharset().name());
//        filter.setForceRequestEncoding(this.properties.shouldForce(org.springframework.boot.web.servlet.server.Encoding.Type.REQUEST));
//        filter.setForceResponseEncoding(this.properties.shouldForce(org.springframework.boot.web.servlet.server.Encoding.Type.RESPONSE));
        System.out.println("zzzz");
        return filter;
    }
```

**注意：**

- 他会去调用自己写的方法。
- 不会调用SpringBoot底层封装的方法。
- 体现了用户的优先级。



**总结**

- SpringBoot会加载所有的自动配置类 xxxAutoConfiguration。
- 每个配置类就会按照需求自动生效，默认都会绑定配置文件指定的值。都是从xxxxProperties这个类里面获取，然而xxxxProperties类又是和配置文件绑定在一起的。
- 生效的配置类就可以给容器中添加组件。
- 只要有这些组件，相当于功能就有了。
- 定制化配置
  - 用户使用@Bean自己替换底层的组件。
  - 用户去看这个组件是获取的配置文件什么值就去修改，直接改配置文件的值。

**xxxAutoConfiguration**  --->**组件** --------->**xxxxProperties类绑定的配置文件里面拿值** --------->**修改application.properties的相关的值。**





### 最佳实践

- 引入场景依赖（maven、tomcat、mysql、web等）

- 查看自动配置了哪些（启动类里面获取bean的定义信息，然后遍历）

  - 自己分析，引入场景对应的自动配置一般都生效了
  - 配置文件里面写一个debug=true；就可以看到哪些是自动配置了的。Native Matches(不生效)下面的不生效。Positive matches（生效的）。

- 是否需要修改（修改配置文件、自定义方法去替代底层方法、添加新的配置属性）

  - 参照文档修改

    - 官网

    - 自己分析，xxxxProperties类绑定了配置文件的哪些（

      ```properties
      spring:
        servlet:
          multipart:
            max-file-size: 10MB
        banner:
          image:
            location: aaa.jpg
      #修改banner、修改文件大小
      ```

    - ）

  - 自定义加入或者替换组件

    - @Bean、@Component、，，，

  - 自定义器：**XXXCustomizer**：修改以前默认的行为

  - 。。。。



### 开发小技巧

#### lombok

简化JavaBean开发

```xml
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
</dependency>
```

搜索安装插件lombok，重启idea

添加@Data注解

```java
/**
 * @author
 * 只有在容器中的组件，才会拥有SpringBoot提供的强大功能
 */
@ToString
@Data
@AllArgsConstructor //全参构造器
@NoArgsConstructor  //无参构造器
@EqualsAndHashCode  //重写equalshashcode方法
@Component
@ConfigurationProperties(prefix = "mycar")
public class Car {
    private String name;
    private Integer price;
}
==========
@Slf4j
@RestController
public class HelloController {

    @Autowired
    Car car;

    @RequestMapping("/car")
    public Car car(){
        return car;
    }


    @RequestMapping("/hello")
    public String hello(){
        log.info("请求进来了");
        return "hello springboot2";
    }
}
```

**注意：**

- @ToString：方法是在编译期间的时候就会生成一个toString()方法。
- @Data：添加getter和setter方法。
- @AllArgsConstructor：添加全参构造器。
- @NoArgsConstructor：添加无参构造器。
- @EqualsAndHashCode：重写equalshashcode方法。
- @Slf4j ：日志会给这个类中注入一个log对象，可以使用里面的方法。



#### dev-tools

热更新

```java
<dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-devtools</artifactId>
            <optional>true</optional>
        </dependency>
```

**注意：**

- 当本地代码变了之后，只需要按住 Ctrl + F9就可以重新编译和项目重启了
- 其实和重启是一样，但是你的代码没有变化的时候按住 Ctrl + F9的时候是不会重启服务的。
- 还有一个付费的。暂时不用，毕竟前后端分离的时候很少用到这个热部署。



#### Spring Initailizr（项目初始化向导）

![springBoot联网建项目](../image/springBoot联网建项目.png)



建立好的项目格式页面

![新建好的格式页面](../image/springboot新建项目格式.png)







## SpringBoot核心技术-核心功能

### 配置文件

#### 文件类型

##### properties

以前使用的是properties用法

```properties
server.port = 8080
```

##### YML

YAML是“YAML Ain‘t Markup Language”（YAMl不是一种标记语言）的递归缩写。在开发的这种语言时，YAML的意思其实是：“Yet Another Markup Language”（仍是一种标记语言）。

非常适合做以数据为中心的配置文件



**基本语法**

- key: value   kv之间有空格
- 大小写敏感
- 使用缩进表示层级关系
- 缩进不允许使用tab，只允许空格
- 缩进的空格数不重要，只要相同的层级数左对齐即可
- ’#‘表示注释
- “与”表示字符串内容，会被  转义/不转义

**数据类型**

- 字面量：单个的、不可再分的值。date、boolean、string、number、null

```properties
k: v
```

- 对象：键值对集合。map、hash、set、object

```java
行内写法：  k: {k1:v1,k2:v2,k3:v3}
#或
k:
	k1: v1
    k2: v2
    k3: v3
```

- 数组：一组按次序排列的值。array、list、queue

```properties
行内写法： k: [v1,v2,v3]
#或
k:
 - v1
 - v2
 - v3
```



**相关案例**

```properties
user:
  userName: "zz \n zzz"
  # 单引号会将 \n作为字符串输出 双引号会将\n 作为换行符输出
  # 双引号不会转义、单引号会转义
  boss: true
  birth: 2022/9/1
  age: 18
#  interests: [tom,jerry,jack,rose]
  interests:
    - 篮球
    - 足球
    - 排球
  animal: [tom,jack]
  score:
    english: 80
    math: 95
#   score: {english: 80,math: 95}
  salary:
    - 999.88
    - 999.98
  pet:
    name: 旺财
    weight: 88.88
  allPets:
    sick:
      - {name: 旺财,weight: 99.99}
      - name: 小黑
        weight: 88.88
    health:
      - {name: 阿发,weight: 99.89}
      - name: 阿花
        weight: 78.55
```



#### **配置提示**

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-configuration-processor</artifactId>
    <optional>true</optional>
</dependency>

<build>
        <plugins>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
                <version>2.5.3</version>
                <configuration>
                    <excludes>
                        <exclude>
                            <groupId>org.springframework.boot</groupId>
                            <artfactId>spring-boot-configurationprocessor</artfactId>
                        </exclude>
                    </excludes>
                </configuration>
            </plugin>
        </plugins>
    </build>
```

**注意：**

- build：里面是打包的文件会排除掉提示信息。
- dependency:配置文件提示信息





### web开发

#### SpringMVC自动配置概述：官网文档

#### 简单功能分析：

#####  静态资源目录：

只要在静态资源放在类路径下： called   **/static**(**/public** or **/resources** or **/META-INF/resources**)

访问：当前项目根路径/ + 静态资源名



原理：静态映射/**。

请求进来，先去找Controller看能不能处理。不能处理的所有请求又交给了静态资源处理器。静态资源也找不到就直接404



```yaml
spring:
  resources:
    static-locations: [classpath:/static/]
```

**注意：**

- 这里是直接在设置默认的访问静态资源的文件夹



##### 静态资源访问前缀

默认无前缀

```yml
spring:
  mvc:
    static-path-pattern: /zz/**
```

当前项目 + static-path-pattern + 静态资源名 = 静态资源文件夹下面找



##### webjars

自动映射

https://www.webjars.org/

```xml
<dependency>
            <groupId>org.webjars</groupId>
            <artifactId>jquery</artifactId>
            <version>3.6.0</version>
        </dependency>
```

**注意：**

- 访问地址：http://localhost:8080/webjars/jquery/3.5.1/jquery.js后面的地址要按照依赖的包路径



#### 欢迎页支持

- 静态资源路径下放 index.html
  - 可以配置静态资源路径
  - 但是不可以配置静态资源的访问前缀，否则导致index.html不能被默认访问

```yaml
spring:
  mvc:
    static-path-pattern: /zz/** #这个会导致默认欢迎页面失效
  resources:
    static-locations: [classpath:/static/]
```

- controller能处理index



#### 自定义Favicon

favicon.ico放在静态资源目录下即可

```yaml
spring:
  mvc:
    static-path-pattern: /zz/**
```

**注意：**

- 还是会导致favion功能失效



#### 静态资源配置原理

- SpringBoot启动默认加载 xxxAutoCofiguration 类（自动配置类）
- SpringMVC功能的自动配置类 WebMvcAutoConfiguration生效

```java
@Configuration(proxyBeanMethods = false)
@ConditionalOnWebApplication(type = Type.SERVLET)
@ConditionalOnClass({Servlet.class, DispatcherServlet.class, WebMvcConfigurer.class})
@ConditionalOnMissingBean({WebMvcConfigurationSupport.class})
@AutoConfigureOrder(-2147483638)
@AutoConfigureAfter({DispatcherServletAutoConfiguration.class, TaskExecutionAutoConfiguration.class, ValidationAutoConfiguration.class})
public class WebMvcAutoConfiguration {}
```

- 给容器中配了什么？

```java
@Configuration(proxyBeanMethods = false)
@Import({WebMvcAutoConfiguration.EnableWebMvcConfiguration.class})
@EnableConfigurationProperties({WebMvcProperties.class, ResourceProperties.class, WebProperties.class})
@Order(0)
public static class WebMvcAutoConfigurationAdapter implements WebMvcConfigurer, ServletContextAware {}
```

- 配置文件的相关属性和XXX进行了绑定。WebMvcProperties === **spring.mvc**，ResourceProperties===**spring.resources**，进行了绑定。





**一个有参构造器**

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

**注意：**

- 如果一个类只有一个有参构造器，**那么这个构造器所有参数的值都会从容器中确定**。
- 参数：ResourceProperties resourceProperties：获取和spring.resources绑定的所有的值的对象。
- 参数：WebProperties webProperties：获取和spring.mvc绑定的所有的值的对象。
- 参数：ListableBeanFactory beanFactory：Spring的beanFactory。
- 参数：ObjectProvider<HttpMessageConverters> messageConvertersProvider：找到所有的HttpMessageConverters（消息转换器）。
- 参数：ObjectProvider<WebMvcAutoConfiguration.ResourceHandlerRegistrationCustomizer> 。resourceHandlerRegistrationCustomizerProvider：找到资源处理器的自定义器。
- 参数：ObjectProvider<DispatcherServletPath> dispatcherServletPath：
- 参数：ObjectProvider<ServletRegistrationBean<?>> servletRegistrations：给应用注册Servlet、Filter...



#### 资源处理的默认规则

```java
public void addResourceHandlers(ResourceHandlerRegistry registry) {
    if (!this.resourceProperties.isAddMappings()) {
        logger.debug("Default resource handling disabled");
    } else {
        //webjars的规则
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

```yaml
spring:
  resources:
    add-mappings: false #禁用所有的静态资源
```



```java
public static class Resources {
    private static final String[] CLASSPATH_RESOURCE_LOCATIONS = new String[]{"classpath:/META-INF/resources/", "classpath:/resources/", "classpath:/static/", "classpath:/public/"};
    private String[] staticLocations;
    private boolean addMappings;
    private boolean customized;
    private final WebProperties.Resources.Chain chain;
    private final WebProperties.Resources.Cache cache;

    public Resources() {
        this.staticLocations = CLASSPATH_RESOURCE_LOCATIONS;
```

**注意：**

- 第一个方法的时候就是判断是都是webjars的规则
- 第二个addResourceHander是判断默认的静态资源路径规则
  - private String[] staticLocations;
  - 调用构造方法this.staticLocations = CLASSPATH_RESOURCE_LOCATIONS;赋值了这些静态资源路径



#### 欢迎页面的处理规则

```java
HandlerMapping：处理器映射。保存了每一个Handler能处理哪些请求。

@Bean
public WelcomePageHandlerMapping welcomePageHandlerMapping(ApplicationContext applicationContext, FormattingConversionService mvcConversionService, ResourceUrlProvider mvcResourceUrlProvider) {
    WelcomePageHandlerMapping welcomePageHandlerMapping = new WelcomePageHandlerMapping(new TemplateAvailabilityProviders(applicationContext), applicationContext, this.getWelcomePage(), this.mvcProperties.getStaticPathPattern());
    welcomePageHandlerMapping.setInterceptors(this.getInterceptors(mvcConversionService, mvcResourceUrlProvider));
    welcomePageHandlerMapping.setCorsConfigurations(this.getCorsConfigurations());
    return welcomePageHandlerMapping;
}


WelcomePageHandlerMapping(TemplateAvailabilityProviders templateAvailabilityProviders, ApplicationContext applicationContext, Resource welcomePage, String staticPathPattern) {
        if (welcomePage != null && "/**".equals(staticPathPattern)) {
            //要想使用欢迎页功能，必须是/**
            logger.info("Adding welcome page: " + welcomePage);
            this.setRootViewName("forward:index.html");
        } else if (this.welcomeTemplateExists(templateAvailabilityProviders, applicationContext)) {
            //调用Controller的 /index方法
            logger.info("Adding welcome page template: index");
            this.setRootViewName("index");
        }

    }
```



#### 返回值解析器

![image-20210915213808673](../image/image-20210915213808673.png)



**注意：**

- 这15个返回值处理器根据方法的返回值类型进行判断。选择哪一个返回值处理器。

```java
try {
    this.returnValueHandlers.handleReturnValue(returnValue, this.getReturnValueType(returnValue), mavContainer, webRequest);
```

**注意：**

- 使用这个方法根据所有的所有的返回值处理器去匹配属于哪一个返回值处理器，并且进行处理返回值信息。

```java
public void handleReturnValue(@Nullable Object returnValue, MethodParameter returnType, ModelAndViewContainer mavContainer, NativeWebRequest webRequest) throws Exception {
    HandlerMethodReturnValueHandler handler = this.selectHandler(returnValue, returnType);
    if (handler == null) {
        throw new IllegalArgumentException("Unknown return value type: " + returnType.getParameterType().getName());
    } else {
        handler.handleReturnValue(returnValue, returnType, mavContainer, webRequest);
    }
}
```

**注意：**

- 具体处理返回值信息
  - 第一步：根据返回值信息和返回类型进行判断是哪个返回值处理器来处理
    - HandlerMethodReturnValueHandler handler = this.selectHandler(returnValue, returnType);
  - 第二步：使用该处理器来处理返回值信息

```java
---handler.handleReturnValue(returnValue, returnType, mavContainer, webRequest);--点进去
public void handleReturnValue(@Nullable Object returnValue, MethodParameter returnType, ModelAndViewContainer mavContainer, NativeWebRequest webRequest) throws IOException, HttpMediaTypeNotAcceptableException, HttpMessageNotWritableException {
    mavContainer.setRequestHandled(true);
    ServletServerHttpRequest inputMessage = this.createInputMessage(webRequest);
    ServletServerHttpResponse outputMessage = this.createOutputMessage(webRequest);
    //使用消息转换器进行写出操作
    this.writeWithMessageConverters(returnValue, returnType, inputMessage, outputMessage);
}
```

**注意：**

- 具体处理返回值信息





**返回值处理器的类：（接口类）**

```java
public interface HandlerMethodReturnValueHandler {
    boolean supportsReturnType(MethodParameter var1);

    void handleReturnValue(@Nullable Object var1, MethodParameter var2, ModelAndViewContainer var3, NativeWebRequest var4) throws Exception;
}
```

**注意：**

- 返回值处理器接口类主要有两个方法：
  - 方法一：supportReturnType()：判断该处理器是否支持处理方法参数
  - 方法二：handleReturnValue()：真正执行处理返回值信息的方法。
  - RequestResponseBodyProcessor：可以处理返回值标注了@ResponseBody注解的。
    - this.writeWithMessageConverters(returnValue, returnType, inputMessage, outputMessage);该方法进行转换为json。

```java
protected <T> void writeWithMessageConverters(@Nullable T value, MethodParameter returnType, ServletServerHttpRequest inputMessage, ServletServerHttpResponse outputMessage) throws IOException, HttpMediaTypeNotAcceptableException, HttpMessageNotWritableException {
    Object body;
    Class valueType;
    Object targetType;
    //判断是否是字符类型
    if (value instanceof CharSequence) {
        body = value.toString();
        valueType = String.class;
        targetType = String.class;
    } else {
        body = value;
        valueType = this.getReturnValueType(value, returnType);
        targetType = GenericTypeResolver.resolveType(this.getGenericType(returnType), returnType.getContainingClass());
    }
	//判断是否是流类型
    if (this.isResourceType(value, returnType)) {
        outputMessage.getHeaders().set("Accept-Ranges", "bytes");
        if (value != null && inputMessage.getHeaders().getFirst("Range") != null && outputMessage.getServletResponse().getStatus() == 200) {
            Resource resource = (Resource)value;

            try {
                List<HttpRange> httpRanges = inputMessage.getHeaders().getRange();
                outputMessage.getServletResponse().setStatus(HttpStatus.PARTIAL_CONTENT.value());
                body = HttpRange.toResourceRegions(httpRanges, resource);
                valueType = body.getClass();
                targetType = RESOURCE_REGION_LIST_TYPE;
            } catch (IllegalArgumentException var19) {
                outputMessage.getHeaders().set("Content-Range", "bytes */" + resource.contentLength());
                outputMessage.getServletResponse().setStatus(HttpStatus.REQUESTED_RANGE_NOT_SATISFIABLE.value());
            }
        }
    }
	//枚举类型
    MediaType selectedMediaType = null;
    //将请求头的类型信息赋值给类型信息对象
    MediaType contentType = outputMessage.getHeaders().getContentType();
    boolean isContentTypePreset = contentType != null && contentType.isConcrete();
    //判断请求头信息是否存在（意思就是判断之前是否有返回的请求头信息）
    if (isContentTypePreset) {
        if (this.logger.isDebugEnabled()) {
            this.logger.debug("Found 'Content-Type:" + contentType + "' in response");
        }
		//存在就直接赋值了
        selectedMediaType = contentType;
        //不存在
    } else {
        HttpServletRequest request = inputMessage.getServletRequest();

        List acceptableTypes;
        try {
            //调用方法得到浏览器可以接受的类型对象（8个）
            acceptableTypes = this.getAcceptableMediaTypes(request);
        } catch (HttpMediaTypeNotAcceptableException var20) {
            int series = outputMessage.getServletResponse().getStatus() / 100;
            if (body != null && series != 4 && series != 5) {
                throw var20;
            }

            if (this.logger.isDebugEnabled()) {
                this.logger.debug("Ignoring error response content (if any). " + var20);
            }

            return;
        }
		//获取服务器能生成的内容类型（5个）
        List<MediaType> producibleTypes = this.getProducibleMediaTypes(request, valueType, (Type)targetType);
        if (body != null && producibleTypes.isEmpty()) {
            throw new HttpMessageNotWritableException("No converter found for return value of type: " + valueType);
        }
		//存放最终写出的数据类型
        List<MediaType> mediaTypesToUse = new ArrayList();
        Iterator var15 = acceptableTypes.iterator();

        MediaType mediaType;
        while(var15.hasNext()) {
            mediaType = (MediaType)var15.next();
            Iterator var17 = producibleTypes.iterator();

            //使用迭代器遍历服务器产生的类型
            while(var17.hasNext()) {
                MediaType producibleType = (MediaType)var17.next();
                //判断服务器产生的类型是否与浏览器要求的类型匹配
                if (mediaType.isCompatibleWith(producibleType)) {
                    mediaTypesToUse.add(this.getMostSpecificMediaType(mediaType, producibleType));
                }
            }
        }

        if (mediaTypesToUse.isEmpty()) {
            if (body != null) {
                throw new HttpMediaTypeNotAcceptableException(producibleTypes);
            }

            if (this.logger.isDebugEnabled()) {
                this.logger.debug("No match for " + acceptableTypes + ", supported: " + producibleTypes);
            }

            return;
        }

        MediaType.sortBySpecificityAndQuality(mediaTypesToUse);
        var15 = mediaTypesToUse.iterator();

        while(var15.hasNext()) {
            mediaType = (MediaType)var15.next();
            if (mediaType.isConcrete()) {
                selectedMediaType = mediaType;
                break;
            }

            if (mediaType.isPresentIn(ALL_APPLICATION_MEDIA_TYPES)) {
                selectedMediaType = MediaType.APPLICATION_OCTET_STREAM;
                break;
            }
        }

        if (this.logger.isDebugEnabled()) {
            this.logger.debug("Using '" + selectedMediaType + "', given " + acceptableTypes + " and supported " + producibleTypes);
        }
    }
	//定义一个消息转换器对象
    HttpMessageConverter converter;
    GenericHttpMessageConverter genericConverter;
    label183: {
        //判断查询到的最终返回值类型是否为空
        if (selectedMediaType != null) {
            //去掉权重好像
            selectedMediaType = selectedMediaType.removeQualityValue();
            //迭代器循环遍历
            Iterator var23 = this.messageConverters.iterator();

            while(var23.hasNext()) {
                converter = (HttpMessageConverter)var23.next();
                genericConverter = converter instanceof GenericHttpMessageConverter ? (GenericHttpMessageConverter)converter : null;
                if (genericConverter != null) {
                    if (((GenericHttpMessageConverter)converter).canWrite((Type)targetType, valueType, selectedMediaType)) {
                        break label183;
                    }
                } else if (converter.canWrite(valueType, selectedMediaType)) {
                    break label183;
                }
            }
        }

        if (body != null) {
            Set<MediaType> producibleMediaTypes = (Set)inputMessage.getServletRequest().getAttribute(HandlerMapping.PRODUCIBLE_MEDIA_TYPES_ATTRIBUTE);
            if (!isContentTypePreset && CollectionUtils.isEmpty(producibleMediaTypes)) {
                throw new HttpMediaTypeNotAcceptableException(this.getSupportedMediaTypes(body.getClass()));
            }

            throw new HttpMessageNotWritableException("No converter for [" + valueType + "] with preset Content-Type '" + contentType + "'");
        }

        return;
    }

    body = this.getAdvice().beforeBodyWrite(body, returnType, selectedMediaType, converter.getClass(), inputMessage, outputMessage);
    if (body != null) {
        LogFormatUtils.traceDebug(this.logger, (traceOn) -> {
            return "Writing [" + LogFormatUtils.formatValue(body, !traceOn) + "]";
        });
        this.addContentDispositionHeader(inputMessage, outputMessage);
        if (genericConverter != null) {
            genericConverter.write(body, (Type)targetType, selectedMediaType, outputMessage);
        } else {
            converter.write(body, selectedMediaType, outputMessage);
        }
    } else if (this.logger.isDebugEnabled()) {
        this.logger.debug("Nothing to write: null body");
    }

}
```

**注意：**

- MediaType selectedMediaType = null;(媒体类型)：内容协商（浏览器会以请求头的方式告诉服务器他能接受什么样的内容）；
- 浏览器可以接受的数据类型：

![](../image/浏览器接收的数据类型.png)

- 服务器可以生产的数据类型(producibleTypes):

![](../image/服务器产生的数据类型.png)



- 服务器最终根据自身的能力来决定服务器能够产生什么样的数据类型。
- List<MediaType> mediaTypesToUse = new ArrayList();获取最终能够生成的数据类型。
- SpringMVC会挨个遍历所有容器底层的HttpMessageConverter，看谁能处理。























**内容协商(前端页面中F12)**

> **RequestHeader：**
> 	text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-	exchange;v=b3;q=0.9
>
> 这里：0.9表示权重，意思就是首先html接收页面，其次就是接收图片等，最后接收其他的

**SpringMVC支持的返回值类型**

```java
ModelAndView
Model
View
ResponseEntity
ResponseBodyEmitter
StreamResponseBody
HttpEntity
HttpHeaders
Callable //异步
DeferredResult
ListenableFuture
CompletionStage
WebAsyncTask
有 @ModelAttribute注解也可以
@ResponseBody注解 ----->RequestResponseBodyProcessor这个类进行处理

```





##### **HttpMessageConverter原理**

###### HttpMessageConverter规范

```java
public interface HttpMessageConverter<T> {
    boolean canRead(Class<?> var1, @Nullable MediaType var2);

    boolean canWrite(Class<?> var1, @Nullable MediaType var2);

    List<MediaType> getSupportedMediaTypes();

    default List<MediaType> getSupportedMediaTypes(Class<?> clazz) {
        return !this.canRead(clazz, (MediaType)null) && !this.canWrite(clazz, (MediaType)null) ? Collections.emptyList() : this.getSupportedMediaTypes();
    }

    T read(Class<? extends T> var1, HttpInputMessage var2) throws IOException, HttpMessageNotReadableException;

    void write(T var1, @Nullable MediaType var2, HttpOutputMessage var3) throws IOException, HttpMessageNotWritableException;
}
```

**注意：**

- 该类的主要作用：将Class类型的对象，转为MediaType类型的数据。
- 例子：对象转换为json（canRead），或者是json转换成对象（canWrite）



![HttpMessageConverter](../image/HttpMessageConverter.png)





###### 系统中默认的MessageConverter

![HttpMessageConverter](../image/HttpMessageConverter-1631945795439.png)

**注意：**

- 0：只支持返回值类型为byte的
- 1：只支持返回值类型为String的
- 2：支持String
- 3：支持返回值为Resource
- 4：支持ResourceRegion
- 5：支持DOMSource.class、SAXSource.class、StAXSource.class、StreamSource.class、Source.class
- 6：支持MultiValueMap
- 7：返回为true
- 8：返回true
- 9：支持注解方式的xml

导入了jackson处理的xml的包，xml的converter就会自动进来

```java
# WebMvcConfigurationSupport
jackson2XmlPresent = ClassUtils.isPresent("com.fasterxml.jackson.dataformat.xml.XmlMapper", classLoader);


//判断支持xml格式
if (jackson2Present) {
            builder = Jackson2ObjectMapperBuilder.json();
            if (this.applicationContext != null) {
                builder.applicationContext(this.applicationContext);
            }

            messageConverters.add(new MappingJackson2HttpMessageConverter(builder.build()));
        }
```

**最终就是MappingJackson2HttpMessageConverter利用底层的Jackson的ObjectMapper将数据转换成Json的**

![](../image/最终转换成Json格式.png)





##### 内容协商

根据客户端接收能力不同，返回不同媒体类型的数据

**1、引入xml依赖**

```xml
<dependency>
    <groupId>com.fasterxml.jackson.dataformat</groupId>
    <artifactId>jackson-dataformat-xml</artifactId>
</dependency>
```

**2、使用postman分别测试返回json和xml**

只需要改变请求头中的Accept字段。Http协议中规定的，告诉服务器可以接收的数据类型。



**3、开启浏览器参数方式内容协商功能**



**4、内容协商原理**

- 判断当前响应头中是否已经有确定的媒体类型（MediaType）。

- **获取客户端（PostMan，浏览器）支持接收的内容类型。（获取客户端Accept请求头字段）【application/xml】**

  - **contentNegotiationManager  内容协商管理器 默认使用基于请求头的策略**

  - **HeaderContentNegotiationStrategy 确定客户端可以接受的内容类型**

    - ```java
      String[] headerValueArray = request.getHeaderValues("Accept");
      ```

  - 参数配置

    - ```xml
      ---配置文件添加开启使用不同的参数配置----
      spring:
        mvc:
          contentnegotiation:
            favor-parameter: true #开启请求参数内容协商模式
      ---访问接口-----
      http://localhost:8080/zz/test?format=json
      http://localhost:8080/zz/test?format=xml
      ```

  - ![](../image/内容协商管理器 .png)

**注意**

1. 确定客户端需要接收什么样的数据类型
2. Parameter策略优先确定是要返回json数据（获取请求头中的format的值）

```java
return request.getParameter(getParameterName());
```

- 循环遍历所有的**messageConverter**，看谁支持操作这个对象(converter第一次使用的地方)
- 找到支持这个对象的converter，把converter支持的媒体类型统计出来。
- 客户端需要【application/xml】，服务端能力【10种，包括json和xml，里面也有重复的】producibleType

![](../image/服务器解析的json和xml格式.png)

- 进行内容协商的最佳匹配媒体类型
- 用 支持 将对象转换为 最佳匹配媒体类型 的converter。调用它进行转化



**5、自定义MessageConverter**

所有的MessageConverter合起来可以支持各种媒体类型数据的操作（读、写）

实现多协议数据兼容。json、xml、x-zz

1、@ResponseBody 响应数据出去 调用RequestResponseBodyMethodProcessor处理

2、Processor处理方法返回值。通过MessageConverter处理

3、服务器中产生了10种返回值类型用于支持媒体类型的操作（读、写）

4、内容协商最终找到适合的messageConverter；																																																																																																																																																																																																		

SpringMVC的自定义自己的配置，就是一个入口，给容器中添加一个WebMvcConfigurer



#### 视图解析与模板引擎

##### 1、视图解析(视图处理方式)

- 转发
- 重定向
- 自定义视图

##### 2、视图解析原理

- 目标方法处理的过程中，所有数据都会被放在**ModelAndViewContainer里面。包括数据和视图地址**
- **方法参数是一个自定义类型对象（从请求参数中确定），把他重新放在ModelAndViewContainer**
- **任何目标方法执行完成之后都会返回ModelAndView**
- **processDispatchResult 处理派发结果（页面该如何响应）**
  - **render(mv(modelAndView),request,response);**进行页面渲染逻辑
    - 根据方法的String返回值得到View对象【定义了页面的渲染逻辑】
      - 所有的视图解析器尝试是否能根据当前返回值得到View对象
      - 得到了redirect:/main.html ---> Thyemeleaf  new **RedirectView();**
      - ContentNegotationViewResolver里面包含了下面所有的视图解析器，内部还是使用下面的所有视图解析器得到视图处理对象。
      - view.render(mv.getMethodInternal(),request,response);视图对象调用自定义的render进行页面渲染工作。
        - **RedirectView如何渲染[重定向到一个页面]**
        - **获取目标url地址**
        - **repsonse.sendRedirect(encodedURL);**
- **视图解析**
  - **返回值以forward：开始：new InternalResourceView(forwardUrl);   --->转发request.getRequestDispatcher(path).forward(request,repsonse);**
  - **返回值以 redirect：开始：new RedirectView(); --->底层：render就是重定向**
  - 返回值是普通字符串：new ThymeleafView()

可以自定义视图解析器+自定义视图



#### 6、拦截器

##### 1、HandlerInterceptor 接口

```java
public interface HandlerInterceptor {
    //预先处理，就是在处理方法之前就进行处理。
    default boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        return true;
    }
	//返回页面之前处理，就是说在方法执行之后进行post进行处理
    default void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, @Nullable ModelAndView modelAndView) throws Exception {
    }
	//页面渲染完成之后有需要进行处理就是用这个方法
    default void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, @Nullable Exception ex) throws Exception {
    }
} 
```

##### 2、配置拦截器

```java
/**
 * @author Zz1806
 * 登录检查
 * 1、配置好拦截器要拦截哪些请求
 * 2、把这些配置放在容器中
 */
@Slf4j
public class LoginInterceptor implements HandlerInterceptor {

    /**
     * 目标方法执行之前
     * @param request
     * @param response
     * @param handler
     * @return
     * @throws Exception
     */
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {

        String requestURI = request.getRequestURI();
        log.info("拦截的请求路径是"+requestURI);

        //登录检查逻辑
        HttpSession session = request.getSession();

        Object loginUser = session.getAttribute("loginUser");

        if(loginUser!=null){
            //放行
            return true;
        }
        //拦截,如果未登录就跳转到登录页面,使用session的设置的话，有可能会出现当前页面被拦截，不会存储消息
        request.setAttribute("msg","请先登录!");
        //response.sendRedirect("/index.html");
        //拿到转发器，并且重定向到指定位置，传递request和Repsonse
        request.getRequestDispatcher("/").forward(request,response);
        return false;
    }

    /**
     * 目标方法执行之后
     * @param request
     * @param response
     * @param handler
     * @param modelAndView
     * @throws Exception
     */
    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        log.info("postHandle执行{}"+modelAndView);
    }

    /**
     * 页面渲染之后
     * @param request
     * @param response
     * @param handler
     * @param ex
     * @throws Exception
     */
    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        log.info("afterCompletion执行异常{}"+ex);
    }
}
```

**拦截器配置类**

```java
**
 * @author Zz1806
 * 1、编写一个拦截器实现HandlerInterceptor接口
 * 2、拦截器注册到容器中（实现WebMvcConfigurer，重写addInterceptor方法）
 * 3、制定拦截规则【如果是拦截所有，静态资源也会被拦截】
 */
@Configuration
public class AdminWebConfig implements WebMvcConfigurer {

    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(new LoginInterceptor())
                .addPathPatterns("/**") //所有请求都会拦截，包括静态资源
                .excludePathPatterns("/","/login","/css/**","/js/**","/fonts/**","/images/**"); //放行的请求
    }
}
```

**注意：**

- 首先编写一个拦截器实现HandlerInterceptor接口
- 拦截器注册到容器中（实现WebMvcConfigurer，重写addInterceptor方法）
- 制定拦截规则【如果是拦截所有，静态资源也会被拦截】





##### 3、验证拦截器

2021-09-22 21:52:37.831  INFO 10096 --- [nio-8080-exec-1] com.cg.zz.interceptor.LoginInterceptor   : 拦截的请求路径是/index.html
2021-09-22 21:52:51.427  INFO 10096 --- [nio-8080-exec-1] com.cg.zz.interceptor.LoginInterceptor   : 拦截的请求路径是/index.html

。。。。



##### 4、拦截器原理

1、根据当前请求，找到HandlerExecutionChain【可以处理请求的handler以及handler的所有拦截器】

2、先 **顺序执行** 所有拦截器的 preHandle方法

- 1、如果当前拦截器的preHandler返回为true。则执行下一个拦截器的preHandle
- 2、如果当前拦截器返回false，就直接   倒叙执行所有已经执行的拦截器的 afterCompletion；

**3、如果任何一个拦截器返回false。直接跳出不执行目标方法**

**4、所有拦截器都返回true。**

**5、倒叙执行所有拦截器的postHandler方法。**

**6、前面的步骤有任何异常都会直接倒叙触发** afterCompletion

**7、页面成功渲染完成，也会倒叙触发** afterCompletion 

![处理链](../image/处理链.png)



#####    5、拦截器的处理方法截图

![](../image/拦截器的处理过程.png)





#### 文件上传



##### 1、前端页面代码

```html
<form method="post" action="/upload" enctype="multipart/form-data">
    <input type="file" name="file"></input>
	<input type="submit" value="提交"></input>
</form>
```

##### 2、文件上传代码

```java
/**
 * MultipartFile 自动封装上传过来的文件
 * @param username
 * @param email
 * @param file
 * @param files
 * @return
 */
@PostMapping("/upload")
public String upload(@RequestParam("username") String username,
                     @RequestParam("email") String email,
                     @RequestPart("headImg") MultipartFile file,
                     @RequestPart("images") MultipartFile[] files) throws IOException {

    if(!file.isEmpty()){
        file.transferTo(new File("D:/xxx"));
    }

    if(files.length>0){
        for (MultipartFile multipartFile : files) {
            if (!multipartFile.isEmpty()){
                String originalFilename = multipartFile.getOriginalFilename();
                multipartFile.transferTo(new File("D:"+originalFilename));
            }
        }
    }

    return "mian";
}

----配置文件----
servlet:
    multipart:
      max-file-size: 10MB
      max-request-size: 100MB
```

##### 3、自动配置原理

**文件上传：MultipartAutoConfiguration-MultipartProperties**

- 自动配好了**StandardServletMultipartResolver【文件上传解析器**】
- **原理步骤**
  - **1、请求进来使用文件上传解析器判断（this.multipartResolver.isMultipart(request)）并且封装文件（this.multipartResolver.resolveMultipart(request);）返回MultipartHttpServletRequest）上传请求**
  - **2、参数解析器（RequestPartMethodArgumentResolver）来解析请求中的文件参数内容，并且将其封装成MultipartFile对象**
  - **3、将request中的文件信息封装为一个Map:MultiValueMap<String,MultipartFile>**

FileCopyUtils。实现文件流的拷贝。

##### 4、异常处理

**1、默认规则**

- 默认情况下，SpringBoot提供/error处理所有的错误的映射
- 对于机器客户端，它将生成JSON响应，其中包含错误，HTTP状态和异常消息的详细信息。对于浏览器客户端，响应一个“whitelable”错误视图，以HTML格式呈现相同的数据
- **要对其自定义，添加View解析为error**
- 要完全替换默认行为，可以实现errorController并注册该类型的Bean定义，或添加ErrorAttributes类型的组件以使用现有机制但替换其中内容。

**2、定制错误处理逻辑**

- **自定义错误页（template/error/。。）**
  
  - error/404.html error/5xx.html；有精确的状态码就会去匹配，如果没有就直接找4xx。5xx
  - 不带请求参数或者参数类型不对，错误码就是400。
  
- **@ControllerAdvice + @ExeceptionHandler处理全局异常：就是调用底层的ExceptionHandlerExceptionResolver来处理异常**

  - ```java
    @Slf4j
    @ControllerAdvice
    public class GlobalException {
    
        /**
         *
         * 该注解只能处理里面写的异常，不能处理其他的异常
         * @return
         */
        @ExceptionHandler({ArithmeticException.class,NullPointerException.class})
        public String HandlerArithException(Exception e){
            log.info("异常是:"+e);
            return "index";
            }
    }
    ```

- **Spring底层的异常**，如参数类型转换异常：DefaultHandlerExceptionResovler来处理框架底层的异常。

  - response.sendError(HttpServletResponse.SC_BAD_REQUEST,ex.getMessage);

- **responseStatus+自定义异常：**底层使用ResponseStatusExceptionResovler来支持：**作用：就是将@ResponseStatus里面的信息调用的是response.sendError(statusCode,resovledReason);相当于是提醒tomcat发送了一个/error的请求，spring的底层就来处理/error请求，注意tomcat的处理/error和spring的/error不一样。 **

  - ```java
    /**
     * @author Zz1806
     * 
     */
    @ResponseStatus(value = HttpStatus.FORBIDDEN,reason = "用户数量太多")
    public class UserTooManyException extends RuntimeException{
    
        public UserTooManyException(){
    
        }
    
        public UserTooManyException(String message){
            super(message);
        }
    }
    ```

- **自定义实现HandlerExceptionResovler 处理异常**。可以作为默认的全局异常处理规则

  - ```java
    /**
     * @author Zz1806
     * @Order(value = Ordered.HIGHEST_PRECEDENCE):设置异常处理最高优先级，数字越小，优先级越高
     */
    @Order(value = Ordered.HIGHEST_PRECEDENCE)
    @Component
    public class CustomerHandlerExceptionResolver implements HandlerExceptionResolver {
        @Override
        public ModelAndView resolveException(HttpServletRequest httpServletRequest,
                                             HttpServletResponse httpServletResponse,
                                             Object o, Exception e) {
            try {
                httpServletResponse.sendError(511,"自定义的错误");
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
    
            return new ModelAndView();
        }
    }
    ```

- **ErrorViewResovler**实现自定义异常

  - response.sendError();error请求会转给BasicErrorController
  - 你的异常没有任何人都能处理。也是tomcat底层的response.sendError();还是传递给这个controller
  - BasicErrorController要去的页面地址是ErrorViewResovler来解析的



**3、异常处理自动配置原理**

- ErrorMvcAutoConfiguration：自动配置了异常处理的规则
  - **容器中的组件：类型：DefaultErrorAttributes ->bean的id：errorAttributes**
    - public class **DefaultErrorAttributes** implements ErrorAttributes, HandlerExceptionResolver, Ordered {}
    - **DefaultErrorAttributes：定义错误信息中应该包含哪些属性。**
    - 比如：exception、trace、trace、errors、timestamp、status等相关属性
  - **容器中的组件：类型：BasicErrorController -->bean的id：basicErrorController**（json+白页 使用协商进行适配）
    - **处理默认/error路径的请求：页面响应 new ModelAndView("error",model);**
    - **容器中有一个组件View，它的bean的id是error**：（响应默认错误页面）
    - **容器中有一个beanNameViewResovler用来进行视图解析的，按照返回的视图名（new ModelAndView("error",model);）作为组件的id，然后根据这个id去找View对象。**
  - **容器中的组件DefaultErrorViewResolver -->id:conventionErrorViewResolver**
    - 如果发生错误，就会调用DefaultErrorViewResolver 类里面的resolveErrorView（。。。）方法，
    - 该方法里面有调用了modelAndView = this.resolve((String)SERIES_VIEWS.get(status.series()), model);方法，参数传递的是错误的状态码和model。
    - 当调用resovle这个方法的时候，就会有这一段String errorViewName = "error/" + viewName;将参数中的状态码和默认/error的包名进行一个拼接，之后再根据这个名称去根目录下面查找这个页面。
    - 如果有这个页面就直接返回，如果没有就创建一个默认的**provider != null ? new ModelAndView(errorViewName, model) : this.resolveResource(errorViewName, model);**，而默认的就会调用**BasicErrorController** 这个组件里面的方法返回一个空白页。



如果想要返回的是页面；就会找到error视图。（默认是一个白页**public void render(Map<String, ?> model, HttpServletRequest request, HttpServletResponse response) throws Exception {}**）

```java
@RequestMapping(produces = {"text/html"})
    public ModelAndView errorHtml(HttpServletRequest request, HttpServletResponse response) {
        HttpStatus status = this.getStatus(request);
        Map<String, Object> model = Collections.unmodifiableMap(this.getErrorAttributes(request, this.getErrorAttributeOptions(request, MediaType.TEXT_HTML)));
        response.setStatus(status.value());
        ModelAndView modelAndView = this.resolveErrorView(request, response, status, model);
        return modelAndView != null ? modelAndView : new ModelAndView("error", model);
    }
```

- 注意：BasicErrorController 的这个方法是返回的是**错误页面**

```java
@RequestMapping
public ResponseEntity<Map<String, Object>> error(HttpServletRequest request) {}
```

- 这个方法是返回的**json格式**



**总结：**

- 如果想要改变**错误页面的路径**就应该重写BasicErrorController。
- 如果想要**自定义错误页面**就重写DefaultErrorViewResolver。
- 如果想要添加其他的错误信息，就应该重写DefaultErrorAttributes 这个类。 



**4、异常处理流程**

1. 执行目标方法（DispatchServlet类中的doDisPatch方法里面的mv = ha.handle(processedRequest, response, mappedHandler.getHandler());）目标方法运行期间一旦有异常就会被catch捕获、而且当前请求也会结束。然后使用dispatchException = var20;这个属性进行封装和存放这些异常。

2. 进入视图解析流程（就是进行页面渲染）。**this.processDispatchResult(processedRequest, response, mappedHandler, mv, (Exception)dispatchException);**此时的mv的空的，因为mv在执行目标方法的时候出现异常。

3. 点进去**processDispatchResult**方法：mv = processHandlerException：处理handler发生的异常，处理完成之后就会返回modelAndView对象（mv）。

   1. 创建一个新的ModelAndView对象（exMv）。遍历所有的**handlerExceptionResolvers**。

      1. **系统默认的异常解析器是DefaultErrorAttributes和HandlerExceptionResolverComposite（里面又有三个组合异常解析器，分别是ExceptionHandlerExceptionResolver、ResponseStatusExceptionResovler、DefaultHandlerExceptionResovler）；**

      2. 里面有一个默认的方法**ModelAndView resolveException(HttpServletRequest var1, HttpServletResponse var2, @Nullable Object var3, Exception var4);**该方法的参数分别是原生的request、response、哪个参数处理器（handler）、哪个异常exception。**该方法的作用就是使用了哪个handler来处理哪个excetion，最后返回的是ModelAndView对象。**

         

   2. exMv = resolver.resolveException(request, response, handler, ex);判断哪个可以解析这个异常，如果有就放在exMv中

      1. **defaultErrorAttributes来处理异常。**把异常保存在request作用域中。并且返回空。所以此时的exMv是null。**作用：是为了保存异常信息，等待后面的BasicController来处理这些异常信息。**
      2. **使用HandlerExceptionResolverComposite异常解析器来处理，发现还是不行，因为这个需要注解来实现。**
      3. **所以此时exMv一直都是null。**

   3. 因为exMv是null，所以直接**抛出异常ex**，此时的ex是你传入的参数异常的ex。

   4. **因为没有人能够处理，所以异常就会被抛出。**

      1. 如果没有人能够处理这个异常，底层就会发送一个/error请求。然后重新执行doDispatch方法，底层的BasicErrorController来进行处理/error请求。
      2. **解析错误视图resovleErrorView；执行：遍历所有的errorResovler，看谁能解析这个异常**
      3. DefaultErrorViewResolver来解析成功，就是底层默认的错误视图解析器。作用：把响应状态码（status）作为错误页面的地址，error/5xx.html
      4. 模板引擎最终响应的就是这个5xx.html页面。



##### **5、Web原生组件注入（Servlet、Filter、Listener）**

**1、使用Servlet  Api**

```java
**
 * @author
 * 启动类
 */
@ServletComponentScan(basePackages = "com.cg.zz")//指定原生的Servlet组件放在哪里
@SpringBootApplication
public class MainApplication {
}
------------------------------
/**
 * @author Zz1806
 */
@WebServlet(urlPatterns = "/my") //直接响应，没有经过登录拦截
public class MyServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.getWriter().write("666");
    }
}
--------------------------
/**
 * @author Zz1806
 */
@Slf4j
@WebFilter(urlPatterns = {"/css/*","/image/*"})
public class MyFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
        log.info("MyFilter初始化完成");
    }

    @Override
    public void doFilter(ServletRequest servletRequest, ServletResponse servletResponse, FilterChain filterChain) throws IOException, ServletException {
        log.info("MyFilter工作");
        filterChain.doFilter(servletRequest,servletResponse);
    }

    @Override
    public void destroy() {
        log.info("MyFilter销毁");
    }
}
----------------------------
/**
 * @author Zz1806
 */
@Slf4j
@WebListener
public class MyServletListener implements ServletContextListener {

    @Override
    public void contextInitialized(ServletContextEvent sce) {
        log.info("MyServletListener监听到项目初始化完成");
    }

    @Override
    public void contextDestroyed(ServletContextEvent sce) {
        log.info("MyServletListener监听到项目销毁");
    }
}
```





**为什么MyServlet（自定义的Servlet）直接跳过验证？**

- myServlet ----->拦截的路径：my（自定义路径）
- DispatchServlet ---->



扩展：DispatcherServlet如何注册进来

- 容器中配置了DispatcherServlet属性绑定到WebMvcProperties：对应的配置文件是：spring.mvc(DispatcherServletAutoConfiguration这个类里面看)。
- 通过ServletRegistrationBean<DispatcherServlet>把DispatcherServlet 配置进来。
- 默认映射的是  /+路径  。



tomcat-Servlet：

多个Servlet都能处理到同一层路径，精确优选原则

A: /my/

B: /my/1



**2、使用RegistrationBean**

ServletRegistrationBean、FilterRegistrationBean、ServletListenerRegistrationBean

```java
/**
 * @author Zz1806
 * (proxyBeanMethods = false)
 */
@Configuration(proxyBeanMethods = true)
public class MyRegistConfig {

    @Bean
    public ServletRegistrationBean myServlet(){
        MyServlet myServlet = new MyServlet();
        return new ServletRegistrationBean(myServlet,"/my","/my02");
    }

    @Bean
    public FilterRegistrationBean myFilter(){
        MyFilter myFilter = new MyFilter();
//        return new FilterRegistrationBean(myFilter,myServlet());拦截上面定义的Servlet路径
        FilterRegistrationBean filterRegistrationBean = new FilterRegistrationBean();
        //自定义拦截Servlet路径，记住servlet路径是一个*，Spring是两个*号
        filterRegistrationBean.setUrlPatterns(Arrays.asList("/css/*","/my"));
        return filterRegistrationBean;
    }

    @Bean
    public ServletListenerRegistrationBean myListener(){
        MyServletListener myServletListener = new MyServletListener();
        return new ServletListenerRegistrationBean(myServletListener);
    }
}
```

**注意：**

- (proxyBeanMethods = false)：不写这个主要是因为创建myServlet这个对象不会冗余。、
- (proxyBeanMethods = true)：保证这个myServlet对象是个单实例





##### 6、嵌入式Servlet容器

**1、切换嵌入式Servlet容器**

- **默认支持的WebServer**
  - Tomcat、jetty、or Undertow
  - ServletWebServerApplicationContext 容器启动寻找ServletWebServerFactory 并引导创建服务器。
- **切换服务器**
  - JettyWebServer
  - NettyWebServer
  - TomcatWebServer
  - UndertowWebServer（默认不支持jsp）

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
    <exclusions>
        <exclusion>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-tomcat</artifactId>
        </exclusion>
    </exclusions>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-jetty</artifactId>
</dependency>
```

- 原理
  - SpringBoot应用启动的时候会发现当前是web引用。web场景包-导入tomcat。
  - web应用会创建一个web版的ioc容器ServletWebServerApplicationContext。
  - ServletWebServerApplicationContext 启动的时候寻找 ServletWebServerFactory (Servlet的web服务器工厂--------->生产Sevlet的web服务器)。
  - SpringBoot底层默认有很多的WebServer工厂：**TomcatServletWebServerFactory**、**JettyServletWebServerFactory**、**UndertowServletWebServletFactory**。
  - 底层直接会有一个自动配置类。**ServletWebServerFactoryAutoConfiguration。**
  - **ServletWebServerFactoryAutoConfiguration**导入了**ServletWebServerFactoryAutoConfiguration。**
  - ServletWebServerFactoryAutoConfiguration配置类，根据动态判断系统中到底导入了哪个web服务器的包。（默认web-starter导入的是tomcat包）。容器中就有一个TomcatServletWebServerFactory。
  - **TomcatServletWebServerFactory**就会创建Tomcat服务器并启动：TomcatWebServer 的构造器拥有初始化的方法--------initialize-----this.tomcat.start();
  - 内嵌服务器，就是手动把启动服务器的代码调用（tomcat核心jar包存在）









**2、定制Servlet容器**

- 实现WebServerFactoryCustomizer<ConfigurationServletWebServletFactory>；web服务器工厂定制化器
  - 把配置文件的值和ServletWebServerFactory（web服务器工厂）进行绑定
- 修改配置文件 server.xml
- 直接自定义 ConfigurableServletWebServerFactory



**xxxxxCustomize：定制化器，可以改变xxx的默认规则**



##### 7、定制化原理

**1、定制化的常用方式**

- 修改配置文件.properties、.yml

- xxxxCustomizer；

- **编写自定义的配置类 xxxConfiguration**+ **@Bean替换、增加容器中默认组件；视图解析器**

- web应用 实现WebMvcConfiguration即可定制化web功能；

  - ```java
    /**
     * @author Zz1806
     */
    @Configuration
    public class MyRegistConfig {
    ```

- **@EnableWebMvc + WebMvcConfigurer ---@Bean 可以全面接管SpringMVC**：实现定制和扩展功能。

  - 原理
  - 1、WebMVCConfiguration 默认的SpringMVC的自动配置类。静态资源、欢迎页。。。
  - 2、一旦使用@EnableWebMvc、会@Import({DelegatingWebMvcConfiguration.class})
  - 3、DelegatingWebMvcConfiguration的作用，只保证SpringMVC最基本的使用。
    - 把系统中的WebMvcConfigurer拿过来。所有功能的定制都是这些 WebMvcConfigurer 合起来一起生效
    - 自动配置了一些非常底层的组件。RequestMappingHandlerMapping、这些组件依赖的组件都是从容器中获取
    - public class DelegatingWebMvcConfiguration extends WebMvcConfigurationSupport{}
  - 4、WebMvcAutoConfiguration里面的配置要能生效必须有@ConditionalOnMissingBean(**WebMvcConfigurationSupport.class**)；意思就是没有这个WebMvcConfigurationSupport类自动配置类就可以生效。
  - 5、@EnableWebMvc 导致了WebMvcAutoConfiguration 没有生效



**2、原理分析处理**

**场景starter** -xxxAutoConfiguration - 导入xxx组件 - 绑定xxxProperties - **绑定配置文件项**

- 我们只需要导入场景starter和修改配置文件项
- 中间的部分就是springBoot帮我们完成的



### 数据访问

#### 1、SQL

##### 1、数据源的自动配置

1、导入jdbc场景

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-jdbc</artifactId>
    <version>2.5.6</version>
</dependency>
```

![](../image/jdbc导入的哪些属性.png)

**注意：**

- tx：表示事务
- jdbc：表示的是jdbc连接
- HikariCP：表示数据源



没有导数据库驱动？

为什么导入jdbc场景，官方不导入驱动？因为官方并不知道你是需要使用mysql还是oracle等数据库。

```xml
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
   <!-- <version>5.1.49</version>-->
</dependency>

---重新声明----
properties>
        <java.version>1.8</java.version>
        <mysql.version>5.1.49</mysql.version>
    </properties>
```

**注意：**

- 导入mysql驱动，SpringBoot默认是有mysql驱动的版本的我这个版本是8.0.27
- 数据库版本要与mysql驱动版本保持一致
- 想要修改版本：
  - 1、直接在驱动依赖中添加<version>5.1.49</version>
  - 2、在pom.xml文件里面的properties里面添加<mysql.version>5.1.49</mysql.version>
- Maven的属性是就近优先原则，就是properites里面的应该比mysql驱动的里面的近一些。



##### 2、分析自动配置类

###### 1、自动配置的类

- DataSourceAutoConfiguration：数据源的自动配置类

  - 修改数据源相关的配置：**spring.datasource**

  - 数据库连接池的配置，是自己容器中没有DataSource才自动配置的

  - ```java
    @Configuration(proxyBeanMethods = false)
    @Conditional({DataSourceAutoConfiguration.PooledDataSourceCondition.class})
    @ConditionalOnMissingBean({DataSource.class, XADataSource.class})
    @Import({Hikari.class, Tomcat.class, Dbcp2.class, OracleUcp.class, Generic.class, DataSourceJmxConfiguration.class})
    protected static class PooledDataSourceConfiguration {
        protected PooledDataSourceConfiguration() {
        }
    }
    ```

  - 底层配置好的连接池是：HikariDataSource

- DataSourceTransactionManagerAutoConfiguration：数据源事务管理自动配置类

- JdbcTemplateAutoConfiguration：jdbcTemplate的自动配置，可以用来对数据库进行CRUD

  - 可以修改这个配置项：@ConfigurationProperties( = "spring.jdbc")来修改jdbctemplate
  - @Bean @Primary JdbcTemplate jdbcTemplate：容器中有这个组件

- JndiDataSourceAutoConfiguration：jndi的自动配置类

- XADataSourceAutoConfiguration：分布式事务相关的配置



##### 3、修改配置项

```yml
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/test
    username: root
    password: root
    # type: com.zaxxer.hikari.HikariDataSource
    driver-class-name: com.mysql.cj.jdbc.Driver
```



##### 4、测试

```java
@Slf4j
@SpringBootTest
class DemoApplicationTests {

    @Autowired
    JdbcTemplate template;

    @Test
    void contextLoads() {

        Long aLong = template.queryForObject("select count(*) from user", Long.class);
        log.info("测试表中的数据个数",aLong);
    }

}
---结果----
2021-10-27 21:37:08.645  INFO 16088 --- [           main] com.cg.zz.DemoApplicationTests           : 测试表中的数据个数2
```





#### 2、使用Druid数据源

##### 1、druid官方github地址

https://github.com/alibaba/druid

整合第三方技术的两种方式

- 自定义
- 找starter



##### 2、自定义方式

###### 1、创建数据源

```xml
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>druid</artifactId>
    <version>1.2.7</version>
</dependency>
```



```java
/**
 * @author Zz1806
 */
@Configuration
public class MyConfig {

    /**
     * 默认的自动配置是判断容器中没有才会配置@ConditionalOnMissingBean(DataSource.class)
     * @return
     */
    @ConfigurationProperties("spring.datasource")
    @Bean
    public DataSource dataSource() throws SQLException {
        DruidDataSource druidDataSource = new DruidDataSource();
        //添加监控功能（stat）和防火墙（wall）
        druidDataSource.setFilters("stat,wall");
        return druidDataSource;

    }

    /**
     * 配置druid的监控页功能
     * @return
     */
    @Bean
    public ServletRegistrationBean statViewServlet(){
        StatViewServlet viewServlet = new StatViewServlet();
        ServletRegistrationBean<StatViewServlet> registrationBean = new ServletRegistrationBean<>(viewServlet,"/index");
        return registrationBean;
    }


    @Bean
    public FilterRegistrationBean webStatFilter(){
        //创建一个监控统计对象
        WebStatFilter webStatFilter = new WebStatFilter();
        FilterRegistrationBean<WebStatFilter> registrationBean = new FilterRegistrationBean<>(webStatFilter);
        //设置拦截路径，这里默认是全路径拦截
        registrationBean.setUrlPatterns(Arrays.asList("/*"));
        //添加初始化参数配置
        registrationBean.addInitParameter("exclusions","*.js");
        return registrationBean;
    }

}
------第二种方式，配置文件----
spring: 
	datasource: 
		max-active: 12
```



###### 2、使用官方starter的方式

**1、引入druid-starter数据源**

```xml
<dependency>
    <groupId>com.alibaba</groupId>
    <artifactId>druid-spring-boot-starter</artifactId>
    <version>1.1.7</version>
</dependency>
```



2、**分析自动配置**

- 扩展配置项 spring.datasources.druid
- @import({DruidSpringAopConfiguration.**class**,监控springBean的；**配置：spring.datasource.druid.aop-patterns。**
- DruidStatViewServletConfiguration.**class**,监控页的配置：**spring.datasources.druid.stat.view.servlet**,默认是开启的true。
- DruidWebStatFilterConfiguration.**class**,web监控配置；**spring.datasource.druid.web.stat,filter**;默认开启。
- DruidFilterConfiguration.**class**})；所有的Druid自己filter的配置。比如：...filter.stat、...filter.config、...filter.slf4j、...filter.wall等等。
- 官方有很多的配置文件https://github.com/alibaba/druid下面有，还有一种方式，就是直接去配置类中找



```yml
spring:
  datasource:
    url: jdbc:mysql://localhost:3306/test
    username: root
    password: root
    # type: com.zaxxer.hikari.HikariDataSource
    driver-class-name: com.mysql.cj.jdbc.Driver
  filters: stat,wall
  stat-view-servlet: #配置监控页功能
      enable: true
      login-username: admin
      login-password: admin
      restEnable: false
  filter:
    stat: #对上面filter里面stat详细的配置
      slow-sql-millis: 1000
      logSlowSql: true
      enable: true
    wall: #对上面filter里面wall详细的配置
      enable: true
      config:
        update-allow: false
  web-stat-filter: #监控web
  	  enable: true
  	  urlPattern: /*
  	  exclusion: '*.js,*.gif...'
  jdbc:
    template:
      query-timeout: 3
```

**注意：**

- 只写了一部分 

#### 3、整合MyBatis操作

https://github.com/mybatis

starter

SpringBoot官方的Starter：Spring-boot-starter-*

第三方的：*-spring-boot-starter

```xml
<dependency>
    <groupId>org.mybatis.spring.boot</groupId>
    <artifactId>mybatis-spring-boot-starter</artifactId>
    <version>2.2.0</version>
</dependency>
```

##### 1、配置模式

- 全局配置文件
- SqlSessionFactory：全都配置好了
- SqlSession：配置了**SqlSessionTemplate 组合了SqlSession **
- @Import(**{MybatisAutoConfiguration.AutoConfiguredMapperScannerRegistrar.class}**)：配置的是扫描哪些文件
- Mapper：只要我们写的操作mybatis的接口标注了**@Mapper注解就会被自动扫描进来**

```java
@Configuration
@ConditionalOnClass({SqlSessionFactory.class, SqlSessionFactoryBean.class})
@ConditionalOnSingleCandidate(DataSource.class)
@EnableConfigurationProperties({MybatisProperties.class}) Mybatis配置项绑定类
@AutoConfigureAfter({DataSourceAutoConfiguration.class, MybatisLanguageDriverAutoConfiguration.class})
public class MybatisAutoConfiguration implements InitializingBean {}

---绑定的类
@ConfigurationProperties(prefix = "mybatis") //可以在配置文件中修改mybatis为前缀的相关属性
public class MybatisProperties {}
```



```xml
#配置mybatis的规则。配置的文件地址都是在根目录下
mybatis:
  config-location: classpath:mybatis/mybatis-config.xml #配置全局配置文件地址
  mapper-locations: classpath:mybatis/mapper/*.xml #配置mapper映射文件地址

----Mapper接口绑定xml-----
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.cg.zz.mapper.UserMapper">
    <select id="getUser" resultType="com.cg.zz.bean.User">
    select * from user where id = #{id}
  </select>
</mapper>

---Mapper类---
/**
 * @author Zz1806
 */
@Mapper
public interface UserMapper {

    /**
     * get:单条获取
     * @param id
     * @return
     */
    User getUser(Long id);
}


----全局配置xml----
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<!-- 配置文件的根元素 -->
<configuration>
    <!--这个是配置驼峰命名，意思是数据库的是下划线（user_id）但是页面显示应该是小驼峰（userId）-->
    <settings>
        <setting name="mapUnderscoreToCameCase" value="true"/>
    </settings>
</configuration>
```

**注意：**

- 配置文件不要出错。
- mapper接口类不要忘记写@Mapper注解。
- mapper接口类的名称和xml的名称一致。



**注意事项**

- 所有的属性都是在MybatisProperties这个类中的，自己去看底层

```java
#配置mybatis的规则
mybatis:
#  config-location: classpath:mybatis/mybatis-config.xml
  mapper-locations: classpath:mybatis/mapper/*.xml
  #指定mybatis全局配置文件中的相关配置项
  configuration:
    map-underscore-to-camel-case: true
```

**注意：**

- 可以不用写全局配置文件#  config-location: classpath:mybatis/mybatis-config.xml
- 当你的全局配置文件配置了某些相关的属性之后，**就不能再配置文件中再写全局配置文件可以配置的条件，只能二选一**



**mybatis的使用流程**

- 导入mybatis官方starter
- 编写mapper接口类，不要忘记添加@Mapper注解
- 编写xml文件与mapper绑定，一般的名字一致
- 在配置文件中（application.yml）配置扫描mapper.xml的文件路径，一般都是在根目录下面新建一个文件夹存放相关xml。以及指定全局配置文件的信息（建议直接配置在mybatis.configuration的标签下面 ）



##### 2、mybatis纯注解模式

```java
 /**
     * 单纯注解版
     * @param name
     * @return
     */
    @Select("select * from user where name =#{name}")
    List<User> getUsers(String name);

	/**
     * 新增
     * @Options里面的参数第一个是使用主键自增，第二个是主键的属性对应类中的哪个字段
     * @param user
     * @return
     */
    @Insert("insert into user('id','name') values(#{id},#{name})")
    @Options(useGeneratedKeys = true,keyProperty = "id")
    public int insertUser(User user);
```



##### 3、混合模式

```java
    /**
     * 单纯注解版
     * @param name
     * @return
     */
    @Select("select * from user where name =#{name}")
    List<User> getUsers(String name);

    /**
     * 新增
     * @param user
     * @return
     */
    public int insertUser(User user);
}
```



##### 总结：

**引入mbatis的最终实现**

- **引用mybatis-starter**
- **编写mapper接口类，不要忘记注解@Mapper**
- **编写xml文件，绑定mapper注解/使用全注解模式**
- **application.yaml中添加mybatis的全局配置文件和mapper扫描文件（mybatis.mapper-location:xxx/mapper/*.xml），如果不知道怎么配置可以去看MybatisProperties这个类，里面有相关属性。**
- **编写Service层，不要忘记添加注解@Service，并且该类里面自动注入mapper接口类，调用mapper层方法**
- **编写controller层，自动注入Service，调用Service方法**
- **进行测试**



##### 扩展：

**如果觉得写@Mapper，比较麻烦，可以在启动类中编写一个注解@MapperScan("com.cg.zz.mapper")，SpringBoot启动的时候就会自动将这个路径里面的类都当做是Mapper接口类。建议给每一个类上面都标注这个@Mapper**

#### 4、整合Mybatis-plus完成CRUD

##### 1、什么是MyBatis-Plus

MyBatis-Plus(简称MP)是一个MyBatis的增强工具，在MyBatis的基础上只做增强，不做改变，为简化开发、提高效率而成。

自己去看mybatis-plus官网https://mp.baomidou.com/

建议安装MyBatisX插件

#####   2、整合MyBatis-Plus

```xml
<dependency>
    <groupId>com.baomidou</groupId>
    <artifactId>mybatis-plus-boot-starter</artifactId>
    <version>3.4.1</version>
</dependency>							
```



**自动配置了哪些（可以直接查看starter的中的spring.factory中的autoconfiguration这个属性的依赖包）**

- MybatisPlusAutoConfiguration：

  - **@EnableConfigurationProperties({MybatisPlusProperties.class})** //绑定的是这个配置项MybatisPlusProperties：

    - **MybatisPlusProperties**：中的**@ConfigurationProperties(prefix = "mybatis-plus")**就是指定**配置文件(application.yml)**中的定制前缀（就像spring.xx/mybatis.xxx），此时就是mybatis-plus.xxx

  - **SqlSessionFactory类：它是@Bean标注的方法，如果一个被@Bean标注的方法的参数是一个对象，那么这个参数就会从容器中自动确定这个组件，它的底层也是用的我们自己的配置的数据源就是在yml中的spring.datasource **

  - **mapperLocations**：这是mybatis-plus自动配置好的mapper扫描路径。**classpath:/mapper/ 这里有两个*号/*.xml**；表示：**任意路径下的所有mapper文件夹下的任意路径下的所有xml都是sql（mapper）映射文件，建议以后sql映射文件，都妨碍mapper文件夹下面**

  - **容器中也自动配置好了SqlSessionTemplate**

  - **MapperScannerRegistrarNotFoundConfiguration:里面的@import注解里面就有@Mapper标注的接口也会被扫描**

    - ```java
      @Configuration
      @Import({MybatisPlusAutoConfiguration.AutoConfiguredMapperScannerRegistrar.class}) //注册mapper的定义信息
      @ConditionalOnMissingBean({MapperFactoryBean.class, MapperScannerConfigurer.class})
      public static class MapperScannerRegistrarNotFoundConfiguration implements InitializingBean {
          public MapperScannerRegistrarNotFoundConfiguration() {
          }
      ```

- MybatisPlusLanguageDriverAutoConfiguration



##### 优点：

- 只需要我们的Mapper继承BaseMapper<实体类>就可以拥有CRUD

- ```java
  /**
       * mybatis-plus独特的功能，表示数据库不存在该字段
       */
      @TableField(exist = false)
      private String username;
      @TableField(exist = false)
      private String password;
  ```



#### NoSQL

##### 1、Redis自动配置

导入redis启动器

```java
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
```

![导入redis相关的依赖](../image/导入redis相关的参数.png)



- RedisAutoConfiguration：自动配置类。RedisProperties属性类 --->spring.redis.xxx是对redis的配置
- 连接工厂是准备好了的。**lettuce**ConnectionConfiguration、**Jedis**ConnectionConfiguration
- RedisTemplate<Object,Object>:xxxTemplate;
- **自动注入了RedisTemplate<Object,Object>:xxxTemplate;**
- **自动注入了StringRedisTemplate;k,v都是String**
- **key：value**
- **只要我们使用StringRedisTemplate、RedisTemplate就可以操作redis**



**redis环境搭配**

- 阿里云按量付费redis。
- 申请redis的公网连接地址
- 设置白名单，允许0.0.0.0/0所有地址进行连接



###### RedisTemplate和lettuce

```java
spring:
  redis:
    host: r-bp1o163g0uv5fp04d2pd.redis.rds.aliyuncs.com
    port: 6379
    password: xhb:Xhb123456

-----测试类-----
@Test
void testRedis(){
    ValueOperations<String, String> forValue = redisTemplate.opsForValue();
    forValue.set("hello","world");
    String hello = forValue.get("hello");
    System.out.println(hello);
}
```



###### 切换至jedis

```xml
<!--导入redis-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-redis</artifactId>
</dependency>
<!--导入jedis-->
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
</dependency>
```

```
@Autowired
    RedisConnectionFactory connectionFactory;

@Test
void testRedis(){
    System.out.println(connectionFactory.getClass());
}
---yml---中的配置文件
spring
	redis:
    	host: r-bp1o163g0uv5fp04d2pd.redis.rds.aliyuncs.com
    	port: 6379
    	password: xhb:Xhb123456
    	client-type: jedis   #切换redis连接类型
    	jedis: 
      		pool:
        	max-active: 10 #设置最大活跃个数
```

### 单元测试

#### 1、JUnit5的变化

SpringBoot 2.2.0 版本开始引入 JUnit5 作为单元测试默认库

> JUnit 5 = JUnit Platform + JUnit Jupiter + JUnit Vintage

 **JUnit Platform：** JUnit Platform是在JVM上启动测试框架的基础，不仅支持Junit自制的测试殷勤，其他测试引擎也都可以接入

**JUnit Jupiter：**JUnit Jupiter提供了JUnit5的新的编程模型，是JUnit5新特性的核心。内部包含了一个测试引擎，用在JUnit Jupiter上运行。

**JUnit Vintage：**由于JUnit已经发展很多年，为了照顾老项目，JUnit Vintage提供了兼容JUnit4.x,JUnit3.x的测试引擎s

**注意：**

**SpringBoot 2.4以上版本移除了默认 堆Vintage的依赖。如果需要兼容junit4需要自动引入。**





**现在版本**

```xml
<!--测试依赖-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
```

```java
//只要标注了@SpringBootTest注解就认为是一个测试类
@SpringBootTest
class DemoApplicationTests {
    @Test
    void contextLoads() {
    }
}
```



**以前版本**

@SpringBoot +@RunWith(SpringTest.class)



**SpringBoot整合Junit之后**

- 编写测试方法：@Test标注（需要注意使用Junit5版本的注解）
- Junit类具有Spring的功能：@Autowired、比如@Transactional标注测试方法，测试完成后自动回滚



#### 2、JUnit5的常用注解

JUnit5的注解与JUnit4的注解有所变化

- **@Test**：表示方法是测试方法。但是他与JUnit4的@Test不同，他的职责非常单一不能声明任何属性，拓展的测试将由Jupitor提供额外测试。
- **@ParameterizedTest**：表示方法是参数化测试
- **@RepeatTest**：表示方法可以重复执行
- **@DisplayName**：为测试类或者测试方法设置展示名称
- **@BeforeEach**：表示在每个单元测试之前执行
- **@AfterEach**：表示在每个单元测试之后执行
- **@BeforeAll**：表示在所有单元测试之前执行
- **@AfterAll**：表示在所有单元测试之后执行 
- **@Tag**：表示单元测试类别，类似于JUnit4中的@Categories
- **@Disabled**：表示测试类或测试方法不执行，类似于JUnit4中的@Ignore
- **@Timeout**：表示测试方法运行如果超过了指定时间将会返回错误
- **@ExtendWith**：为测试类或测试方法提供扩展引用

```java
/**
 * @author Zz1806
 */
@DisplayName("JUnit5测试")
public class Junit5Test {

    @DisplayName("测试displayName注解")
    @Test
    void testDisplayName(){
        System.out.println(1);
    }

    @Disabled
    @DisplayName("测试displayName注解")
    @Test
    void testDisplayName2(){
        System.out.println(2);
    }

    @BeforeEach
    void testBeforeEach(){
        System.out.println("测试即将开始");
    }

    @AfterEach
    void testAfterEach(){
        System.out.println("测试已结束");
    }

    @Timeout(value = 500,unit = TimeUnit.SECONDS)
    void testTimeout() throws InterruptedException {
        Thread.sleep(400);
    }

    @RepeatedTest(5)
    void testRepeat(){
        System.out.println(3);
    }

    @BeforeAll
    static void testBeforeAll(){
        System.out.println("所有测试即将开始");
    }

    @AfterAll
    static void testAfterAll(){
        System.out.println("所有测试已结束");
    }
}
```



#### 3、断言机制

断言是测试方法中的核心部分，用来堆测试需要满足的条件进行验证。**这些断言方法都是org.junit.jupiter.api.Assertiond的静态方法**。JUnit 5内置的断言可以分为如下几个类别：

**检查业务逻辑返回的数据是否合理**

**所有测试结束之后，就有一个详细的测试报告。**



##### 1、简单断言

用来对单个值进行简单验证。如：

| 方法            | 说明                                 |
| --------------- | ------------------------------------ |
| assertEquals    | 判断两个对象或两个原始类型是否相等   |
| assertNotEquals | 判断两个对象或两个原始类型是否步相等 |
| assertSame      | 判断两个对象引用是否指向同一个对象   |
| assertNotSame   | 判断两个对象引用是否指向不同的对象   |
| assertTrue      | 判断给定的布尔值是否为true           |
| assertFalse     | 判断给定的布尔值是否为false          |
| assertNull      | 判断给定的对象引用是否为null         |
| assertNotNull   | 判断给定的对象引用是否不为null       |



```java
@DisplayName("测试断言机制")
@Test
void test(){
    int cal = cal(1,3);
    //判断是否相等
    Assertions.assertEquals(4,cal);
    Object o1 = new Object();
    Object o2 = new Object();
    Assertions.assertSame(o1,o2,"两个对象不一样");
}

@DisplayName("数组断言")
@Test
void array(){
    Assertions.assertArrayEquals(new int[]{1,3},new int[]{1,3});
}

@DisplayName("组合断言")
@Test
void all(){
    Assertions.assertAll(
            ()->Assertions.assertSame(true ,true),
            () ->Assertions.assertEquals(1,3));
}

private int cal(int i, int i1) {
    return i+i1;
}
```



##### 2、异常断言（断定业务逻辑一定出现异常）

```java
@DisplayName("异常断言")
@Test
void testException(){
    Assertions.assertThrows(ArithmeticException.class,() ->{int i=10/0;},"数学运算异常");
}
```



##### 3、超时断言（断定业务逻辑一定超时）

```java
@DisplayName("超时异常")
@Test
void testTimeout1(){
    Assertions.assertTimeout(Duration.ofMillis(1000),() ->Thread.sleep(5000));
}
```



##### 4、快速失败（通过fail方法直接使得测试失败）

```
@DisplayName("快速失败")
    @Test
    void testFail(){
        if(1 == 2){
            Assertions.fail("测试失败");
        }
    }
```





#### 4、前置条件（assumptions）

JUnit 5 中的前置条件（assumtions【假设】）类似于断言，不同之处在于**不满足的断言会使得测试方法失败**，而不满足的前置条件**只会使得测试方法的执行终止。**前置条件可以看成是测试方法的前提，当该前提不满足时，就没有继续执行的必要。

```java
@DisplayName("测试前置条件")
@Test
void testAssumptions(){
    Assumptions.assumeTrue(false,"结果不是true");
    System.out.println("111111");
}
```



#### 5、嵌套测试

JUnit 5 可以通过java中的内部类和@Nested注解实现嵌套测试，从而更好的把相关的测试方法组织在一起。在内部类中可以使用@BeforeEach和@AfterEach注解，而且嵌套的层次没有限制

```java
/**
 * @author Zz1806
 */
@DisplayName("嵌套测试")
public class TestNest {
    Stack<Object> stack;
    @Test
    @DisplayName("new Stack")
    void isInstantiateWithNew(){
        new Stack<>();
        //嵌套测试下，外层的test不能驱动内层的@BeforeEach/@AfterEach之前的方法/之后运行
        Assertions.assertNull(stack);
    }


    @Nested
    @DisplayName("内部嵌套测试")
    class WhenWith{

        @BeforeEach
        void createNewStack(){
            stack = new Stack<>();
        }

        /**
         * 嵌套测试下，内层的test可以驱动外层的@BeforeEach/@AfterEach之前的方法/之后运行
         */
        @AfterEach
        void testNewStack(){
            Assertions.assertNotNull(stack);
        }
    }
}
```



#### 6、参数化测试

参数化测试是JUnit5中一个很重要的特性，它使得不同的参数可以多次运行，也为我们的单元测试带来了便利。

利用@ValueSource等注解，指定入参，我们将可以使用不同的参数，进行多次单元测试，而不需要每新增一个参数就新增一个单元测试，省去了很多冗余代码。



@ValueSource：为参数化测试指定入参来源，支持八大基础类以及String类型，Class类型

@NullSource：表示为参数化测试提供一个null的入参

@EnumSource：表示为参数化测试提供一个枚举入参

@CsvFileSource：表示读取指定CSV文件内容作为参数化测试入参

@MethodSource：表示读取指定方法的返回值作为参数化测试入参(注意方法返回需要时一个流)

他可以支持外部的各类入参。如CSV、YML、JSON等文件甚至是他们的返回值参数入参。只需要我们去实现ArgumentProvider接口，任何外部文件都可以作为它的入参。



```java
@DisplayName("参数化测试")
@ParameterizedTest
@ValueSource(ints = {1,2,3,4,2})
void parameterizedTest(int i){
    System.out.println(i);
}

@ParameterizedTest
@MethodSource("stream")
void MethodTest(String i){
    System.out.println(i);
}

static Stream<String> stream(){
    return Stream.of("aa","bbb","ccc");
}
```

### 指标监控

#### 1、SpringBoot Actuator

##### 1、简介

未来每一个微服务在云上部署后，我们都需要对其进行监控、追踪、审计、控制等。SpringBoot就抽取了Actuator场景，使得我们每个微服务快速引用即可获得生产级别的应用监控、审计等功能。



##### 2、快速入门

- 引入相关启动器(starter)

```java
<!--引入监控功能-->
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>
```

- http://localhost:8082/actuator查看监控命令
- 暴露监控信息为HTTP

```java
management:
  endpoints:
    enabled-by-default: true  #默认开启监控端点
    web:
      exposure:
        include: '*' #以web方式暴露所有的端点
```

- 测试
  - http://localhost:8082/actuator/beans
  - http://localhost:8082/actuator/endpointName/detailpath
  - http://localhost:8082/actuator/metrics
  - http://localhost:8082/actuator/metrics/jvm.gc.pause

##### 3、可视化

https://github.com/codecentric/spring-boot-admins



#### 2、Actuator Endpoint

##### 1、最常使用的端点

| ID          | 描述                                                         |
| ----------- | ------------------------------------------------------------ |
| auditevents | 暴露当前应用程序的审核事件信息。需要一个**AudiEventRepository**组件。 |
| beans       | 显示应用程序中所有Spring Bean的完整列表                      |
| caches      | 暴露可用的缓存                                               |
| conditions  | 显示自动配置的所有条件信息，包括匹配或不匹配的原因           |
| configprops | 显示所有@ConfigurationProperties                             |
| env         | 暴露Spring的属性ConfigurableEnvironments                     |
| flyway      | 显示已应用的所有Flyway数据库迁移，需要一个或多个Flyway组件。 |
| health      | 显示应用程序运行状况信息                                     |
| httptrace   | 显示HTTP跟踪信息（默认情况下，最近100个HTTP请求-响应）。需要一个HttpTraceRepository组件 |
| info        | 显示应用信息                                                 |
| 。。        |                                                              |
| 。。        |                                                              |
| 。。        |                                                              |
| 。。        |                                                              |

**最常用的Endpoint**

- **Health：监控健康状态**
- **Metric：运行时状况**
- **Loggers：日志记录**



##### 2、Heath Endpoint

健康检查端点，我们一般用于云平台，平台会定时的检查应用的健康状态，我们需要Health Endpoint可以作为平台返回当前应用的一系列组件健康状况的集合。包括k8s的自愈系统

- 重要的几点：
  - health endpoint 返回的结果应该是一系列检查结果的汇总报告。
  - 很多的健康检查默认已经自动配置好了，比如：数据库，redis等。
  - 可以很容易的添加自定义的健康检查机制

##### 3、Metrics Endpoint

提供详细的、层级的、空间指标信息、这些信息可以被pull（主动推送）或者push（被动获取）方式得到。

- 通过Metric对接多种监控系统
- 简化核心Metrics开发
- 添加自定义Metric或者扩展自己已有Metrics





#### 3、定制Endpoint

##### 1、定制Health信息

```java
package com.cg.zz.health;

import org.springframework.boot.actuate.health.AbstractHealthIndicator;
import org.springframework.boot.actuate.health.Health;
import org.springframework.boot.actuate.health.Status;
import org.springframework.stereotype.Component;

import java.util.HashMap;

/**
 * @author Zz1806
 */
@Component
public class MyComHealthIndicator extends AbstractHealthIndicator {
    /**
     * 真实的检查方法
     * @param builder
     * @throws Exception
     */
    @Override
    protected void doHealthCheck(Health.Builder builder) throws Exception {
        //如果是连接mongodb -----》获取连接进行测试
        HashMap<String,Object> map = new HashMap<>();
        if(1==1){
            //builder.up(); //健康
            builder.status(Status.UP);
            map.put("count",1);
            map.put("ms",100);
        }else{
            //builder.down();
            builder.status(Status.OUT_OF_SERVICE);
            map.put("error","连接超时");
            map.put("ms",3000);
        }

        builder.withDetail("code",100)
                .withDetails(map);
    }
}
```

```
management:
  endpoint:  #配置单个端点
    health:
      show-details: always  #总是显示详细信息
      enabled: true
```



##### 2、定制info信息

```java
import org.springframework.stereotype.Component;

import java.util.Collections;

/**
 * @author Zz1806
 */
@Component
public class AppInfoContributor implements InfoContributor {


    @Override
    public void contribute(Info.Builder builder) {
        builder.withDetail("msg","坚持下去")
                .withDetail("hello","zz")
                .withDetails(Collections.singletonMap("zz","加油"));
    }
}
```



##### 3、定制Metrics信息

###### 1、SpringBoot支持自动适配的Metrics

- JVM Metrics，report
- CPU Metrics
- File description metrics
- 。。。
- Spring Integration metrics

```java
package com.cg.zz.service.imp;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.cg.zz.bean.User;
import com.cg.zz.mapper.UserMapper;
import com.cg.zz.service.UserService;
import io.micrometer.core.instrument.Counter;
import io.micrometer.core.instrument.MeterRegistry;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * @author Zz1806
 */
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements UserService {

    @Autowired
    UserMapper userMapper;

    Counter counter;

    public UserServiceImpl (MeterRegistry meterRegistry){
        counter = meterRegistry.counter("userService.saveUser.count");
    }

    public void saveUser(User user){
        counter.increment();
        userMapper.insert(user);
    }
}
----方法二-----
@Bean
MeterBinder qeueSize(Queue queue){
    return (registry)  -> Gauge.builder("queueSize",queue::size).register(registry);
}
```



##### 4、定制Endpoint

```java
package com.cg.zz.actuotor.endpoint;

import org.springframework.boot.actuate.endpoint.annotation.Endpoint;
import org.springframework.boot.actuate.endpoint.annotation.ReadOperation;
import org.springframework.boot.actuate.endpoint.annotation.WriteOperation;
import org.springframework.stereotype.Component;

import java.util.Collections;
import java.util.Map;

/**
 * @author Zz1806
 */
@Component
@Endpoint(id = "myservice")
public class MyServiceEndpoint {

    @ReadOperation
    public Map getDockerInfo(){
        //读操作 
        return Collections.singletonMap("dockerInfo","docker.start....");s
    }

    @WriteOperation
    public void stopDocker(){
        System.out.println("zz-docker-stop...s");
    }
}‘
```

应用场景：开发RedinessEndpoint来管理程序是否就绪，或者LivenessEndpoint来管理程序是否存活



```java
<dependency>
    <groupId>de.codecentric</groupId>
    <artifactId>spring-boot-admin-server</artifactId>
    <version>2.3.1</version>
</dependency>

<dependency>
    <groupId>de.codecentric</groupId>
    <artifactId>spring-boot-admin-starter-client</artifactId>
    <version>2.5.3</version>
</dependency>
```



### 原理解析

#### 1、profile功能

为了方便多环境适配，springboot简化了profile功能



##### 1、application-profile功能

- **默认配置文件 application.yaml；任何时候都会加载**
- **指定环境配置文件 application-(test、prod).yaml**
- **激活指定环境**
  - **配置文件激活（spring.profiles.active=test）**
  - **命令行激活**（**java -jar +打包好的包名+ --spring.profiles.active = 配置环境名称（test、prod）**）
    - **可以修改配置文件的任意值，命令行优先**：java -jar +打包好的包名+ --spring.profiles.active = 配置环境名称（test、prod） --person.name = haha
- **默认配置与环境配置同时生效**
- **同名配置项，profile配置(指定的配置环境)优先，会覆盖原来配置文件的属性**



##### 2、@Profile条件装配

```java
----person----
/**
 * @author Zz1806
 */
public interface Person {

    /**
     *
     * @return
     */
   String getName();

    /**
     *
     * @return
     */
   Integer getAge();
}
-----profile的prod环境-----
@Profile("test")
@Data
@Component
@ConfigurationProperties("person")
public class Boos implements Person{
    private String name;
    private Integer age;
}
----profile的test环境---
/**
 * @author Zz1806
 */
@Profile("prod")
@Data
@Component
@ConfigurationProperties("person")
public class Worker implements Person{
    private String name;

    private Integer age;
}
-----测试----
/**
 * @author Zz1806
 */
@RestController
public class HelloController {

   // @Value("${person.name:张三1}")
   // private String name;

    @Autowired
    private Person person;

    @GetMapping("/")
    public String getName(){
        return person.getClass().toString();
    }
}
----配置文件application.properties----
person.name = 张三

#激活特定的环境
spring.profiles.active=prod

----配置文件application-prod.yaml-----
person:
  name: prod-张三
  age: 15
---配置文件application-test.yaml----
person:
  name: test-张三
```

**注意：**

- 会根据系统默认的配置文件里面看是激活了哪个配置文件
- 不同的配置文件里面可以其他配置比如server.port=8081
- 相同的配置文件指定之后就会覆盖相同的配置属性



##### 3、profile分组

```java
----配置文件application.properties----

#激活特定的环境
spring.profiles.active=myPro

spring.profiles.group.myPro[0] = ppd
spring.profiles.group.myPro[1] = prod

spring.profiles.group.myTest[0] = test

    
----配置文件application-ppd.yaml-----
person:
  name: prod-张三

----配置文件application-prod.yaml-----
server:
  port: 8000
person:
  age: 15

---测试-----
/**
 * @author Zz1806
 */
@RestController
public class HelloController {

   // @Value("${person.name:张三1}")
   // private String name;

    @Autowired
    private Person person;

    @GetMapping("/person")
    public Person getPerson(){
        return person;
    }
}
```



### 2、外部化配置

#### 1、外部配置数据源

**常用：java属性配置文件、yaml文件、环境变量、命令行参数**

#### 2、配置文件查找位置

- **classpath 根路径**
- **classpath 根路径下config目录(优先级高于classpath根路径下的)**
- **jar包当前目录**
- **jar包当前目录的config目录**
- **/config子目录的直接子目录（Linux系统中可以有）**

#### 3、配置文件加载顺序

1、当前jar包内部的application.properties和application.yaml

2、当前jar包内部的application-{profile}.properties和application-{profile}.yaml

3、引用的外部jar包的application.properties和application.yaml

4、引用的外部jar的application-{profile}.properties和application-{profile}.yaml	

5、下面的覆盖上面的

#### 4、指定的环境优先，外部的优先与内部，后面的覆盖前面的配置项





### 3、SpringBoot原理

Spring原理、SpringMVC原理、自动配置原理、SpringBoot原理



#### 1、SpringBoot启动过程

- **创建SpringApplication**
  - **保存一些信息**
  - **判定当前应用的类型WebApplicationType：使用ClassUtils这个工具类来判断，一般是Servlet这个应用类型**
  - **初始启动器：bootstrapRegistryInitializers（List<BootstrapRegistryInitializer>）**去spring.factories里面找这个类，如果没有就不会加载初始启动器
  - **找ApplicationContextInitializer：**去spring.facotries找ApplicationContextInitializer
    - **List<ApplicationContextInitializer<?>>  initializers;7个**
  - **找ApplicationListener应用监听器：**
    - **List<ApplicationListener<?>>  listeners;9个**
- **运行SpringApplication**
  - **StopWatch：**
    - **记录应用的启动时间和应用名称**
  - **创建引导上下文（context环境）：this.createBootstrapContext()**
    - 获取到之前的**bootstrapRegistryInitializers**挨个执行它的initialize方法  来完成对引导启动器上下文环境设置
  - **this.configureHeadlessProperty();**让当前应用进入headless模式（java.awt.headless），网上可以查查，自力更生模式。
  - **获取所有的运行监听器(this.getRunListeners(args))**【为了方便所有的listener进行事件感知】
    - **getSpringFactoriesInstances:去spring.factories里面找SpringApplicationRunListener.class**、
    - 遍历所有的**SpringApplicationRunListener**调用starting方法
    - **通知所有感兴趣系统正在启动过程的人，项目正在启动（starting）**
  - **ApplicationArguments：保存命令行参数**
  - **准备环境（this.prepareEnvironment）：**
    - **返回或创建新的基础环境信息对象enviroment**，new ApplicationServletEnvironment()
    - **配置环境信息对象（this.configureEnvironment（环境对象enviroment，命令行参数））。**
      - **this.configurePropertySources(environment, args);读取所有的配置源的配置属性值（内部配置和外部配置（@PropertiesResources））**
      - **this.configureProfiles(environment, args);激活profile环境，若没配置就没使用**
    - **ConfigurationPropertySources.attach((Environment)environment);绑定环境信息**
    - **监听器调用环境准备方法：listeners.environmentPrepared（应道初始化器对象，基础环境对象enviroment）；通知所有的监听器，当前环境准备完成**
    - **DefaultPropertiesPropertySource.moveToEnd((ConfigurableEnvironment)environment);将环境信息设置到该类的最后面。**
    - **SpringApplicatio中绑定一些环境属性：this.bindToSpringApplication((ConfigurableEnvironment)environment);**
    - **此时环境准备完毕**
  - **this.configureIgnoreBeanInfo(environment);配置一些忽略的bean的相关信息**
  - **this.printBanner(environment)；打印banner**
  - **创建IOC容器：this.createApplicationContext();**
    - **根据当前项目类型进行创建（这里是Servlet）：new AnnotationConfigServletWebServerApplicationContext();**
  - **IOC容器保存startup：context.setApplicationStartup(this.applicationStartup);**
  - **准备IOC容器的信息：this.prepareContext(bootstrapContext（引导上下文对象）, context（IOC对象）, environment（基础环境对象）, listeners（监听器对象）, applicationArguments（应用属性参数对象）, printedBanner（banner对象）);**
    - **IOC保存基础环境信息：context.setEnvironment(environment);**
    - **IOC容器的后置处理流程：this.postProcessApplicationContext(context);**
    - **应用初始化器：this.applyInitializers(context);**
      - 遍历所有的ApplicationContextInitializer:**(有7个，在启动流程的时候保存起的)**，调用它的initialize()方法，参数是IOC对象，**对IOC容器进行初始化扩展**
        - **IOC容器都有这7个ApplicationContextInitializer对象的编号就是id**
    - **遍历所有的listener，调用listeners.contextPrepared(context);方法，这里的Listeners就是启动流程里面保存的Listener，就是EventPublishRunListener,事件派发的listener；作用：通知所有的监听器contextPrepared()**
    - ，，，配置banner
    - 。。。
    - **加载这些配置的信息:this.load(context, sources.toArray(new Object[0]));**
    - **所有的监听器调用contextLoaded。通知所有的监听器进行加载，listeners.contextLoaded(context);**
    - **到这里IOC的preparedContext才完成。IOC的前置准备工作完成**
  - **刷新IOC容器：this.refreshContext(context);**
    - 注册一个钩子：shutdownHook.registerApplicationContext(context);
    - **Spring的核心源码：this.refresh(context);开始刷新**
    - **进去到这个类中AbstractApplicationContext：Spring的13个方法，作用就是创建容器中的所有组件**
  - **容器刷新完后后的工作：this.afterRefresh(context, applicationArguments);**
  - **当前容器全部启动完成：stopWatch.stop();里面记录了发费时间**
  - 所有监听器调用started方法，listeners.**started(context);**
  - 调用所有的runners：this.callRunners(context, applicationArguments);
    - **获取容器中的所有ApplicationRunner**
    - **获取容器中的所有的CommandLineRunner**
    - **合并上面的所有runner，按照order排序：AnnotationAwareOrderComparator.sort(runners);**
    - **遍历所有的runner，调用run方法**
  - **如果该以上有异常**
    - **就会调用：listeners.failed(context, exception);**
  - **如果以上全部完成：**
    - **调用Listener的running方法：listeners.running(context);表示程序真正的在运行了**
    - **通知所有的监听器running**
  - **running有问题：**
    - **继续调用listeners.failed(context, exception);**









#### 2、Application Events and Listeners

- **ApplicationContextInitializer**
- **ApplicationListener**
- **SpringApplicationRunListeners**

自定义：

```java
/**
 * @author Zz1806
 */
public class MyApplicationContextInitializer implements ApplicationContextInitializer {
    @Override
    public void initialize(ConfigurableApplicationContext applicationContext) {
        System.out.println("MyApplicationContextInitializer......Initializer.....");
    }
}
---------------
/**
 * @author Zz1806
 */
public class MyApplicationListener implements ApplicationListener {
    @Override
    public void onApplicationEvent(ApplicationEvent event) {
        System.out.println("MyApplicationListener....onApplicationEvent.....");
    }
}

----------------------
/**
 * @author Zz1806
 */
@Order(1)
@Component
public class MyApplicationRunner implements ApplicationRunner {
    /**
     *
     * @param args 命令行参数
     * @throws Exception
     */
    @Override
    public void run(ApplicationArguments args) throws Exception {
        System.out.println("MyApplicationRunner....run....");
    }
}

--------------
/**
 * @author Zz1806
 */
@Order(2)
@Component
public class MyCommandLineRunner implements CommandLineRunner {
    @Override
    public void run(String... args) throws Exception {
        System.out.println("MyCommandLineRunner....run....");
    }
}

-----------
/**
 * @author Zz1806
 */
public class MySpringApplicationRunListener implements SpringApplicationRunListener {

    private SpringApplication application;
    public MySpringApplicationRunListener(SpringApplication application,String[] args){
        this.application = application;
    }

    @Override
    public void starting(ConfigurableBootstrapContext bootstrapContext) {
        System.out.println("MySpringApplicationRunListener....starting....");
    }


    @Override
    public void environmentPrepared(ConfigurableBootstrapContext bootstrapContext, ConfigurableEnvironment environment) {
        System.out.println("MySpringApplicationRunListener....environmentPrepared....");
    }


    /**
     * IOC容器准备完成
     * @param context
     */
    @Override
    public void contextPrepared(ConfigurableApplicationContext context) {
        System.out.println("MySpringApplicationRunListener....contextPrepared....");
    }

    /**
     * IOC容器加载完成
     * @param context
     */
    @Override
    public void contextLoaded(ConfigurableApplicationContext context) {
        System.out.println("MySpringApplicationRunListener....contextLoaded....");
    }

    /**
     * 要等到IOC容器刷新之后，全部属性准备玩成
     * @param context
     */
    @Override
    public void started(ConfigurableApplicationContext context) {
        System.out.println("MySpringApplicationRunListener....started....");
    }

    /**
     * 整个应用程序没有异常，启动之后才开始调用该方法
     * @param context
     */
    @Override
    public void running(ConfigurableApplicationContext context) {
        System.out.println("MySpringApplicationRunListener....running....");
    }

    /**
     * 程序出现异常，调用failed方法
     * @param context
     * @param exception
     */
    @Override
    public void failed(ConfigurableApplicationContext context, Throwable exception) {
        System.out.println("MySpringApplicationRunListener....failed....");
    }
}
------根目录下(resources/META-INF)
org.springframework.context.ApplicationContextInitializer=\
  com.cg.springbootprofile.listener.MyApplicationContextInitializer

org.springframework.context.ApplicationListener=\
  com.cg.springbootprofile.listener.MyApplicationListener

org.springframework.boot.SpringApplicationRunListener=\
  com.cg.springbootprofile.listener.MySpringApplicationRunListener
```









































