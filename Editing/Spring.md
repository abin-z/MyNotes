# Spring笔记

# 一. 框架概述

### 1. 框架是什么:

* 框架一般处在底层应用平台和高层业务逻辑之间的中间层
* 将可复用的组件功能进行重构----形成半成品
* 让设计人员或者开发人员将精力集中于核心业务
* 好处: **高内聚, 低耦合.**



### 2. 三层架构

1. **数据访问层(ORM-Mapper层)**: 负责数据库的交互

2. **业务处理层(service层)**: 用于控制层和数据访问层之间的业务处理(承前启后)

3. **控制层(controller层)**: 用于处理用户请求

* 前端--------后端						//技术层面

* 前端--------中台--------后端       //用户的使用角色



### **3. 为啥使用spring框架**

采用原生态的Java语言开发项目: 可行,但是有不足

原生Java开发的不足: 代码量大,耦合度高, 维护性差,开发成本高,开发效率低

框架: 通过技术重构形成了一个半成品: 公共组件--重构,封装,代码的复用, 开发成本低

 # 二. Spring框架概述

Spring 是 Java EE 编程领域的一款轻量级的开源框架，由被称为“Spring 之父”的 Rod Johnson 于 2002 年提出并创立，它的目标就是要简化 Java 企业级应用程序的开发难度和周期。

Spring 自诞生以来备受青睐，一直被广大开发人员作为 Java 企业级应用程序开发的首选。时至今日，Spring 俨然成为了 Java EE 代名词，成为了构建 Java EE 应用的事实标准。

## 1. Spring框架架构

![Spring体系结构图](https://gitee.com/abin_z/pic_bed/raw/master/163550G63-0.png)


上图中包含了 Spring 框架的所有模块，这些模块可以满足一切企业级应用开发的需求，在开发过程中可以根据需求有选择性地使用所需要的模块。下面分别对这些模块的作用进行简单介绍。

### 1.1. Data Access/Integration（数据访问／集成）

数据访问／集成层包括 JDBC、ORM、OXM、JMS 和 Transactions 模块，具体介绍如下。

- **JDBC 模块**：提供了一个 JBDC 的样例模板，使用这些模板能消除传统冗长的 JDBC 编码还有必须的事务控制，而且能享受到 Spring 管理事务的好处。
- **ORM 模块**：提供与流行的“对象-关系”映射框架无缝集成的 API，包括 JPA、JDO、Hibernate 和 MyBatis 等。而且还可以使用 Spring 事务管理，无需额外控制事务。
- **OXM 模块**：提供了一个支持 Object /XML 映射的抽象层实现，如 JAXB、Castor、XMLBeans、JiBX 和 XStream。将 Java 对象映射成 XML 数据，或者将XML 数据映射成 Java 对象。
- **JMS 模块**：指 Java 消息服务，提供一套 “消息生产者、消息消费者”模板用于更加简单的使用 JMS，JMS 用于用于在两个应用程序之间，或分布式系统中发送消息，进行异步通信。
- **Transactions 事务模块**：支持编程和声明式事务管理。

### 1.2. Web 模块

Spring 的 Web 层包括 Web、Servlet、WebSocket 和 Portlet 组件，具体介绍如下。

- **Web 模块**：提供了基本的 Web 开发集成特性，例如多文件上传功能、使用的 Servlet 监听器的 IOC 容器初始化以及 Web 应用上下文。
- **Servlet 模块**：提供了一个 Spring MVC Web 框架实现。Spring MVC 框架提供了基于注解的请求资源注入、更简单的数据绑定、数据验证等及一套非常易用的 JSP 标签，完全无缝与 Spring 其他技术协作。
- **WebSocket 模块**：提供了简单的接口，用户只要实现响应的接口就可以快速的搭建 WebSocket Server，从而实现双向通讯。
- **Portlet 模块**：提供了在 Portlet 环境中使用 MVC 实现，类似 Web-Servlet 模块的功能。

### 1.3. Core Container（Spring 的核心容器）

Spring 的核心容器是其他模块建立的基础，由 Beans 模块、Core 核心模块、Context 上下文模块和 SpEL 表达式语言模块组成，没有这些核心容器，也不可能有 AOP、Web 等上层的功能。具体介绍如下。

- **Beans 模块**：提供了框架的基础部分，包括控制反转和依赖注入。
- **Core 核心模块**：封装了 Spring 框架的底层部分，包括资源访问、类型转换及一些常用工具类。
- **Context 上下文模块**：建立在 Core 和 Beans 模块的基础之上，集成 Beans 模块功能并添加资源绑定、数据验证、国际化、Java EE 支持、容器生命周期、事件传播等。ApplicationContext 接口是上下文模块的焦点。
- **SpEL 模块**：提供了强大的表达式语言支持，支持访问和修改属性值，方法调用，支持访问及修改数组、容器和索引器，命名变量，支持算数和逻辑运算，支持从 Spring 容器获取 Bean，它也支持列表投影、选择和一般的列表聚合等。

### 1.4. AOP、Aspects、Instrumentation 和 Messaging

在 Core Container 之上是 AOP、Aspects 等模块，具体介绍如下：

- **AOP 模块**：提供了面向切面编程实现，提供比如日志记录、权限控制、性能统计等通用功能和业务逻辑分离的技术，并且能动态的把这些功能添加到需要的代码中，这样各司其职，降低业务逻辑和通用功能的耦合。
- **Aspects 模块**：提供与 AspectJ 的集成，是一个功能强大且成熟的面向切面编程（AOP）框架。
- **Instrumentation 模块**：提供了类工具的支持和类加载器的实现，可以在特定的应用服务器中使用。
- **messaging 模块**：Spring 4.0 以后新增了消息（Spring-messaging）模块，该模块提供了对消息传递体系结构和协议的支持。

### 1.5. Test 模块

**Test 模块**：Spring 支持 Junit 和 TestNG 测试框架，而且还额外提供了一些基于 Spring 的测试功能，比如在测试 Web 框架时，模拟 Http 请求的功能。



## **2. spring框架核心**

Spring 框架是一个分层的、面向切面的 Java 应用程序的一站式轻量级解决方案，它是 Spring 技术栈的核心和基础，是为了解决企业级应用开发的复杂性而创建的。

Spring 有两个核心部分： IOC 和 AOP。

| 核心 | 描述                                                         |
| ---- | ------------------------------------------------------------ |
| IOC  | Inverse of Control 的简写，译为“控制反转”，指把创建对象过程交给 Spring 进行管理。 |
| AOP  | Aspect Oriented Programming 的简写，译为“面向切面编程”。  AOP 用来封装多个类的公共行为，将那些与业务无关，却为业务模块所共同调用的逻辑封装起来，减少系统的重复代码，降低模块间的耦合度。另外，AOP 还解决一些系统层面上的问题，比如日志、事务、权限等。 |


Spring 是一种基于 Bean 的编程技术，它深刻地改变着 Java 开发世界。Spring 使用简单、基本的 Java Bean 来完成以前只有 EJB 才能完成的工作，使得很多复杂的代码变得优雅和简洁，避免了 EJB 臃肿、低效的开发模式，极大的方便项目的后期维护、升级和扩展。

在实际开发中，服务器端应用程序通常采用三层体系架构，分别为表现层（web）、业务逻辑层（service）、持久层（dao）。

Spring 致力于 Java EE 应用各层的解决方案，对每一层都提供了技术支持。

- 在表现层提供了对 Spring MVC、Struts2 等框架的整合；
- 在业务逻辑层提供了管理事务和记录日志的功能；
- 在持久层还可以整合 MyBatis、Hibernate 和 JdbcTemplate 等技术，对数据库进行访问。

这充分地体现了 Spring 是一个全面的解决方案，对于那些已经有较好解决方案的领域，Spring 绝不做重复的事情。



## 3. Spring框架特点

#### **方便解耦，简化开发**

Spring 就是一个大工厂，可以将所有对象的创建和依赖关系的维护交给 Spring 管理。

#### **方便集成各种优秀框架**

Spring 不排斥各种优秀的开源框架，其内部提供了对各种优秀框架（如 Struts2、Hibernate、MyBatis 等）的直接支持。

#### **降低 Java EE API 的使用难度**

Spring 对 Java EE 开发中非常难用的一些 API（JDBC、JavaMail、远程调用等）都提供了封装，使这些 API 应用的难度大大降低。

#### **方便程序的测试**

Spring 支持 JUnit4，可以通过注解方便地测试 Spring 程序。

#### **AOP 编程的支持**

Spring 提供面向切面编程，可以方便地实现对程序进行权限拦截和运行监控等功能。

#### **声明式事务的支持**

只需要通过配置就可以完成对事务的管理，而无须手动编程。

**spring是一个轻量级的==控制反转IOC==的==面向切面编程AOP==的开源框架**

**spring框架不足:**集合了很多的主流框架,每个组件都有各自的使用规范和要求, 于是产生了很多的配置文件. 维护成本高, 开发效率低, 配置文件安全性差,版本管理成本高



## 4. IoC  控制反转

IoC 是 Inversion of Control 的简写，译为“控制反转”，**它不是一门技术，而是一种设计思想，是一个重要的面向对象编程法则，能够指导我们如何设计出松耦合、更优良的程序。**

Spring 通过 IoC 容器来管理所有 Java 对象的实例化和初始化，控制对象与对象之间的依赖关系。我们将由 IoC 容器管理的 Java 对象称为 Spring Bean，它与使用关键字 new 创建的 Java 对象没有任何区别。

IoC 容器是 Spring 框架中最重要的核心组件之一，它贯穿了 Spring 从诞生到成长的整个过程。

### 4.1.控制反转（IoC）

在传统的 Java 应用中，一个类想要调用另一个类中的属性或方法，通常会先在其代码中通过 new Object() 的方式将后者的对象创建出来，然后才能实现属性或方法的调用。为了方便理解和描述，我们可以将前者称为“调用者”，将后者称为“被调用者”。也就是说，调用者掌握着被调用者对象创建的控制权。

但在 Spring 应用中，Java 对象创建的控制权是掌握在 IoC 容器手里的，其大致步骤如下。

1. **==开发人员通过 XML 配置文件、注解、Java 配置类==等方式，对 Java 对象进行定义，例如在 XML 配置文件中使用 <bean> 标签、在 Java 类上使用 @Component 注解等。**
2. **Spring 启动时，==IoC 容器会自动根据对象定义，将这些对象创建并管理起来==。这些被 IoC 容器创建并管理的对象被称为 Spring Bean。**
3. **当我们想要使用某个 Bean 时，==可以直接从 IoC 容器中获取==（例如通过 ApplicationContext 的 getBean() 方法），而不需要手动通过代码（例如 new Object() 的方式）创建。**


IoC 带来的最大改变不是代码层面的，而是从思想层面上发生了“主从换位”的改变。原本调用者是主动的一方，它想要使用什么资源就会主动出击，自己创建；但在 Spring 应用中，IoC 容器掌握着主动权，调用者则变成了被动的一方，被动的等待 IoC 容器创建它所需要的对象（Bean）。

这个过程在职责层面发生了控制权的反转，把原本调用者通过代码实现的对象的创建，反转给 IoC 容器来帮忙实现，因此我们将这个过程称为 Spring 的“控制反转”。

**在Spring 开发中，由IOC容器控制对象的创建、初始化、销毁等。这也就实现了对象控制权的反转，由我们对对象的控制转变成了Spring IOC 对对象的控制。**

### 4.2. IoC 的工作原理

在 Java 软件开发过程中，系统中的各个对象之间、各个模块之间、软件系统和硬件系统之间，或多或少都存在一定的耦合关系。

若一个系统的耦合度过高，那么就会造成难以维护的问题，但完全没有耦合的代码几乎无法完成任何工作，这是由于几乎所有的功能都需要代码之间相互协作、相互依赖才能完成。因此我们在程序设计时，所秉承的思想一般都是在不影响系统功能的前提下，最大限度的降低耦合度。

IoC 底层通过工厂模式、Java 的反射机制、XML 解析等技术，将代码的耦合度降低到最低限度，其主要步骤如下。

1. 在配置文件（例如 Bean.xml）中，对各个对象以及它们之间的依赖关系进行配置；
2. 我们可以把 IoC 容器当做一个工厂，这个工厂的产品就是 Spring Bean；
3. 容器启动时会加载并解析这些配置文件，得到对象的基本信息以及它们之间的依赖关系；
4. IoC 利用 Java 的反射机制，根据类名生成相应的对象（即 Spring Bean），并根据依赖关系将这个对象注入到依赖它的对象中。


由于对象的基本信息、对象之间的依赖关系都是在配置文件中定义的，并没有在代码中紧密耦合，因此即使对象发生改变，我们也只需要在配置文件中进行修改即可，而无须对 Java 代码进行修改，这就是 Spring IoC 实现解耦的原理。

### 4.3. IoC 容器的两种实现

IoC 思想基于 IoC 容器实现的，IoC 容器底层其实就是一个 Bean 工厂。Spring 框架为我们提供了两种不同类型 IoC 容器，它们分别是 BeanFactory 和 ApplicationContext。

#### BeanFactory

BeanFactory 是 IoC 容器的基本实现，也是 Spring 提供的最简单的 IoC 容器，它提供了 IoC 容器最基本的功能，由 org.springframework.beans.factory.BeanFactory 接口定义。

BeanFactory 采用懒加载（lazy-load）机制，容器在加载配置文件时并不会立刻创建 Java 对象，只有程序中获取（使用）这个对对象时才会创建。

下面我们通过一个实例演示，来演示下 BeanFactory 的使用。

1. 在 HelloSpring 项目中，将 MainApp 的代码修改为使用 BeanFactory 获取 HelloWorld 的对象，具体代码如下。

```Java
public static void main(String[] args) { 
    BeanFactory context = new ClassPathXmlApplicationContext("Beans.xml");
    HelloWorld obj = context.getBean("helloWorld", HelloWorld.class);
    obj.getMessage();
}
```

2. 运行 MainApp.java，控制台输出如下。

```
message : Hello World!
```

> 注意：BeanFactory 是 Spring 内部使用接口，通常情况下不提供给开发人员使用。 

#### ApplicationContext

**ApplicationContext 是 BeanFactory 接口的子接口**，是对 BeanFactory 的扩展。ApplicationContext 在 BeanFactory 的基础上增加了许多企业级的功能，例如 AOP（面向切面编程）、国际化、事务支持等。

ApplicationContext 接口有两个常用的实现类，具体如下表。

| 实现类                          | 描述                                                         | 示例代码                                                     |
| ------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ClassPathXmlApplicationContext  | 加载类路径 ClassPath 下指定的 XML 配置文件，并完成 ApplicationContext 的实例化工作 | ApplicationContext applicationContext = new ClassPathXmlApplicationContext(String configLocation); |
| FileSystemXmlApplicationContext | 加载指定的文件系统路径中指定的 XML 配置文件，并完成 ApplicationContext 的实例化工作 | ApplicationContext applicationContext = new FileSystemXmlApplicationContext(String configLocation); |

> 在上表的示例代码中，参数 configLocation 用于指定 Spring 配置文件的名称和位置，如 Beans.xml。
>
> ApplicationContext 容器包括 BeanFactory 容器的所有功能，所以通常不建议使用BeanFactory。BeanFactory 仍然可以用于轻量级的应用程序，如移动设备或基于 applet 的应用程序，其中它的数据量和速度是显著。

下面我们就通过一个实例，来演示 ApplicationContext 的使用。

1. 修改 HelloSpring 项目 MainApp 类中 main() 方法的代码，具体代码如下。

```Java
public static void main(String[] args) {    
    //使用 FileSystemXmlApplicationContext 加载指定路径下的配置文件 Bean.xml    
    BeanFactory context = new FileSystemXmlApplicationContext("D:\\eclipe workspace\\spring workspace\\HelloSpring\\src\\Beans.xml"); 
    HelloWorld obj = context.getBean("helloWorld", HelloWorld.class);   
    obj.getMessage();
}
```

2. 运行 MainApp.java，控制台输出如下。

```
message : Hello World!
```



## 5. DI  依赖注入

依赖注入（Dependency Injection，简写为 DI）是 Martin Fowler 在 2004 年在对“控制反转”进行解释时提出的。Martin Fowler 认为“控制反转”一词很晦涩，无法让人很直接的理解“到底是哪里反转了”，因此他建议使用“依赖注入”来代替“控制反转”。

**在面向对象中，对象和对象之间是存在一种叫做“依赖”的关系**。简单来说，依赖关系就是在一个对象中需要用到另外一个对象，即对象中存在一个属性，该属性是另外一个类的对象。

例如，有一个名为 B 的 Java 类，它的代码如下。

```Java
public class B { 
	String name; 
    A a;
    }
```

从代码可以看出，B 中存在一个 A 类型的对象属性 a，此时我们就可以说 B 的对象依赖于对象 a。而依赖注入就是就是基于这种“依赖关系”而产生的。

**我们知道，控制反转核心思想就是由 Spring 负责对象的创建，管理。在对象创建过程中，Spring 会自动根据依赖关系，将它依赖的对象注入到当前对象中，这就是所谓的“依赖注入”。**

依赖注入本质上是的一种，只不过这个属性是一个对象属性而已。依赖注入又分为**构造器注入**和**setter注入**。

假设你有一个包含文本编辑器组件的应用程序，并且你想要提供拼写检查。标准代码看起来是这样的：

```Java
public class TextEditor {
   private SpellChecker spellChecker;  
   public TextEditor() {
      spellChecker = new SpellChecker();			//在TextEditor内部直接将SpellChecker new出来
   }
}
```

在这里我们所做的就是创建一个 TextEditor 和 SpellChecker 之间的依赖关系。**而在控制反转IoC的场景中**，我们会这样做：

```Java
public class TextEditor {
   private SpellChecker spellChecker;
   public TextEditor(SpellChecker spellChecker) {		//并不直接new，而是通过向构造器传SpellChecker参数
      this.spellChecker = spellChecker;
   }
}
```

**在这里，TextEditor 不应该担心 SpellChecker 的实现。SpellChecker 将会独立实现，并且在 TextEditor 实例化的时候将提供给 TextEditor，整个过程是由 Spring 框架的控制。**

在这里，我们已经从 TextEditor 中删除了全面控制，并且把它保存到其他地方（即 XML 配置文件），且依赖关系（即 SpellChecker 类）通过**类构造函数**被注入到 TextEditor 类中。因此，控制流通过依赖注入（DI）已经“反转”，因为你已经有效地委托依赖关系到一些外部系统。



依赖注入的**第二种方法**是通过 TextEditor 类的 **Setter 方法**，我们将创建 SpellChecker 实例，该实例将被用于调用 setter 方法来初始化 TextEditor 的属性。

因此，DI 主要有两种变体和下面的两个子章将结合实例涵盖它们：

| 序号 | 依赖注入类型 & 描述                                          |
| ---- | ------------------------------------------------------------ |
| 1    | Constructor-based dependency injection 当容器**调用带有多个参数的构造函数类时，实现基于构造函数的 DI，每个代表在其他类中的一个依赖关系。** |
| 2    | Setter-based dependency injection基于 setter 方法的 DI 是**通过在调用无参数的构造函数或无参数的静态工厂方法实例化 bean 之后容器调用 beans 的 setter 方法来实现的。** |

你页可以混合这两种方法，部分使用构造函数和基于 setter 方法的 DI，**一般存在着==有强制性依存关系依赖的使用构造函数==和==有可选依赖关系的使用 setter==是一个好的做法。**



## 6. AOP 面向切面编程：

Spring 框架的一个关键组件是**面向切面的程序设计（AOP）**框架。一个程序中跨越多个点的功能被称为**横切关注点**，这些横切关注点在概念上独立于应用程序的业务逻辑。有各种各样常见的很好的关于方面的例子，比如日志记录、声明性事务、安全性，和缓存等等。

在 OOP 中模块化的关键单元是类，而在 AOP 中模块化的关键单元是方面。AOP 帮助你将横切关注点从它们所影响的对象中分离出来，然而依赖注入帮助你将你的应用程序对象从彼此中分离出来。

Spring 框架的 AOP 模块提供了面向方面的程序设计实现，可以定义诸如方法拦截器和切入点等，从而使实现功能的代码彻底的解耦出来。使用源码级的元数据，可以用类似于 .Net 属性的方式合并行为信息到代码中。

### 6.1. AOP 的目的

AOP 即 Aspect Oriented Program 面向切面编程，在面向切面编程的思想里面，把功能分为核心业务功能，和周边功能。

- **所谓的核心业务**，比如登陆，增加数据，删除数据都叫核心业务
- **所谓的周边功能**，比如性能统计，日志，事务管理等等

周边功能在 Spring 的面向切面编程AOP思想里，即被定义为切面

在面向切面编程AOP的思想里面，核心业务功能和切面功能分别独立进行开发，然后把切面功能和核心业务功能 "编织" 在一起，这就叫AOP

AOP能够将那些与业务无关，**却为业务模块所共同调用的逻辑或责任（例如事务处理、日志管理、权限控制等）封装起来**，便于**减少系统的重复代码**，**降低模块间的耦合度**，并**有利于未来的可拓展性和可维护性**。

### 6.2. AOP 当中的概念：

- 切入点（Pointcut）
   在哪些类，哪些方法上切入（**where**）
- 通知（Advice）
   在方法执行的什么实际（**when:**方法前/方法后/方法前后）做什么（**what:**增强的功能）
- 切面（Aspect）
   切面 = 切入点 + 通知，通俗点就是：**在什么时机，什么地方，做什么增强！**
- 织入（Weaving）
   把切面加入到对象，并创建出代理对象的过程。（由 Spring 来完成）

# 三. spring framework

## 1. spring快速入门

1. 导入坐标
2. 创建Bean
3. 创建applicationContext.xml
4. 在配置文件中进行配置
5. 创建ApplicationContext对象getBean

pom.xml 添加spring相关Maven依赖:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>
  <groupId>org.example</groupId>
  <artifactId>SpringDemo</artifactId>
  <version>1.0-SNAPSHOT</version>
  <properties>
    <maven.compiler.source>8</maven.compiler.source>
    <maven.compiler.target>8</maven.compiler.target>
  </properties>
  <dependencies>
    <dependency>
      <groupId>org.springframework</groupId>
      <artifactId>spring-context</artifactId>
      <version>5.1.0.RELEASE</version>
    </dependency>
  </dependencies>
</project>
```

Dao层模拟:

```Java
public class UserDaoImpl implements UserDao {
  @Override
  public void save() {
    System.out.println("saveDao 被调用!!");
  }
}
```

Service层:

```Java
public class UserServiceImpl implements UserService {

  @Override
  public void saveUser() {
    ApplicationContext appContext = new ClassPathXmlApplicationContext("ApplicationContext.xml");
    UserDao userDao = (UserDao) appContext.getBean("userDao");
    userDao.save();
  }
}
```

Controller层:

```Java
public class UserController {
  public static void main(String[] args) {
    ApplicationContext applicationContext = new ClassPathXmlApplicationContext("ApplicationContext.xml");
    UserService userService = (UserService) applicationContext.getBean("userService");
    userService.saveUser();
  }
}
```

`ApplicationContext.xml`配置Bean

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
  <bean id="userDao" class="com.abin.dao.impl.UserDaoImpl"/>
  <bean id="userService" class="com.abin.service.impl.UserServiceImpl"/>
</beans>
```



## 2. spring IoC容器

由 Spring IoC 容器管理的对象称为 Bean，Bean 根据 Spring 配置文件中的信息创建。

我们可以把 Spring IoC 容器看作是一个大工厂，Bean 相当于工厂的产品。如果希望这个大工厂生产和管理 Bean，就需要告诉容器需要哪些 Bean，以哪种方式装配。

### 2.1 Bean的定义

Spring IoC 容器完全由实际编写的配置元数据的格式解耦。有下面三个重要的方法把配置元数据提供给 Spring 容器：

- 基于 XML 的配置文件
- 基于注解的配置
- 基于 Java 的配置

用于配置对象交由Spring来创建,spring容器管理。
**==默认情况下它调用的是类中的无参构造函数==，如果没有无参构造函数如则不能创建成功。**

通常情况下，Spring 的配置文件都是使用 XML 格式的。XML 配置文件的根元素是 <beans>，该元素包含了多个子元素 <bean>。每一个 <bean> 元素都定义了一个 Bean，并描述了该 Bean 是如何被装配到 Spring 容器中的。

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
   http://www.springframework.org/schema/beans/spring-beans-3.0.xsd">
    <bean id="helloWorld" class="net.biancheng.c.HelloWorld">
        <property name="message" value="Hello World!"/>
    </bean>
</beans>
```

在 XML 配置的<beans> 元素中可以包含多个属性或子元素，常用的属性或子元素如下表所示。

| 属性名称        | 描述                                                         |
| --------------- | ------------------------------------------------------------ |
| id              | **Bean 的唯一标识符**，Spring IoC 容器对 Bean 的配置和管理都通过该属性完成。id 的值必须以字母开始，可以使用字母、数字、下划线等符号。 |
| name            | 该属性表示 Bean 的名称，我们可以通过 name 属性为同一个 Bean 同时指定多个名称，每个名称之间用逗号或分号隔开。Spring 容器可以通过 name 属性配置和管理容器中的 Bean。 |
| class           | **该属性指定了 Bean 的具体实现类，==它必须是一个完整的类名，即类的全限定名。==** |
| scope           | 表示 Bean 的作用域，属性值可以为 singleton（单例）、prototype（原型）、request、session 和 global Session。默认值是 singleton。 |
| constructor-arg | <bean> 元素的子元素，我们可以通过该元素，将构造参数传入，以实现 Bean 的实例化。该元素的 index 属性指定构造参数的序号（从 0 开始），type 属性指定构造参数的类型。 |
| property        | <bean>元素的子元素，用于调用 Bean 实例中的 setter 方法对属性进行赋值，从而完成属性的注入。该元素的 name 属性用于指定 Bean 实例中相应的属性名。 |
| ref             | <property> 和 <constructor-arg> 等元素的子元素，用于指定对某个 Bean 实例的引用，即 <bean> 元素中的 id 或 name 属性。 |
| value           | <property> 和 <constractor-arg> 等元素的子元素，用于直接指定一个常量值。 |
| list            | 用于封装 List 或数组类型的属性注入。                         |
| set             | 用于封装 Set 类型的属性注入。                                |
| map             | 用于封装 Map 类型的属性注入。                                |
| entry           | <map> 元素的子元素，用于设置一个键值对。其 key 属性指定字符串类型的键值，ref 或 value 子元素指定其值。 |
| init-method     | 容器加载 Bean 时调用该方法，类似于 Servlet 中的 init() 方法  |
| destroy-method  | 容器删除 Bean 时调用该方法，类似于 Servlet 中的 destroy() 方法。该方法只在 scope=singleton 时有效 |
| lazy-init       | 懒加载，值为 true，容器在首次请求时才会创建 Bean 实例；值为 false，容器在启动时创建 Bean 实例。该方法只在 scope=singleton 时有效 |

![img](https://gitee.com/abin_z/pic_bed/raw/master/c8e2277ef063f7249b5f71167dedf8d7.png)

![image-20220331162358827](https://gitee.com/abin_z/pic_bed/raw/master/image-20220331162358827.png)



### 2.2 Bean的作用域

当在 Spring 中定义一个 bean 时，你必须声明该 bean 的作用域的选项。例如，为了强制 Spring 在每次需要时都产生一个新的 bean 实例，你应该声明 bean 的作用域的属性为 **prototype**。同理，如果你想让 Spring 在每次需要时都返回同一个bean实例，你应该声明 bean 的作用域的属性为 **singleton**。

Spring 框架支持以下五个作用域，分别为 singleton、prototype、request、session 和 global session，5种作用域说明如下所示，

注意，如果你使用 web-aware ApplicationContext 时，其中三个是可用的。   

| 作用域         | 描述                                                         |
| -------------- | ------------------------------------------------------------ |
| **singleton**  | 在spring IoC容器仅存在一个Bean实例，Bean以单例方式存在，默认就是singleton |
| **prototype**  | 每次从容器中调用Bean时，都返回一个新的实例，即每次调用getBean()时，相当于执行newXxxBean() |
| request        | 每次HTTP请求都会创建一个新的Bean，该作用域仅适用于WebApplicationContext环境 |
| session        | 同一个HTTP Session共享一个Bean，不同Session使用不同的Bean，仅适用于WebApplicationContext环境 |
| global-session | 一般用于Portlet应用环境，该作用域仅适用于WebApplicationContext环境 |

![image-20220329175726462](https://gitee.com/abin_z/pic_bed/raw/master/image-20220329175726462.png)

#### singleton 作用域

==**singleton 是默认的作用域**==，也就是说，当定义 Bean 时，如果没有指定作用域配置项，则 Bean 的作用域被默认为 singleton。

当一个bean的作用域为 Singleton，那么 Spring IoC 容器中只会存在一个共享的 bean 实例，并且所有对 bean 的请求，只要 id 与该 bean 定义相匹配，则只会返回 bean 的同一实例。

也就是说，当将一个 bean 定义设置为 singleton 作用域的时候，Spring IoC 容器只会创建该 bean 定义的唯一实例。

Singleton 是单例类型，就是**==在创建起容器时就同时自动创建了一个 bean 的对象==，不管你是否使用，他都存在了，每次获取到的对象都是同一个对象**。注意，Singleton 作用域是 Spring 中的缺省作用域。你可以在 bean 的配置文件中设置作用域的属性为 singleton，如下所示：

```xml
<!-- A bean definition with singleton scope -->
<bean id="..." class="..." scope="singleton">
    <!-- collaborators and configuration for this bean go here -->
</bean>
```

#### prototype 作用域

**==当一个 bean 的作用域为 Prototype，表示一个 bean 定义对应多个对象实例==**。Prototype 作用域的 bean 会导致在每次对该 bean 请求（将其注入到另一个 bean 中，或者以程序的方式调用容器的 getBean() 方法）时都会创建一个新的 bean 实例。Prototype 是原型类型，**==它在我们创建容器的时候并没有实例化，而是当我们获取bean的时候才会去创建一个对象，而且我们每次获取到的对象都不是同一个对象==**。根据经验，对有状态的 bean 应该使用 prototype 作用域，而对无状态的bean则应该使用 singleton 作用域。

为了定义 prototype 作用域，你可以在 bean 的配置文件中设置作用域的属性为 prototype，如下所示：

```xml
<!-- A bean definition with singleton scope -->
<bean id="..." class="..." scope="prototype">
   <!-- collaborators and configuration for this bean go here -->
</bean>
```

```xml
  <bean id="userDao" class="com.abin.dao.impl.UserDaoImpl" scope="singleton"/>   <!-- 单例的 -->
  <bean id="userService" class="com.abin.service.impl.UserServiceImpl" scope="prototype"/>   <!-- 多例的 -->
```

`scope="singleton"`表示单例模式, 每次请求的都是同一个对象, 会在类加载的时候就创建该对象

`scope="prototype"`表示多例模式, 每次请求的都是不同的对象, 只有在getBean时候被创建



### 2.3 Bean生命周期

理解 Spring bean 的生命周期很容易。当一个 bean 被实例化时，它可能需要执行一些初始化使它转换成可用状态。同样，当 bean 不再需要，并且从容器中移除时，可能需要做一些清除工作。

**(1)当scope 的取值为singleton时**

- Bean的实例化个数：只有1个

- Bean的实例化时机：**当Spring核心文件被加载时，实例化配置的Bean实例**

- Bean的生命周期：

  ```
  	对象创建：当应用加载，创建容器时，对象就被创建了
  	对象运行：只要容器在，对象一直活着
  	对象销毁：当应用卸载，销毁容器时，对象就被销毁了
  ```

  

**(2)当scope 的取值为prototype时**

- Bean的实例化个数：多个

- Bean的实例化时机：**当调用getBean()方法时实例化Bean**

- Bean的生命周期:

  	对象创建：当使用对象时，创建新的对象实例
  	对象运行：只要对象在使用中，就一直活着
  	对象销毁：当对象长时间不用时，被Java的垃圾回收器回收了

为了定义安装和拆卸一个 bean，我们只要声明带有 **init-method** 和/或 **destroy-method** 参数的 。init-method 属性指定一个方法，在实例化 bean 时，立即调用该方法。同样，destroy-method 指定一个方法，只有从容器中移除 bean 之后，才能调用该方法。

Bean的生命周期可以表达为：Bean的定义——Bean的初始化——Bean的使用——Bean的销毁

#### 初始化回调

*org.springframework.beans.factory.InitializingBean* 接口指定一个单一的方法：

```Java
void afterPropertiesSet() throws Exception;
```

因此，你可以简单地实现上述接口和初始化工作可以在 afterPropertiesSet() 方法中执行，如下所示：

```Java
public class ExampleBean implements InitializingBean {		//实现InitializingBean接口
   public void afterPropertiesSet() {
      // do some initialization work
   }
}
```

在基于 XML 的配置元数据的情况下，你可以使用 **init-method** 属性来指定带有 void 无参数方法的名称。例如：

```Java
<bean id="exampleBean" class="examples.ExampleBean" init-method="init"/>
```

下面是类的定义：

```Java
public class ExampleBean {
   public void init() {
      // do some initialization work
   }
}
```

#### 销毁回调

*org.springframework.beans.factory.DisposableBean* 接口指定一个单一的方法：

```Java
void destroy() throws Exception;
```

因此，你可以简单地实现上述接口并且结束工作可以在 destroy() 方法中执行，如下所示：

```Java
public class ExampleBean implements DisposableBean {		//实现DisposableBean接口
   public void destroy() {
      // do some destruction work
   }
}
```

在基于 XML 的配置元数据的情况下，你可以使用 **destroy-method** 属性来指定带有 void 无参数方法的名称。例如：

```Java
<bean id="exampleBean" class="examples.ExampleBean" destroy-method="destroy"/>
```

下面是类的定义：

```Java
public class ExampleBean {
   public void destroy() {
      // do some destruction work
   }
}
```

如果你在非 web 应用程序环境中使用 Spring 的 IoC 容器；例如在丰富的客户端桌面环境中；那么在 JVM 中你要注册关闭 hook。这样做可以确保正常关闭，为了让所有的资源都被释放，可以在单个 bean 上调用 destroy 方法。

建议: 不要使用 InitializingBean 或者 DisposableBean 的回调方法，使用init-method和destroy-method, 因为 XML 配置在命名方法上提供了极大的灵活性。

- init-method:指定类中的初始化方法名称
- destroy-method:指定类中销毁方法名称

Dao添加相应的方法:

```Java
public class UserDaoImpl implements UserDao {
  @Override
  public void save() {
    System.out.println("saveDao 被调用!!");
  }

  @Override
  public void init() {
    System.out.println("init初始化方法被调用");
  }

  @Override
  public void destroy() {
    System.out.println("destroy初始化方法被调用");
  }
}
```

需要配置xml文件:

```xml
<bean id="userDao" class="com.abin.dao.impl.UserDaoImpl" init-method="init" destroy-method="destroy"/>   <!-- 单例的 -->
```



### 2.4 Bean的后置处理器

Bean 后置处理器允许在调用初始化方法前后对 Bean 进行额外的处理。

BeanPostProcessor 接口也被称为后置处理器，通过该接口可以自定义调用初始化前后执行的操作方法。

BeanPostProcessor 接口源码如下：

```Java
public interface BeanPostProcessor {    
    Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException;  
    Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException;
}
```


该接口中包含了两个方法：

- postProcessBeforeInitialization() 方法：在 Bean 实例化、属性注入后，初始化前调用。
- postProcessAfterInitialization() 方法：在 Bean 实例化、属性注入、初始化都完成后调用。


当需要添加多个后置处理器实现类时，默认情况下 Spring 容器会根据后置处理器的定义顺序来依次调用。也可以通过实现 Ordered 接口的 getOrder 方法指定后置处理器的执行顺序。该方法返回值为整数，默认值为 0，取值越大优先级越低。

可以配置多个 `BeanPostProcessor `接口，通过设置 `BeanPostProcessor `实现的` Ordered `接口提供的` order` 属性来控制这些` BeanPostProcessor` 接口的执行顺序。

`BeanPostProcessor` 可以对` bean`（或对象）实例进行操作，这意味着 `Spring IoC` 容器实例化一个 `bean` 实例，然后 `BeanPostProcessor` 接口进行它们的工作。

**注意：**

`ApplicationContext` 会自动检测由 `BeanPostProcessor` 接口的实现定义的 `bean`，注册这些` bean` 为后置处理器，然后通过在容器中创建` bean`，在适当的时候调用它。

在你自定义的` BeanPostProcessor` 接口实现类中，要实现以下的两个抽象方法 `BeanPostProcessor.postProcessBeforeInitialization(Object, String)` 和 `BeanPostProcessor.postProcessAfterInitialization(Object, String)` 和，注意命名要准确

否则会出现： `“ The type InitHelloWorld must implement the inherited abstract method BeanPostProcessor.postProcessBeforeInitialization(Object, String) ”`之类的错误

[Bean后置处理器案例代码](https://www.w3cschool.cn/wkspring/xs181ici.html)



### 2.5 Bean的定义继承

在 Spring 中，Bean 和 Bean 之间也存在继承关系。我们将被继承的 Bean 称为父 Bean，将继承父 Bean 配置信息的 Bean 称为子 Bean。

bean 定义可以包含很多的配置信息，包括构造函数的参数，属性值，容器的具体信息例如初始化方法，静态工厂方法名，等等。

子 bean 的定义继承父定义的配置数据。子定义可以根据需要重写一些值，或者添加其他值。

**Spring Bean 定义的继承与 Java 类的继承无关，但是继承的概念是一样的**。你可以定义一个父 bean 的定义作为模板和其他子 bean 就可以从父 bean 中继承所需的配置。

Spring Bean 的定义中可以包含很多配置信息，例如构造方法参数、属性值。子 Bean 既可以继承父 Bean 的配置数据，也可以根据需要重写或添加属于自己的配置信息。

在 Spring XML 配置中，我们通过子 Bean 的 parent 属性来指定需要继承的父 Bean，配置格式如下。

```xml
<!--父Bean-->
<bean id="parentBean" class="xxx.xxxx.xxx.ParentBean" >    
    <property name="xxx" value="xxx"></property>    
    <property name="xxx" value="xxx"></property>
</bean> 
<!--子Bean--> 
<bean id="childBean" class="xxx.xxx.xxx.ChildBean" parent="parentBean"></bean>
```

[Bean的继承案例](https://www.w3cschool.cn/wkspring/tydj1ick.html)



## 3. spring依赖注入

#### 3.1 Dependency Injection

依赖注入（Dependency Injection）：它是Spring框架核心IOC的具体实现。

每个基于应用程序的 Java 都有几个对象，由这些对象一起工作来呈现出终端用户所看到的工作的应用程序。当编写一个复杂的 Java 应用程序时，应用程序类应该尽可能独立于其他 Java 类来增加这些类重用的可能性，并且在做单元测试时，测试独立于其他类的独立性。`依赖注入（或有时称为布线）`有助于把这些类粘合在一起，同时保持他们独立。

假设你有一个需要用户信息访问的应用程序，并且你需要查询数据库。标准代码看起来是这样的：

```Java
public class UserService {
   private UserDao userDao;  
   public UserService() {
      userDao = new UserDao();
   }
}
```

在这里我们所做的就是创建一个 UserService和 UserDao之间的依赖关系。而在控制反转IoC的场景中，我们会这样做：

```Java
public class UserService {
   private UserDao userDao;
   public UserService(UserDao userDao) {
      this.userDao = userDao;
   }
}
```

在这里，UserService不应该担心 UserDao的实现。UserService 将会独立实现，并且在 UserService 实例化的时候将UserDao提供给 UserService，整个过程是由 Spring 框架的控制。

在这里，我们已经从 UserService中删除了全面控制，并且把它保存到其他地方（即 XML 配置文件），且依赖关系（即 UserDao类）通过**类构造函数**被注入到 UserService类中。因此，控制流通过依赖注入（DI）已经“反转”，因为你已经有效地委托依赖关系到一些外部系统。

#### 3.2 案例

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
  <bean id="userDao" class="com.abin.dao.impl.UserDaoImpl" init-method="init" destroy-method="destroy"/>   <!-- 单例的 -->
  <bean id="userService" class="com.abin.service.impl.UserServiceImpl"></bean>
</beans>
```

UserController模拟:

```Java
public class UserController {
  public static void main(String[] args) {
    ClassPathXmlApplicationContext applicationContext = new ClassPathXmlApplicationContext("ApplicationContext.xml");
    UserService userService = (UserService) applicationContext.getBean("userService");
    userService.saveUser();
    applicationContext.registerShutdownHook();
  }
}
```

UserService模拟:

```Java
public class UserServiceImpl implements UserService {
  private  UserDao userDao;
  @Override
  public void saveUser() {
    ApplicationContext appContext = new ClassPathXmlApplicationContext("ApplicationContext.xml");
    UserDao userDao = (UserDao) appContext.getBean("userDao");
    userDao.save();
  }
}
```

UserDao模拟:

```Java
public class UserDaoImpl implements UserDao {
  @Override
  public void save() {
    System.out.println("saveDao 被调用!!");
  }
  @Override
  public void init() {
    System.out.println("init初始化方法被调用");
  }
  @Override
  public void destroy() {
    System.out.println("destroy初始化方法被调用");
  }
}
```

上述代码实际上存在如下的问题:  UserService和UserDao都在容器中,但是我们是手动注入的.

![image-20220331170620554](https://gitee.com/abin_z/pic_bed/raw/master/image-20220331170620554.png)

因为UserService和UserDao都在Spring容器中，而最终程序直接使用的是UserService，所以可以在Spring容器中，将UserDao设置到UserService内部。

#### 3.3 Setter方法注入

我们可以使用Setter方法让spring的IOC容器帮我们依赖注入

```Java
public class UserServiceImpl implements UserService {
  private  UserDao userDao;

  public void setUserDao(UserDao userDao) {		// 添加Setter函数
    this.userDao = userDao;
  }

  @Override
  public void saveUser() {
    userDao.save();		// 配置好后可以直接使用, spring会自动注入对应的属性
  }
}
```

在XML文件中进行配置:

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">

  <bean id="userDao" class="com.abin.dao.impl.UserDaoImpl" init-method="init" destroy-method="destroy"/>   <!-- 单例的 -->
  <bean id="userService" class="com.abin.service.impl.UserServiceImpl">
      <property name="userDao" ref="userDao"></property>	<!--基于setter方法注入-->
  </bean>
</beans>
```

![image-20220331171258075](https://gitee.com/abin_z/pic_bed/raw/master/image-20220331171258075.png)

在编写程序时，通过控制反转，把对象的创建交给了Spring，但是代码中不可能出现没有依赖的情况。IOC 解耦只是降低他们的依赖关系，但不会消除。例如：业务层仍会调用持久层的方法。
那这种业务层和持久层的依赖关系，在使用Spring之后，就让Spring来维护了。简单的说，就是坐等框架把持久层对象传入业务层，而不用我们自己去获取。

依赖注入有两种方式: **一种是基于Setter注入, 另外一种是基于构造器注入**

#### 3.4 有参构造器注入

通过有参构造器注入: 

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans.xsd">
  <bean id="userDao" class="com.abin.dao.impl.UserDaoImpl" init-method="init" destroy-method="destroy"/>   <!-- 单例的 -->
  <bean id="userService" class="com.abin.service.impl.UserServiceImpl">
    <constructor-arg name="userDao" ref="userDao"></constructor-arg>	<!-- 通过有参构造器注入 -->
  </bean>
</beans>
```

```Java
public class UserServiceImpl implements UserService {
  private  UserDao userDao;
  public UserServiceImpl(UserDao userDao) {		// 添加有参构造器
    this.userDao = userDao;
  }
  public UserServiceImpl() {		// 默认无参构造器
  }
  @Override
  public void saveUser() {
    userDao.save();
  }
}
```



#### 3.4 注入集合等数据

现在如果你想传递多个值，如 Java Collection 类型 List、Set、Map 和 Properties，应该怎么做呢。为了处理这种情况，Spring 提供了四种类型的集合的配置元素，如下所示：

| 元素    | 描述                                                        |
| :------ | :---------------------------------------------------------- |
| <list>  | 它有助于连线，如注入一列值，允许重复。                      |
| <set>   | 它有助于连线一组值，但不能重复。                            |
| <map>   | 它可以用来注入名称-值对的集合，其中名称和值可以是任何类型。 |
| <props> | 它可以用来注入名称-值对的集合，其中名称和值都是字符串类型。 |

你可以使用`<list>`或`<set>`来连接任何 `java.util.Collection` 的实现或数组。

你会遇到两种情况（a）传递集合中直接的值（b）传递一个 bean 的引用作为集合的元素。

##### 注入集合案例

这里是 **JavaCollection.java** 文件的内容：

```Java
package com.tutorialspoint;
import java.util.*;
public class JavaCollection {
   List addressList;
   Set  addressSet;
   Map  addressMap;
   Properties addressProp;
   // a setter method to set List
   public void setAddressList(List addressList) {
      this.addressList = addressList;
   }
   // prints and returns all the elements of the list.
   public List getAddressList() {
      System.out.println("List Elements :"  + addressList);
      return addressList;
   }
   // a setter method to set Set
   public void setAddressSet(Set addressSet) {
      this.addressSet = addressSet;
   }
   // prints and returns all the elements of the Set.
   public Set getAddressSet() {
      System.out.println("Set Elements :"  + addressSet);
      return addressSet;
   }
   // a setter method to set Map
   public void setAddressMap(Map addressMap) {
      this.addressMap = addressMap;
   }  
   // prints and returns all the elements of the Map.
   public Map getAddressMap() {
      System.out.println("Map Elements :"  + addressMap);
      return addressMap;
   }
   // a setter method to set Property
   public void setAddressProp(Properties addressProp) {
      this.addressProp = addressProp;
   } 
   // prints and returns all the elements of the Property.
   public Properties getAddressProp() {
      System.out.println("Property Elements :"  + addressProp);
      return addressProp;
   }
}
```

下面是 **MainApp.java** 文件的内容：

```Java
package com.tutorialspoint;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
public class MainApp {
   public static void main(String[] args) {
      ApplicationContext context = 
             new ClassPathXmlApplicationContext("Beans.xml");
      JavaCollection jc=(JavaCollection)context.getBean("javaCollection");
      jc.getAddressList();
      jc.getAddressSet();
      jc.getAddressMap();
      jc.getAddressProp();
   }
}
```

下面是配置所有类型的集合的配置文件 **Beans.xml** 文件：

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
    http://www.springframework.org/schema/beans/spring-beans-3.0.xsd">
   <!-- Definition for javaCollection -->
   <bean id="javaCollection" class="com.tutorialspoint.JavaCollection">

      <!-- results in a setAddressList(java.util.List) call -->
      <property name="addressList">
         <list>
            <value>INDIA</value>
            <value>Pakistan</value>
            <value>USA</value>
            <value>USA</value>
         </list>
      </property>

      <!-- results in a setAddressSet(java.util.Set) call -->
      <property name="addressSet">
         <set>
            <value>INDIA</value>
            <value>Pakistan</value>
            <value>USA</value>
            <value>USA</value>
        </set>
      </property>

      <!-- results in a setAddressMap(java.util.Map) call -->
      <property name="addressMap">
         <map>
            <entry key="1" value="INDIA"/>
            <entry key="2" value="Pakistan"/>
            <entry key="3" value="USA"/>
            <entry key="4" value="USA"/>
         </map>
      </property>

      <!-- results in a setAddressProp(java.util.Properties) call -->
      <property name="addressProp">
         <props>
            <prop key="one">INDIA</prop>
            <prop key="two">Pakistan</prop>
            <prop key="three">USA</prop>
            <prop key="four">USA</prop>
         </props>
      </property>
       
   </bean>
</beans>
```

一旦你创建源代码和 bean 配置文件完成后，我们就可以运行该应用程序。你应该注意这里不需要配置文件。如果你的应用程序一切都正常，将输出以下信息：

```
List Elements :[INDIA, Pakistan, USA, USA]
Set Elements :[INDIA, Pakistan, USA]
Map Elements :{1=INDIA, 2=Pakistan, 3=USA, 4=USA}
Property Elements :{two=Pakistan, one=INDIA, three=USA, four=USA}
```

##### 注入 Bean 引用

下面的 Bean 定义将帮助你理解如何注入 bean 的引用作为集合的元素。甚至你可以将引用和值混合在一起，如下所示：

```xml
<?xml version="1.0" encoding="UTF-8"?>

<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
    http://www.springframework.org/schema/beans/spring-beans-3.0.xsd">

   <!-- Bean Definition to handle references and values -->
   <bean id="..." class="...">

      <!-- Passing bean reference  for java.util.List -->
      <property name="addressList">
         <list>
            <ref bean="address1"/>
            <ref bean="address2"/>
            <value>Pakistan</value>
         </list>
      </property>

      <!-- Passing bean reference  for java.util.Set -->
      <property name="addressSet">
         <set>
            <ref bean="address1"/>
            <ref bean="address2"/>
            <value>Pakistan</value>
         </set>
      </property>

      <!-- Passing bean reference  for java.util.Map -->
      <property name="addressMap">
         <map>
            <entry key="one" value="INDIA"/>
            <entry key ="two" value-ref="address1"/>
            <entry key ="three" value-ref="address2"/>
         </map>
      </property>

   </bean>
</beans>
```

为了使用上面的 `bean` 定义，你需要定义 `setter` 方法，它们应该也能够是用这种方式来处理引用。

##### 注入 null 和空字符串的值

如果你需要传递一个空字符串作为值，那么你可以传递它，如下所示：

```xml
<bean id="..." class="exampleBean">
   <property name="email" value=""/>
</bean>
```

前面的例子相当于 Java 代码：`exampleBean.setEmail("")`。

如果你需要传递一个 NULL 值，那么你可以传递它，如下所示：

```xml
<bean id="..." class="exampleBean">
   <property name="email"><null/></property>
</bean>
```

前面的例子相当于 Java 代码：`exampleBean.setEmail(null)`

## 4.获取bean的方式

```xml
  <bean id="userService" class="com.abin.service.impl.UserServiceImpl">
		<!--    <property name="userDao" ref="userDao"></property>-->
    <constructor-arg name="userDao" ref="userDao"></constructor-arg>
  </bean>
```

```Java
  public Object getBean(String name) throws BeansException {
    this.assertBeanFactoryActive();
    return this.getBeanFactory().getBean(name);
  }
// 根据id或者name获取Bean 
UserService userService = (UserService) applicationContext.getBean("userService");
```

```Java
  public <T> T getBean(Class<T> requiredType) throws BeansException {
    this.assertBeanFactoryActive();
    return this.getBeanFactory().getBean(requiredType);
  }
// 根据.class类型获取Bean
UserService userService = applicationContext.getBean(UserService.class);
```

常用的就是根据name或者是根据类型获取Bean.  细节: 

- **当参数的数据类型是字符串时，表示根据Bean的id从容器中获得Bean实例，返回是Object，需要强转。**
- **当参数的数据类型是Class类型时，表示根据类型从容器中匹配Bean实例，当容器中相同类型的Bean有多个时，**
  **则此方法会报错。**



## 5.spring注解开发

Spring是轻代码而重配置的框架, 配置比较繁重, 影响开发效率, 所以注解开发是一种趋势, 注解代替XML配置文件可以简化配置,提高开发效率!

Spring 从 2.5 版本开始提供了对注解技术的全面支持，我们可以使用注解来实现自动装配，简化 Spring 的 XML 配置。

Spring 通过注解实现自动装配的步骤如下：

1. 引入依赖
2. 开启组件扫描
3. 使用注解定义 Bean
4. 依赖注入

### 5.1 需要开启组件扫描

Spring 默认不使用注解装配 Bean，因此我们需要在 Spring 的 XML 配置中，通过 <context:component-scan> 元素开启 Spring Beans的自动扫描功能(后面也可以通过注解配置)。开启此功能后，Spring 会自动从扫描指定的包（base-package 属性设置）及其子包下的所有类，如果类上使用了 @Component 注解，就将该类装配到容器中。

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"      
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"      
	xmlns:context="http://www.springframework.org/schema/context"      
	xsi:schemaLocation="http://www.springframework.org/schema/beans    
	http://www.springframework.org/schema/beans/spring-beans-3.0.xsd   
    http://www.springframework.org/schema/context            
    http://www.springframework.org/schema/context/spring-context.xsd">   
    <!--开启组件扫描功能-->    
    <context:component-scan base-package="com.abin"></context:component-scan>
</beans>
```

> 注意：在使用 <context:component-scan> 元素开启自动扫描功能前，首先需要在 XML 配置的一级标签 <beans> 中添加 context 相关的约束。



### 5.2. 使用注解定义 Bean

Spring 提供了以下多个注解，这些注解可以直接标注在 Java 类上，将它们定义成 Spring Bean。

| 注解            | 说明                                                         |
| --------------- | ------------------------------------------------------------ |
| **@Component**  | **该注解用于描述 Spring 中的 Bean，它是一个泛化的概念，仅仅表示容器中的一个组件（Bean）**，并且可以作用在应用的任何层次，例如 Service 层、Dao 层等。  使用时只需将该注解标注在相应类上即可。 |
| **@Repository** | **该注解用于将数据访问层（Dao 层）**的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |
| **@Service**    | **该注解通常作用在业务层（Service 层）**，用于将业务层的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |
| **@Controller** | **该注解通常作用在控制层（如 Struts2 的 Action、SpringMVC 的 Controller）**，用于将控制层的类标识为 Spring 中的 Bean，其功能与 @Component 相同。 |



### 5.3. 注解方式实现依赖注入

我们可以通过以下注解将定义好 Bean 装配到其它的 Bean 中。用于注入引用类型的数据, 对应原来的ref

| 注解           | 说明                                                         |
| -------------- | ------------------------------------------------------------ |
| **@Autowired** | 可以应用到 Bean 的属性变量、setter 方法、非 setter 方法及构造函数等，==默认按照 Bean 的**类型**进行装配==。  @Autowired 注解默认按照 Bean 的类型进行装配，默认情况下它要求依赖对象必须存在，如果允许 null 值，可以设置它的 required 属性为 false。**如果我们想使用按照名称（byName）来装配，可以结合 @Qualifier 注解一起使用** |
| **@Resource**  | ==作用与 Autowired 相同，区别在于 @Autowired 默认按照 Bean 类型装配，而 @Resource 默认按照 Bean 的**名称**进行装配。==  @Resource 中有两个重要属性：name 和 type。 Spring 将 name 属性解析为 Bean 的实例名称，type 属性解析为 Bean 的实例类型。如果指定 name 属性，则按实例名称进行装配；如果指定 type 属性，则按 Bean 类型进行装配；如果都不指定，则先按 Bean 实例名称装配，如果不能匹配，则再按照 Bean 类型进行装配；如果都无法匹配，则抛出 NoSuchBeanDefinitionException 异常。 |
| **@Qualifier** | ==只能与 @Autowired 注解配合使用==，会将默认的按 Bean 类型装配修改为按 Bean 的实例名称装配，Bean 的实例名称由 @Qualifier 注解的参数指定。 |



### 5.4 其他标签

| 注解               | 说明                                                         |
| ------------------ | ------------------------------------------------------------ |
| **@Value**         | 注入普通属性                                                 |
| **@Scope**         | 标注Bean的作用范围, singleton 或者是prototype                |
| **@PostConstruct** | 使用在方法上, 标注**该方法是Bean的初始化方法**               |
| **@PreDestory**    | 使用在方法上, 标注**该方法是Bean的销毁方法**                 |
| **@Required**      | @Required 注解==应用于 bean 属性的 setter 方法==，**它表明受影响的 bean 属性在配置时必须放在 XML 配置文件中**，否则容器就会抛出一个 BeanInitializationException 异常。 |



### 5.5 Spring新注解

| 注解                | 说明                                                         |
| ------------------- | ------------------------------------------------------------ |
| **@Configuration**  | 用于指定当前类是一个==Spring配置类==, 当创建容器时会从该类上加载注解用于配置 |
| **@ComponentScan**  | 用于==指定Spring在初始化容器时要扫描的包==<br />作用和在Spring的xml配置文件中的<context:component-scan base-package="com.abin"/> 一样 |
| **@PropertySource** | 用于==加载 .properties 配置文件中的配置==                    |
| **@Import**         | 用于==导入其他配置类==                                       |
| **@Bean**           | 用于方法上, ==Spring会将当前方法的**返回值**存到Spring容器中== ( 适用于第三方,比如数据源配置, 因为无法直接修改第三方代码 ) |

