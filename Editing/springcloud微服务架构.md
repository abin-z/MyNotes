# spring cloud微服务架构体系

微服务架构区别于传统的单体软件架构，是一种为了适应当前互联网后台服务的「**三高需求：高并发、高性能、高可用**」而产生的的软件架构。是一种经过良好架构的设计分布式架构方案



## **1.传统的单体式应用程序**

与微服务相对的另一个概念是传统的**单体式应用程序**( Monolithic application )，单体式应用内部包含了所有需要的服务。而且各个服务功能模块有很强的耦合性，也就是相互依赖彼此，很难拆分和扩容。

### 单体应用程序的优点

- 开发简洁，功能都在单个程序内部，便于软件设计和开发规划。
- 容易部署，程序单一不存在分布式集群的复杂部署环境，降低了部署难度。
- 容易测试，没有各种复杂的服务调用关系，都是内部调用方便测试。



### **单体应用程序的缺点**

单体程序的缺点一开始不是特别明显，项目刚开始需求少，业务逻辑简单，写代码一时爽，一直爽。噩梦从业务迭代更新，系统日益庞大开始，前期的爽没有了，取而代之的是软件维护和迭代更新的无尽痛苦。



![img](https://pic1.zhimg.com/80/v2-28abdbf63886720b624e7d72f9bdb418_720w.jpg)



由于单体式应用程序就像一个大型容器一样，里面放置了许多服务，且他们都是密不可分的，这导致应用程序在扩展时必须以「应用程序」为单位。

当里面有个业务模块负载过高时，并不能够单独扩展该服务，必须扩展整个应用程序（就是这么霸道），这可能导致额外的资源浪费。

此外，单体式应用程序由于服务之间的紧密度、相依性过高，这将导致测试、升级有所困难，且开发曲线有可能会在后期大幅度地上升，令开发不易。相较之下「微服务架构」能够解决这个问题。



## **微服务与SOA区别**

**面向服务的体系结构** SOA (Service-Oriented Architecture) 听起来和微服务很像，但 SOA 早期均使用了总线模式，这种总线模式是与某种技术栈强绑定的，比如：J2EE。这导致很多企业的遗留系统很难对接，切换时间太长，成本太高，新系统稳定性的收敛也需要一些时间，最终 SOA 看起来很美，但却成为了企业级奢侈品，中小公司都望而生畏。

此外，实施SOA时会遇到很多问题，比如通信协议（例如SOAP)的选择、第三方中间件如何选择、服务粒度如何确定等，目前也存在一些关于如何划分系统的指导性原则，但其中有很多都是错误的。SOA并没有告诉你如何划分单体应用成微服务，所以在实施SOA时会遇到很多问题。

这些问题再微服务框架中得到很好的解决，你可以认为微服务架构是SOA的一种特定方法。

## **微服务架构**

合久必分，鉴于「单体应用程序」有上述的缺点，单个应用程序被划分成各种小的、互相连接的微服务，一个微服务完成一个比较单一的功能，相互之间保持独立和解耦合，这就是微服务架构。

### **微服务优点**

相对于单体服务，微服务有很多优点，这里列举几个主要的好处

#### 技术异构性

不同服务内部的开发技术可以不一致，你可以用java来开发helloworld服务A，用golang来开发helloworld服务B，大家再也不用为哪种语言是世界上最好的语言而争论不休。

![img](https://pic2.zhimg.com/v2-7562b0be8f63c7823e09d7a295d9cf99_r.jpg)



为不同的服务选择最适合该服务的技术，系统中不同部分也可以使用不同的存储技术，比如A服务可以选择redis存储，B服务你可以选择用MySQL存储，这都是允许的，你的服务你做主。



#### 隔离性

一个服务不可用不会导致另一个服务也瘫痪，因为各个服务是相互独立和自治的系统。这在单体应用程序中是做不到的，单体应用程序中某个模块瘫痪，必将导致整个系统不可用，当然，单体程序也可以在不同机器上部署同样的程序来实现备份，不过，同样存在上面说的资源浪费问题。



#### 可扩展性

庞大的单体服务如果出现性能瓶颈只能对软件整体进行扩展，可能真正影响性能的只是其中一个很小的模块，我们也不得不付出升级整个应用的代价。这在微服务架构中得到了改善，你可以只对那些影响性能的服务做扩展升级，这样对症下药的效果是很好的。



#### 简化部署

如果你的服务是一个超大的单体服务，有几百万行代码，即使修改了几行代码也要重新编译整个应用，这显然是非常繁琐的，而且软件变更带来的不确定性非常高，软件部署的影响也非常大。在微服务架构中，各个服务的部署是独立的，如果真出了问题也只是影响单个服务，可以快速回滚版本解决。



#### 易优化

微服务架构中单个服务的代码量不会很大，这样当你需要重构或者优化这部分服务的时候，就会容易很多，毕竟，代码量越少意味着代码改动带来的影响越可控。



### **微服务缺点**

我们上面一直在强调微服务的好处，但是，微服务架构不是万能的，并不能解决所有问题，其实这也是微服务把单体应用拆分成很多小的分布式服务导致的，所谓人多手杂，服务多起来管理的不好各种问题就来了。

为了解决微服务的缺点，前辈们提出了下面这些概念。

#### 服务注册与发现

微服务之间相互调用完成整体业务功能，如何在众多微服务中找到正确的目标服务地址，这就是所谓「服务发现」功能。

常用的做法是服务提供方启动的时候把自己的地址上报给「服务注册中心」，这就是「服务注册」。服务调用方「订阅」服务变更「通知」，动态的接收服务注册中心推送的服务地址列表，以后想找哪个服务直接发给他就可以。



![img](https://pic2.zhimg.com/v2-3578297e7768e6c99d1fa1f33ebde659_r.jpg)



#### 服务监控

单体程序的监控运维还好说，大型微服务架构的服务运维是一大挑战。服务运维人员需要实时的掌握服务运行中的各种状态，最好有个控制面板能看到服务的内存使用率、调用次数、健康状况等信息。

这就需要我们有一套完备的服务监控体系，包括拓扑关系、监控（Metrics）、日志监控（Logging）、调用追踪（Trace）、告警通知、健康检查等，防患于未然。

#### 服务容错

任何服务都不能保证100%不出问题，生产环境复杂多变，服务运行过程中不可避免的发生各种故障（宕机、过载等等），工程师能够做的是在故障发生时尽可能降低影响范围、尽快恢复正常服务。

程序员为此避免被祭天，需要引入「熔断、隔离、限流和降级、超时机制」等「服务容错」机制来保证服务持续可用性。

#### 服务安全

有些服务的敏感数据存在安全问题，「服务安全」就是对敏感服务采用安全鉴权机制，对服务的访问需要进行相应的身份验证和授权，防止数据泄露的风险，安全是一个长久的话题，在微服务中也有很多工作要做。

#### **服务治理**

说到「治理」一般都是有问题才需要治理，我们平常说环境治理、污染治理一个意思，微服务架构中的微服务越来越多，上面说的那些问题就更加显现，为了解决上面微服务架构缺陷「服务治理」就出现了。



# 微服务架构

![image-20211124100326723](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241003905.png)

![image-20211124100506417](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241005558.png)

### 所用的技术栈:

![image-20211124100747664](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241007803.png)

## 微服务结构特征:

* ==单一职责==: 微服务拆分粒度很小,每个业务都对应唯一的业务能力,做到单一职责,避免重复业务开发
* ==面向服务==: 微服务对外暴露业务接口
* ==自治==: 团队独立. 技术独立. 数据独立. 部署独立
* ==隔离性强==: 服务调用做好隔离. 容错. 降级. 避免出现级联的问题

![image-20211124105123919](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241051036.png)

#### 微服务架构的实现

国内最知名的就是Spring Cloud和阿里巴巴的Dubbo

**微服务技术的对比**



![image-20211124142710201](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241427386.png)

**不同企业采用不同的技术组合**

![image-20211124142810317](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241428414.png)

SpringCloudAlibaba是SpringCloud的一部分.

SpringCloud集成了各种微服务功能组件,并基于SpringBoot实现了这些组件的自动装配, 从而提供了良好的开箱即用体验

![image-20211124144128032](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241441167.png)



##### 服务拆分注意事项

* 不同微服务, 不要重复开发相同的业务, 满足单一职责
* 微服务数据独立,不要直接访问其他微服务的数据库
* 微服务可以将自己的业务暴露为接口,供其他微服务调用



#### 服务远程调用

**提供者与消费者**

- 服务提供者: 一次业务中,被其他微服务调用的服务. (提供接口给其他微服务)

- 服务消费者: 一次业务中, 调用其他微服务的服务. (调用其他微服务提供的接口)
  * 注意: 提供者和消费者是相对的,并不是绝对的,一个服务既可以是提供者又可以是消费者
- 注册中心: 根据服务名称,存储对应的ip:port以及其他信息, 常用的注册中心有Eureka和nacos

##### 微服务的调用方式

* 基于RestTemplate发起的http请求实现远程调用
* http请求做远程调用是与语言无关的调用,只要知道对方的ip, 端口, 接口路径, 请求参数即可.

 

## 注册中心

**什么是注册中心**?

注册中心可以说是微服务架构中的”通讯录“，它记录了服务和服务地址的映射关系。在分布式架构中，服务会注册到这里，当服务需要调用其它服务时，就到这里找到服务的地址，进行调用。



**为什么需要注册中心**?

1. 需要手动的维护所有的服务访问ip地址列表。
2. 单个服务实现负载均衡需要自己搭建，例如使用nginx负载均衡策略，或者基于容器化多实例部署单个服务，在实例之间做负载均衡。



注册中心示意图:

![image-20211124152232082](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241522153.png)

**服务注册和服务发现:**

服务注册: 将提供某个服务的模块信息(通常是这个服务的ip和端口)注册到1个公共的组件(注册中心)上去

服务发现: 新注册的这个服务模块能够及时的被其他调用者发现。不管是服务新增和服务删减都能实现自动发现。



## Eureka注册中心

https://www.bilibili.com/video/BV1LQ4y127n4?p=10&spm_id_from=pageDriver

主要有如下角色:

**Eureka Server**，主要包含注册中心

**Eureka Client**，主要包括服务消费者和服务提供者 

![image-20211124152721270](https://gitee.com/abin_z/pic_bed/raw/master/img/202111241527394.png)

**1. 消费者该如何获取服务提供者具体信息**？

​	◆服务提供者启动时向eureka注册自己的信息, eureka保存这些信息

​	◆消费者根据服务名称向eureka拉取提供者信息



**2. 如果有多个服务提供者**，**消费者该如何选择**？

​	◆服务消费者利用负载均衡算法，从服务列表中挑选一个



**3. 消费者如何感知服务提供者健康状态**？

​	◆服务提供者会每隔30秒向EurekaServer发送心跳请求，报告健康状态eureka会更新记录服务列表信息，心跳不正常会被剔除

​	◆消费者就可以拉取到最新的信息



在Eureka架构中，微服务角色有两类：
==**1. EurekaServer**==：服务端，注册中心

- 记录服务信息

- 心跳监控

==**2. EurekaClient**==：客户端

- **Provider**：服务提供者，例如案例中的user-service
  - 注册自己的信息到EurekaServer
  - 每隔30秒向EurekaServer发送心跳

- **consumer**：服务消费者，例如案例中的order-service
* 根据服务名称从EurekaServer拉取服务列表
  
* 基于服务列表做负载均衡，选中一个微服务后发起远程调用



#### 使用Eureka的步骤

说明: Eureka本身是一个服务, 需要启动一个对应的EurekaServer的服务

**1. 搭建EurekaServer** 

- 引入eureka-server依赖 

* 在启动类上添加==@EnableEurekaServer==注解 

* 在application.yml中配置eureka地址

 **2. 服务注册**

* 引入eureka-client依赖
* 在application.yml中配置eureka地址

**3. 服务发现**

* 引入eureka-client依赖
* 在application.yml中配置eureka地址
* 给RestTemplate添加==@LoadBalanced==注解, 用来实现负载均衡
* 用服务提供者的服务名称远程调用



一. **搭建Eureka服务端(EurekaServer)的的实际操作步骤**:

1. 创建项目, 在pom.xml文件中引入spring-cloud-starter-netflix-eureka-server的依赖

   ```xml
   <dependency>
       <groupId>org.springframework.cloud</groupId>
       <artifactId>spring-cloud-starter-netflix-eureka-server</artifactId>
       <version>3.0.0</version>
   </dependency>
   ```

2. 编写启动类, 添加 ==@EnableEurekaServer==注解

3. 添加application.yml文件, 编写配置如下:

   ```yml
   #设置Eureka服务端口
   server:
     port: 10086
   
   #配置Eureka服务的名称
   spring:
     application:
       name: eurekaserver
   #配置Eureka的地址信息
   eureka:
     client:
       service-url:
         defaultZone: http://127.0.0.1:10086/eureka/
   ```

二. **服务注册**

将user-service服务注册到EurekaServer步骤如下：

1. 在user-service项目引入spring-cloud-starter-netflix-eureka-client的依赖

   ```xml
   <dependency>
       <groupId>org.springframework.cloud</groupId>
       <artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
   </dependency>
   ```

2. 在application.yml文件中,编写下面的配置:

   ```yml
   #配置Eureka服务的名称
   spring:
     application:
       name: userservice	#用户服务的名称
   #配置Eureka的地址信息
   eureka:
     client:
       service-url:
         defaultZone: http://127.0.0.1:10086/eureka/
   ```

   需要注册多个服务的时候进行多次配置, 一个服务要搭建集群的时候, 需要修改相应的端口号

三. **服务发现**

服务拉取是基于服务名称获取服务列表，然后在对服务列表做负载均衡

1. 修改OrderService的代码,修改访问的url路径, 用服务名代替ip, 端口:

   ```Java
   String url = "http://userservice/user/" + order.getUserId();
   ```

2. 在order-service项目的启动类OrderApplication(配置类也可以)中的RestTemplate添加负载均衡注解:

   ```Java
   @Bean
   @LoadBalanced
   public RestTemplate restTemplate(){
       return new RestTemplate();
   }
   ```

   



## Ribbon负载均衡

Ribbon的负载均衡策略、原理和扩展: https://www.jianshu.com/p/79b9cf0d0519

**什么是负载均衡**?

Load Balance负载均衡是用于解决一台机器(一个进程)无法解决所有请求而产生的一种算法。像nginx可以使用负载均衡分配流量，ribbon为客户端提供负载均衡

Eureka的底层使用的是Ribbon组件来实现负载均衡

@LoadBalanced作用是实现负载均衡



**负载均衡流程**:

![image-20211124224717979](https://gitee.com/abin_z/pic_bed/raw/master/img/202111242247133.png)



Ribbon的负载均衡规则是一个叫做**IRule**的接口来定义的,每一个实现类都是一种规则

![image-20211124225038650](https://gitee.com/abin_z/pic_bed/raw/master/img/202111242250754.png)

负载均衡有好几种实现策略，常见的有：

- 随机 (Random)
- 轮询 (RoundRobin)
- 一致性哈希 (ConsistentHash)
- 哈希 (Hash)
- 加权（Weighted）

### Ribbon内置的负载均衡规则：

|         规则名称          |                             特点                             |
| :-----------------------: | :----------------------------------------------------------: |
| AvailabilityFilteringRule | 过滤掉一直连接失败的被标记为circuit tripped的后端Server，并 过滤掉那些高并发的后端Server或者使用一个AvailabilityPredicate 来包含过滤server的逻辑，其实就是检查status里记录的各个server 的运行状态 |
|     BestAvailableRule     | 选择一个最小的并发请求的server，逐个考察server， 如果Server被tripped了，则跳过 |
|        RandomRule         |                      随机选择一个Server                      |
| ResponseTimeWeightedRule  |            已废弃，作用同WeightedResponseTimeRule            |
| WeightedResponseTimeRule  | 根据响应时间加权，响应时间越长，权重越小，被选中的可能性越低 |
|         RetryRule         | 对选定的负载均衡策略加上重试机制，在一个配置时间段内当 选择Server不成功，则一直尝试使用subRule的方式选择一个 可用的Server |
|      RoundRobinRule       |        轮询选择，轮询index，选择index对应位置的Server        |
|   ==ZoneAvoidanceRule==   | ==默认的负载均衡策略==，即复合判断Server所在区域的性能和Server的可用性 选择Server，在没有区域的环境下，类似于轮询(RoundRobinRule) |

通过定义IRule实现可以修改Ribbon负载均衡规则,主要有两种方式:

1. 代码的方式: 在配置类中定义一个新的IRule

   ```Java
   @Bean
   public IRule randomRule(){
       return new RandomRule();
   }
   //需要写在配置类里面,作用范围是全部服务
   ```

2. 写在配置文件中: 在application.yml文件中,添加新的配置信息

   ```yml
   userservice:
     ribbon:
       NFLoadBaLancerRULeCLassName: com.netflix.loadbalancer.RandomRule #随机负载均衡规则
       #改配置文件只对当前服务起作用
   ```

* Ribbon默认是采用懒加载，即第一次访问时才会去创建LoadBalanceClient，请求时间会很长。
  而饥饿加载则会在项目启动时创建，降低第一次访问的耗时，通过下面配置开启饥饿加载

  ```yml
  ribbon:
    eager-load:
      enabled: true 	#开启饥饿加载 饿汉式
      clients: 
        - servicename #指定对servicename这个服务进行饥饿加载
  ```

**1. Ribbon负载均衡规则**

- ==规则接口是IRule==

- 默认实现是ZoneAvoidanceRule，根据zone

- 选择服务列表，然后轮询

**2. 负载均衡自定义方式**

- 代码方式：配置灵活，但修改时需要重新打包发布

* 配置方式：直观，方便，无需重新打包发布，但是无法做全局配置

**3. 饥饿加载**

- 开启饥饿加载

- 指定饥饿加载的微服务名称



## Nacos注册中心

Nacos是阿里巴巴的产品, 现在是SpringCloud中的一个组件, 相较于Eureka有着更加丰富的功能,在国内受欢迎程度较高

Nacos版本需要与SpringCloud版本相对应

版本对应关系:    https://github.com/alibaba/spring-cloud-alibaba/wiki/%E7%89%88%E6%9C%AC%E8%AF%B4%E6%98%8E



nacos的     https://cloud.tencent.com/developer/article/1882004?from=article.detail.1805561

### nacos的服务发现与注册

Nacos的Windows安装:

Nacos的下载地址: https://github.com/alibaba/nacos    下载压缩包后直接解压后就可以运行(需要jre)

目录结构:

![image-20211125103712366](https://gitee.com/abin_z/pic_bed/raw/master/img/202111251037422.png)

配置文件路径为: nacos/conf/application.properties

![image-20211125103934333](https://gitee.com/abin_z/pic_bed/raw/master/img/202111251039374.png)



启动Nacos服务: `startup.cmd -m standalone`     standalone 表示单机启动, Windows下

![image-20211125104321912](https://gitee.com/abin_z/pic_bed/raw/master/img/202111251043968.png)

进入nacos控制台: http://192.168.0.198:8848/nacos/index.html      用户名和密码都是 nacos

![image-20211125104600341](https://gitee.com/abin_z/pic_bed/raw/master/img/202111251046406.png)

##### **基本操作步骤:**

1. Nacos服务搭建
   - 下载nacos安装包并解压
   - 在bin目录下运行指令: startup.cmd -m standalone
2. Nacos服务注册和服务发现
   - 引入nacos.discovery依赖
   - 配置nacos地址: spring.cloud.nacos.server-addr



**服务注册到Nacos:**

1. 在父工程中添加spring-cloud-alibaba的依赖管理

   ```xml
   <dependency>
       <groupId>com.alibaba.cloud</groupId>
       <artifactId>spring-cloud-alibaba-dependencies</artifactId>
       <version>2.2.5.RELEASE</version>
       <type>pom</type>
       <scope>import</scope>
   </dependency>
   ```

2. 注释掉oder-service和user-service中原有的Eureka的依赖.

3. 添加nacas的客户端依赖:

   ```xml
   <dependency>
       <groupId>com.alibaba.cloud</groupId>
       <artifactId>spring-cloud-starter-alibaba-nacos-discovery</artifactId>
   </dependency>
   ```

4. 然后修改application.yml文件,将原来的Eureka的地址信息注释掉,添加nacos的服务地址

   ```yml
   spring:
     cloud:
       nacos:
         server-addr: localhost:8848		#nacos的服务地址
   ```

### Nacos服务的分级存储模型

![image-20211125113609157](https://gitee.com/abin_z/pic_bed/raw/master/img/202111251136289.png)



## Http客户端Feign





## 消息队列MQ(Message Queue)

**MQ用于服务间的异步通信**



**同步通讯**: 发送方发出数据后，等接收方发回响应以后才发下一个数据包的通讯方式。(能够立即得到回复)

**异步通讯**: 发送方发出数据后，不等接收方发回响应，接着发送下个数据包的通讯方式。(不一定立即得到回复)

==同步是阻塞模式，异步是非阻塞模式。==



**生活中的同步和异步通讯:** 

同步通讯类似于打视频电话, 只能处理一个, 但是时效性比较高, 能够立即得到回复

异步通讯类似于发聊天消息, 你可以同时和多个人进行聊天, 但是时效性比较差, 不一定能立即得到回复

---

同步通信，就是送快递的面对面给交你，交互完成即完在，但双方都需要在同一时间内反应，否则会造成另一方阻塞等待。

异步通信，就是送快递的放在门卫或快递箱，你自己去取，中间不是同步完成的。



### 同步通讯方案

#### 同步通讯的优点

- 时效性比较强,可以立即得到结果

#### 同步调用的缺点

微服务间的Feign的调用就是属于同步方式,存在诸多的问题. 

- **代码的耦合度高**, 添加新业务时需要修改以前写好的代码.
- **性能的下降, 延迟高**, 同步通讯属于阻塞式的, 必须等待所有服务提供者响应完成后才能返回, 时间之和.
- **资源浪费**, 调用链中每个服务在等待响应过程中,不释放请求资源,在高并发场景下浪费资源.
- **存在级联失败问题**,  如果服务提供者出现问题,所有调用方都会跟着出问题, 迅速导致整个微服务故障. 

![image-20211130112706396](https://gitee.com/abin_z/pic_bed/raw/master/img/202111301127536.png)

### 异步通讯方案

**异步调用常见的实现是==事件驱动模式==** : 事件来了后由Broker去通知相应的服务执行

![image-20211130113101495](https://gitee.com/abin_z/pic_bed/raw/master/img/202111301131611.png)

#### 异步通讯事件驱动优点:

-  **服务间解耦合**: 使用了Broker(中间代理), 添加或删除服务只需要订阅事件就行了.
- **性能提升,吞吐量提升**: 异步调用是非阻塞的, 延迟大幅度减少
- **故障隔离**: 不用在担心级联失败的问题, 故障隔离, 服务间没有强依赖关系
- **流量消峰**: Broker可以对高并发进行缓存, 按照服务的处理速率进行分布事件 

![image-20211130113928145](https://gitee.com/abin_z/pic_bed/raw/master/img/202111301139275.png)

#### 异步通讯的缺点:

- 依赖于Broker的可靠性,安全性,吞吐能力
- 架构更加复杂, 业务没有明显的流程线, 不好追踪管理



### MQ 消息队列

MQ(Message Queue), 消息队列, 字面意思就是存放消息的队列, 也就是事件驱动架构中的Broker

![image-20211130170401043](https://gitee.com/abin_z/pic_bed/raw/master/img/202111301704170.png)





## 初识elasticsearch

什么是elastic
