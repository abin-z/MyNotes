# Spring 系列框架

#### 框架是什么:

* 框架一般处在底层应用平台和高层业务逻辑之间的中间层
* 将可复用的组件功能进行重构----形成半成品
* 让设计人员或者开发人员将精力集中于核心业务
* 好处: 高内聚, 低耦合.



在企业级开发中有三个抽象层

1. **数据访问层(ORM-Mapper层)**: 负责数据库的交互

2. **业务处理层(service层)**: 用于控制层和数据访问层之间的业务处理(承前启后)

3. **控制层(controller层)**:
* 前端--------后端						//技术层面
  
* 前端--------中台--------后端       //用户的使用角色



**为啥使用spring框架**

采用原生态的Java语言开发项目: 可行,但是有不足

原生Java开发的不足: 代码量大,耦合度高, 维护性差,开发成本高,开发效率低

框架: 通过技术重构形成了一个半成品: 公共组件--重构,封装,代码的复用, 开发成本低



 ## Spring框架

**描述:**

Spring框架是一个[开放源代码](https://baike.baidu.com/item/开放源代码/114160)的[J2EE](https://baike.baidu.com/item/J2EE/110838)应用程序框架，由[Rod Johnson](https://baike.baidu.com/item/Rod Johnson/1423612)发起，是针对bean的生命周期进行管理的轻量级容器（lightweight container）。 Spring解决了开发者在J2EE开发中遇到的许多常见的问题，提供了功能强大IOC、[AOP](https://baike.baidu.com/item/AOP/1332219)及Web MVC等功能。Spring可以单独应用于构筑应用程序，也可以和Struts、Webwork、Tapestry等众多Web框架组合使用，并且可以与 Swing等[桌面应用程序](https://baike.baidu.com/item/桌面应用程序/2331979)AP组合。因此， Spring不仅仅能应用于J2EE应用程序之中，也可以应用于桌面应用程序以及小应用程序之中。Spring框架主要由七部分组成，分别是 Spring Core、 Spring AOP、 Spring ORM、 Spring DAO、Spring Context、 Spring Web和 Spring Web MVC。



**spring框架特征:**

1. **轻量级:** 体积小, 非侵入式, 非污染性
2. **容器:** bean的形式管理对象,对象之间的依赖
3. **控制反转IOC:** 降低代码耦合度, 依赖注入. **当某个角色(可能是**一个Java实例，调用者)需要另一个角色(另一个Java实例，被调用者)的协助时，在 传统的程序设计过程中，通常由调用者来创建被调用者的实例。但在Spring里，创建被调用者的工作不再由调用者来完成，因此称为控制反转;创建被调用者 实例的工作通常由Spring容器来完成，然后**注入**调用者，因此也称为**依赖注入**。
4. **面向切面编程AOP:**  允许通过分离应用的业务逻辑与系统级服务（例如审计（auditing）和[事务](https://baike.baidu.com/item/事务)（[transaction](https://baike.baidu.com/item/transaction)）管理）进行[内聚性](https://baike.baidu.com/item/内聚性)的开发, 让开发人员只关心业务逻辑
5. **依赖注入DI:** 所谓**依赖注入**，**是**指程序运行过程中，如果需要调用另一个对象协助时，无须在代码中创建被调用者，而是**依赖**于外部的**注入**。
6. **框架:** Spring可以将简单的[组件](https://baike.baidu.com/item/组件)配置、组合成为复杂的应用;



**spring是一个轻量级的==控制反转IOC==的==面向切面编程AOP==的开源框架**

**spring框架不足:**集合了很多的主流框架,每个组件都有各自的使用规范和要求, 于是产生了很多的配置文件. 维护成本高, 开发效率低, 配置文件安全性差,版本管理成本高



## spring MVC 

![image-20210920230956918](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210920230956918.png)

1. 基于B/S架构的互联网开发应用框架

2. 应用于前端和后端的交付:

   1. 请求------响应

   2. URL-----统一资源定位符

   3. 请求网址:  协议-----IP/域名------端口------请求字符串

   4. 请求字符串:  GET, POST

   5. 异步请求: Ajax 用于局部刷新(异步JavaScript和XML),提升用户体验

   6. json: JavaScript Object Notation

      * 一种轻量级的数据交换格式
      * 独立于任何编程语言的文本格式来存储数据
      * 易于机器解析和生成, 并有效的提升网络传输效率
      * 对象:     { }
      * 键值对 K---V :       "name":"张三"
      * 集合或者数组:   [] 
      * 对象和集合之间可以嵌套:     [{},{}]
      *  [{"name": "John Doe", "age": 18, "address": {"country" : "china", "zip-code": "10000"}}]



## ORM 对象关系映射

* **对象关系映射**（英语：**Object Relational Mapping**，简称**ORM**，或**O/RM**，或**O/R mapping**）.

* 是一种[程序设计](https://baike.baidu.com/item/程序设计)技术，用于实现[面向对象](https://baike.baidu.com/item/面向对象)编程语言里不同[类型系统](https://baike.baidu.com/item/类型系统/4273825)的[数据](https://baike.baidu.com/item/数据/5947370)之间的转换。
* 实体类(POJO, bean类)---------业务表
  * 属性(变量), 一般是指表中的字段 [最好名字相同]
  * 属性的类型(开发语言的类型), 参考数据库相关的类型
  * 业务方法: CRUD(增删改查)



## MyBatis

MyBatis参考网址:    https://mybatis.org/mybatis-3/zh/index.html

* 基于Java的数据持久层的开源框架

* MyBatis 是一款优秀的持久层框架，它支持定制化 SQL、存储过程以及高级映射。

* MyBatis 避免了几乎所有的 JDBC 代码和手动设置参数以及获取结果集。

* MyBatis 可以使用简单的 XML 或注解来配置和映射原生信息，将接口和 Java 的 POJOs(Plain Ordinary Java Object,普通的 Java对象)映射成数据库中的记录

* 比较主流的ORM产品, 半自动化的ORM产品 (了解另一款全自动化的ORM框架: Hibernate)



## MyBatis-Plus

[MyBatis-Plus ](https://github.com/baomidou/mybatis-plus)（简称 MP）是一个 [MyBatis](https://www.mybatis.org/mybatis-3/)的增强工具，在 MyBatis 的基础上只做增强不做改变，为简化开发、提高效率而生。

MyBatis-Plus参考网址:   https://mp.baomidou.com/

#### 特性:

- **无侵入**：只做增强不做改变，引入它不会对现有工程产生影响，如丝般顺滑
- **损耗小**：启动即会自动注入基本 CURD，性能基本无损耗，直接面向对象操作
- **强大的 CRUD 操作**：内置通用 Mapper、通用 Service，仅仅通过少量配置即可实现单表大部分 CRUD 操作，更有强大的条件构造器，满足各类使用需求
- **支持 Lambda 形式调用**：通过 Lambda 表达式，方便的编写各类查询条件，无需再担心字段写错
- **支持主键自动生成**：支持多达 4 种主键策略（内含分布式唯一 ID 生成器 - Sequence），可自由配置，完美解决主键问题
- **支持 ActiveRecord 模式**：支持 ActiveRecord 形式调用，实体类只需继承 Model 类即可进行强大的 CRUD 操作
- **支持自定义全局通用操作**：支持全局通用方法注入（ Write once, use anywhere ）
- **内置代码生成器**：采用代码或者 Maven 插件可快速生成 Mapper 、 Model 、 Service 、 Controller 层代码，支持模板引擎，更有超多自定义配置等您来使用
- **内置分页插件**：基于 MyBatis 物理分页，开发者无需关心具体操作，配置好插件之后，写分页等同于普通 List 查询
- **分页插件支持多种数据库**：支持 MySQL、MariaDB、Oracle、DB2、H2、HSQL、SQLite、Postgre、SQLServer 等多种数据库
- **内置性能分析插件**：可输出 SQL 语句以及其执行时间，建议开发测试时启用该功能，能快速揪出慢查询
- **内置全局拦截插件**：提供全表 delete 、 update 操作智能分析阻断，也可自定义拦截规则，预防误操作





## Spring Boot

Spring Boot是由Pivotal团队提供的全新[框架](https://baike.baidu.com/item/框架/1212667)，其设计目的是用来[简化](https://baike.baidu.com/item/简化/3374416)新[Spring](https://baike.baidu.com/item/Spring/85061)应用的初始搭建以及开发过程。该框架使用了特定的方式来进行配置，从而使开发人员不再需要定义样板化的配置。通过这种方式，Spring Boot致力于在蓬勃发展的快速应用开发领域(rapid application development)成为领导者。

* Spring Boot框架中还有两个非常重要的策略：**开箱即用**和**约定优于配置**。

**Spring Boot特点**

Spring Boot基于Spring4.0设计，不仅继承了Spring框架原有的优秀特性，而且还通过简化配置来进一步简化了Spring应用的整个搭建和开发过程。另外SpringBoot通过集成大量的框架使得依赖包的版本冲突，以及引用的不稳定性等问题得到了很好的解决。

**SpringBoot所具备的特征有：**

（1）可以创建独立的[Spring](https://baike.baidu.com/item/Spring/85061)应用程序，并且基于其Maven或Gradle插件，可以创建可执行的JARs和WARs；

（2）内嵌Tomcat或Jetty等Servlet容器；

（3）提供自动配置的“starter”项目对象模型（POMS）以简化[Maven](https://baike.baidu.com/item/Maven/6094909)配置；

（4）尽可能自动配置Spring容器；

（5）提供准备好的特性，如指标、健康检查和外部化配置;

（6）绝对没有代码生成，不需要XML配置;



## 感受Spring Boot的魅力



![基本结构](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/4B0E4EEC-3FE8-4613-BF1E-CA985F7879F1.png)





### 数据访问层的专业技能训练

2021-09.16  pm

1. #### pom.xml 加载MySQL驱动

![image-20210916144227354](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210916144227354.png)

2. #### 单独使用MyBatis: 添加相应的GAV坐标

![image-20210916144617443](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210916144617443.png)

提示: 如果使用的是MyBatis-plus依赖, 就不用添加MyBatis和MyBatis-spring, 防止冲突



3. #### 添加核心配置文件application.yml或者application.properties

**添加数据库连接:**

* 可以直接连接MySQL数据库
* 可以通过数据库中间件MyCat连接数据库

**数据源:**

1. 可以使用SpringBoot默认的数据源

2. 也可以使用阿里巴巴开源的Druid(德鲁伊)数据源



**如果使用ORM映射文件:**

  		1. 一般情况下接口名和.xml文件名应该一致

2. 需要在核心配置文件application.yml或者application.properties中添加映射文件位置

![image-20210916151140822](https://my-pic-bed.oss-cn-chengdu.aliyuncs.com/typora_picture/image-20210916151140822.png)







如果不使用ORM映射文件开发, 而使用注解开发, 则可以不加载或者不配置.xml文件

在实际开发中复杂的,动态的查询在ORM映射文件中配置, 简单的查询就使用注解

